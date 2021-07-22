#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
점들의 visit으로 하면 해결이 안됨.
때론 원문 그대로를 옮겨서 할 줄도 알아야 함..
*/
bool ok(int y, int x){
    return (y >=0 && y < 11 && x>=0 && x < 11) ? true : false;
}
void memorizeMovement(vector<vector<int>>& movement, vector<int>& move){
    movement.push_back(move);
    swap(move[1], move[3]);
    swap(move[0], move[2]);
    movement.push_back(move);
}
bool check_already_visit(vector<vector<int>> movement, vector<int> move){
    for(int i=0; i<movement.size(); i++){
        if(movement[i] == move)
            return true;
    }
    return false;
}
int solution(string dirs) {
    int answer = 0;
    vector<vector<int>> movement;
    int src_x = 5, src_y = 5;
    int dst_x, dst_y;
    for(int i=0; i<dirs.size(); i++){
        vector<int> move;
        char direction = dirs[i];
        dst_x = src_x;
        dst_y = src_y;
        move.push_back(src_y);
        move.push_back(src_x);
        if(direction == 'U')
            dst_y -= 1;
        else if(direction == 'R')
            dst_x += 1;
        else if(direction == 'D')
            dst_y += 1;
        else if(direction == 'L')
            dst_x -= 1;
        move.push_back(dst_y);
        move.push_back(dst_x);
        if(ok(dst_y, dst_x)){
            if(!check_already_visit(movement, move)){
                memorizeMovement(movement, move);   
                answer++;
            } 
            src_y = dst_y;
            src_x = dst_x;
        }
        
    }
    return answer;
}
