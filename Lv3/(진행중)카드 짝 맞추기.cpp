//
//minMove의 fix_directions수정 요함.

/*
내가 놓친 부분
카드 쌍을 지울 때, 어떤 것을 먼저 지울지 결정하는 부분에서
내가 했던 것은 현재 커서로부터 A1, A2과의 거리만 비교하여 단순 작은것부터 이동했다.
이러면 안되고, (커서->A1->A2)의 값과 (커서->A2->A1)의 값을 비교하여야 한다.
*/
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int dy[4] = {1, -1, 0, 0};
const int dx[4] = {0, 0, 1, -1};
int board[4][4];

bool ok(int y, int x){
    return (y >=0 && y < 4 && x >= 0 && x < 4) ? true : false;
}
void setCardPositions(vector<pair<int, int>>& path, int num){
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(board[i][j] == num)
                path.push_back({i, j});
    return;
}
pair<int, int> getCtrlMove(int d, int y, int x){
    if(d - 4 < 2){//y축에 대한 움직임
        while(ok(y, x)){
            y += dy[d];
            if(!ok(y, x))break;
            if(board[y][x] != 0)
                return {y, x};
        }
        if(y < 0) y = 0;
        if(y > 3) y = 3;
        
    }else{
        while(ok(y, x)){
            x += dx[d];
            if(!ok(y, x)) break;
            if(board[y][x] != 0)
                return {y, x};
        }
        if(d < 0) d = 0;
        if(d > 3) d = 3;
    }
    return {y, x};
}
int getDistance(pair<int, int> start, pair<int, int> goal){
    if(start == goal)
        return 0;
    bool visit[4][4];
    memset(visit ,false, sizeof(visit));
    queue<pair<int, pair<int, int>>> wait;
    wait.push({0, start});
    while(!wait.empty()){
        pair<int , pair<int, int>> here = wait.front(); wait.pop();
        if(here.second.first == goal.first && here.second.second == goal.second)
            return here.first;
        int hereY = here.second.first;
        int hereX = here.second.second;
        int move = here.first;
        visit[hereY][hereX]=true;
        for(int i=0; i<8; i++){
            if(i < 4){
                int nextY = hereY + dy[i];
                int nextX = hereX + dx[i];
                if(ok(nextY, nextX) && visit[nextY][nextX] == false)
                    wait.push({move+1, {nextY, nextX}});
            }else{
                pair<int, int> nextPair = getCtrlMove(i, hereY, hereX);
                if(ok(nextPair.first, nextPair.second) && visit[nextPair.first][nextPair.second] == false)
                    wait.push({move+1, nextPair});
            }
        }
        
    }
    return -987654321;//OOPS!
}
int solution(vector<vector<int>> b, int r, int c) {
    int answer = 987654321;
    set<int> cards;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(b[i][j] != 0)
                cards.insert(b[i][j]);
    vector<int> card_list;
    for(auto i : cards)
        card_list.push_back(i);
    sort(card_list.begin(), card_list.end());
    
    do{
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                board[i][j] = b[i][j];
        
        pair<int, int> cursor = {r, c};
        //현재 cursor의 위치로부터
        int temp_answer = 0;
        for(int i=0; i<card_list.size(); i++){
            vector<pair<int, int>> char_pos;
            setCardPositions(char_pos, card_list[i]);
            pair<int, int> pos1 = char_pos[0];
            pair<int, int> pos2 = char_pos[1];
            
            int dist_c2A = getDistance(cursor, pos1);
            int dist_A2B = getDistance(pos1, pos2);
            
            int dist_c2B = getDistance(cursor, pos2);
            int dist_B2A = getDistance(pos2, pos1);
            
            board[pos1.first][pos1.second] = 0;
            board[pos2.first][pos2.second] = 0;
            
            if(dist_c2A + dist_A2B < dist_c2B + dist_B2A){
                temp_answer += (dist_c2A + dist_A2B + 2);
                cursor = pos2;
            }
            else{
                temp_answer += (dist_c2B + dist_B2A + 2);
                cursor = pos1;
            }
            
            
        }        
        if(temp_answer < answer)
            answer = temp_answer;
    }while(next_permutation(card_list.begin(), card_list.end()));
    
    return answer;
}
