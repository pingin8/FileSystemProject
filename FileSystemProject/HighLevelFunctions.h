#ifndef HIGHLEVELFUNCTIONS_H
#define HIGHLEVELFUNCTIONS_H

#include "LowLevelFunctions.h"
#include <vector>

using namespace std;

void FileCreateHigh(vector<uint> *path_vector, char *FileName);								//�������� �����+
void DirCreateHigh(vector<uint> *path_vector, char *DirName);									//�������� ����������+
void FileDeleteHigh(vector<uint> *path_vector,char *FileName);							//�������� �����+
void DirDeleteHigh(vector<uint> *path_vector, char *DirName);							//�������� ��������+
//void CopyFile(char *FileName, char *_DestDirName);			//����������� �����
//void MoveFile(char *FileName, char *_DestDirName);		//����������� �����+
void EnterDir(vector<uint> *path_vector,char *DirName);							//����� � ����������+
void LeaveDir(vector<uint> *path_vector);											//�������� ����������+
//void ReadFile(char *FileName);							//������ �����+
//void WriteFile(char *FileName);							//������ � ����+
//void Format(int FSSize, int KlasterSize);				//�������������� �����, ��������� ������� ������ � ������� ��������+
//void VIEWFILE();											//�������� ����� ����������� � �����-������
//void SYSINFO();											//�������� ��������� ����������+
void ViewCurrentDirectory(vector<uint> *path_vector);				//�������� ����������� ������� ����������+
void About();											//�������
//char* Path();												//���� � ������� ���������� � ������
//void SetFilePassword(char *FileName, char *Password);	//���������� ������ �� ����
//void SetDirPassword(char DirName, char *Password);		//���������� ������ �� �����
//void CopyFromHDD(char *_DestFileName, char *_SourceFileName); //����������� ���� �� ������� �������� ������� � ���



#endif HIGHLEVELFUNCTIONS_H