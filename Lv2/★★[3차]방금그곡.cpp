//failed

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;
int calculatePlayTime(int hour, int minute){
    if(minute < 0){
        hour--;
        minute+=60;
    }
    return hour * 60 + minute;
}
string trans_sharp(string s){
    string temp = "";
    for(int i=0; i<s.size(); i++){
        if(i!=s.size() - 1 && s[i+1] == '#'){
            temp = temp + (char)(s[i] - 'A'+'a');
            ++i;
        }else temp += s[i];
    }
    return temp;
}
string solution(string m, vector<string> musicinfos) {
    string answer = "(None)";
    m = trans_sharp(m);
    int maxPlayTime = 0;
    for(int i=0; i<musicinfos.size(); i++){
        stringstream ss(musicinfos[i]);
        string temp;
        
        
        string startTime, endTime, songTitle, musicInfo;
        vector<string> parsing;
        while(getline(ss, temp, ',')){
            parsing.push_back(temp);
        }
        
        startTime = parsing[0];
        endTime = parsing[1];
        songTitle = parsing[2];
        musicInfo = parsing[3];
        
        musicInfo = trans_sharp(musicInfo);
        //cout << startTime << ' ' << endTime << ' ' << songTitle << ' ' << musicInfo << '\n';
        
        int endHour = stoi(endTime.substr(0, 2));
        int startHour = stoi(startTime.substr(0, 2));
        int endMinute = stoi(endTime.substr(3, 2));
        int startMinute = stoi(startTime.substr(3, 2));
        int playTime = calculatePlayTime(endHour-startHour, endMinute-startMinute);
        
        string totalMusicInfo ="";
        int idx = 0;
        
        int full = playTime / musicInfo.size();
        int part = playTime % musicInfo.size();
        for(int i=0; i<full; i++){
            totalMusicInfo+=musicInfo;
        }
        totalMusicInfo+=musicInfo.substr(0,part);
        
        if(totalMusicInfo.find(m)!=string::npos && playTime > maxPlayTime){
            answer = songTitle;
            maxPlayTime = playTime;
        }
        
    }
    
    return answer;
}
