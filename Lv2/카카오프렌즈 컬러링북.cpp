#include <vector>
//19번째줄 유심히 .. 봐라..
using namespace std;

bool visit[101][101];
int arr[101][101];
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int w, h;
bool ok(int x, int y){
    if(x >=0 && x < h && y >= 0 && y < w)
        return true;
    return false;
}
int dfs(int x, int y){
    if(!ok(x, y))
        return 0;
    if(visit[x][y])
        return 0;//이걸 안하다니 .. 이런 삐리리..ㅋㅋ
    visit[x][y] = true;
    int ret = 1;
    for(int i=0; i<4; i++){
        int _dx = x + dx[i];
        int _dy = y + dy[i];
        if(arr[x][y] == arr[_dx][_dy]){
            ret += dfs(_dx, _dy);   
        }
    }
    return ret;
}
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    
    //init
    for(int i=0; i<m;i ++){
        for(int j=0; j<n; j++){
            arr[i][j] = picture[i][j];
            visit[i][j] = false;
        }
    }
    h = m, w = n;
    int areaNumber = 0;
    for(int i=0; i<m;i ++){
        for(int j=0; j<n; j++){
            int areaSize = 0 ;
            if(arr[i][j] != 0 && !visit[i][j]){
                areaNumber++;
                areaSize += dfs(i, j);
            }
            if(areaSize > max_size_of_one_area)
                 max_size_of_one_area = areaSize;
        }
    }
    number_of_area = areaNumber;
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}
