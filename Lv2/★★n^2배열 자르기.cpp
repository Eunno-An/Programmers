//18번째 줄, 임시변수로 잡아야 함. 가끔 하는 실수였음.
//19번째 줄 처럼 하면 안됨.
#include <string>
#include <vector>

using namespace std;
vector<int> get_elements_row_i(int n, int row_idx) {
    vector<int> ret;
    //n이 3이고, row_idx가 1이면
    //223
    //n이 4고 row_idx가 2면
    //3334
    //n이 3이고, row_idx가 0이면?
    int count = row_idx;
    for (int i = 0; i <= row_idx; i++)
        ret.push_back(row_idx + 1);
    for (int i = 1; i < (n - row_idx); i++)
        ret.push_back(++count + 1);
  //ret.push_back(++row_idx + 1);
    return ret;
}
vector<int> solution(int n, long long left, long long right) {
    vector<int> answer;
    //몇 행인지 따져보기
    long long total_element = (long long)n * n;
    int row_idx_left, row_idx_right;

    row_idx_left = left / n;
    row_idx_right = right / n;
    //몇 열인지 따져보기
    int col_idx_left, col_idx_right;
    col_idx_left = left % n;
    col_idx_right = right % n;

    //i번째 수들 = (i+1)이 (i+1)개 있고, (i+2)부터 n까지 각 숫자가 한개 씩 존재함.
    vector<int> elements_i = get_elements_row_i(n, row_idx_left);
    if (row_idx_left == row_idx_right) {
        for (int i = col_idx_left; i <= col_idx_right; i++)
            answer.push_back(elements_i[i]);
    }
    else {
        for (int i = col_idx_left; i < n; i++)
            answer.push_back(elements_i[i]);//해당되는 첫 줄의 요소들을 넣어준다.
        for (int i = row_idx_left + 1; i < row_idx_right; i++) {//그 다음줄 부터 마지막 줄 이전까지 요소들을 더해준다.
            elements_i = get_elements_row_i(n, i);
            for (int j = 0; j < n; j++)
                answer.push_back(elements_i[j]);
        }
        elements_i = get_elements_row_i(n, row_idx_right);
        for (int i = 0; i <= col_idx_right; i++)//마지막 줄의 요소들을 넣어준다.
            answer.push_back(elements_i[i]);
    }

    return answer;
}
int main() {
    solution(3, 2, 5);
    solution(4, 7, 14);
}
