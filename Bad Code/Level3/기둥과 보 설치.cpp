
#include <string>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
class Point {//상하좌우로 뭐가 있는지.
public:
    int u, d, l, r;
    Point(int u, int d, int l, int r) {
        this->u = u;
        this->d = d;
        this->l = l;
        this->r = r;
    }
};
Point* matrix[101][101];
bool visit[101][101];
//0 : 기둥, 1 : 보
bool is_able_set(int x, int y, int a) {
    if (a == 0) {//기둥 설치
        //바닥 위에 있거나(y == 0)
        //보의 한쪽 끝 부분 위에 있거나(matrix[y][x]->l == 1 || matrix[y][x]->r == 1)
        //다른 기둥 위에 있을 때(matrix[y][x]->d == 1)
        if (y == 0 || matrix[y][x]->l == 1 || matrix[y][x]->r == 1 || matrix[y][x]->d == 1) {
            matrix[y][x]->u = 1;
            matrix[y + 1][x]->d = 1;
            return true;
        }
        else
            return false;
    }
    else {//보 설치
        //한쪽 끝 부분이 기둥 위에 있거나(matrix[y][x]->d == 1)
        //양쪽 끝 부분이 다른 보와 동시에 연결되어 있어야 한다(matrix[y][x]->l == 1 && matrix[y][x+1]->l == 1)
        if (matrix[y][x]->d == 1 || matrix[y][x + 1]->d == 1 || (matrix[y][x]->l == 1 && matrix[y][x + 1]->r == 1)) {
            matrix[y][x]->r = 1;
            matrix[y][x + 1]->l = 1;
            return true;
        }
        else
            return false;
    }

}
bool is_able_delete(int x, int y, int a) {
    if (a == 0) {//기둥 삭제

        //matrix[y+1][x]지점에 무언가 받쳐줄게 있어야 한다.
        //(y+1, x)지점의 양쪽이 보로 연결되어 있을때(matrix[y+1][x]->l == 1 && matrix[y+1][x]->r == 1) 

        if (matrix[y + 1][x]->l == 1 && matrix[y + 1][x]->r == 1) {
            matrix[y][x]->u = 0;
            matrix[y + 1][x]->d = 0;
            return true;
        }
        else
            return false;
    }
    else {//보 삭제
       //보 삭제는 
       //(y, x+1)지점이 기둥으로 받쳐져 있고 
       //(y, x)지점이 기둥으로 받쳐져 있을 때
        if (matrix[y][x + 1]->d == 1 && matrix[y][x]->d == 1) {
            matrix[y][x]->r = 0;
            matrix[y][x + 1]->l = 0;
            return true;
        }
        else
            return false;
    }
}
void set_structure(int x, int y, int a) {
    if (is_able_set(x, y, a))
        return;
}
void delete_structure(int x, int y, int a) {
    if (is_able_delete(x, y, a))
        return;
}

bool compare(vector<int> a, vector<int> b) {
    if (a[0] == b[0]) {
        if (a[1] == b[1])
            return a[2] < b[2];
        return a[1] < b[1];
    }
    return a[0] < b[0];
}
vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;

    for (int i = 0; i < 101; i++)
        for (int j = 0; j < 101; j++)
            matrix[i][j] = new Point(0, 0, 0, 0);

    for (int i = 0; i < build_frame.size(); i++) {
        int x = build_frame[i][0];
        int y = build_frame[i][1];
        int a = build_frame[i][2];//1: 보, 0: 기둥
        int b = build_frame[i][3];//1:설치, 0: 삭제
        if (b == 1)
            set_structure(x, y, a);
        else
            delete_structure(x, y, a);
    }
    int startX;
    for (int i = 0; i <= n; i++)
        if (matrix[0][i]->u == 1) {
            startX = i;
            break;
        }

    queue<vector<int>> temp;

    vector<int> pos = { 0, startX };
    temp.push(pos);
    while (!temp.empty()) {
        vector<int> tempPos = temp.front(); temp.pop();
        int here_y = tempPos[0];
        int here_x = tempPos[1];

        visit[here_y][here_x] = true;

        int up = matrix[here_y][here_x]->u;
        int down = matrix[here_y][here_x]->d;
        int left = matrix[here_y][here_x]->l;
        int right = matrix[here_y][here_x]->r;

        vector<int> nextPos;
        vector<int> nowStructure;
        if (up == 1 && visit[here_y + 1][here_x] == false) {
            nextPos = { here_y + 1, here_x };
            temp.push(nextPos);//다음 좌표를 넣는다.
            nowStructure = { here_y, here_x, 0 };
            answer.push_back(nowStructure);//현재 구조물을 넣는다.
        }
        if (down == 1 && visit[here_y - 1][here_x] == false) {
            nextPos = { here_y - 1, here_x };
            temp.push(nextPos);
            nowStructure = { here_y - 1, here_x, 0 };
            answer.push_back(nowStructure);
        }
        if (left == 1 && visit[here_y][here_x - 1] == false) {
            nextPos = { here_y, here_x - 1 };
            temp.push(nextPos);
            nowStructure = { here_y, here_x - 1, 1 };
            answer.push_back(nowStructure);
        }
        if (right == 1 && visit[here_y][here_x + 1] == false) {
            nextPos = { here_y, here_x + 1 };
            temp.push(nextPos);
            nowStructure = { here_y, here_x, 1 };
            answer.push_back(nowStructure);
        }
    }
    for (int i = 0; i < answer.size(); i++)
        swap(answer[i][0], answer[i][1]);

    sort(answer.begin(), answer.end(), compare);
    return answer;
}
int main() {
    solution(5, { {1, 0, 0, 1}, {1, 1, 1, 1}, {2, 1, 0, 1}, {2, 2, 1, 1}, {5, 0, 0, 1}, {5, 1, 0, 1}, {4, 2, 1, 1}, {3, 2, 1, 1} });
}
