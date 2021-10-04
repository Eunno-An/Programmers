#include <string>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    int matrix[101][101];
    int incoming[101];
    int outcoming[101];
    memset(matrix, 0, sizeof(matrix));
    memset(incoming, 0, sizeof(incoming));
    memset(outcoming, 0, sizeof(outcoming));
    for(int i=0; i<results.size(); i++){
        int winner = results[i][0];
        int loser = results[i][1];
        matrix[winner][loser]=1;
        matrix[loser][winner]=-1;
        incoming[loser]++;
        outcoming[winner]++;
    }
    bool finish = true;
    int nodeNum = n;
    while(finish){
        finish=false;
        
        for(int i=1; i<=n; i++){
            
            if(incoming[i]+outcoming[i] == nodeNum-1){
                nodeNum--;
                finish = true;
                answer++;
                vector<int> losers;//i한테 진 애들
                vector<int> winners;//i한테 이긴 애들
                for(int j=1; j<=n && j != i; j++){
                    if(matrix[i][j] == 1)//i가 j를 이겼을 때 
                        losers.push_back(j);    
                    else if(matrix[i][j] == -1)//i가 j한테 졌을 떄
                        winners.push_back(j);
                }
                for(int j=0; j<losers.size(); j++){
                    int first = losers[j];
                    for(int k=0; k<winners.size(); k++){
                        int second = winners[k];
                        matrix[second][first]=1;
                        matrix[first][second]=-1;
                    }
                }
                for(int j=1; j<=n; j++){
                    matrix[i][j]=0;
                    matrix[j][i]=0;
                }
                for(int j=1; j<=n; j++){
                    int num_income =0, num_outcome=0;
                    for(int k=1; k<=n; k++){
                        if(matrix[j][k] == 1)
                            num_outcome++;
                        else if(matrix[j][k] == -1)
                            num_income++;
                    }
                    incoming[j] = num_income;
                    outcoming[j] = num_outcome;
                }
            }
        }
        
    }
    
    return answer;
}
