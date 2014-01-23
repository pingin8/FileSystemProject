#include "HighLevelFunctions.h"
#include "LowLevelFunctions.h"
#include <iostream>
#include <iomanip>

using namespace std;

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
	uint dir_id = GetIdByName(DirName, *path_vector[path_vector->size]);
	path_vector->push_back(dir_id);
}

void LeaveDir(vector<uint> *path_vector)
{
	path_vector->pop_back();
}

void ViewCurrentDirectory(vector<uint> *path_vector)
{
	uint count = 0;
	FileInfo **content = GetFileList(*path_vector[path_vector->size], &count);

	for(int i=0; i<count; i++)
	{


		cout << setw(15) << *content[i]->Name;
		if(content[i]->Type == FILETYPE_DIR)
			cout << setw(3) << "DIR" << endl;
		else
			cout << endl;
	}


}
void About()
{
}
