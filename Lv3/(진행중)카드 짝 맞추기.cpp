//minMove의 fix_directions수정 요함.

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int dy[4] = { 1, 0, -1, 0 };
const int dx[4] = { 0, 1, 0, -1 };
bool is_flipped[4][4];//true: 앞면, false: 뒷면
int board[4][4];
vector<int> number_list;//보드에 사용된 숫자들.
pair<int, int> cursor_pos;//커서의 현재 위치
int min_move = 987654321;
bool ok(int y, int x) {
	return (y >= 0 && y < 4 && x >= 0 && x < 4) ? true : false;
}
void init(vector<vector<int>> b, int r, int c) {
	vector<int> temp_list(10, 0);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			board[i][j] = b[i][j];

			if (temp_list[board[i][j]] == 0)
				temp_list[board[i][j]]++;
		}
	for (int i = 0; i < temp_list.size(); i++)
		if (i != 0 && temp_list[i] != 0)
			number_list.push_back(i);
	sort(number_list.begin(), number_list.end());
	cursor_pos.first = r;
	cursor_pos.second = c;
	return;
}


int minMove(pair<int, int> start, pair<int, int> goal) {
	if (start == goal)
		return 0;
	bool visit[4][4];
	memset(visit, false, sizeof(visit));
	vector<int> arrow;
	queue<vector<pair<bool, pair<int, int>>>> pos; // pair<bool, pair<int, int>> = bool or true : 카드인지 아닌지, 
	for (int i = 0; i < 4; i++) {
		int nextY = start.first + dy[i];
		int nextX = start.second + dx[i];
		if (ok(nextY, nextX)) {
			vector<pair<bool, pair<int, int>>> temp;
			if (board[nextY][nextX] != 0)
				temp.push_back(make_pair(true, make_pair(nextY, nextX)));
			else
				temp.push_back(make_pair(false, make_pair(nextY, nextX)));
			pos.push(temp);
		}
	}
	vector<pair<bool, pair<int, int>>> min_move_list;
	
	while (!pos.empty()) {
		vector<pair<bool, pair<int, int>>> here_list = pos.front(); pos.pop();
		pair<int, int> here = here_list.back().second;
		if (here == goal) {
			if (board[start.first][start.second])
				min_move_list.push_back(make_pair(true, start));
			else
				min_move_list.push_back(make_pair(false, start));
			for (int i = 0; i < here_list.size(); i++)
				min_move_list.push_back(here_list[i]);
			break;
		}
		visit[here.first][here.second] = true;
		for (int i = 0; i < 4; i++) {
			int nextY = here.first + dy[i];
			int nextX = here.second + dx[i];
			if (ok(nextY, nextX) && !visit[nextY][nextX]) {
				if (board[nextY][nextX] != 0)
					here_list.push_back(make_pair(true, make_pair(nextY, nextX)));
				else
					here_list.push_back(make_pair(false, make_pair(nextY, nextX)));
				pos.push(here_list);
				here_list.pop_back();
			}
		}
	}
	
	vector<pair<bool, int>> directions;
	
	for (int i = 1; i < min_move_list.size(); i++) {
		pair<int, int> before = min_move_list[i - 1].second;
		pair<int, int> now = min_move_list[i].second;
		int temp_dy = now.first - before.first;
		int temp_dx = now.second - before.second;
		for (int j = 0; j < 4; j++)
			if (temp_dy == dy[j] && temp_dx == dx[j]) {
				if (board[now.first][now.second] == 0)
					directions.push_back(make_pair(false, j));
				else
					directions.push_back(make_pair(true, j));
				break;
			}
	}
	
	vector<int> fix_directions;
	if (directions.size() == 1)
		return 1;

	
	for (int i = 0; i < directions.size() - 1; ++i) {
		for (int j = i + 1; j < directions.size(); ++j) {
			if (directions[i].second != directions[j].second) {
				j = i;
				break;
			}
			else if (directions[i].second == directions[j].second && directions[j].first == false) //둘의 방향이 같고 또는 다음 칸이 카드가 아닐때
				continue;
			else
				fix_directions.push_back(directions[j].second);

		}
	}
	return fix_directions.size();
}

int init_cursor_to_character(int character) {//커서의 위치를 현재 위치에서 캐릭터가 있는 곳으로 옮긴다.
	vector<pair<int, int>> char_pos;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (board[i][j] == character)
				char_pos.push_back(make_pair(i, j));

	pair<int, int> pos1 = char_pos[0];
	pair<int, int> pos2 = char_pos[1];

	pair<int, int> back_up = cursor_pos;
	int distance1 = minMove(cursor_pos, pos1);
	cursor_pos = back_up;
	int distance2 = minMove(cursor_pos, pos2);
	cursor_pos = back_up;
	if (distance1 < distance2)
		cursor_pos = pos1;
	else
		cursor_pos = pos2;
	return (cursor_pos == pos1 ? distance1 : distance2);
}
//사용된 숫자들의 순열을 만든다. (ok)
//어떤 좌표에서 다른 좌표로 최소 이동하는 횟수를 구하는 함수를 구한다.(ok)
//커서의 위치를 현재 위치에서 캐릭터가 있는 곳으로 옮긴다.
//보드에 있는 페어를 찾아 없앤다.
//만약 못없애면 다음 순열로 넘어간다.


pair<int, int> findPair(int character) {
	pair<int, int> ret;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == character && cursor_pos.first != i && cursor_pos.second != j) {//캐릭터와 같으면서, 현재 cursorPos가 아닌 경우
				ret.first = i;
				ret.second = j;
				return ret;
			}
		}
	}
	return make_pair(-1, -1);
}


int solution(vector<vector<int>> b, int r, int c) {
	int answer = 987654321;

	init(b, r, c);
	do {
		cursor_pos.first = r;
		cursor_pos.second = c;
		int temp_answer = 0;
		bool fail = false;
		for (int i = 0; i < number_list.size(); i++) {
			temp_answer += init_cursor_to_character(number_list[i]);//커서의 위치를 처음에서 i번째 숫자로 옮김. 
			board[cursor_pos.first][cursor_pos.second] = 0;
			temp_answer++;//enter 입력
			pair<int, int> another = findPair(number_list[i]);
			temp_answer += minMove(cursor_pos, another);
			temp_answer++; //enter입력
			board[another.first][another.second] = 0;
		}
		if (temp_answer < answer)
			answer = temp_answer;
	} while (!next_permutation(number_list.begin(), number_list.end()));
	return answer;
}

int main() {
	solution({{1, 0, 0, 3}, {2, 0, 0, 0}, {0, 0, 0, 2}, {3, 0, 1, 0}}, 1, 0);
	solution({{3, 0, 0, 2}, {0, 0, 1, 0}, {0, 1, 0, 0}, {2, 0, 0, 3}}, 0, 1);
}
