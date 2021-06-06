#include <string>
#include <vector>

using namespace std;

long long solution(int a, int b) {
    long long answer = 0;
    int min_num = a < b ? a : b;
    int max_num = a < b ? b : a;
    for(int i=min_num; i<=max_num; i++){
        answer += i;    
    }
    return answer;
}
