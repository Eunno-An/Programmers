#include <string>
#include <vector>
#include <cstring>
using namespace std;
int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    int terrain[51][51];//if true: exist path
    memset(terrain, 0, sizeof(terrain));
    //우리는 주어진 맵을 x축에 뒤집어서 생각해야 한다.

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
                    if (terrain[j][k] == 1) 
                        continue;
                    
                    else {
                        if (terrain[j][k] == 2 && (j == below_y || j == above_y || k == below_x || k == above_x)) {
                            //기존의 테두리와 새로운 도형의 테두리가 만나는 경우
                            //꼭짓점은 그대로 두고, 꼭짓점이 아닌 테두리가 만나는 부분만 0으로 놔야 한다.
                            if (j > below_y && j < above_y && k>below_x && k < above_x) 
                                terrain[j][k] = 0;
                            
                            else
                                continue;
                        }
                    }
                }
            }
    }

    //전체 순회 하면서 terrain이 2인곳을 남긴다.
    for (int i = 0; i < 51; i++)
        for (int j = 0; j < 51; j++)
            if (terrain[i][j] != 2)
                terrain[i][j] = 0;

    return answer;
}
int main() {
    solution({ {1, 1, 7, 4},{3, 2, 5, 5},{4, 3, 6, 9},{2, 6, 8, 8} }, 1, 3, 7, 8);
}
