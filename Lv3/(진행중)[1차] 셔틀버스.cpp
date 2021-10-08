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
bool compare(Crew* slave1, Crew* slave2){
    if(slave1->HH == slave2->HH)
        return slave1->MM < slave2->MM;
    return slave1->HH < slave2->HH;
}
void print_Crews_Info(vector<Crew*> Crews){
    for(int i=0; i<Crews.size(); i++)
        cout << Crews[i]->HH << ':' << Crews[i]->MM << '\n';
}
string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";
    vector<Crew*> Crews;
    for(int i=0; i<timetable.size(); i++){
        int HH = stoi(timetable[i].substr(0, 2));
        int MM = stoi(timetable[i].substr(3, 2));
        Crew* slave = new Crew(HH, MM);
        Crews.push_back(slave);
    }
    sort(Crews.begin(), Crews.end(), compare);
    print_Crews_Info(Crews);   
    return answer;
}
