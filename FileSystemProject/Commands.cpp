#define _CRT_SECURE_NO_WARNINGS

#include "Commands.h"

char com1[] = "cd";
char com2[] = "cd..";
char com3[] = "df";
char com4[] = "dd";
char com5[] = "dir";
char com6[] = "help";
char com7[] = "/?";
char com8[] = "crf";
char com9[] = "crd";
char com10[] = "mf";
char com11[] = "rf";
char com12[] = "wf";
char com13[] = "format";
char com14[] = "sysinfo";
char com15[] = "exit";
char com16[] = "cf";

char** FindWordsInStr(char *InputStr, int *nWordRet)
{
	char** com;
	
	int num = 0;
	int len = strlen(InputStr);

	for(int i=0; i<len; i++)
	{
		if(InputStr[i] == ' ')//Пробел
		{
			num++;
			while(InputStr[i] == ' ')
				i++;
			i--;
		}
	}
	if(InputStr[len-1] != ' ')
		num += 1; //Слов больше на 1 чем пробелов

	com = (char**)calloc(num, sizeof(char*));
	for(int i=0; i<num; i++)
	{
		com[i] = (char*)calloc(255, sizeof(char));
	}
	for(int i=0, j=0, k=0; i<len; i++)
	{
		if(InputStr[i] == ' ')
		{
			com[j][k] = '\0';
			j++;
			k=0;
			while(InputStr[i] == ' ')
				i++;
			i--;
		}
		else
			com[j][k++] = InputStr[i];
	}
	*nWordRet = num;
	return com;
}
int GetCommandNumber(char *Com)
{
	if(!strcmp(Com, com1))
		return 1;
	if(!strcmp(Com, com2))
		return 2;
	if(!strcmp(Com, com3))
		return 3;
	if(!strcmp(Com, com4))
		return 4;
	if(!strcmp(Com, com5))
		return 5;
	if(!strcmp(Com, com6))
		return 6;
	if(!strcmp(Com, com7))
		return 7;
	if(!strcmp(Com, com8))
		return 8;
	if(!strcmp(Com, com9))
		return 9;
	if(!strcmp(Com, com10))
		return 10;
	if(!strcmp(Com, com11))
		return 11;
	if(!strcmp(Com, com12))
		return 12;
	if(!strcmp(Com, com13))
		return 13;
	if(!strcmp(Com, com14))
		return 14;
	if(!strcmp(Com, com15))
		return 15;
	if(!strcmp(Com, com16))
		return 16;
	return -1;
}

char* ShowPath(vector<uint> path_vector)
{
	//char path[255];
	char *path = (char*)calloc(255, sizeof(char));

	for(int i=0; i<255; i++)
		path[i] = '\0';

	for(int i = 0; i < path_vector.size(); i++)
	{
		strcat(path, GetInfoById(path_vector[i])->Name);
		strcat(path, "\\");
	}
	return  path;
}
