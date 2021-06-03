#include<vector>
#include <cmath>

bool is_odd_measure(int number){
    int sqrt_num = sqrt(number);
    int num_measure = 0;
    for(int i=1; i<=number; i++){
        if(number % i == 0){
            num_measure++;
        }
    }
    if(num_measure % 2 == 0)
        return false;
    return true;
}
int solution(int left, int right) {
    int answer = 0;
    for(int i=left; i<=right; i++){
        if(is_odd_measure(i)){
            answer -=i;
        }else{
            answer += i;
        }
    }
    return answer;
}
