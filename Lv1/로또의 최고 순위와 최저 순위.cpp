#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    
    vector<int> answer;
    int base_count =0 ;
    int zero_count =0 ;
    for(int i=0; i<6; i++){
        if(lottos[i] == 0){
            zero_count++;
            continue;
        }   
        for(int j=0; j<6; j++)
            if(win_nums[j] == lottos[i])
                base_count++;    
    }
    if(base_count + zero_count <= 1 )
        answer.push_back(6);
    else
        answer.push_back(7 - (base_count+zero_count));
    if(base_count <= 1)
        answer.push_back(6);
    else
        answer.push_back(7 - base_count);
    return answer;
}
