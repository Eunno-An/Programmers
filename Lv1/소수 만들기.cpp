#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
// 조합으로 풀면 안됨! 왜냐하면 50_C_3 이니까!
// 그냥 3개로 정해져 있으니까 3중 for문으로 돌려라.
// prime 체크 하는 법만 알면 쉽다.
bool check_prime(int number){
    int x = sqrt(number);
    for(int i=2; i<=x; i++){
        if(number % i == 0){
            return false;
        }
    }
    return true;
}
int solution(vector<int> nums) {
    int answer = -1;
    answer=0;
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    //cout << "Hello Cpp" << endl;
    for(int i=0; i<nums.size(); i++){
        for(int j=i+1; j<nums.size(); j++){
            for(int k=j+1; k<nums.size(); k++){
                int result = nums[i] + nums[j] + nums[k];
                if(check_prime(result))
                    answer++;
            }
        }
    }
    return answer;
}
