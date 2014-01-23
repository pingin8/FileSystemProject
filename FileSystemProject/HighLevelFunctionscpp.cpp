#include "HighLevelFunctions.h"


void FileCreateHigh(vector<uint> *path_vector, char *FileName)
{
	FileCreate(FileName, FILETYPE_FILE, path_vector->back());
}

void DirCreateHigh(vector<uint> *path_vector, char *DirName)
{
	FileCreate(DirName, FILETYPE_DIR, path_vector->back());
}

void FileDeleteHigh(vector<uint> *path_vector, char *FileName)
{
	uint id = GetIdByName(FileName, path_vector->back());
	if (id)
	{
		FileDelete(id);
	}
}

void DirDeleteHigh(vector<uint> *path_vector, char *DirName)
{
	uint id = GetIdByName(DirName, path_vector->back());
	if (id)
	{
		FileDelete(id);
	}
}

void EnterDir(vector<uint> *path_vector, char *DirName)
{

}

void LeaveDir(vector<uint> *path_vector)
{

}

void ViewCurrentDirectory(vector<uint> *path_vector)
{

}
void About()
{

}
