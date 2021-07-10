//네이버에서 -9 mod 2 하면 1이 나오는데
//visual에서는 -1이 나온다..

#include <string>
#include <vector>
#include <iostream>
using namespace std;

string solution(int num) {
    string answer = "";
    int res = num%2;
    //cout << -9 % 2 << '\n';
    if(num < 0){
        return res == -1 ? "Odd" : "Even";
    }else{
        return (res == 1 ?"Odd" : "Even");    
    }
    
}
