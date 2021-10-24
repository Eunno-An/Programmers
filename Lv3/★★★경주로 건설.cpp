//fail
//나와 비슷하게 DFS로 풀었다가 시간초과가 난 분의 블로그 글
//https://blog.naver.com/raylee00/222023229068
//DFS와 BFS의 성능 차이에 대한 글
//https://blog.naver.com/vici2021/222529846271

//결론: 그냥 완전 탐색이고 최소 비용찾는거면 BFS로 하자
#include <string>
#include <vector>
#include <queue>
using namespace std;
const int dy[4] = { 0, 1, 0, -1 };
const int dx[4] = { 1, 0, -1, 0 };
int dp[26][26][4];
bool visit[26][26][4];
class Car {
public:
	int y, x, dir;
	Car(int y, int x, int dir) {
		this->y = y;
		this->x = x;
		this->dir = dir;

	}
};
bool ok(int y, int x, int n) {
	return (y >= 0 && y < n&& x >= 0 && x < n) ? true : false;
}
int solution(vector<vector<int>> board) {
	int answer = 987654321;
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			for (int k = 0; k < 4; k++) {
				dp[i][j][k] = 987654321;
				visit[i][j][k] = false;
			}

	dp[0][0][0] = 0;
	dp[0][0][1] = 0;
	visit[0][0][0] = true;
	visit[0][0][1] = true;


	queue<Car*> q;
	Car* car = new Car(0, 0, 0);
	Car* car2 = new Car(0, 0, 1);
	q.push(car);
	q.push(car2);
	while (!q.empty()) {
		Car* frontCar = q.front(); q.pop();
		if (frontCar->y == board.size() - 1 && frontCar->x == frontCar->y) {
			if (answer > dp[frontCar->y][frontCar->x][frontCar->dir])
				answer = dp[frontCar->y][frontCar->x][frontCar->dir];
			continue;
		}

		int now_dir = frontCar->dir;
		int& now_cost = dp[frontCar->y][frontCar->x][now_dir];
		for (int i = 0; i < 4; i++) {
			int next_y = frontCar->y + dy[i];
			int next_x = frontCar->x + dx[i];

			if (ok(next_y, next_x, board.size()) && board[next_y][next_x] != 1) {
				Car* car = new Car(next_y, next_x, i);
				if (i != now_dir) {
					now_cost += 600;
					if (visit[next_y][next_x][i] == true) 
						if (now_cost <= dp[next_y][next_x][i]) 
							q.push(car);
					
					
					else {
						dp[next_y][next_x][i] = now_cost;
						visit[next_y][next_x][i] = true;
						q.push(car);
					}
				}

				else {
					now_cost += 100;
					if (visit[next_y][next_x][i] == true) {
						if (now_cost <= dp[next_y][next_x][i]) {

							dp[next_y][next_x][i] = now_cost;
							q.push(car);
						}
					}
					else {
						dp[next_y][next_x][i] = now_cost;
						visit[next_y][next_x][i] = true;
						q.push(car);
					}
				}

				
			}
		}
	}

	return answer;
}
