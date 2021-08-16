//fail
//floor, col, sum을 매개변수로 사용하게 되면, 동적계획법으로 sum까지 저장하는 배열을 만들어야 하는데, 
//근데 그러면 메모리를 너무 많이 잡아먹음.
//그렇다고 해서 sum을 매개변수로 사용하면서 메모이제이션을 안하면 답이 부정확하게 나올 수 있음.
//따라서 정확하게 점화식을 세우고, 이를 그대로 구현해야 함.
//solve(floor, col) = max(solve(floor+1, col), solve(floor+1, col+1)) + arr[floor][col];
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int arr[501][501];
int cache[501][501];
void init(vector<vector<int>> triangle) {
    for (int i = 0; i < triangle.size(); i++)
        for (int j = 0; j < triangle[i].size(); j++) {
            cache[i][j] = -1;
            arr[i][j] = triangle[i][j];
        }
}
int solve(int floor, int col, int max_floor) {
    if (floor == max_floor-1)
        return arr[floor][col];
    int& ret = cache[floor][col];
    if (ret != -1)
        return ret;
    return ret= max(solve(floor + 1, col, max_floor), solve(floor + 1, col + 1, max_floor))+arr[floor][col];
}
int solution(vector<vector<int>> triangle) {
    int answer = 0;
    init(triangle);
    answer = solve(0, 0, triangle.size());
    return answer;
}
int main() {
    solution({ {7},{3, 8},{8, 1, 0},{2, 7, 4, 4},{4, 5, 2, 6, 5} });
}
