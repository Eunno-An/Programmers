//나의 플로이드 와샬 알고리즘 문제점을 알려준 문제.
//플로이드 와샬은 1부터 n까지의 모든 정점들끼리의 최단거리를 구하는 문젠데
//내가 실수했던 부분은 
//dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
//위와 같은 식을 쓰기 위해서는, k가 맨 바깥 for문에 위치해 있어야 하는데, 엉뚱하게 안에다 집어넣었었음.
/* 내가 실수했던 code
for(int i=1; i<=n; i++){
  for(int j=1; j<=n; j++){
    for(int k=1; k<=n; k++){
      dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
   }
}
*/
#include <string>
#include <vector>

using namespace std;
int dist[201][201];
const int MAX = 20000000;
int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = MAX;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++){
            if(i == j) dist[i][j] = 0;
            else dist[i][j] = MAX;
        }
    for(int i=0; i<fares.size(); i++){
        int pointA = fares[i][0];
        int pointB = fares[i][1];
        int fare = fares[i][2];
        dist[pointA][pointB]=fare;
        dist[pointB][pointA]=fare;
    }
    for(int k=1; k<=n; k++){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    for(int i=1; i<=n; i++)
        answer = min(dist[i][a] + dist[i][b] + dist[s][i], answer);
    
    return answer;
}
