#include "LowLevelFunctions.h"

HANDLE file;
uchar bitmap[8192];

int main() // test main
{
	InitializeFileSystem();
	FormatFileSystem();
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
	WriteFile(file, data, 8192, &lp, null);
	data[0] = 0;
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

uint FileCreate(char name[MAX_FILENAME_LENGTH], uchar type, uint parentId){return 0;}
bool FileDelete(uint id){return 0;}
void WriteToFile(uint id, char * data, uint size){}
void ReadFromFile(uint id, char * buffer){}
void FileCopy(uint fileId, uint dir){}
void FileMove(uint fileId, uint dir){}

FileInfo * GetInfoById(uint id){return 0;}
uint GetIdByName(char name[MAX_FILENAME_LENGTH], uint dir){return 0;}
