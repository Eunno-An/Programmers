#include <string>
#include <vector>

using namespace std;
int dfs(string begin, string target, int idx, vector<string> words, vector<bool> visit) {
    if (begin == target)
        return 0;
    
    int ret = 101;
    for (int i = 0; i < words.size(); i++) {
        if (visit[i]) continue;
       
        int unmatch = 0;
        for (int j = 0; j < words[i].size(); j++)
            if (begin[j] != words[i][j])
                unmatch++;
        if (unmatch == 1) {
            visit[i] = true;
            ret = min(ret, 1 + dfs(words[i], target, i, words, visit));
            visit[i] = false;
        }
    }
    
    return ret;
}
int solution(string begin, string target, vector<string> words) {
    vector<bool> visit(words.size(), false);
    int answer = 0;
    answer = dfs(begin, target, 0, words, visit);
    return answer >= 101 ? 0 : answer;
}
int main() {
    solution("hit", "cog", { "hot", "dot", "dog", "lot", "log", "cog" });
}
