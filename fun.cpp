#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<windows.h>
#include "fun.h"
using namespace std;

void WeclomeScreen(){
	printf("\n！！！！！！！！！！！！！！！！！！\n\n");
	printf("    *----* *----* *    *  *----*\n");
	printf("         | |    | |    |  |    |\n");
	printf("    *----* |    | *----*  *----*\n");
	printf("    |      |    |      |  |    |\n");
	printf("    *----* *----*      *  *----*\n\n");
	printf("！！！！Welcome to the game!！！！！\n\n");
}

int ChooseMode(){
	printf("Please choose the mode of the game:\n\n");
	printf("     #Single player，，，1\n     #Two-player ，，，，2\n\n");
	printf("Please input your choice (1 or 2) :\n");
	char buff[20];
	fgets(buff, 20, stdin);
	return (buff[1] == '\n')? atoi(&buff[0]) : 0; 
}

void SinglePlayerMode(Chessboard &game){
	int result;
	Player p1;
	system("cls");
	game.PrintMap();
    do{
		printf("Now,your score is: %d\n", p1.score);
		printf("Please input the command:\n");
		while(game.GenerateMap(game.AskForOrder(), p1.score)){ 
			printf("Invalid operation, please choose another direction to move.\n");
		}
		game.GenerateNum();
		game.PrintMap();
		result = game.EndJudge();
	}while(result / 2);
	SinglePlayerModeOver(result, p1);
}
void TwoPlayerMode(Chessboard &game){
	Player p1("Player1"), p2("Player2");
	Player players[2] = {p1, p2};
	system("cls");
	game.PrintMap();
	int result, i = 0; 
    do{
		printf("Now,the score of %s is: %d\n", players[0].p_name.c_str(), players[0].score);
		printf("    the score of %s is: %d\n", players[1].p_name.c_str(), players[1].score);
		printf("\nThe operator of the next round is: %s\n\n", players[i % 2].p_name.c_str());
		bool entercheat = players[i % 2].cheat.selfparameter.empty();
		string direction = "wasd";
		if(!entercheat)   direction.assign(MoveJudge(game));
		if(!entercheat && direction.length() == 1){
			char dir = direction[0];
			CheatAskForOrder(players[i % 2], dir);
			game.GenerateMap(dir, players[i % 2].score);
		}
		else{
			while(game.GenerateMap(game.AskForOrder(players[i % 2], players[(i + 1) % 2]), players[i % 2].score)){ 
				printf("Invalid operation, please choose another direction to move.\n");
			}
		}
		game.GenerateNum();
		game.PrintMap();
		result = game.EndJudge();	i++;
	}while(result / 2);
	TwoPlayerModeOver(players[0], players[1]);
}

Cheat::Cheat(){
	usage = 1;
}
Player::Player(){
	score = 0;
}
Player::Player(const string Name){
	p_name.resize(100); 
	printf("Please input %s's name:\n", Name.c_str());
	getline(cin, p_name); 
	fflush(stdin);
	score = 0;
}
Player::Player(const Player &p){
	p_name.assign(p.p_name);
	score = p.score;
	cheat.usage = p.cheat.usage;
}
Chessboard::Chessboard(const Chessboard &c):Size(c.Size){
	ROW = c.ROW; COL = c.COL;
	EndCondition = c.EndCondition;
	int *MAP = new int[Size * Size];
	map = new int *[Size];
	for(int i = 0; i < Size; i++){
		map[i] = MAP + i * Size;
	}
	for(int i = 0; i < Size; i++){
		for(int j = 0; j < Size; j++){
			map[i][j] = c.map[i][j];
		}
	}
}
Chessboard::Chessboard(int s = 4, int end = 2048):Size(s){
	ROW = COL = s;
	int *MAP = new int[Size * Size];
	map = new int *[Size];
	for(int i = 0; i < Size; i++){
		map[i] = MAP + i * Size;
	}
    EndCondition = end;
	memset(&map[0][0], 0, Size * Size * sizeof(int));
	GenerateNum();	GenerateNum();
}
Chessboard::~Chessboard(){
	delete [] map;
}

char Chessboard::AskForOrder(){
	printf("Please input the command:\n"); 
	char order, cr, buff[20];
	int end = 1;
	while(end){
		fgets(buff, 20, stdin);
		order = buff[0]; cr = buff[1];
		if(strcmp(buff, Test) == 0){
			EndCondition = 64;
		 	printf("Has entered test mode.\n"); continue;
		}
		else{
			switch((int)order){
				case (int)'w':	case (int)'s':	case (int)'a':	case (int)'d':
					if(cr == '\n') end = 0;
					break;
				default:
					printf("Nullity!Please enter again!\n");	break;
			}
		}
		fflush(stdin);
	}	
	return order;
}
char Chessboard::AskForOrder(Player &presentp, Player &otherp){
	printf("Please input the command:\n"); 
	char order, cr, buff[20];
	int end = 1;
	while(end){
		fgets(buff, 20, stdin);
		order = buff[0]; cr = buff[1];
		switch((int)order){
			case (int)'w':	case (int)'s':	case (int)'a':	case (int)'d':
				if(cr == '\n') end = 0;
				else printf("Nullity!Please enter again!\n");
				break;
			case (int)'c':
				if(cr == ' '){
					string parameter;
					parameter.resize(100);
					parameter.assign(buff, 2, string::npos);
					HandleCheat(parameter, presentp, otherp);
				}
				else printf("Nullity!Please enter again!\n");	
				break;
			default:
				printf("Nullity!Please enter again!\n");	break;
			}
		fflush(stdin);
	}	
	return order;
}
void CheatAskForOrder(Player &cplayer,char dir){
	printf("%sIf you agree, please enter %c.\n", cplayer.cheat.selfparameter.c_str(), dir);
	char order, cr, buff[20];
	while(true){
		fgets(buff, 20, stdin); fflush(stdin);
		order = buff[0]; cr = buff[1];
		if(order == dir && cr == '\n'){
			cplayer.cheat.selfparameter.clear(); break;
		} 
		else printf("Nullity!Please enter again!\n");
	}	
}
void Chessboard::PrintMap(){
	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL; j++){
			printf("+-----");
		}
		printf("+\n");
		for(int j = 0; j < COL; j++){
			if(map[i][j] != 0) printf("|%-5d", map[i][j]);
			else printf("|     ");
		}
		printf("|\n");
	}
	for(int j = 0; j < COL; j++){
		printf("+-----");
	}
	printf("+\n");
}

int Chessboard::GenerateMap(char order, int& score){
	int row = 0, col = 0, count = 0;
	HandleOrder(row, col, order);
	int dir = row + col;
	if(row == 0) Transpose();
	Translation(dir, count);
	score += Merge(dir, count);
	if(count == 0){
		if(row == 0) Transpose();
		return 1;
	}
	//system("cls");
	Translation(dir, count);
	if(row == 0) Transpose();
	return 0;
}

void Chessboard::GenerateNum(){
	int i, j;
    srand(time(NULL));
	do{
		i = rand()%ROW; j = rand()%COL;
	}while(map[i][j] > 0);
	map[i][j] = 2;
}

void Chessboard::HandleOrder(int &row, int &col, char order){
	switch((int)order){
		case (int)'w':	row = 0; col = 1;	break;
		case (int)'s':	row = 0; col = -1;	break;
		case (int)'a':	row = 1; col = 0;	break;
		case (int)'d':	row = -1; col = 0;	break;
	}
}

void Chessboard::Transpose(){
	if(ROW != COL) exchange(ROW, COL);
	for(int i = 0; i < Size; i++){
		for(int j = i + 1; j < Size; j++){
			exchange(map[i][j], map[j][i]);
		}
	}
}

bool Chessboard::CirculationEnd(int j, int end){
	if(end > 0)		return j < end ? true : false;
	else			return j > end ? true : false;
}

void Chessboard::Translation(int dir, int &count){
	int start = dir > 0 ? 0 : (COL - 1), end = COL - 1 - start;
	for(int i = 0; i < ROW; i++){
		for(int j = start; CirculationEnd(j, end); j += dir){
			if(map[i][j] == 0){
				int k = j + dir, tra = 0;
				while(CirculationEnd(k, end + dir)){
					if(map[i][k]){
						count = 1;
						tra = 1; break;
					}
					else k += dir;
				}
				if(tra) { map[i][j] = map[i][k]; map[i][k] = 0; }
				else break;
			}
		}
	}
}

int Chessboard::Merge(int dir, int &count){
	int score = 0;
	int start = dir > 0 ? 0 : (COL - 1), end = COL - 1 - start;
	for(int i = 0; i < ROW; i++){
		for(int j = start; CirculationEnd(j, end); j += dir){
			if((map[i][j] != 0) && (map[i][j] == map[i][j + dir])){
				score += map[i][j] *= 2; 
				map[i][j + dir] = 0; count = 1;
				j += dir;
			}
		}
	}
	return score;
}

int Chessboard::EndJudge(){
	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL; j++){
			if(map[i][j] >= EndCondition) return 1;// Sucessed
		}
	}
	if(MoveJudge(*this).length() == 0) return 0;	// Fail
	else return 2;			// Countinue
}

void SinglePlayerModeOver(int result,Player p1){
	printf("！！！！Game Over!！！！！\n");
	printf("Your final score is: %d\n", p1.score);
	if(result == 1) printf("Congratulations��You successed!\n");
	else printf("Unfortunately��Please try again and you will make progress!\n");
}
void TwoPlayerModeOver(Player p1, Player p2){
	printf("！！！！Game Over!！！！！\n");
	printf("The final score of %s is: %d\n", p1.p_name.c_str(), p1.score);
	printf("The final score of %s is: %d\n\n", p2.p_name.c_str(), p2.score);
	if(p1.score == p2.score){
		printf("What a coincidence!The game ends in a tie!\n\n");
	}
	else
		printf("%s is the WINNER!\nCongratulations!\n\n", p1.score > p2.score ? p1.p_name.c_str() : p2.p_name.c_str());
}

void exchange(int &a, int &b){
	a = a + b;
	b = a - b;
	a = a - b;
}

string MoveJudge(const Chessboard &game){
	string all = "wasd";int j = 0;
	for(int k = 0; k < all.length() && j < all.length(); k++){
		Chessboard buff(game);
			if(buff.GenerateMap(all[k], j)){
				all.erase(j, 1); k--;
			}
			else j++;
	}
	return all;
}

void HandleCheat(string &parameter, Player &presentp, Player &otherp){
	if(presentp.cheat.usage == 0){
		printf("You have used this order!\n");
	}
	else{
		presentp.cheat.usage--;
		otherp.cheat.usage--;
		otherp.cheat.selfparameter.resize(100);
		otherp.cheat.selfparameter.assign(parameter);
		printf("Command successed!Please go on entering.\n");
	}
}