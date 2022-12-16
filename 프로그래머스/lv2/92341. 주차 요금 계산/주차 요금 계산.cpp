#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
//outTime: (2:20), inTime: (1:30)
//remainTime = 51

int calMin(string& outTime, string& inTime){
    int hour = stoi(outTime.substr(0,2)) - stoi(inTime.substr(0,2));
    int minute = stoi(outTime.substr(3,2)) - stoi(inTime.substr(3,2));
    return hour*60 + minute;
}

int calCost(int minute, vector<int>& fees){
    return fees[1] + ceil((double)(minute - fees[0])/fees[2]) * fees[3]; 
}

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    vector<pair<int, int>> before_answer;
    unordered_map<int, string> bucket;//차량 번호, 차량 입차 시간
    unordered_map<int, int> bucket2;//차량 번호, 차량 누적 시간
    string lastTime = "23:59";
    for(int i=0; i<records.size(); i++){
        string time = records[i].substr(0, 5);
        int carNum = stoi(records[i].substr(6,4));
        if(records[i][11] == 'I'){
            bucket[carNum] = time;
        }else{
            string inTime = bucket[carNum];
            int remainTime = calMin(time, inTime);
            //1909 - 0759
            //12, -50
            //720 - 50 = 670
            bucket2[carNum] += (remainTime);
            bucket.erase(carNum);
        }
    }
    //23:59까지 출차 기록이 없는 경우 다 뺀다.
    for(auto p : bucket){
        bucket2[p.first] += (calMin(lastTime, p.second));
    }
    
    //요금들을 계산한다.
    for(auto p : bucket2){
        cout << p.first << ' ' << p.second << '\n';
        before_answer.push_back({p.first, calCost(p.second, fees)});
    }
    
    sort(before_answer.begin(), before_answer.end());
    for(int i=0; i<before_answer.size(); i++)
        answer.push_back((fees[1] > before_answer[i].second ? fees[1] : before_answer[i].second));
    return answer;
}