#include "LowLevelFunctions.h"

HANDLE file;
uchar bitmap[8192];

//test
////
//int main() // test main
//{
//	InitializeFileSystem();
//	//FormatFileSystem();
//	//FileCreate("filetestj345rf", FILETYPE_FILE, ROOT_DIR);
//	char data[97] = "abcsdffewrgfhyjyfijfaijeriuhfaiuhfiajvioaernvileunriuvn3498hge eu h rhaeh ahf afh jdlfhi ehrih r";
//	WriteToFile(ROOT_DIR, data, 97);
//	/*char buff[11];
//	uint count = 0;
//	ReadFromFile(ROOT_DIR, buff, &count);*/
//	///*for (int i = 0; i < 25; i++)
//	//{
//	//	FileCreate("testfile2i", FILETYPE_FILE, ROOT_DIR);		
//	//}*/
//	//FileDelete(ROOT_DIR);
//	//FreeCluster(10);
//	CloseFileSystem();
//
//	return 0;
//}

void InitializeFileSystem()
{
	file = CreateFile("FileSystem", FILE_READ_DATA | FILE_WRITE_DATA,
		FILE_SHARE_READ, NULL, OPEN_ALWAYS,	FILE_ATTRIBUTE_NORMAL, NULL);
	if (file ==	INVALID_HANDLE_VALUE)
	{
		file = 0;
		return;
	}
	ReadBitmap();	
}

void FormatFileSystem()
{
	unsigned long lp = 0;
	SetFilePointer(file, 0, (long*)&lp, FILE_BEGIN); 
	uchar data[8192];
	ZeroMemory(data, 8192);
	data[0] = 0xFF;
	data[1] = 0x80;
	WriteFile(file, data, 8192, &lp, null);
	data[0]= data[1] = 0;
	for (int i = 0; i < 8191; i++)
	{
		WriteFile(file, data, 8192, &lp, null);
	}
	SetEndOfFile(file);
}

void CloseFileSystem()
{
	CloseHandle(file);
}


//
//===========BITMAP================
//
void ReadBitmap()
{
	ulong pos = SetFilePointer(file, 0, NULL, FILE_CURRENT);
	SetFilePointer(file, 0, NULL, FILE_BEGIN);
	DWORD temp = 0;
	ReadFile(file, bitmap, 8192, &temp, NULL);
	SetFilePointer(file, pos, NULL, FILE_BEGIN);
}

ushort FindEmptyCluster()
{
	USHORT i = 0;
	UCHAR j = 0;
	while (bitmap[i] == 0xFF) i++;
	UCHAR mask = 0x80;
	while (bitmap[i] & mask) 
	{
		mask >>= 1;
		j++;
	}
	return i * 8 + j;
}

void TakeCluster(ushort offset)
{
	ushort i = offset / 8;
	uchar j = offset % 8;
	uchar mask = 0x80;
	while (j--) mask >>= 1;
	bitmap[i] |= mask;
	WriteBitmap();
}

void FreeCluster(ushort offset)
{
	ushort i = offset / 8;
	uchar j = offset % 8;
	uchar mask = 0x80;
	while (j--) mask >>= 1;
	bitmap[i] &= mask ^ 0xFF;
	WriteBitmap();
}

void WriteBitmap()
{
	ulong pos = SetFilePointer(file, 0, NULL, FILE_CURRENT);
	SetFilePointer(file, 0, NULL, FILE_BEGIN);
	DWORD temp = 0;
	WriteFile(file, bitmap, 1024 * 8, &temp, NULL);
	SetFilePointer(file, pos, NULL, FILE_BEGIN);
}

uint FileCreate(char name[MAX_FILENAME_LENGTH], uchar type, uint parentId)
{
	uint count = 0;
	FileInfo ** infos = GetFileList(parentId, &count);
	bool found = false;
	for (uint i = 0; i < count; i++)
	{
		if (!strcmp(name, infos[i]->Name))
		{
			found = true;
		}
		delete infos[i];
	}
	if (infos)
		delete[] infos;
	if (found)
		return 0;
	FileInfo * fileinfo = new FileInfo;
	fileinfo->Size = 0;
	fileinfo->Parent = parentId;
	fileinfo->Type = type;
	fileinfo->Cluster = 0;
	memmove(fileinfo->Name, name, MAX_FILENAME_LENGTH);
	fileinfo->Id = FindEmptyInfoId(parentId);
	WriteInfo(fileinfo);
	return fileinfo->Id;
}

uint FindEmptyInfoId(uint dir)
{
	ushort offset = ((dir == ROOT_DIR )
		? ROOT_DIR / 1024
		: GetInfoById(dir)->Cluster);
	if (!offset)
	{
		offset = FindEmptyCluster();
		TakeCluster(offset);
		FileInfo * info = GetInfoById(dir);
		info->Cluster = offset;
		WriteInfo(info);
		delete info;
	}
	Cluster * cluster = ReadCluster(offset);
	FileInfo * info = new FileInfo;
	ulong lp = 0;
	int i = 0;
	bool found = false;
	ulong pos = SetFilePointer(file, 0, null, FILE_CURRENT);
	SetFilePointer(file, offset * 1024, null, FILE_BEGIN);
	while (!found)
	{
		for (; i < MAX_CLUSTER_DATA_SIZE - sizeof(FileInfo) && !found; i += sizeof(FileInfo))
		{
			ReadFile(file, info, sizeof(FileInfo), &lp, null);
			if (info->Type == FILETYPE_EMPTY)
			{
				found = true;				
			}
		}
		if (!found)
		{
			cluster = ReadNextCluster(cluster);		
			SetFilePointer(file, cluster->Offset * 1024, null, FILE_BEGIN);
			i = 0;
		}
	}
	SetFilePointer(file, pos, null, FILE_BEGIN);
	return cluster->Offset * 1024 + i - sizeof(FileInfo);
}

Cluster * ReadCluster(ushort offset)
{
	ulong pos = SetFilePointer(file, 0, null, FILE_CURRENT);
	SetFilePointer(file, offset * 1024, null, FILE_BEGIN);
	ulong lp;
	Cluster * cluster = new Cluster;
	ReadFile(file, cluster, sizeof(Cluster), &lp, null);
	SetFilePointer(file, pos, null, FILE_BEGIN);
	if (!cluster->Offset)
	{
		cluster->Offset = offset;
	}
	return cluster;
}

void WriteCluster(Cluster * cluster)
{
	ulong pos = SetFilePointer(file, 0, null, FILE_CURRENT);
	SetFilePointer(file, cluster->Offset * 1024, null, FILE_BEGIN);
	ulong lp;
	WriteFile(file, cluster, sizeof(Cluster), &lp, null);
	SetFilePointer(file, pos, null, FILE_BEGIN);
}

Cluster * ReadNextCluster(Cluster * cluster)
{
	ushort next = cluster->Next;
	if (!next)
	{
		ushort prev = cluster->Offset;
		next = FindEmptyCluster();
		TakeCluster(next);
		cluster->Next = next;
		WriteCluster(cluster);
		delete cluster;
		cluster = new Cluster;
		ZeroMemory(cluster, sizeof(Cluster));
		cluster->Offset = next;	
		cluster->Prev = prev;
		return cluster;
	}
	delete cluster;
	return ReadCluster(next);
}

void WriteInfo(FileInfo * fileinfo)
{
	ulong pos = SetFilePointer(file, 0, null, FILE_CURRENT);
	SetFilePointer(file, fileinfo->Id, null, FILE_BEGIN);
	ulong lp = 0;
	Cluster * cluster = ReadCluster(fileinfo->Id / 1024);
	cluster->Size += sizeof(FileInfo);
	WriteCluster(cluster);
	WriteFile(file, fileinfo, sizeof(FileInfo), &lp, null);
	SetFilePointer(file, pos, null, FILE_BEGIN);
}

bool FileDelete(uint id)
{
	FileInfo * info = GetInfoById(id);
	if (info->Type == FILETYPE_DIR)
	{
		uint count = 0;
		FileInfo ** infos = GetFileList(info->Id, &count);
		for (uint i = 0; i < count; i++)
		{
			FileDelete(infos[i]->Id);
			delete infos[i];
		}
		if (infos)
			delete[] infos;
	}
	ushort offset = info->Cluster;
	Cluster * cluster = ReadCluster(id / 1024);
	cluster->Size -= sizeof(FileInfo);
	WriteCluster(cluster);
	if (!cluster->Size)
	{
		ushort prev = cluster->Prev;
		delete cluster;
		if (prev)
		{
			cluster = ReadCluster(prev);
			cluster->Next = 0;
			WriteCluster(cluster);
		}
	}
	if (info->Type == FILETYPE_FILE)
	{
		DeleteData(offset);
	}
	info->Type = FILETYPE_EMPTY;
	WriteInfo(info);
	return true;
}

void DeleteData(ushort offset)
{
	while (offset)
	{
		Cluster * cluster = ReadCluster(offset);
		cluster->Size = 0;
		offset = cluster->Next;
		cluster->Prev = 0;
		cluster->Next = 0;
		FreeCluster(cluster->Offset);
		WriteCluster(cluster);
		delete cluster;		
	}
}

void WriteToFile(uint id, char * data, uint size)
{
	FileInfo * fileinfo = GetInfoById(id);
	if (!fileinfo->Cluster)
	{
		fileinfo->Cluster = FindEmptyCluster();
		TakeCluster(fileinfo->Cluster);
	}
	fileinfo->Size = size;
	Cluster * cluster = ReadCluster(fileinfo->Cluster);
	uint writted = 0;
	WriteInfo(fileinfo);
	delete fileinfo;
	while(size > 0)
	{
		ushort towrite = size > MAX_CLUSTER_DATA_SIZE ? MAX_CLUSTER_DATA_SIZE : size;
		memmove(cluster->Data, data + writted, towrite);
		writted += towrite;
		cluster->Size = towrite;
		size -= towrite;
		if (size)
		{
			WriteCluster(cluster);
			cluster = ReadNextCluster(cluster);
		}
		else
		{
			if (cluster->Next)
			{
				DeleteData(cluster->Next);
				cluster->Next = 0;
			}
			WriteCluster(cluster);
		}
	}
}

void ReadFromFile(uint id, char * buffer, uint * size)
{
	FileInfo * info = GetInfoById(id);
	ushort offset = info->Cluster;
	*size = info->Size;
	delete info;
	Cluster * cluster = ReadCluster(offset);
	uint writed = 0;
	while (writed < (*size) )
	{
		memmove(buffer + writed, cluster->Data, cluster->Size);
		writed += cluster->Size;
		if (cluster->Next)
		{
			cluster = ReadNextCluster(cluster);
		}
	}
}

void FileCopy(uint fileId, uint dir)
{
	FileInfo * info = GetInfoById(fileId);
	uint id = FileCreate(info->Name, info->Type, dir);
	char * buffer = new char[info->Size];
	if (info->Type == FILETYPE_FILE)
	{
		FileInfo * newinfo = GetInfoById(id);
		ReadFromFile(info->Id, buffer, &newinfo->Size);
		WriteToFile(newinfo->Id, buffer, newinfo->Size);
		delete newinfo;
	}
	if (info->Type == FILETYPE_DIR)
	{
		uint count = 0;
		FileInfo ** infos = GetFileList(info->Id, &count);
		for (uint i = 0; i < count; i++)
		{
			FileCopy(infos[i]->Id, info->Id);
			delete infos[i];
		}
		if (infos)
			delete[] infos;
	}
}

void FileMove(uint fileId, uint dir)
{
	FileInfo * info = GetInfoById(fileId);
	uint id = FileCreate(info->Name, info->Type, dir);
	FileInfo * newinfo = GetInfoById(id);
	newinfo->Cluster = info->Cluster;
	newinfo->Size = info->Size;
	WriteInfo(newinfo);
	delete newinfo;
	if (info->Type == FILETYPE_DIR)
	{
		uint count = 0;
		FileInfo ** infos = GetFileList(info->Id, &count);
		for (uint i = 0; i < count; i++)
		{
			FileMove(infos[i]->Id, info->Id);
			delete infos[i];
		}
		if (infos)
			delete[] infos;
	}
}

FileInfo * GetInfoById(uint id)
{	
	FileInfo * info = new FileInfo;
	ulong lp = 0;
	ulong pos = SetFilePointer(file, 0, null, FILE_CURRENT);
	SetFilePointer(file, id, null, FILE_BEGIN);
	ReadFile(file, info, sizeof(FileInfo), &lp, null);
	SetFilePointer(file, pos, null, FILE_BEGIN);
	return info;
}

FileInfo ** GetFileList(uint dir, uint * count)
{
	FileInfo * info = GetInfoById(dir);
	if (!info->Cluster)
	{
		*count = 0;
		return null;
	}
	vector<FileInfo *> infos;
	Cluster * cluster = ReadCluster(info->Cluster);
	delete info;
	while (true)
	{	
		ulong lp = 0;
		for (int i = 0; i < MAX_CLUSTER_DATA_SIZE - sizeof(FileInfo); i += sizeof(FileInfo))
		{
			ReadFile(file, info, sizeof(FileInfo), &lp, null);
			if (info->Type != FILETYPE_EMPTY)
			{
				infos.push_back(info);
			}
		}
		if (cluster->Next)
		{
			cluster = ReadNextCluster(cluster);
		}
		else
		{
			break;
		}
	}
	*count = infos.size();
	FileInfo ** result = new FileInfo*[infos.size()];
	for (int i = 0; i < infos.size(); i++)
	{
		result[i] = infos[i];
	}
	return result;
}

uint GetIdByName(char name[MAX_FILENAME_LENGTH], uint dir)
{
	uint count = 0;
	FileInfo ** infos = GetFileList(dir, &count);
	uint id = 0;
	uint i = 0;
	for (; i < count; i++)
	{
		if (!strcmp(name, infos[i]->Name))
		{
			id = infos[i]->Id;
			break;
		}
		delete infos[i];
	}
	for (; i < count; i++)
		delete infos[i];
	if (infos)
		delete[] infos;
	return id;
}
