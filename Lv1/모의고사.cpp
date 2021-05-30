#include <string>
#include <vector>
#include <stack>
#include<iostream>
#include <algorithm>
using namespace std;

//최대 사용자가 여러명일 때는, stack을 이용하는게 편하다.
vector<int> solution(vector<int> answers) {
    vector<int> answer;
    
    int count_1 =0, count_2 =0, count_3=0;
    int pick1[5] = {1, 2, 3, 4, 5};
    int pick2[8] = {2, 1, 2, 3, 2, 4, 2, 5};
    int pick3[10] = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
    
    for(int i=0, j=0, k=0, l = 0; i<answers.size(); i++, j++, k++, l++){
        if(j % 5 == 0)
            j %=5;
        if(k % 8 == 0)
            k %= 8;
        if(l % 10 == 0)
            l %= 10;
        if(answers[i] == pick1[j])
            count_1++;
        if(answers[i] == pick2[k])
            count_2++;
        if(answers[i] == pick3[l])
            count_3++;
    }
    vector<int> temp;
    temp.push_back(count_1);
    temp.push_back(count_2);
    temp.push_back(count_3);
    
    stack<pair<int, int>> s; // s.top().first = count, s.top().second = idx
    for(int i=0; i<3; i++){
        //스택 사용시 조건문이랑 같이 쓸 때, 비어있는 가를 반드시 먼저 검사해야 런타임 에러가 안뜬다. 
        //while(s.top().first < temp[i] && !s.empty()) -> 런타임에러
        while(!s.empty() && s.top().first < temp[i]){
            s.pop();
        }
        if(!s.empty() && s.top().first > temp[i]){
            //들어온게 작을 때 예외처리
            continue;
        }
        s.push(make_pair(temp[i], i+1));
    }
    
    while(!s.empty()){
        cout << s.top().first << ' ' << s.top().second << '\n';
        int idx = s.top().second;
        s.pop();
        answer.push_back(idx);
    }
    sort(answer.begin(), answer.end());
    return answer;
}
