#ifndef HIGHLEVELFUNCTIONS_H
#define HIGHLEVELFUNCTIONS_H

#include "Structures.h"
#include "Constants.h"
#include <vector>

using namespace std;

void FileCreateHigh(vector<uint> path_vector, char *FileName);								//�������� �����+
void DirCreateHigh(vector<uint> path_vector, char *DirName);									//�������� ����������+
void FileDeleteHigh(char *FileName);							//�������� �����+
void DirDeleteHigh(char *DIrName);							//�������� ��������+
//void CopyFile(char *FileName, char *_DestDirName);			//����������� �����
//void MoveFile(char *FileName, char *_DestDirName);		//����������� �����+
void EnterDir(char *DirName);							//����� � ����������+
void LeaveDir();											//�������� ����������+
//void ReadFile(char *FileName);							//������ �����+
//void WriteFile(char *FileName);							//������ � ����+
//void Format(int FSSize, int KlasterSize);				//�������������� �����, ��������� ������� ������ � ������� ��������+
//void VIEWFILE();											//�������� ����� ����������� � �����-������
//void SYSINFO();											//�������� ��������� ����������+
void ViewCurrentDirectory();				//�������� ����������� ������� ����������+
void About();											//�������
//char* Path();												//���� � ������� ���������� � ������
//void SetFilePassword(char *FileName, char *Password);	//���������� ������ �� ����
//void SetDirPassword(char DirName, char *Password);		//���������� ������ �� �����
//void CopyFromHDD(char *_DestFileName, char *_SourceFileName); //����������� ���� �� ������� �������� ������� � ���



#endif HIGHLEVELFUNCTIONS_H