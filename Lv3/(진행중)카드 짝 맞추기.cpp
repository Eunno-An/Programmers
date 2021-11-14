#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

//키 조작 횟수의 최솟값.
//1. 배열에 존재하는 요소들의 순열을 생성한다. = list 1~6가지 총 6가지의 수를 순열로 생성하면 6! = 720
//2. 각 순열에 해당하는 요소가 board안에서 바로 연결될 수 있는지 체크한다. 
//2-1. 연결될 수 있는지 체크할 때, 움직이는 연산들을 이용한다. (moveOne, moveCtrl, Enter)
int nowY, nowX;
vector<vector<int>> global_board;
const int dy[4] = {0, 1, 0, -1};
const int dx[4] = {1, 0, -1, 0};
bool is_flipped[4][4];//true:앞면, false: 뒷면
bool ok(int y, int x){//빈 공간이면서 보드의 범위 안에 있을 때
    if(y >=0 && y < 4 && x>=0 && x < 4 && global_board[y][x] == 0) return true;
    else return false;
}
void pushArrow(int directionY, int directionX){
    if(ok(nowY + directionY, nowX + directionX)){
        nowY += directionY;
        nowX += directionX;
    }
    return;
}
void pushCtrlArrow(int directionY, int directionX){
    int nextY, nowX;
    if(directionY == 1){
        for(int i=1; i<=3; i++){
            nextY = nowY + i;
            if(!ok(nextY, nowX))
                break;
        }
        nowY = nextY-1;
    }else if(directionX == 1){
        for(int i=1; i<=3; i++){
            nextX = nowX + i;
            if(!ok(nowY, nextX))
                break;
        }
        nowX = nextX-1;
    }else if(directionY == -1){
        for(int i=1; i<=3; i++){
            nextY = nowY - i;
            if(!ok(nextY, nowX))
                break;
        }
        nowY = nextY+1;
    }else{
        for(int i=1; i<=3; i++){
            nextX = nowX - i;
            if(!ok(nowY, nextX))
                break;
        }
        nowX = nextX+1;
    }
    return;
}
bool pushEnter(int num_flipCard){
    
    is_flipped[nowY][nowX] != is_flipped[nowY][nowX];
    num_flipCard++;
    if(num_flipCard == 1)
        return false; // 아직 앞면이 보이는 카드가 1장 뿐
    else if(num_flipCard == 2)
        return true; // 앞면이 보이는 카드가 2장이 된 경우
}

int solution(vector<vector<int>> board, int r, int c) {
    int answer = 0;
    nowY = r;
    nowX = c;
    global_board = board;
    memset(is_flipped, false, sizeof(is_flipped));
    vector<int> cards(7, 0);
    for(int i=0; i<board.size(); i++)
        for(int j=0; j<board[i].size(); j++)
            if(board[i][j])
                cards[board[i][j]]++;
    
    vector<int> cardList;
    for(int i=0; i<cards.size(); i++)
        if(cards[i])
            cardList.push_back(i);
    
    //커서를 현재 위치인 (r, c)에서 처음 찍고자 하는 캐릭터 위로도 옮기는데 횟수가 필요함.
    
    
    do{
        queue<pair<int, int>> cursor;
        
        vector<vector<int>> tempBoard = board;
        for(int i=0; i<4; i++){
            int nextY = r + dy[i];
            int nextX = c + dx[i];
        }
    }while(next_permutation(cardList.begin(), cardList.end()));
    
    
    
    return answer;
}
