/*
Описание команд по работе с файловой системой 
*/

#ifndef __Commands_H
#define __Commands_H
#endif

#include <string.h>
#include <stdlib.h>
#include <vector>
#include "LowLevelFunctions.h"
#include "Structures.h"

using namespace std;

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

char**		FindWordsInStr(char *InputStr, int *nWordRet);
int			GetCommandNumber(char *Com);
char*		ShowPath(vector<uint> path_vector);