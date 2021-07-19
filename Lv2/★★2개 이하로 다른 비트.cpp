#include <string>
#include <vector>
#include <bitset>
using namespace std;

/*
bitset의 사용 방법에 대해서 배웠던 중요한 문제이다.

0번째를 제외하고, 최적의 경우의 수는
비트가 0인 것을 찾는다.
0번째 비트가 0일때는 1로만 바꿔주고, 아니라면
i번째 비트를 1으로 바꾸고, 그 뒤에 있는 비트를 0으로 한다.
*/
vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    for(int i=0; i<numbers.size(); i++){
        long long n = numbers[i];
        bitset<50> b = bitset<50>(n);
        for(int j=0; j<b.size(); j++){//bitset 뒤에서부터가 0번째임. 25는 00000...00011001 이니까 0번째 비트는 맨 뒤의 1
            if(b[j] == 0){
                if(j == 0)
                    b[j] = 1;
                else{
                    b[j] = 1;
                    b[j-1] = 0;
                }
                break;
            }
        }
        answer.push_back(b.to_ulong());
    }
    return answer;
}
