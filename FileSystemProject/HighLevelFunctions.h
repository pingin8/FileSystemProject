#ifndef HIGHLEVELFUNCTIONS_H
#define HIGHLEVELFUNCTIONS_H

#include "LowLevelFunctions.h"
#include <vector>

using namespace std;

void FileCreateHigh(vector<uint> *path_vector, char *FileName);								//Создание файла+
void DirCreateHigh(vector<uint> *path_vector, char *DirName);									//Создание директории+
void FileDeleteHigh(vector<uint> *path_vector,char *FileName);							//Удаление файла+
void DirDeleteHigh(vector<uint> *path_vector, char *DirName);							//Удаление каталога+
//void CopyFile(char *FileName, char *_DestDirName);			//Копирование файла
//void MoveFile(char *FileName, char *_DestDirName);		//Перемещение файла+
void EnterDir(vector<uint> *path_vector,char *DirName);							//Войти в директорию+
void LeaveDir(vector<uint> *path_vector);											//Покинуть директорию+
//void ReadFile(char *FileName);							//Чтение файла+
//void WriteFile(char *FileName);							//Запись в файл+
//void Format(int FSSize, int KlasterSize);				//Форматирование файла, установка размера образа и размера кластера+
//void VIEWFILE();											//Просмотр всего содержимого в файле-образе
//void SYSINFO();											//Просмотр системной информации+
void ViewCurrentDirectory(vector<uint> *path_vector);				//Просмотр содержимого текущей директории+
void About();											//Справка
//char* Path();												//Путь к текущей директории в образе
//void SetFilePassword(char *FileName, char *Password);	//Установить пароль на файл
//void SetDirPassword(char DirName, char *Password);		//Установить пароль на папку
//void CopyFromHDD(char *_DestFileName, char *_SourceFileName); //Скопировать файл из внешней файловой системы в мою



#endif HIGHLEVELFUNCTIONS_H