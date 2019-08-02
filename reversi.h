#ifndef REVERSI_H
#define REVERSI_H

#define boardSize 4 //盤面の大きさ 2の倍数にする
#define none 0 //石が置かれていない場合の配列に格納する数字
#define black 1 //黒石が置かれている場合の配列に格納する数字
#define white 2 //白石が置かれている場合の配列に格納する数字
#define noneBoard "-" //石が置かれていない場合の盤面の表示文字
#define blackStone "x" //黒石が置かれている場合の盤面の表示文字
#define whiteStone "o" //白石が置かれている場合の盤面の表示文字

void initializeBoard(void); //盤面の初期化
void printBoard(void); //盤面の表示
void printFirst(void); //ゲーム開始時の説明表示
void printPlayer(int player); //playerの表示
int validate(int *x,int *y); //入力のチェック
void println(char *moji); //改行文字の入力を省いた出力
int canPutStoneToBoard(int player); //playerの手番がパスされるかどうか
int canPutStoneToSquare(int x, int y, int player, int isTurnOver); //石を置ける場所が一箇所でも存在するか
int changePlayer(int player); //playerの切り替え
int boardValue(int y,int x); //盤面への配列外の参照が起きないようにする
void whoWin(); //勝者判定および表示

#endif
