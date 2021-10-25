#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(int k, vector<vector<int>> dungeons) {
    int answer = -1;
    answer = 0;
    vector<int> permutations;
    for(int i=0; i<dungeons.size(); i++)
        permutations.push_back(i);
    int max_num = -1;
    int temp_k = k;
    do{
        int num = 0;
        for(int i=0; i<permutations.size(); i++){
            int idx = permutations[i];//idx번째 던전
            int minimum_tired = dungeons[idx][0];
            int need_tired = dungeons[idx][1];
            if(k >= minimum_tired){
                k -= need_tired;
                num++;
            }
            else
                break;
            
        }
        if(max_num < num)
            max_num = num;
        k = temp_k;
    }while(next_permutation(permutations.begin(), permutations.end()));
    return answer=max_num;
}
