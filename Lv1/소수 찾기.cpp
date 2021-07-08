#include <string>
#include <vector>
#include <cmath>
using namespace std;
//O(nloglogn) 시간 복잡도.
//이 거 왜 이렇 게 나 오 는지 확인 해 보 자.
int arr[1000001];

int solution(int n) {
    for(int i=1; i<=n; i++)
        arr[i] = i;
    int answer = 0;
    for(int i=2; i <= sqrt(n); i++){
        for(int j=2*i; j<=n; j+=i)
            
            arr[j] = 0;
    }
    for(int i=1; i<=n ;i++){
        if(arr[i]!= 1 && arr[i] != 0)
            answer++;
    }
    return answer;
}
