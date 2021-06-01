#include <string>
#include<algorithm>
#include <vector>
#include <iostream>
using namespace std;

//조건에 나온 문자들의 인덱스를 뽑아내고, next_permutation만 사용할 수 있다면 쉬운 문제

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.

int solution(int n, vector<string> data) {
    int answer = 0;
    vector<int> friends;
    friends.push_back('A'-65);
    friends.push_back('C'-65);
    friends.push_back('F'-65);
    friends.push_back('J'-65);
    friends.push_back('M'-65);
    friends.push_back('N'-65);
    friends.push_back('R'-65);
    friends.push_back('T'-65);
    do{
        bool isOk = true;
        for(int i=0; i<n; i++){
            int f1 = data[i][0] - 65;
            int f2 = data[i][2] - 65;
            char opt = data[i][3];
            int gap = data[i][4] - '0';
            int left_idx, right_idx; 
            for(int j=0; j<8; j++){
                if(friends[j] == f1){
                    left_idx = j;
                }
                if(friends[j] == f2){
                    right_idx = j;
                }
            }
            switch(opt){
                case '=':
                    if(abs(left_idx - right_idx)-1 != gap)
                        isOk = false;
                    break;
                case '<':
                    if(abs(left_idx - right_idx)-1 >= gap)
                        isOk = false;
                    break;
                case '>':
                    if(abs(left_idx - right_idx)-1 <= gap)
                        isOk = false;
                    break;
            }
            if(!isOk) break;
        }    
        if(isOk)answer++;
    }while(next_permutation(friends.begin(), friends.end()));
    
    return answer;
}
