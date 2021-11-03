#include <string>
#include <vector>
#include <cstring>
using namespace std;

//보는 항상 왼쪽의 좌표만, 기둥은 항상 아래 좌표만 기입하면 됨.
//우리는 좌표를 위 아래 뒤집어서 생각할 것이고, 그렇게 되면 위-아래의 조건도 바뀌게 됨.
//그리고 문제에서 원하는 (x, y) 좌표도 (y, x)로 생각해야 함. ex) 문제에서 (2, 1)은 내 좌표에서는 (1, 2)가 됨. -> 반드시 나중에 좌표 뒤집어서 리턴하기!

//matrix[y][x] == -1? 아무것도 없음. 
//0 == 기둥 아래(기둥을 설치하는 곳)
//1 == 기둥 위
//2 == 보 왼쪽(보를 설치하는 곳)
//3 == 보 오른쪽
//4 == 기둥과 기둥이 맞닿음.
//5 == 기둥과 보가 맞닿음.
//6 == 보와 보가 맞닿음.
int matrix[101][101];

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    memset(matrix, -1, sizeof(matrix));
    
    for(int i=0; i<build_frame.size(); i++){
        //우리 좌표에서는 반대로 생각하기! (x, y) -> (y, x)
        int y = build_frame[i][0];
        int x = build_frame[i][1];
        //a =  설치 또는 삭제할 구조물의 종류. 0 = 기둥, 1 = 보
        int a = build_frame[i][2];
        //b = 구조물을 설치할 지, 혹은 삭제할 지를 나타냄. 0 = 삭제, 1 = 설치
        int b = build_frame[i][3];
        
        //벽면을 벗어나게 기둥, 보를 설치하는 경우는 없다!
        //바닥에 보를 설치하는 경우는 없다.
        //구조물이 겹치도록 설치하는 경우와, 없는 구조물을 삭제하는 경우는 입력으로 주어지지 않습니다.
        if(b == 0){//구조물을 설치
            if(a == 0){//기둥을 설치할 경우!
                if(y == 0){//바닥 위에 있는 경우
                    matrix[y][x] = 0;
                    matrix[y+1][x] = 1;
                }else if(matrix[y][x] == 2 || matrix[y][x] == 3){//보의 한쪽 끝에 설치 할 경우
                    matrix[y][x] = 5;
                    matrix[y+1][x] = 1;
                }else if(matrix[y][x] == 1){//다른 기둥 위에 있는 경우
                    matrix[y][x] = 4;
                    matrix[y+1][x] = 1;
                }
            }
            else{//보를 설치할 경우!
                if(matrix[y][x] == 1){//한쪽 끝 부분이 기둥 위에.
                    matrix[y][x] = 5;
                    matrix[y][x+1] = 3;
                }else if(matrix[y][x+1] == 2 && matrix[y][x] == 3){//양쪽 끝 부분이 다른 보와 동시에 연결되어 있는 경우
                    matrix[y][x] = 6;
                    matrix[y][x+1] = 6;
                }
            }
        }else{//구조물을 삭제
            if(a == 0){//기둥을 삭제할 경우!
                
            }
            else{//보를 삭제할 경우!
                
            }
        }
    }
    
    return answer;
}
