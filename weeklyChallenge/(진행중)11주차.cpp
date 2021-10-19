#include <string>
#include <vector>
#include <cstring>
using namespace std;
//plain sweeping
int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    int terrain[51][51];//if true: exist path
    memset(terrain, 0, sizeof(terrain));
    //우리는 주어진 맵을 x축에 뒤집어서 생각해야 한다.
    int top_y=51, top_x =51;//위에서부터 쓸기 위한 맨 위 좌표들 
    for(int i=0; i<rectangle.size(); i++){
        //rectangle[i][0]=좌 하단 x좌표, rectangle[i][1] = 좌 하단 y좌표
        //실제 terrain에서는 둘을 바꿔서 써야 한다.
        int below_x = rectangle[i][0], below_y = rectangle[i][1];
        int above_x = rectangle[i][2], above_y = rectangle[i][3];
        
        //최소 y, x좌표를 저장
        if(below_x < top_x) top_x = below_x;
        if(below_y < top_y) top_y = below_y;
        
        //경로가 지나가는 곳을 ++
        for(int j=below_y; j<=above_y; j++)
            for(int k=below_x; k<=above_x; k++)
                terrain[j][k]++;
    }
    return answer;
}
