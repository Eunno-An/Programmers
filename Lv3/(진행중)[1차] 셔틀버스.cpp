#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Crew{
public:
    Crew(int HH, int MM){
        this->HH = HH;
        this->MM = MM;
    }
    int HH;
    int MM;
};
class Bus{
public:
    Bus(int HH, int MM){
        this->HH = HH;
        this->MM = MM;
    }
    int HH;
    int MM;
};
bool compare(Crew* slave1, Crew* slave2){
    if(slave1->HH == slave2->HH)
        return slave1->MM < slave2->MM;
    return slave1->HH < slave2->HH;
}
void print_Crews_Info(vector<Crew*> Crews){
    for(int i=0; i<Crews.size(); i++)
        cout << Crews[i]->HH << ':' << Crews[i]->MM << '\n';
}
Crew* getConArriveTime(vector<Bus*> buses, vector<Crew*> crews, int n, int t, int m){
    //버스들의 타임테이블이 주어질 때, crew들 중 이 안에 탈 수 있는 크루들만 뽑는다.
    //그 다음에 콘이 탈 수 있는 가장 늦은 시간을 뽑는다.
    int maximum_crew = n * m - 1;//반드시 콘이 타야함!
    Crew* Con = new Crew(0, 0);
    vector<Crew*> waiting;
    Bus* lastBus = buses.back();
    for(int i=0; i<crews.size(); i++){
        if(waiting.size() == maximum_crew)
            break;
        int HH = crews[i]->HH;
        int MM = crews[i]->MM;
        if(HH <=lastBus->HH && MM <= lastBus->MM)
            waiting.push_back(crews[i]);
        else//이 이상은 이미 버스가 떠난것!
            break;
    }
    if(waiting.empty()){
        Con->HH = lastBus->HH;
        Con->MM = lastBus->MM;
        return Con;
    }
    if(maximum_crew > waiting.size()){
        Con->HH = lastBus->HH;
        Con->MM = lastBus->MM;
    }
    else{
        Con->HH = waiting.back()->HH;
        Con->MM = waiting.back()->MM - 1;
        if(Con->MM == -1){
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
    for(int i=0; i<timetable.size(); i++){
        int HH = stoi(timetable[i].substr(0, 2));
        int MM = stoi(timetable[i].substr(3, 2));
        Crew* slave = new Crew(HH, MM);
        Crews.push_back(slave);
    }
    int default_Bus_arrive_hour = 9;
    int default_Bus_arrive_min = 0;
    for(int i=0; i<n; i++){
        Bus* bus = new Bus(default_Bus_arrive_hour, default_Bus_arrive_min);
        default_Bus_arrive_min += t;
        if(default_Bus_arrive_min >= 60){
            default_Bus_arrive_hour += 1;
            default_Bus_arrive_min -= 60;
        }
        Buses.push_back(bus);
    }    
    
    sort(Crews.begin(), Crews.end(), compare);
    Crew* Con = getConArriveTime(Buses, Crews, n, t, m);
    
    if(Con->HH < 10)
        answer += "0";
    answer += to_string(Con->HH);
    answer += ":";
    if(Con->MM < 10)
        answer += "0";
    answer += to_string(Con->MM);
    
    return answer;
}
