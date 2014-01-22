#include "LowLevelFunctions.h"

HANDLE file;
uchar bitmap[8192];

//test

int main() // test main
{
	InitializeFileSystem();
	//FormatFileSystem();
	//FileCreate("testfile2i", FILETYPE_FILE, ROOT_DIR);
	
	//FreeCluster(10);
	CloseFileSystem();

	return 0;
}

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
	Cluster * cluster = ReadCluster(offset);
	FileInfo * info = new FileInfo;
	ulong lp = 0;
	int i = 0;
	bool found = false;
	ulong pos = SetFilePointer(file, 0, null, FILE_CURRENT);
	SetFilePointer(file, offset * 1024, null, FILE_BEGIN);
	while (!found)
	{
		for (; i < MAX_CLUSTER_DATA_SIZE && !found; i += sizeof(FileInfo))
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
		next = FindEmptyCluster();
		TakeCluster(next);
		cluster->Next = next;
		WriteCluster(cluster);
		delete cluster;
		cluster = new Cluster;
		ZeroMemory(cluster, sizeof(Cluster));
		cluster->Offset = next;	
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
	WriteFile(file, fileinfo, sizeof(FileInfo), &lp, null);
	SetFilePointer(file, pos, null, FILE_BEGIN);
}

bool FileDelete(uint id){return 0;}
void WriteToFile(uint id, char * data, uint size){}
void ReadFromFile(uint id, char * buffer){}
void FileCopy(uint fileId, uint dir){}
void FileMove(uint fileId, uint dir){}

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

uint GetIdByName(char name[MAX_FILENAME_LENGTH], uint dir)
{
	return 0;
}
