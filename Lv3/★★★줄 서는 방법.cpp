//중복된게 없고, 단순히 줄을 나열시켰을 때, 몇번째 경우의 줄 상태를 나타내시오 라는 문제.
//next_permutation을 쓰면 시간 초과.
//greedy 테크닉으로 (n-1)!보다 k가 크면 앞에 수는 어쨌든 그 다음 수라는게 보장이 된다는 성질을 이용한 문제.
//그리고 반드시 dp[0] = 1 처리를 해 주어야 함.
#include <string>
#include <vector>

using namespace std;
bool visit[10];
long long dp[21];
long long factorial(int n){
    if(dp[n])
        return dp[n];
    return dp[n] = n * factorial(n-1);
}
vector<int> solution(int n, long long k) {
    vector<int> answer;
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    
    
    vector<int> numbers;
    for(int i=1; i<=n; i++)
        numbers.push_back(i);
    
    while(!numbers.empty()){
        int frontIdx = 0;
        long long fact = factorial(n-1); // n-1개를 나열했을때 경우의 수
        while(k-fact > 0){
            k -= fact;
            frontIdx++;
        }
        answer.push_back(numbers[frontIdx]);
        numbers.erase(numbers.begin() + frontIdx);
        n -= 1;
    }
    return answer;
}
