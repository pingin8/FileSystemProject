#ifndef LOWLEVELFUNCTIONS_H
#define LOWLEVELFUNCTIONS_H

#include "Structures.h"
#include <Windows.h>
#include <vector>

using namespace std;

void InitializeFileSystem();
void FormatFileSystem();
void CloseFileSystem();

void ReadBitmap();
ushort FindEmptyCluster();
void TakeCluster(ushort offset);
void FreeCluster(ushort offset);
void WriteBitmap();
uint CalculateFreeSpace();

uint FindEmptyInfoId(uint dir);
void WriteInfo(FileInfo * fileinfo);
Cluster * ReadCluster(ushort offset);
void WriteCluster(Cluster * cluster);
Cluster * ReadNextCluster(Cluster * cluster);

uint FileCreate(char name[MAX_FILENAME_LENGTH], uchar type, uint parentId);
bool FileDelete(uint id);
void DeleteData(ushort offset);

void WriteToFile(uint id, char * data, uint size);
void ReadFromFile(uint id, char * buffer, uint * size);
void FileCopy(uint fileId, uint dir);
void FileMove(uint fileId, uint dir);

void FileCopyIn(char * path, uint dest_dir, uchar type);
void FileCopyOut(uint id, char * dest_path);

FileInfo * GetInfoById(uint id);
uint GetIdByName(char name[MAX_FILENAME_LENGTH], uint dir);

FileInfo ** GetFileList(uint dir, uint * count);



#endif LOWLEVELFUNCTIONS_H