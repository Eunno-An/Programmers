#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int arr[101][101];
void init(int rows, int cols) {
    for (int i = 1; i <= rows; i++)
        for (int j = 1; j <= cols; j++)
            arr[i][j] = (i - 1) * cols + j;
}
vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;

    init(rows, columns);

    for (int i = 0; i < queries.size(); i++) {

        int y1, x1, y2, x2;
        y1 = queries[i][0];
        x1 = queries[i][1];
        y2 = queries[i][2];
        x2 = queries[i][3];
        //(y1, x1)부터 (y2, x2)까지 테두리를 시계방향으로 회전한다.
        //항상 (y1, x1)이 왼쪽 위에 존재한다. 그리고 좌표 축과 평행한 일직선 상에 두 점이 존재하는 경우는 없다.

        /*
        (y1, x1) = leftTop (y1, x2) = rightTop
        (y2, x1) = leftBottom (y2, x2) = rightBottom
        각 꼭짓점을 변수에 저장한다.

        (y1, x2-1) 부터 (y1, x1+1)에 있는 수를 오른쪽으로 한 칸 이동한다.

        (y2-1, x2) 부터 (y1+1, x2)에 있는 수를 아래로 한 칸 이동한다.

        (y2, x1+1) 부터 (y2, x2-1)에 있는 수를 왼쪽으로 한 칸 이동한다.

        (y2-1, x1) 부터 (y1+1, x1)에 있는 수를 위로 한 칸 이동한다.
        그리고
        arr[y1+1][x2] = rightTop
        arr[y2][x2-1] = rightBottom
        arr[y2-1][x1] = leftBottom
        arr[y1][x1+1] = leftTop
        예외처리
        만약 2*2 사각형 처럼 어느 한 변의 길이가 2인 경우 패스한다.
        */
        int leftTop = arr[y1][x1];
        int rightTop = arr[y1][x2];
        int leftBottom = arr[y2][x1];
        int rightBottom = arr[y2][x2];


        vector<int> temp;
        for (int j = y1; j <= y2; j++)
            for (int k = x1; k <= x2; k++)
                if (j == y1 || j == y2 || k == x1 || k == x2)
                    temp.push_back(arr[j][k]);

        //(y1, x2-1) 부터 (y1, x1+1)에 있는 수를 오른쪽으로 한 칸 이동한다.
        for (int j = x2 - 1; j >= x1 + 1; j--)
            arr[y1][j + 1] = arr[y1][j];
        arr[y1][x1 + 1] = leftTop;


        //(y2-1, x2) 부터 (y1+1, x2)에 있는 수를 아래로 한 칸 이동한다.
        for (int j = y2 - 1; j >= y1 + 1; j--)
            arr[j + 1][x2] = arr[j][x2];
        arr[y1 + 1][x2] = rightTop;

        //(y2, x1+1) 부터 (y2, x2-1)에 있는 수를 왼쪽으로 한 칸 이동한다.
        for (int j = x1 + 1; j <= x2 - 1; j++)
            arr[y2][j - 1] = arr[y2][j];
        arr[y2][x2 - 1] = rightBottom;


        //(y2-1, x1) 부터 (y1+1, x1)에 있는 수를 위로 한 칸 이동한다.
        for (int j = y1 + 1; j <= y2 - 1; j++)
            arr[j - 1][x1] = arr[j][x1];
        arr[y2 - 1][x1] = leftBottom;
        //기존과 다른 수들이 있으면 넣는다.

        sort(temp.begin(), temp.end());
        answer.push_back(temp[0]);
    }

    return answer;
}

int main() {
    //solution(6, 6, { {2, 2,5,4},{3,3,6,6},{5,1,6,3} });
    //solution(3, 3, { {1,1,2,2},{1,2,2,3},{2,1,3,2},{2,2,3,3} });
    //solution(100, 97, { {1,1,100,97} });
    solution(100, 2, { {2, 1, 3, 2} });
}
