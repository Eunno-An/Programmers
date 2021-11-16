#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int dy[4] = {1, 0, -1, 0};
const int dx[4] = {0, 1, 0, -1};
bool is_flipped[4][4];//true: 앞면, false: 뒷면
int board[4][4];
vector<int> number_list;//보드에 사용된 숫자들.
pair<int, int> cursor_pos;//커서의 현재 위치
int min_move = 987654321;
bool ok(int y, int x){
    return (y >=0 && y < 4 && x>=0 && x < 4) ? true : false;
}
void init(vector<vector<int>> board, int r, int c){
    vector<int> temp_list(10, 0);
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++){
            new_board[i][j] = board[i][j];
            
            if(temp_list[board[i][j]] == 0)
                temp_list[board[i][j]]++;
        }
    for(int i=0; i<temp_list.size(); i++)
        if(i != 0 && temp_list[i] != 0)
            number_list.push_back(i);
    sort(number_list.begin(), number_list.end());
    cursor_pos.first = r;
    cursor_pos.second = c;
    return;
}


int minMove(pair<int, int> start, pair<int, int> goal)
    bool visit[4][4];
    memset(visit, false, sizeof(visit));
    vector<int> arrow;
    queue<vector<pair<int, int>>> pos;
    for(int i=0; i<4; i++){
        int nextY = start.first + dy[i];
        int nextX = start.second + dx[i];
        if(ok(nextY, nextX)){
            vector<pair<int, int>> temp;
            temp.push_back(make_pair(nextY, nextX));
            pos.push(temp);
        }
    }
    while(!pos.empty()){
        vector<pair<int, int>> here_list= pos.front(); pos.pop();
        pair<int, int> here = here_list.back();
        if(here == goal)
            break;
        visit[here.first][here.second]=true;
        for(int i=0; i<4; i++){
            int nextY = here.first + dy[i];
            int nextX = here.second + dx[i];
            if(ok(nextY, nextX) && !visit[nextY][nextX]){
                here_list.push_back(make_pair(nextY, nextX));
                pos.push(here_list);
                here_list.pop_back();
            }
        }
    }
    vector<int> directions;
    for(int i=1; i<here_list.size(); i++){
        pair<int, int> before = here_list[i-1];
        pair<int, int> now = here_list[i];
        int temp_dy = now.first - before.first;
        int temp_dx = now.second - before.second;
        for(int j=0; j<4; j++)
            if(temp_dy == dy[j] && temp_dx == dx[j])
                directions.push_back(j);
    }
    vector<int> fix_directions;
    for(int i = 0; i<directions.size()-1; i++)
        if(directions[i] != directions[i+1])
            fix_directions.push_back(directions[i]);
    
    return fix_directions.size();
}

int init_cursor_to_character(int character){//커서의 위치를 현재 위치에서 캐릭터가 있는 곳으로 옮긴다.
    vector<pair<int, int>> char_pos;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(board[i][j] == character)
                char_pos.push_back(make_pair(i, j));
            
    pair<int, int> pos1 = char_pos[0];
    pair<int, int> pos2 = char_pos[1];
    
    int distance1 = minMove(cursor_pos, pos1);
    int distance2 = minMove(cursor_pos, pos2);
    cursor_pos = (distance1 < distance2 ? distance1: distance2);
    return (cursor_pos == distance1 ? distance1 : distance2);
}
//사용된 숫자들의 순열을 만든다. (ok)
//어떤 좌표에서 다른 좌표로 최소 이동하는 횟수를 구하는 함수를 구한다.
//커서의 위치를 현재 위치에서 캐릭터가 있는 곳으로 옮긴다.
//보드에 있는 페어를 찾아 없앤다.
//만약 못없애면 다음 순열로 넘어간다.


bool findPair(int character){
    
}

int solution(vector<vector<int>> b, int r, int c) {
    int answer = 0;
    
    init(b);
    do{
        int temp_answer = 0;
        for(int i=0; i<number_list.size(); i++){
            temp_answer += init_cursor_to_character(number_list[i]);//커서의 위치를 처음에서 i번째 숫자로 옮김. 
            is_flipped[cursor_pos.first][cursor_pos.second] = true;
            temp_answer++;//enter 입력
            
            if(findPair(number_list[i]))
        }
        
    }while(!next_permutation(number_list.begin(), number_list.end()));
    return answer;
}
