#include "Constants.h"
#include "LowLevelFunctions.h"
#include "HighLevelFunctions.h"
#include "Structures.h"
#include "commands.h"
#include <iostream>
#include <vector>

using namespace std;

void HELPCOM()
{
	cout <<	"\ncd - enter dir // cd [DIRNAME]\n";
	cout << "cd.. - leave current dir\n";
	cout << "df - delete file // df [FILENAME]\n";
	cout << "dd - delete dir // dd [DIRNAME]\n";
	cout << "dir - view all dirs & files in current dir // dir 1 - view hidden 0 - view without hidden\n";
	cout << "help - view commands\n";
	cout << "/? - about programm\n";
	cout << "crf - create file // crf [FILENAME]\n";
	cout << "crd - create dir // crd [DIRNAME]\n";
	cout << "mf - move file // mf [FILENAME] [_DEST DIRNAME]\n";
	cout << "rf - read file // rf [FILENAME]\n";
	cout << "wf - write file // wf [FILENAME]\n";
	cout << "format - format image // format [FileSystem Size] [Klaster Size]\n";
	cout << "sysinfo - show system information\n";
}

int main()
{
	setlocale(LC_ALL,"Russian");
	system("cls");

	char command[255];
	char** words;
	int nWords;
	vector<uint> path;

	while(1)
	{
		cout << "\n";	
		cout << ShowPath(path) << ">";

		cin.getline(command,255);
		words = FindWordsInStr(command, &nWords);

		switch(GetCommandNumber(words[0]))
		{
		case 1:{	
					if(nWords < 2)
						break;
					EnterDir(&path, words[1]);		break;}

		case 2:{	LeaveDir(&path);				break;}
		case 3:{
					if(nWords < 2)
						break;
					FileDeleteHigh(&path, words[1]);	break;}
		case 4:{
					if(nWords < 2)
						break;
					DirDeleteHigh(&path, words[1]);	break;}
		case 5:{	
					if(nWords < 2)
						ViewCurrentDirectory(&path);		break;}
		case 6:{	HELPCOM();						break;}
		case 7:{		About();		break;}
		case 8:{	
					if(nWords < 2)
						break;
					FileCreateHigh(&path, words[1]); break;}
		case 9:{	
					if(nWords < 2)
						break;
					DirCreateHigh(&path, words[1]);
													break;}
		case 10:{	
					if(nWords < 3)
						break;
					/*пустота*/;	break;}
		case 11:{	
					if(nWords < 2)
						break;
					/*пустота*/;		break;}
		case 12:{	
					if(nWords < 2)
						break;
					/*пустота*/;	break;}
		case 13:{	
					if(nWords < 3)
						break;
					if(!atoi(words[1]))
						break;
					if(!atoi(words[2]))
						break;
					/*пустота*/; break;}
		case 14:{	/*пустота*/;				break;}
		case 15:{	return 0;}
		case 16:{	if(nWords < 3)
						break;
					/*пустота*/;
													break;}
		}
	}
}