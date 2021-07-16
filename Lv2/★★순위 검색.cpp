#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <map>
#include<unordered_map>
using namespace std;

/*알고리즘
info를 순회하면서 문자열 파싱 후에 모든 경우의 수(16가지=24 )에 점수를 넣는다.
ex. "javabackendjuniorpizza" [150], "-backendjuniorpizza" [150], ... ,
(저는 중복된 것은 알아서 넣어지도록 저는 C++의 map 컨테이너(key, value) 사용했습니다, value는 vector<int>)

모든 map의 key에 대해서 순회하면서 오름차순 정렬(처음에 빨리 짜다가 query 순회하면서 했다가 시간초과 났어요... 먼저 해주세요!)

query를 순회하면서 query 정보를 문자열 파싱.

해당 문자열을 key로 map에 접근해서 정렬돼있는 배열 뽑아와서 이분탐색.
*/

/*효율성
아래와 같은 식으로 했었다가 시간초과 났었음.
unordered_map<string, vector<int>> getMapKey(vector<string>& v) {
    unordered_map<string, vector<int>> ret = map_v;
    for (int i = 0; i < v.size(); i++) {
        vector<bool> choice(v.size() - 1 - i, false);
        choice.insert(choice.end(), i, true);
        int count = 0;
        do {
            string result = "";
            for (int j = 0; j < choice.size(); j++) {
                if (choice[j]) result += v[j];
                else result += "-";
            }

            if (ret.find(result) == ret.end()) {
                vector<int> input;
                input.push_back(stoi(v.back()));
                ret.insert(make_pair(result, input));
            }
            else {
                ret[result].push_back(stoi(v.back()));
            }
            cout << count++ << endl;
        } while (next_permutation(choice.begin(), choice.end()));
    }
    return ret;
}
이런식으로 바꾸니 시간초과가 나지 않음
void setMap(vector<string>& v) {
    for (int i = 0; i < 16; i++) {
        string tmp = "";
        for (int j = 0; j < 4; j++) {
            if (i & (1 << j)) tmp.push_back('-'); //i의 j번째 비트가 set되었는지 확인하기.
            else tmp += v[j];
        }
        if (map_v.find(tmp) == map_v.end()) {
            vector<int> input;
            input.push_back(stoi(v.back()));
            map_v.insert(make_pair(tmp, input));
        }
        else {
            map_v[tmp].push_back(stoi(v.back()));
        }
    }
    
}
그리고 136번째 ~ 138번째 줄도 잘 보기.
*/
unordered_map<string, vector<int>> map_v;
void setMap(vector<string>& v) {
    for (int i = 0; i < 16; i++) {
        string tmp = "";
        for (int j = 0; j < 4; j++) {
            if (i & (1 << j)) tmp.push_back('-');
            else tmp += v[j];
        }
        if (map_v.find(tmp) == map_v.end()) {
            vector<int> input;
            input.push_back(stoi(v.back()));
            map_v.insert(make_pair(tmp, input));
        }
        else {
            map_v[tmp].push_back(stoi(v.back()));
        }
    }
    
}
vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
   
    for (int i = 0; i < info.size(); i++) {
        string l, m, o, s;
        int x;

        stringstream ss(info[i]);
        string temp;
        vector<string> res;
        while (getline(ss, temp, ' ')) {
            res.push_back(temp);
        }

        setMap(res);

    }

    for (unordered_map<string, vector<int>>::iterator it = map_v.begin(); it != map_v.end(); it++) {
        sort(it->second.begin(), it->second.end());
        /*cout << "Key is " << it->first << '\n';
        for (int i = 0; i < it->second.size(); i++) {
            cout << it->second[i] << ' ';
        }
        cout << endl;*/
    }
    

    for (int i = 0; i < query.size(); i++) {
        string l, m, o, s;
        int x;
        stringstream ss(query[i]);
        string temp;
        vector<string> res;
        while (getline(ss, temp, ' ')) {
            res.push_back(temp);
        }
        l = res[0];
        m = res[2];
        o = res[4];
        s = res[6];
        x = stoi(res[7]);

        string key_value = l + m + o + s;

        
        int count = lower_bound(map_v[key_value].begin(), map_v[key_value].end(), x) - map_v[key_value].begin();
        if (count == map_v[key_value].size()) answer.push_back(0);
        else answer.push_back(map_v[key_value].size() - count);
        
    }

    return answer;
}
int main() {
    vector<string> info = { "java backend junior pizza 150","python frontend senior chicken 210","python frontend senior chicken 150","cpp backend senior pizza 260","java backend junior chicken 80","python backend senior chicken 50" };
    vector<string> query = { "java and backend and junior and pizza 100","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150" };
    solution(info, query);
}
