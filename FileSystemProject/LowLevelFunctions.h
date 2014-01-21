#ifndef LOWLEVELFUNCTIONS_H
#define LOWLEVELFUNCTIONS_H

#include "Structures.h"
#include <Windows.h>

HANDLE InitializeFileSystem();
void Format(HANDLE file);
void Close(HANDLE file);

void ReadBitmap();
ushort FindEmptyCluster();
void TakeCluster(ushort offset);
void FreeCluster(ushort offset);
void WriteBitmap();

uint FileCreate(char name[MAX_FILENAME_LENGTH], uchar type, uint parentId);
bool FileDelete(uint id);
void WriteToFile(uint id, char * data, uint size);
void ReadFromFile(uint id, char * buffer);

void FileCopy(uint fileId, uint dir);
void FileMove(uint fileId, uint dir);
FileInfo * GetInfoById(uint id);






#endif LOWLEVELFUNCTIONS_H