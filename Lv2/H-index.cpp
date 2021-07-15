#include <string>
#include <vector>

using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
    int max_h = 0;
    for (int i = 0; i <= 10000; i++) {
        int count = 0;
        for (int j = 0; j < citations.size(); j++) {
            if (i <= citations[j])
                count++;
        }
        if (i <= count && citations.size()-count <= i) { // count = i 번 이상 인용된 논문의 개수
            if (max_h < i)
                max_h = i;
        }
    }
    answer = max_h;
    return answer;
}
int main() {
    vector<int> a = { 3, 0, 6, 1, 5 };

    solution(a);
}
