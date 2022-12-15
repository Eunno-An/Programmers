#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <stack>
using namespace std;

int solution(vector<int> order) {
    int answer = 0;
    queue<int> conv;//1, 2, 3, 4, ..., n
    stack<int> help;
    int orderNum = 0;
    for(int i=0; i<order.size(); i++)
        conv.push(i+1);
    //2 3 1 4 5
    while(!conv.empty()){
        int now = conv.front(); 
        //cout << now << ' ';
        if(order[orderNum] == now){//컨베이어 벨트 앞에 있는거랑 맞는 경우
            answer++;
            orderNum++;
            conv.pop();
            //cout << "1\n";
        }else{//그렇지 않은 경우
            if(!help.empty() and help.top() == order[orderNum]){//help 스택의 탑이 현재 해야되는거랑 맞는 경우
                answer++;
                orderNum++;
                help.pop();
                //cout << "2\n";
            }else{//그렇지 않으면
                help.push(now);
                conv.pop();
                //cout << "3\n";
            }
        }
    }
    while(!help.empty() and help.top() == order[orderNum]){
        answer++;
        help.pop();
        orderNum++;
    }
    return answer;
}