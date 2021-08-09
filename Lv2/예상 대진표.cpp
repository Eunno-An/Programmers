#include <iostream>

using namespace std;

int solution(int n, int a, int b)
{
    int answer = 0;

    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    cout << "Hello Cpp" << endl;
    while(a != b){
        answer++;
        if(a != 1){
            if(a%2) a+=1;
            a/=2;
        }
        if(b != 1){
            if(b%2) b+=1;
            b/=2;
        }
    }
    return answer;
}
