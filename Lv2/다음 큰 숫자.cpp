#include <string>
#include <vector>
#include <bitset>
using namespace std;
//bitset 연습
int solution(int n) {
    int answer = 0;
    bitset<20> bit(n);
    int n_count = bit.count();
    for(int i=n+1; ; i++){
        bitset<20> bit2(i);
        if(n_count == bit2.count()){
            answer = i;
            break;
        }         
    }
    return answer;
}
