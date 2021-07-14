#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int arr[51][51];
bool visit[51];
int already[51];

//굳이 int형으로 하지 말고, 잘 생각해보면 visit으로만 쓰면 오류가 발생한다. 그러니까, 한번이라도 방문했던 점들만 기록하는 already를썼다.
void dilivery(int start, int K, int N) {
    if (K < 0) {
        return ;
    }
    
    
    visit[start] = true;
    already[start] = 1;
    for (int i = 1; i <= N; i++) {
        if (arr[i][start] != 10000000 && !visit[i]) {
            dilivery(i, K - arr[i][start], N);
            
        }
    }
    
    visit[start] = false;
    
}
int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;

    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    cout << "Hello Cpp" << endl;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
            if (i == j)
                arr[i][j] = 0;
            else
                arr[i][j] = 10000000;
    }
    for (int i = 0; i < road.size(); i++) {
        int a = road[i][0];
        int b = road[i][1];
        int c = road[i][2];
        arr[a][b] = min(arr[a][b], c);
        arr[b][a] = arr[a][b];
    }
    dilivery(1, K, N);
    for(int i=1; i<=N; i++){
        if(already[i])
            answer++;
    }
    return answer;
}
int main() {
    vector<vector<int>> a = { {1, 2, 1},{2, 3, 3},{5, 2, 2},{1, 4, 2},{5, 3, 1},{5, 4, 2} };
    solution(5, a, 3);
}
