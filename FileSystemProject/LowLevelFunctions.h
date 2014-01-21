#ifndef LOWLEVELFUNCTIONS_H
#define LOWLEVELFUNCTIONS_H

#include "Structures.h"
#include <Windows.h>

void InitializeFileSystem();
void FormatFileSystem();
void CloseFileSystem();

void ReadBitmap();
ushort FindEmptyCluster();
void TakeCluster(ushort offset);
void FreeCluster(ushort offset);
void WriteBitmap();
uint CalculateFreeSpace();

uint FileCreate(char name[MAX_FILENAME_LENGTH], uchar type, uint parentId);
bool FileDelete(uint id);
void WriteToFile(uint id, char * data, uint size);
void ReadFromFile(uint id, char * buffer);
void FileCopy(uint fileId, uint dir);
void FileMove(uint fileId, uint dir);

FileInfo * GetInfoById(uint id);
uint GetIdByName(char name[MAX_FILENAME_LENGTH], uint dir);






#endif LOWLEVELFUNCTIONS_H