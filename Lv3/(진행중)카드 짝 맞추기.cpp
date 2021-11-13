#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

//키 조작 횟수의 최솟값.
//1. 배열에 존재하는 요소들의 순열을 생성한다. = list 1~6가지 총 6가지의 수를 순열로 생성하면 6! = 720
//2. 각 순열에 해당하는 요소가 board안에서 바로 연결될 수 있는지 체크한다. 
//2-1. 연결될 수 있는지 체크할 때, 움직이는 연산들을 이용한다. (moveOne, moveCtrl, Enter)
void pushArrow(){
    
}
void pushCtrlArrow(){
    
}
void pushEnter(){
    
}
int solution(vector<vector<int>> board, int r, int c) {
    int answer = 0;
   
    vector<int> cards(7, 0);
    for(int i=0; i<board.size(); i++)
        for(int j=0; j<board[i].size(); j++)
            if(board[i][j])
                cards[board[i][j]]++;
    
    vector<int> cardList;
    for(int i=0; i<cards.size(); i++)
        if(cards[i])
            cardList.push_back(i);
    
    do{
        
    }while(next_permutation(cardList.begin(), cardList.end()));
    
    
    
    return answer;
}
