#include <vector>
#include <map>
#include<iostream>
using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;
    map<int, int> m;
    for(int i=0; i<nums.size(); i++){
        if(m.find(nums[i]) == m.end()){
            m.insert(make_pair(nums[i], 1));
            //일단 중복되지 않은거 부터 우선 선택해야 하므로, answer++;
            answer++;
        }
    }
    //최대 개수는 nums.size()/2개
    //중복된 걸 최대한 안 선택한 경우, N/2개 보다 많을 수 있으므로
    //최대치인 nums.size()/2를 넘으면 그만!
    if(answer > nums.size()/2){
        answer = nums.size()/2;
    }
    return answer;
}
