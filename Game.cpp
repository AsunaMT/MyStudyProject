#include<iostream>
#include<cstdlib>
#include<getopt.h>
#include "fun.h"
using namespace std;

int main(int argc, char **argv){
	int end = 2048,size = 4;
	int ch;
    opterr = 0;
    while((ch = getopt(argc, argv, "s:t")) != -1){
        switch(ch){
            case 't':
				end = 64;
                break;
            case 's':
				size = atoi(optarg);
				while(size < 2 || size > 5){
					printf("The dimension you set is illegal!\nPlease set again!\n");
					scanf("%d", &size);
					fflush(stdin);
				}
                break;
            default:
                printf("You entered an invalid parameter!\n");
		}
    }
	WeclomeScreen(); 
	Chessboard game(size, end);
	bool command = false;
	do{
		command = false;
		switch(ChooseMode()){
			case 1:
				SinglePlayerMode(game); break;
			case 2:
				TwoPlayerMode(game); break;
			default:
				printf("Invalid input, please try again!\n");
				command = true;	break;
		}
	}while(command);
	system("pause");
	return 0;
}