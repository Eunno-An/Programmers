//fail
//나눗셈에 대한 예외처리 하였음.
//1. 1번에 대한 예외처리: 8,53 -> 8*8 - 88/8로 해야 하는데, 그럴 경우 N=3, N=2로 각각 계산한 결과를 뺴 주어야 함. 근데 난 무지성으로 앞에서 부터 훑어 버렸고, 답이 제대로 나올 수가 없었음.
//2. 4~7번에 대한 예외처리: N=4일 경우, 기존에 세개를 쓰던 방법에서 하나를 추가하는 방법으로 했지만, 생각해보니 2, 2인 경우도 생각해 주어야 했음.
//3. 8번에 대한 예외처리 진행중.
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
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
pair<string, long long> calculating(string f, string f2, int op) { // 기존 공식에 operator와 N을 더해서 새로운 공식을 만들고, 그로부터 계산 결과값을 반환함.
    string formula = "";

    formula = f;
    pair<string, long long> res1 = getResult_FromFormula(f);
    pair<string, long long> res2 = getResult_FromFormula(f2);
    long long res_num = res1.second;
    if (op == 0) {
        formula += "+";
        res_num += res2.second;
    }
    else if (op == 1) {
        formula += "-";
        res_num -= res2.second;
    }
        
    else if (op == 2) {
        formula += "*";
        res_num *= res2.second;
    }
    else if (op == 3 && res2.second != 0) {
        formula += "/";
        res_num /= res2.second;
    }
    if (op != 3 || res2.second != 0)
        formula += f2;
    pair<string, long long> result_pair;
    result_pair.first = formula;
    result_pair.second = res_num;
    return result_pair;
}
int solution(int N, int number) {
    int answer = 1;
    vector<vector<string>> formulas(number * 2 + 1);
    //formulas[i]에는 N을 i번 만큼 사용했을 때 들어갈 수 있는 값의 후보들이 들어간다.
    //그렇다면 formulas[i+1]에는 기존의 formulas[i]에 있었던 값들에 4번 + 4번의 사칙연산을 적용한 값들과, N을 i+1번 붙인 값이 들어간다.

    //5
    //
    if (N == number)
        return 1;
    formulas[1].push_back(to_string(N));

    for (int use_N = 2; use_N < 10; use_N++) {
        if (use_N == 9)
            return -1; // 최솟값이 8보다 클 경우, -1을 리턴한다.
        string number_str = "";
        for (int i = 0; i < use_N; i++) //N을 use_N번 붙인 값을 formulas[i+1]에 넣는다. 
            number_str += to_string(N);
        if (to_string(number) == number_str)
            return use_N;
        formulas[use_N].push_back(number_str);
        for (int first = 1; first < use_N; first++) {//first = 기존에 사용한 N의 개수. 이건 formulas[first]에 저장되어 있는 식이다.

            vector<string> formulas_first = formulas[first];
            vector<string> formulas_second = formulas[use_N - first];
            for (int i = 0; i < formulas_first.size(); i++) {
                string formula1 = formulas_first[i];
                for (int j = 0; j < formulas_second.size(); j++) {
                    string formula2 = formulas_second[j];
                    for (int op = 0; op < 4; op++) {
                        pair<string, long long> result = calculating(formula1, formula2, op);
                        if (result.second == number)
                            return answer = use_N;
                        formulas[use_N].push_back(result.first);
                        string temp = result.first;
                        result = calculating(formula2, formula1, op);
                        if (result.second == number)
                            return answer = use_N;
                        if (temp != result.first)
                            formulas[use_N].push_back(result.first);
                    }
                }
            }

        }
        sort(formulas[use_N].begin(), formulas[use_N].end());
        formulas[use_N].erase(unique(formulas[use_N].begin(), formulas[use_N].end()), formulas[use_N].end());
    }


    return -1;
}
int main() {
    solution(8, 53);
}
