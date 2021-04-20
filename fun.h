#ifndef FUN_H
#define FUN_H
#include<string>
using namespace std;

#define Test "-t\n" //测试（64）

class Cheat{
public:
    int usage;
    string selfparameter; 
    Cheat();
};
class Player{
public:
    string p_name;
    int score;
    Cheat cheat;
    Player();
    Player(const string Name);
    Player(const Player &p);
};
class Chessboard{
private:
    const int Size;
    int ROW;
    int COL;
    int **map;
    int EndCondition;
public:
    Chessboard(const Chessboard &c);
    Chessboard(int s, int end);
    ~Chessboard();
    void PrintMap();   
    char AskForOrder();
    char AskForOrder(Player &presentp, Player &otherp);
    void GenerateNum();     //随机生成一个2
    int GenerateMap(char order, int &score);    //进行一整步操作
    void HandleOrder(int &row, int &col, char order);
    void Transpose();   //转置棋盘
    void Translation(int dir, int &count);  //朝某一方向平移到底
    int Merge(int dir, int &count); //进行一次合并，返回这一步的得分
    bool CirculationEnd(int j, int end);    
    int EndJudge();
};

void CheatAskForOrder(Player &cplayer,char dir);
void exchange(int &a, int &b);
void WeclomeScreen();
int ChooseMode();
void SinglePlayerMode(Chessboard &game);
void TwoPlayerMode(Chessboard &game);
void SinglePlayerModeOver(int result, Player p1);
void TwoPlayerModeOver(Player p1, Player p2);
string MoveJudge(const Chessboard &game);
void HandleCheat(string &ask, Player &presentp, Player &otherp);
#endif