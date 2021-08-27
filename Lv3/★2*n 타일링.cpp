#include <string>
#include <vector>

using namespace std;
//기저조건
//if(n is 1) : 1
//if(n is 2) : 2
//if(n is 3) : 3 (2 1 또는 1 2 또는 1 1 1)
//if(n is 4) : solve(2) + solve(3)
//if(n is 홀수)
//if(n is 짝수) = solve(n-2) + solve(n-4) // 양 끝에 세로로 한개씩 세워 놓는 경우 + 한쪽 끝을 가로로 두개 채워놓는 경우 * 2 
int fibo[60001];
int fibonacci(int n){
    if(fibo[n])
        return fibo[n];
    return fibo[n] = (fibonacci(n-1) % 1000000007 + fibonacci(n-2) % 1000000007) % 1000000007;
}
int solution(int n) {
    int answer = 0;
    fibo[1] = 1;
    fibo[2] = 2;
    answer = fibonacci(n);
    return answer;
}
