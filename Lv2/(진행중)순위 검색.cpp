#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
using namespace std;
class Volunteer {
private:
    string language;
    string major;
    string old;
    string soulfood;
    int score;
public:
    Volunteer(string l, string m, string o, string s, int x) {
        language = l;
        major = m;
        old = o;
        soulfood = s;
        score = x;
    }
    string getLanguage() { return language; }
    string getMajor() { return major; }
    string getOld() { return old; }
    string getSoulFood() { return soulfood; }
    int getScore() { return score; }

    void setLanguage(string l) { language = l; }
    void setMajor(string m) { major = m; }
    void setOld(string o) { old = o; }
    void setSoulFood(string f) { soulfood = f; }
    void setScore(int x) { score = x; }
};
bool compare(Volunteer* a, Volunteer* b) {
    return (a->getScore() < b->getScore());
}
vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    vector<Volunteer*> volunteers;
    for (int i = 0; i < info.size(); i++) {
        string l, m, o, s;
        int x;
        
        stringstream ss(info[i]);
        string temp;
        vector<string> res;
        while (getline(ss, temp, ' ')) {
            res.push_back(temp);
        }
        Volunteer* v = new Volunteer(res[0], res[1], res[2], res[3], stoi(res[4]));
        volunteers.push_back(v);
    }
    sort(volunteers.begin(), volunteers.end(), compare);
    
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

        //volunteers에서 x라는 점수 이상인 사람들을 찾으면 됨. 
        int lo = 0, hi = volunteers.size();
        //50 80 150 150 210 260 이중에 100보다 높은 사람을 찾을꺼임
        //mid = 2
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (volunteers[mid]->getScore() < x) {//query에서 요구한 점수보다 중앙에 있는 사람의 점수가 낮을 때
                lo = mid + 1;
            }
            else {
                hi = mid;
            }
        }
        int count = 0;
        for (int j = lo; j < volunteers.size(); j++) {
            if (volunteers[j]->getLanguage() == l || l == "-") {
                if (volunteers[j]->getMajor() == m || m == "-") {
                    if (volunteers[j]->getOld() == o || o == "-") {
                        if (volunteers[j]->getSoulFood() == s || s == "-") {
                            count++;
                        }
                    }
                }
            }
        }
        answer.push_back(count);
    }

    return answer;
}
int main() {
    vector<string> info = { "java backend junior pizza 150","python frontend senior chicken 210","python frontend senior chicken 150","cpp backend senior pizza 260","java backend junior chicken 80","python backend senior chicken 50" };
    vector<string> query = { "java and backend and junior and pizza 100","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150" };
    solution(info, query); 
}
