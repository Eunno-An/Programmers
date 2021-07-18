//#bitset의 사용방법에 대해서 중요!
#include <string>
#include <vector>
#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;


    for (int i = 0; i < numbers.size(); i++) {//10만
        long long x = numbers[i];
        //if x == 0?
        if (x == 0) {
            answer.push_back(3);
            continue;
        }
        int bitSize_x = log2(x) + 2;
        for (long long j = x + 1; ; j++) {
            int count = 0;
            /*
            1의비트의 수가 두개인거
            11, 101, 110, 1001, 1010, 1100, 10001, 10010, 10100, 11000, ...
            3, 5, 6, 9, 10, 12, 17, 18, 20, 24
            1의 비트의 수가 한개인거
            1, 10, 100, 1000, 10000, ...
            */
            long long num = (x ^ j);
            const int bitSize_of_num = log2(num) + 1;
            bool flag = false;
            for (int k = 1; k <= bitSize_of_num; k++) {
                if ((long long)pow(2, k-1) >= num) {
                    if ((long long)pow(2, k-1) == num) {
                        answer.push_back(j);
                        flag = true;
                    }
                    break;
                }
            }
            if (flag) {
                break;
            }
            bitset<56> two_bit_same;
            two_bit_same.reset();
            two_bit_same.flip(bitSize_of_num - 1);
            for (int k = 0; k < bitSize_of_num - 1; k++) {
                two_bit_same.flip(k);
                if (num == two_bit_same.to_ullong()) {
                    answer.push_back(j);
                    flag = true;
                    break;
                }
                two_bit_same.flip(k);
            }
            if (flag) {
                break;
            }
        }
    }
    return answer;
}
int main() {
    vector<long long>numbers = { 2, 7 };
    solution(numbers);
}
