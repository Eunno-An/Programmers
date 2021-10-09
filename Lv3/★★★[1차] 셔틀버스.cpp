//시뮬레이션 문제
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Crew {
public:
    Crew(int HH, int MM) {
        this->HH = HH;
        this->MM = MM;
    }
    int HH;
    int MM;
};
class Bus {
public:
    Bus(int HH, int MM) {
        this->HH = HH;
        this->MM = MM;
    }
    int HH;
    int MM;
    vector<Crew*> people;
};
bool compare(Crew* slave1, Crew* slave2) {
    if (slave1->HH == slave2->HH)
        return slave1->MM < slave2->MM;
    return slave1->HH < slave2->HH;
}
void print_Crews_Info(vector<Crew*> Crews) {
    for (int i = 0; i < Crews.size(); i++)
        cout << Crews[i]->HH << ':' << Crews[i]->MM << '\n';
}
Crew* getConArriveTime(vector<Bus*> buses, vector<Crew*> crews, int n, int t, int m) {
    Crew* Con = new Crew(buses.back()->HH, buses.back()->MM);//기본은 마지막 버스의 시간!
    //각 버스에 탈 수 있는 인원들을 조사한다.
    int bus_idx = 0;
    for (int i = 0; i < crews.size(); i++) {
        if (bus_idx == buses.size())
            break;
        int crewHH = crews[i]->HH;
        int crewMM = crews[i]->MM;
        for (int j = 0; j < buses.size(); j++) {//각 버스에 탈 수 있는 인원들을 넣는다.
            if (buses[j]->HH > crewHH || (buses[j]->HH == crewHH && buses[j]->MM >= crewMM)) {
                if (buses[j]->people.size() < m) {
                    buses[j]->people.push_back(crews[i]);
                    break;
                }
                else 
                    continue;
                
            }
        }


    }
    //현재 buses정보에는 어떤 버스에 몇명이 타는지가 기록이 되어 있음.
    if (buses.back()->people.size() == m) {//마지막 버스가 꽉 찼으면, 거기서 마지막 사람을 미뤄내야 함.
        Con->HH = buses.back()->people.back()->HH;
        Con->MM = buses.back()->people.back()->MM - 1;
        if (Con->MM < 0) {
            Con->MM += 60;
            Con->HH--;
        }
    }
    return Con;
}
string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";
    vector<Crew*> Crews;
    vector<Bus*> Buses;
    for (int i = 0; i < timetable.size(); i++) {
        int HH = stoi(timetable[i].substr(0, 2));
        int MM = stoi(timetable[i].substr(3, 2));
        Crew* slave = new Crew(HH, MM);
        Crews.push_back(slave);
    }
    int default_Bus_arrive_hour = 9;
    int default_Bus_arrive_min = 0;
    for (int i = 0; i < n; i++) {
        Bus* bus = new Bus(default_Bus_arrive_hour, default_Bus_arrive_min);
        default_Bus_arrive_min += t;
        if (default_Bus_arrive_min >= 60) {
            default_Bus_arrive_hour += 1;
            default_Bus_arrive_min -= 60;
        }
        Buses.push_back(bus);
    }

    sort(Crews.begin(), Crews.end(), compare);
    Crew* Con = getConArriveTime(Buses, Crews, n, t, m);

    if (Con->HH < 10)
        answer += "0";
    answer += to_string(Con->HH);
    answer += ":";
    if (Con->MM < 10)
        answer += "0";
    answer += to_string(Con->MM);

    return answer;
}
int main() {
    solution(1, 1, 5, { "00:01", "00:01", "00:01", "00:01", "00:01" });
}
