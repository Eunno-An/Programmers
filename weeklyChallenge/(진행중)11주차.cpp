#include <string>
#include <vector>
#include <cstring>
using namespace std;
const int dy[4] = { 1, 0, -1, 0 };
const int dx[4] = { 0, 1, 0, -1 };
int terrain[102][102];//if true: exist path
bool ok(int y, int x) {
	return (y >= 0 && y < 102 && x >= 0 && x < 102) ? true : false;
}
int findMaxResult(int terrain[102][102], vector<vector<bool>> visit, pair<int, int> character, pair<int, int> item, int length) {
	if (character == item) {

		return length;
	}
	int ret = 1000000;
	visit[character.first][character.second] = true;
	for (int i = 0; i < 4; i++) {
		int next_y = character.first + dy[i];
		int next_x = character.second + dx[i];
		if (ok(next_y, next_x) && terrain[next_y][next_x] == 2 && visit[next_y][next_x] == false) 
			ret = min(ret, findMaxResult(terrain, visit, make_pair(next_y, next_x), item, length + 1));
	}
	visit[character.first][character.second] = false;
	return ret;
}
int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
	int answer = 0;
	memset(terrain, 0, sizeof(terrain));
	
	for (int i = 0; i < rectangle.size(); i++) {
		for (int j = 0; j < rectangle[i].size(); j++) {
			rectangle[i][j] *= 2;
		}
	}
	//우리는 주어진 맵을 x축에 뒤집어서 생각해야 한다.
	vector<vector<bool>> visit(102);
	for (int i = 0; i < 102; i++)
		visit[i].resize(102, false);
	for (int i = 0; i < rectangle.size(); i++) {
		//rectangle[i][0]=좌 하단 x좌표, rectangle[i][1] = 좌 하단 y좌표
		//실제 terrain에서는 둘을 바꿔서 써야 한다.
		int below_x = rectangle[i][0], below_y = rectangle[i][1];
		int above_x = rectangle[i][2], above_y = rectangle[i][3];

		//최소 y, x좌표를 저장


		//경로가 지나가는 곳을 표시함. 나중에 1인 곳만 남기기 위함임.
		//테두리는 2, 안쪽 영역은 1, 아직 없는 영역은 0
		for (int j = below_y; j <= above_y; j++)
			for (int k = below_x; k <= above_x; k++) {
				if (terrain[j][k] == 0) {//아직 아무것도 없는 영역인 경우
					if (j == below_y || j == above_y || k == below_x || k == above_x)//테두리
						terrain[j][k] = 2;
					else//테두리가 아님
						terrain[j][k] = 1;
				}
				else {//이미 어떤 곳의 안쪽 영역인 경우, 또는 어떤 곳의 테두리인 경우
					if (terrain[j][k] == 2) {
						if ((j > below_y && j < above_y) && (k > below_x && k < above_x)) {
							terrain[j][k] = 1;
						}
					}

				}
			}
	}

	//전체 순회 하면서 terrain이 2인곳을 남긴다.
	for (int i = 0; i < 102; i++)
		for (int j = 0; j < 102; j++)
			if (terrain[i][j] != 2)
				terrain[i][j] = 0;
	pair<int, int> character;
	character.first = characterY;
	character.second = characterX;
	pair<int, int> item;
	item.first = itemY;
	item.second = itemX;

	//terrain은 
	return answer = findMaxResult(terrain, visit, character, item, 0);
}
int main() {
	solution({ {1, 1, 7, 4},{3, 2, 5, 5},{4, 3, 6, 9},{2, 6, 8, 8} }, 1, 3, 7, 8);
}

