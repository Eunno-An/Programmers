#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
using namespace std;

//문제의 원인들
//(long long)stoi(num1) -> core dump의 원인. stol을 쓰자.
//str1.find(str2)를 쓸 때, 없음을 나타내고 싶을 때는 string::npos와 비교하자.
/*
그리고 next_permutation(s.begin(), s.end())를 쓸 때!!
만약 s가 정렬이 안되어 있으면 이상한 결과를 나타낼 수가 있다.
이게 무슨말이냐, s가 1234면 next_permutation시에 1234 1243... 4321 까지의 경우를 정상적으로 반환하지만,
s가 애초에 4123 같은거면, 큰 요소가 앞에 있으므로 4123부터의 경우를 반환해 버린다!
이 점을 명심하자.
*/
long long calc(string num1, string num2, char op) {
    if (op == '+') {
        return (long long)stol(num1) + (long long)stol(num2);
    }
    else if (op == '-') {
        return (long long)stol(num1) - (long long)stol(num2);
    }
    else  {
        return (long long)stol(num1) * (long long)stol(num2);
    }
}
long long solution(string expression) {
    long long answer = 0;
    string operators = "";



    long long max_val = -2;
    deque<string> d1;
    string temp = "";
    for (int i = 0; i < expression.size(); i++) {
        if (!isdigit(expression[i])) {
            d1.push_back(temp);
            if (operators.empty())
                operators += expression[i];
            else if (operators.find(expression[i]) == string::npos) {
                operators += expression[i];
            }
            d1.push_back(string(1, expression[i]));
            temp = "";
        }
        else {
            temp += expression[i];
        }
    }
    d1.push_back(temp);
    deque<string>d3=d1;
    sort(operators.begin(), operators.end());
    string copy_operators = operators;
    do {
        operators = copy_operators;
        
        
        d1 = d3;
        
        
        for (int i = 0; i < operators.size(); i++) {
            deque<string> d2;
            while (!d1.empty()) {
                if (d1.front() == string(1, operators[i])) {
                    string operand1 = d2.back();
                    string operand2 = d1[1];
                    long long res = calc(operand1, operand2, d1[0][0]);

                    d1.pop_front();



                    d1.pop_front();


                    d2.pop_back();

                    d2.push_back(to_string(res));
                }
                else {
                    d2.push_back(d1.front());

                    d1.pop_front();

                }


            }
            d1 = d2;

        }
        long long result = (long long)stol(d1.back());
        if (result < 0)
            result *= -1;
        if (max_val < result)
            max_val = result;

    } while (next_permutation(copy_operators.begin(), copy_operators.end()));
    return max_val;
}
int main() {

    solution("50*6-3*2");
}
