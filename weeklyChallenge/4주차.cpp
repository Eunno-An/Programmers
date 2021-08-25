#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;


void init_dict_preference(map<string, int>& dict_preference, vector<string> languages, vector<int> preference) {
    for (int i = 0; i < preference.size(); i++)
        dict_preference.insert(make_pair(languages[i], preference[i]));
}
void init_vocational_language_score(map<string, vector<int>>& vocational_language_score, vector<string> table, vector<string> languages, map<string, int> dict_preference) {
    vector<int> a;
    for (auto it : dict_preference)
        vocational_language_score.insert(make_pair(it.first, a));
    //vocational_language_score
    //key : language
    //value: points
    //JAVA : n1 n2 n3 n4 n5(앞에서부터 SI, CONTENTS, HARDWARE, PORTAL, GAME)
    vector < vector<pair<string, int>>> original_vocational_language_score;
    for (int job = 0; job < table.size(); job++) {
        string job_info = table[job];
        stringstream ss(job_info);
        string temp;
        vector<pair<string, int>> res;
        int point = 6;
        while (getline(ss, temp, ' '))
            res.push_back(make_pair(temp, point--));
        res.erase(res.begin());
        original_vocational_language_score.push_back(res);
    }
    //JAVA,5 JAVASCRIPT,4 SQL,3 PYTHON,2 C#,1
    //JAVASCRIPT JAVA PYTHON ...
    
    //파이썬, C++, SQL만 사용해야 함.
    for (int i = 0; i < original_vocational_language_score.size(); i++) {
        for (int j = 0; j < original_vocational_language_score[i].size(); j++)
            for (int k = 0; k < languages.size(); k++)
                if (original_vocational_language_score[i][j].first == languages[k])
                    vocational_language_score[languages[k]].push_back(original_vocational_language_score[i][j].second);
        for (int j = 0; j < languages.size(); j++)
            if (vocational_language_score[languages[j]].size() != i + 1)
                vocational_language_score[languages[j]].push_back(0);
    }
            
    //PYTHON: 2 
    //C++: 
    //SQL: 3
    
    return;
}
bool compare(pair<string, int> a, pair<string, int> b) {
    if (a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}
string solution(vector<string> table, vector<string> languages, vector<int> preference) {
    map<string, int> dict_preference;
    map<string, vector<int>> vocational_language_score;//직업군 언어 점수


    init_dict_preference(dict_preference, languages, preference);
    init_vocational_language_score(vocational_language_score, table, languages, dict_preference);

    vector<pair<string, int>> jobs;
    jobs.push_back(make_pair("SI", 0));
    jobs.push_back(make_pair("CONTENTS", 0));
    jobs.push_back(make_pair("HARDWARE", 0));
    jobs.push_back(make_pair("PORTAL", 0));
    jobs.push_back(make_pair("GAME", 0));
    for (auto it : vocational_language_score) 
        for (int i = 0; i < it.second.size(); i++) 
            jobs[i].second += (it.second[i] * dict_preference[it.first]);
    
    sort(jobs.begin(), jobs.end(), compare);
    string answer = "";
    answer = jobs.front().first;
    return answer;
}
int main() {
    solution({ "SI JAVA JAVASCRIPT SQL PYTHON C#", "CONTENTS JAVASCRIPT JAVA PYTHON SQL C++", "HARDWARE C C++ PYTHON JAVA JAVASCRIPT", "PORTAL JAVA JAVASCRIPT PYTHON KOTLIN PHP", "GAME C++ C# JAVASCRIPT C JAVA" }
    , { "PYTHON", "C++", "SQL" }, { 7, 5, 5 });
}
