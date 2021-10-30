//auto 와 sort 사용시 정렬이 안되는 문제. 이슈로 남겨놓겠음.
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
bool compare(pair<int, int>& a, pair<int, int>& b) {
    if (a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}
bool compare2(pair<string, int> a, pair<string, int> b) {
    return a.second > b.second;
}
vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    map<string, vector<pair<int, int>>> streaming;
    for (int i = 0; i < genres.size(); i++) {
        //genres와 plays의 길이는 같으며, 1 이상 10,000이하이다.
        string genreName = genres[i];
        int playCount = plays[i];
        if (streaming.find(genreName) == streaming.end()) {
            streaming.insert(make_pair(genreName, vector<pair<int, int>>()));
            streaming[genreName].push_back(make_pair(i, playCount));
        }
        else 
            streaming[genreName].push_back(make_pair(i, playCount));
    }
    //auto 뒤에 & 안붙이면 소용이 없음.
    for (auto & it : streaming) 
        sort(it.second.begin(), it.second.end(), compare);
    
    vector<pair<string, int>> genre_sort_by_playCount;
    for (auto it : streaming) {
        string genreName = it.first;
        int totalPlayCount = 0;
        for (auto it2 : it.second)
            totalPlayCount += it2.second;
        genre_sort_by_playCount.push_back(make_pair(genreName, totalPlayCount));
    }

    sort(genre_sort_by_playCount.begin(), genre_sort_by_playCount.end(), compare2);
    for (int i = 0; i < genre_sort_by_playCount.size(); i++) {
        string firstGenre = genre_sort_by_playCount[i].first;
        int pushCount = 0; // 수록곡은 각 트랙 당 두번
        for (auto it : streaming[firstGenre]) {
            answer.push_back(it.first);
            pushCount++;
            if (pushCount == 2)
                break;
        }
            
    }
    return answer;
}
int main() {
    solution({ "classic", "pop", "classic", "classic", "pop" }, { 500, 600, 150, 800, 2500 });
}
