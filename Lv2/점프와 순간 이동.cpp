#include <iostream>
using namespace std;

int solution(int n)
{
    int ans = 0;
    
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    cout << "Hello Cpp" << endl;
    //N 
   
    while(n != 0){
        if(n%2)
            ans++;
        n = n/2;
    }
    /*
    5 = 1 4 = 1 2 w = 1 1 w w
    6 = 1w1w = 3 w = 1 2 w = 1 1 w w
    5000 = 2500w = 1250ww = 625www = 1,624www = 1 312wwww = 1 156wwwww = 1 78wwwwww = 1 39 wwwwwww
    = 1 1 19 wwwwwww = 1 1 1 9 wwwwwwww = 1 1 1 1 4 wwwwwwwww = 1 1 1 1 2 wwwwwwwwww = 1 1 1 1 1
    */
    return ans;
}
