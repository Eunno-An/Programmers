//fail
//아이디어 참고
//두 직선의 교점이 유일하게 존재할 경우, 그 교점에 대한 식이 존재함.
//그리고 평행한 경우와 교점이 무수히 많은 경우도 판별 가능.
//아이디어 [출처] [프로그래머스] 위클리챌린지 - Level 2 10주차 (교점 에 별 만들기), 28, 29번은 long으로 해결 // (Java)|작성자 누스타
#include <string>
#include <vector>

using namespace std;

vector<string> solution(vector<vector<int>> line) {
    vector<string> answer;
    vector<pair<long, long>> intersections;
    for (int i = 0; i < line.size(); i++) {
        vector<int> A = line[i];
        for (int j = i + 1; j < line.size(); j++) {
            vector<int> B = line[j];
            long long int bunmo = (long long)A[0] * B[1] - A[1] * B[0];
            if (bunmo == 0)
                continue;
            else {
                long long int bunzaA = (long long )A[1] * B[2] - A[2] * B[1];
                long long int bunzaB = (long long)A[2] * B[0] - A[0] * B[2];
                if (bunzaA % bunmo == 0 && bunzaB % bunmo == 0)
                    intersections.push_back(make_pair(bunzaA / bunmo, bunzaB / bunmo));
            }

        }
    }
    long long int minY = intersections[0].second;
    long long int minX = intersections[0].first;
    long long int maxY = intersections[0].second;
    long long int maxX = intersections[0].first;
    for (int i = 1; i < intersections.size(); i++) {
        long long int y = intersections[i].second;
        long long int x = intersections[i].first;
        if (minY > y)
            minY = y;
        if (minX > x)
            minX = x;
        if (maxY < y)
            maxY = y;
        if (maxX < x)
            maxX = x;
    }
    for (int i = 0; i < intersections.size(); i++) {
        intersections[i].first -= minX;
        intersections[i].second -= minY;
    }
    int height = maxY - minY + 1;
    int width = maxX - minX + 1;
    answer.resize(height);
    for (int i = 0; i < answer.size(); i++)
        answer[i].resize(width, '.');
    for (int i = 0; i < intersections.size(); i++) {
        int y = height - intersections[i].second - 1;
        int x = intersections[i].first;
        answer[y][x] = '*';
    }
    return answer;
}
int main() {
    solution({ {0, 1, -1},{1, 0, -1},{1, 0, 1} });
}
