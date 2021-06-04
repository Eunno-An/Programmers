#include<iostream>
#include<vector>
using namespace std;

int solution(int n) {
    long long answer = 0;
    int count = 1;
    while(n != 0){
        int k = n %3;
        n /= 3;
        answer += k * count;
        count *= 10;
    }
    //cout << answer << '\n';
    count /= 10; //count = 현재 자릿수
    //cout << count;
    vector<int> numbers;
    while(count != 0){
        int count2 = 1;
        int front_num = answer / count;
        cout << front_num << '\n';
        answer -= front_num * count;
            
        count /= 10;
        numbers.push_back(front_num);
    }
    for(int i=0; i<numbers.size(); i++){
        cout << numbers[i] << ' ';
    }
    answer = 0;
    int third=1;
    for(int i=0; i<=numbers.size(); i++){
        answer += numbers[i] *third;
       // cout << result << '\n';
        third*=3;
    }
    return answer;
}
