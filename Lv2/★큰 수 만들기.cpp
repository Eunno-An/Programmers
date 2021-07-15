#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) {
    string answer = "";
    //현재 우리가 선택한 단어의 길이 = answer.size(), 나중에 우리가 선택해야 할 단어의 개수 number.size()-k-answer.size()
    //[start, end)에서 어떤 값 max_val을 선택했을 때, 그 인덱스를 max_idx라고 하자.
    //max_idx+1부터 number.size()-1까지의 개수는 number.size()-1-max_idx-1+1 = number.size()-max_idx-1
    //이게 우리가 뽑을 수 있는 가짓수고, 이것들 중에서 하나를 담아야 함.
    
    
    //두번째 예시
    //우린 2번 인덱스의 3을 선택했을 때, 3번 인덱스부터 있는 값들인 1234 들 중에서 세개를 뽑아야 함.
    //그럼 최대 몇개를 남겨놔야 하나? 우린 현재 단계에서 세개를 뽑아야 하지만, 뒤에 있는거에는 최소 두개를 남겨놔야함.
    //그럼 end는 k - answer.size()가 되겠군.
    int returnSize = number.size() - k; //결과의 길이
    int start = 0;
    int end = number.size()-returnSize+1;
    while(answer.size() != number.size() - k){
        int max_idx = 0;
        int max_val = -1;//max_val이 반드시 -1이어야 함. 자연수만 들어가 있는게 아니라 0부터거든
        for(int i = start; i<end; i++){
            if(max_val < (number[i] - '0')){
                max_val = (number[i] - '0');
                max_idx = i;
            }
        }
        answer += to_string(max_val);
        returnSize--;
        start = max_idx+1;
        end = number.size()-returnSize+1;
    }
    return answer;
}
