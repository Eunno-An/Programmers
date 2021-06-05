#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//벡터 중복요소 지우기
//unique(answer.begin(), answer.end()) -> 중복 요소 중 남는 요소를 뒤에다 보내고, 그 값들의 시작 위치를 반환함.
//answer.erase(unique(answer.begin(), answer.end()), answer.end()) -> unique에서 반환한 값부터 end까지 요소를 지움.
vector<int> solution(vector<int> numbers) {
    vector<int> answer;
    for(int i=0; i<numbers.size(); i++){
        for(int j=0; j<numbers.size(); j++){
            if(i != j){
                answer.push_back(numbers[i]+numbers[j]);
            }
        }
    }
    sort(answer.begin(), answer.end());
    answer.erase(unique(answer.begin(), answer.end()), answer.end());
    return answer;
}
