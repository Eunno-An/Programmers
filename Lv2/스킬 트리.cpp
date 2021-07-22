#include <string>
#include <vector>

using namespace std;
int arr[26];

int solution(string skill, vector<string> skill_trees) {
    int answer = 0;
    for (int i = 0; i < skill.size(); i++) {
        arr[skill[i] - 65] = i + 1;
    }
    
    for (int i = 0; i < skill_trees.size(); i++) {
        string temp = "";
        for (int j = 0; j < skill_trees[i].size(); j++) {
            if (arr[skill_trees[i][j] - 65] == 0)
                continue;
            temp += skill_trees[i][j];
        }
        skill_trees[i] = temp;
    }
    for (int i = 0; i < skill_trees.size(); i++) {
        string user_skillTree = skill_trees[i];
        int skillIdx = 1;
        bool able = true;
        for (int j = 0; j < user_skillTree.size(); j++) {
            if (arr[user_skillTree[j] - 65] == skillIdx) {
                skillIdx++;
            }
            else {
                able = false;
                break;
            }
        }
        if (able) {
            answer++;
        }
    }
    return answer;
}
int main() {
    solution("CBD", { "BACDE", "CBADF", "AECB", "BDA" });
}
