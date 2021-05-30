#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

int crank(vector<vector<int>> &board, int col){
    int num_doll = 0;
    for(int i=0; i<board.size(); i++){
        if(board[i][col] != 0){
            
            num_doll = board[i][col];
            board[i][col] = 0;
            break;
        }
    }
    return num_doll;
}
//[1,5,3,5,1,2,1,4]
int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    stack<int> st;
    for(int i=0; i<moves.size(); i++){
        int num_doll = crank(board, moves[i]-1);
        
        if(num_doll != 0){
            if(!st.empty()){
                if(st.top() == num_doll){
                    st.pop();
                    answer++;
                    continue;
                }
            }
            st.push(num_doll);
        }
       //out << st.size() << '\n';
    }
    
    return answer * 2;
}
