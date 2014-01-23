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


char**		FindWordsInStr(char *InputStr, int *nWordRet);
int			GetCommandNumber(char *Com);
char*		ShowPath(vector<uint> path_vector);