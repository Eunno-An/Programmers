//이거 진짜 중요한 문제
//캐스팅 관련해서 신경써야 할 부분(func 함수를 잘 보자)
#include<iostream>
using namespace std;

long long func(int w, int h, int x){
    long double tilt = (long double)h/ w;
    //cout << tilt * x  <<'\n'; 이렇게 해도 틀리고
    //return h * x / w 로 해도 틀린다.
    return (long long)h * x / w ; 
}
long long solution(int w,int h) {
    long long answer = 1;
    //1 <= w, h <= 1억
    
    //(0,0), (h, w)를 잇는 선 = f(x)
    
    //각 사각형이 있다고 가정했을 때, 
    //f(x)보다 아래에 있는 부분 = 각 정사각형(1*1)의 오른쪽 위의 사각형 좌표가 f(x)보다 밑에 있거나 같으면 사용 가능. 
    //f(x)보다 위에 있는 부분 = 각 정사각형의 왼쪽 아래 좌표가 f(x)보다 위에 있거나 같으면 사용 가능함
    //1억 * 1억 = time limit
    
    //2번 방법
    //대칭이니까 개수는 한쪽만 구하면 됨.
    
    long long ret = 0;
    for(int i=1; i<=w-1; i++){
        ret += func(w, h, i);
    }
    return ret *= 2;
}
