#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
bool compare(pair<pair<int, string>, int> a, pair<pair<int, string>, int> b){
    if(a.first.first == b.first.first){
        return a.second > b.second;
    }
    return a.first.first > b.first.first;
}
string solution(string m, vector<string> musicinfos) {
    string answer = "";
    //m: 네오가 기억한 멜로디를 담은 문자열
    //musicinfos = 방송된 곡의 정보를 담고 있는 배열
    queue<int> remember;
    int songLength = 0;
    for (int i = 0; i < m.size(); i++) {
        if (m[i] == '#')
            remember.push(-1);
        else {
            remember.push(m[i]);
            songLength++;
        }
    }
    queue<int> remember_temp = remember;
    vector<pair<pair<int, string>, int>> matches;//first = playTime, second = songTitle
    for (int i = 0; i < musicinfos.size(); i++) {
        stringstream ss(musicinfos[i]);
        string temp;
        vector<string> song_info;
        while (getline(ss, temp, ',')) {
            song_info.push_back(temp);
        }

        string startTime = song_info[0];
        string endTime = song_info[1];
        string songTitle = song_info[2];
        string info = song_info[3];

        queue<int> info_int;
        
        for (int j = 0; j < info.size(); j++) {
            if (info[j] == '#')
                info_int.push(-1);
            else 
                info_int.push(info[j]);
                
            
                
        }

        int playTime = 0;
        playTime += stoi(endTime.substr(3, 2)) - stoi(startTime.substr(3, 2));
        playTime += (stoi(endTime.substr(0, 2)) - stoi(startTime.substr(0, 2))) * 60;

        int matchCount = 0;
        int top_remember = 0;
        bool isSharp_remember = false;
        
        for (int j = 0; j < playTime; j++) {
            //playTime 동안에는, info_top을 순회한다.
            //만약 #이 붙은 멜로디라면, #까지를 넣어준다.
            //remember또한 맞을 경우 순회하면서, matchCount를 증가시켜준다.
            //matchCount가 remember.size()와 같을 경우, matches에 추가하고,
            //remember.top()과 top_melody가 다를 경우, remember를 tempRemember로 바꿔준다.
            int top_melody = info_int.front(); info_int.pop();
            bool isSharp = false;
            isSharp_remember = false;
            top_remember = remember.front(); remember.pop();

            info_int.push(top_melody);
            if (info_int.front() == -1) {
                isSharp = true;
                info_int.pop();
                info_int.push(-1);
            }
            if (remember.front() == -1) {
                isSharp_remember = true;
                remember.pop();
            }

            if (top_remember == top_melody && isSharp_remember == isSharp) {
                matchCount++;
                if (matchCount == songLength) {
                    matches.push_back(make_pair(make_pair(songLength, songTitle), i));
                    break;
                }
                remember.push(top_remember);
                if (isSharp_remember)
                    remember.push(-1);
            }
            else {
                matchCount = 0;
                remember = remember_temp;
            }
            
        }
        //11:58,12:04
       
        remember = remember_temp;
    }
    sort(matches.begin(), matches.end(), compare);
    if (matches.empty())
        answer = "(None)";
    else
        answer = matches.back().first.second;
    return answer;
}
int main() {
    //solution("CC#BCC#BCC#BCC#B", { "03:00,03:30,FOO,CC#B", "04:00,04:08,BAR,CC#BCC#BCC#B" });
    solution("ABC", { "12:00,12:14,HELLO,C#DEFGAB", "13:00,13:05,WORLD,ABCDEF" });
}
