#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

string solution(string m, vector<string> musicinfos) {
    string answer = "";
    //m: 네오가 기억한 멜로디를 담은 문자열
    //musicinfos = 방송된 곡의 정보를 담고 있는 배열
    answer = "(None)";
    for(int i=0; i<musicinfos.size(); i++){
        stringstream ss(musicinfos[i]);
        string temp;
        vector<string> song_info;
        while(getline(ss, temp, ',')){
            song_info.push_back(temp);
        }
        
        string startTime = song_info[0];
        string endTime = song_info[1];
        string songTitle = song_info[2];
        string info = song_info[3];
        //cout << startTime << ' ' << endTime << ' ' << songTitle << ' ' << info << '\n';
        //조건이 일치하는 음악이 여러 개일 때에는 라디오에서 재생된 시간이 제일 긴 음악 제목을 반환한다. 재생된 시간도 같을 경우 먼저 입력된 음악 제목을 반환한다.
        
        
        // O(1439)*O(1439)*O(100) 으로 해야 할듯. 즉,악보 정보를 이어 붙이지 말고, 순회하면서 돌아야 함.
    }
    
    return answer;
}
