#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    for(int i=0;i <commands.size(); i++){
        int first_idx = commands[i][0];
        int second_idx = commands[i][1];
        int third_idx = commands[i][2];
        vector<int> temp;
        for(int j=first_idx-1; j<second_idx; j++){
            temp.push_back(array[j]);
        }
        sort(temp.begin(), temp.end());
        answer.push_back(temp[third_idx-1]);
    }
    return answer;
}
