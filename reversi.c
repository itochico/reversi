#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reversi.h"

int board[boardSize][boardSize];
int direction8[3] = {0,-1,1};

int main(int argc, const char * argv[]) {
    int x,y,player=black;
    int reValue;
    initializeBoard();
    printFirst();
    while(1){
        printBoard();
        printPlayer(player);
        reValue = validate(&x,&y);
        if(reValue==1){//入力が間違っているなら
            continue;
        }
//        if(putStone(x,y,player)==1){//入力箇所に石が置けないなら
//            continue;
//        }
        if(canPutStoneToSquare(x,y,player,1)==1){
            continue;
        }
        player = changePlayer(player);
        if(canPutStoneToBoard(player) == 1){//石を置ける場所が無いなら
            player = changePlayer(player);
            if(canPutStoneToBoard(player) == 1){//石を置ける場所がないならゲーム終了
                printBoard();
                println("Game Finish!");
                whoWin();
                break;
            }else{
                println("You cannot put stone. Pass your turn.");
            }
        }
    }
    return 0;
}

void println(char *moji){//改行文字を入れるのが面倒な時に使用
    printf("%s\n", moji);
}

void printFirst(void){//初回のゲーム説明
    println("Start Reversi game.");
    println("Please input the place to put the stone alternately.");
    println("When the letter \"please put stone :\" appears, ");
    println("enter the place where you want to put the stone with two numbers separated by comma like ");
    println("\"1,6\"");
    println("and press Enter.");
    println("In this case, place the stones in a column 1,low 6 position.");
    printf("The stone for player-black is ");
    printf("\"%s\"",blackStone);
    printf("and the stone for player-white is ");
    printf("\"%s\".\n",whiteStone);
}

int changePlayer(int player){
    //playerの切り替えを行う
    //playerは1または2
    return 3-player;
}

void printPlayer(int player){//playerを出力し入力を促す
    printf("Player ");
    if(player == black){
        printf(blackStone);
    }else if(player == white){
        printf(whiteStone);
    }
    printf(", please put stone :\n");
}

void printBoard(void){//盤面の出力
    printf(" ");
    for (int i = 0; i < boardSize; ++i) {
        printf(" %d",i);
    }
    printf("\n");
    for(int i=0;i<boardSize;i++){
        printf("%d ",i);
        for(int j=0;j<boardSize;j++){
            if(board[i][j]==none){
                printf(noneBoard);
            }else if(board[i][j]==black){
                printf(blackStone);
            }else if(board[i][j]==white){
                printf(whiteStone);
            }
            printf(" ");
        }
        printf("\n");
    }
}

void initializeBoard(void){//盤面の初期化
    int halfSize = boardSize/2;
    for(int i=0;i<boardSize;i++){
        for(int j=0;j<boardSize;j++){
            board[i][j] = none;
        }
    }
    board[halfSize-1][halfSize] = black;
    board[halfSize][halfSize-1] = black;
    board[halfSize-1][halfSize-1] = white;
    board[halfSize][halfSize] = white;
}

int boardValue(int y,int x){//盤面外に配列アクセスしたときに-1を返す
    if(x<0||x>boardSize-1||y<0||y>boardSize-1){
        return -1;
    }else{
        return board[y][x];
    }
}

void whoWin(){//勝者を判定し出力する
    int score = 0;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if(board[i][j]==black){
                score += 1;
            }else if(board[i][j]==white){
                score -=1;
            }
        }
    }
    if(score>0){
        println("player-black is winner!");
    }else if(score<0){
        println("player-white is winner!");
    }else{
        println("Draw game.");
    }
}


int canPutStoneToSquare(int x, int y, int player, int isTurnOver){
    //与えられた(x,y)に石がおけるか判定し、isTurnOverが1かつ置ける場合はひっくり返す処理を行う
    int enemy = changePlayer(player);
    int frag = 1;
    if(board[y][x]!=none&&isTurnOver==1){//入力場所にすでに石がある
        println("You cannot put stone here!");
        return 1;
    }
    int dirx,diry,n;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            dirx = direction8[j];
            diry = direction8[i];
            n=1;
            if((dirx!=0||diry!=0)&&boardValue(y+diry,x+dirx)==enemy){//入力場所の周囲マスに敵の石があるか
                while(boardValue(y+n*diry,x+n*dirx)==enemy){
                    n+=1;
                }
                if(boardValue(y+n*diry,x+n*dirx)==player){//敵の石を自分の石で挟めるか
                    if(isTurnOver==1){
                        for(int k=1;k<n;k++){//敵の石をひっくり返す
                            board[y+k*diry][x+k*dirx]=player;
                        }
                        frag = 0;
                    }else{
                        return 0;
                    }

                }
            }
        }
    }
    if(frag == 1){//入力場所に石をおいてもひっくり返せる石が無い
        if(isTurnOver==1){
            println("There is no stone that can be turned over.");
        }
        return 1;
    }else{
        board[y][x]=player;
        return 0;
    }
}

int canPutStoneToBoard(player){//playerにとって石を置ける場所が存在するかどうか
    int frag;
    for(int i=0;i<boardSize;i++){
        for(int j=0;j<boardSize;j++){
            if(board[i][j]==none){
                frag = canPutStoneToSquare(j, i, player,0);
                if(frag == 0){//一箇所でも石を置ける場所があれば
                    return 0;
                }
            }
        }
    }
    return 1;//石を置けない
}

int validate(int *x,int *y){//入力のチェック
    char input[4];
    scanf("%3s%*[^\n]%*c",input);
    println(input);
    if(input[1]!=','){
        println("Input format is wrong!");
        return 1;
    }
    int xInput = input[0] - '0';
    int yInput = input[2] - '0';
    if(xInput<0||xInput>boardSize-1||yInput<0||yInput>boardSize-1){//入力された数値が盤面の範囲外
        println("Can't put stone here!");
        return 1;
    }else{
        (*x)=xInput;
        (*y)=yInput;
    }
    return 0;
}


