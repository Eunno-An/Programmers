#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int solution(vector<int> cards) {
    int answer = 0;
    //cards[i] = i+1번째 상자에 담긴 숫자
    
    for(int choice=0; choice<cards.size(); choice++){//1번 상자부터 cards.size()번 상자까지 중 하나 선택
        vector<bool> visit(cards.size(), false);
        int boxSize = 0;
        int nowChoice = choice;
        while(visit[cards[nowChoice]-1] == false){
            visit[cards[nowChoice]-1] = true;
            nowChoice = cards[nowChoice]-1;
            boxSize++;
        }
        
        for(int leftChoice = 0; leftChoice<cards.size(); leftChoice++){
            if(visit[leftChoice] == false){
                int boxSize2 = 0;
                int nowChoice2 = leftChoice;
                while(visit[cards[nowChoice2]-1] == false){
                    visit[cards[nowChoice2]-1]=true;
                    nowChoice2 = cards[nowChoice2]-1;
                    boxSize2++;
                }
                if(answer < boxSize * boxSize2)
                    answer = boxSize * boxSize2;
            }
        }
    }
    
    return answer;
}