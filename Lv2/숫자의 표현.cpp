//fail
//연속한 수의 합 공식을 그냥 구현만 하면 되는건데.. 쫄았음..
#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    for(int first = 1; first < n; first++){
        for(int end = first + 1; end < n; end++){
            int number = (first + end) * (end - first + 1);
            if(number == 2 * n){
                answer++;
                break;
            }
            else if(number > 2 *n)
                break;
            
            
        }
    }
    


    return answer+1;
}
