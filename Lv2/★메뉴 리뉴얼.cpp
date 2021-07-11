#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

//메모리 초과의 이유: 16번째 줄 orders[j].size() -course[i]< 0 라고 하니까 디버그 에러뜸..
//26번째 줄: 그리고 XY, YX 처럼 들어올 때도 있으니, 일관성을 위해 temp를 sorting해주어야 함.
vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    //cout << "Hello World!\n";

    for (int i = 0; i < course.size(); i++) {
        int sizeSet = course[i];
        map<string, int> set_menu;
        for (int j = 0; j < orders.size(); j++) {
            //orders[j]에 있는 요소들을 조합으로 뽑는다.
            if (orders[j].size() < course[i]) // orders[j].size() -course[i]< 0 라고 하니까 디버그 에러뜨네
                continue;
            vector<bool> v(orders[j].size() - course[i], 0);
            v.insert(v.end(), course[i], 1);
            do {
                string temp = "";
                for (int k = 0; k < v.size(); k++)
                    if (v[k]) temp += orders[j][k];
                sort(temp.begin(), temp.end());//3번 케이스
                if (set_menu.find(temp) == set_menu.end()) {
                    set_menu.insert(make_pair(temp, 1));
                }
                else {
                    set_menu[temp]++;
                }
            } while (next_permutation(v.begin(), v.end()));
        }
        vector<string> res_vec;
        int max_val = -1;
        for (map<string, int>::iterator it = set_menu.begin(); it != set_menu.end(); it++) {
            if (it->second > max_val && it->second != 1) {
                res_vec.clear();
                max_val = it->second;
                res_vec.push_back(it->first);
            }
            else if (it->second == max_val && it->second != 1)
                res_vec.push_back(it->first);
        }
        for (int j = 0; j < res_vec.size(); j++) {
            answer.push_back(res_vec[j]);
        }
        set_menu.clear();
    }
    sort(answer.begin(), answer.end());
    return answer;
}
int main() {
    vector<string> a = { "ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH" };
    vector<int> b = { 2, 3, 4 };
    solution(a, b);
}
