#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

//N 사용횟수의 후보는 1부터 number*2 까지이다.
//N이 2 이상이면? N을 붙여서 쓰거나, N 사이사이에 괄호 또는 사칙연산을 넣는 것이 가능하다.
//N이 5고, 2번 사용했으면 그 후보는 55, 5 + 5, 5 - 5, 5 / 5, 5 * 5가 있다.
//3번 사용했으면 555, 5를 2번 이용한 결과 + 5, 5를 2번 이용한 결과 - 5, 5를 2번 이용한 결과 * 5, 5를 2번 이용한 결과 / 5, 또는 5 + 5를 2번 이용한 결과, 5 - 5를 2번 이용한 결과, 5 * 5를 2번 이용한 결과, 5 / 5를 2번 이용한 결과, 가 된다.
//우리는 괄호가 복잡하므로, 계산 순서에 상관없이 생각해 보자.
//근데 여기서 중복이 있다. 5를 2번 이용한 결과 '+' 5와 5 '+' 5를 2번 이용한 결과는 같나? 
// 5/5+5 != 5+5/5 , 5*5+5, 5+5*5, 5-5+5, 5+5-5, 5+5+5, 5+5+5 다르다.

//algorithm:
//N의 사용 횟수 후보만큼 돈다. 
map<string, long long> already_calculated_map;
pair<string, long long> getResult_FromFormula(string f) {//만들어진 공식이 기존에 있던 공식이면 바로 값을 반환하고, 그렇지 않다면 새로운 공식을 만들어서 map에 추가함.
    if (already_calculated_map.find(f) != already_calculated_map.end())
        return make_pair(f, already_calculated_map[f]);
    long long result = 0;
    vector<char> ops;
    vector<long long> numbers;
    int op_idx = -1;
    string number = "";
    for (int i = 0; i < f.size(); i++) {
        if (!isdigit(f[i])) {//연산자 일 경우
            string s = "";
            ops.push_back(f[i]);
            numbers.push_back(stol(number));
            number = "";
            op_idx = i;
        }
        else
            number += f[i];

    }
    numbers.push_back(stol(number));
    result = numbers[0];
    for (int i = 0; i < ops.size(); i++) {
        if (ops[i] == '+')
            result += numbers[i + 1];
        else if (ops[i] == '-')
            result -= numbers[i + 1];
        else if (ops[i] == '/')
            result /= numbers[i + 1];
        else if (ops[i] == '*')
            result *= numbers[i + 1];
    }
    already_calculated_map.insert(make_pair(f, result));
    return make_pair(f, result);
}
pair<string, long long> calculating(string f, int b, int op, bool isReverse) { // 기존 공식에 operator와 N을 더해서 새로운 공식을 만들고, 그로부터 계산 결과값을 반환함.
    string formula = "";
    if (isReverse) { // f op b 순서
        formula = f;
        if (op == 0)
            formula += "+";
        else if (op == 1)
            formula += "-";
        else if (op == 2)
            formula += "*";
        else if (op == 3)
            formula += "/";
        formula += to_string(b);
    }
    else {//b op f 순서
        formula = to_string(b);
        if (op == 0)
            formula += "+";
        else if (op == 1)
            formula += "-";
        else if (op == 2)
            formula += "*";
        else if (op == 3)
            formula += "/";
        formula += f;
    }
    long long result = 0;
    pair<string, long long> result_pair;
    result_pair.first = f;
    result_pair.second = result;
    return result_pair = getResult_FromFormula(formula);
}
int solution(int N, int number) {
    int answer = 0;
    vector<vector<string>> formulas(number * 2 + 1);
    //formulas[i]에는 N을 i번 만큼 사용했을 때 들어갈 수 있는 값의 후보들이 들어간다.
    //그렇다면 formulas[i+1]에는 기존의 formulas[i]에 있었던 값들에 4번 + 4번의 사칙연산을 적용한 값들과, N을 i+1번 붙인 값이 들어간다.

    //5
    //
    if (N == number)
        return 1;
    formulas[1].push_back(to_string(N));
    for (int use_N = 1; use_N < number * 2; use_N++) {
        if (use_N == 8)
            return -1; //최솟값이 8보다 크면 -1을 리턴하라. 왜냐하면 수의 범위 때문에 그런듯 하다.

        for (int before = 0; before < formulas[use_N].size(); before++) {
            string formula = formulas[use_N][before];
            for (int op = 0; op < 4; op++) {
                pair<string, long long> result = calculating(formula, N, op, true);
                if (result.second == number)
                    return answer = use_N + 1;

                formulas[use_N + 1].push_back(result.first);
            }
            if (use_N > 2)
                for (int op = 0; op < 4; op++) {
                    pair<string, long long> result = calculating(formula, N, op, false);
                    if (result.second == number)
                        return answer = use_N + 1;
                    formulas[use_N + 1].push_back(result.first);
                }
        }
        string number_str = "";
        for (int i = 0; i <= use_N; i++) //N을 i+1번 붙인 값을 formulas[i+1]에 넣는다. 
            number_str += to_string(N);
        if (to_string(number) == number_str)
            return use_N + 1;
        formulas[use_N + 1].push_back(number_str);

    }
    return answer;
}
int main() {
    solution(5, 5);
}
