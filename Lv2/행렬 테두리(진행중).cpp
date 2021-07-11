#include <string>
#include <vector>

using namespace std;

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    
    for(int i=0; i<queries.size(); i++){
        int arr[101][101];
        for(int j=1; j<=100; j++){
            for(int k=1; k<=100; k++){
                arr[j][k] = ((j-1)*columns+j);
            }
        }
        int x1, y1, x2, y2;
        x1 = queries[i][0];
        y1 = queries[i][1];
        x2 = queries[i][2];
        y2 = queries[i][3];
        int temp = arr[y1][x2];
        //1 1 2 3 4 5, temp = 6
        /*          6
                    12
                    18
                    24
        32 33  34  35  36 30
                    
        */
        for(int col = x2-1; col >= x1; col--){
            arr[y1][col+1] = arr[y1][col];            
        }
        int temp2 = arr[y2][x2];
        for(int row = y2-1; row > y1; row--){
            arr[row+1][x2] = arr[row][x2];
        }
        arr[y1+1][x2] = temp;
        
        int temp3 = arr[y2][x1];
        for(int col = x1+1; col > x2; col++){
            arr[y2][col-1] = arr[y2][col]
        }
        arr[y2][x2-1]=temp2;
        
        
        for(int row = y1+1; row < y2; row++){
            arr[row-1][x1] = arr[row][x1];
        }
        arr[y2-1][x1] = temp3;
        
        //왼쪽
        //위
        //오른쪽
        //아래
        
    }
    return answer;
}
