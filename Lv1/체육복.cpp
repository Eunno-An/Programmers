#include <string>
#include <vector>

using namespace std;
int arr[31];
int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    //2<=n<=30
    //여벌 체육복이 있는 학생이 체육복을 도난 당했을 수도 있음.
    for(int i=1; i<= n; i++){
        arr[i] = 1;
    }
    for(int i=0; i<reserve.size(); i++){
        int res_idx = reserve[i];
        arr[res_idx]++;
    }
    for(int i=0; i<lost.size(); i++){
        int lost_idx = lost[i];
        
        arr[lost_idx] -= 1;
    }
    for(int i=1; i<=n; i++){
        if(arr[i]){
            answer+=1;
        }
    }
    for(int i=1; i<=n; i++){
        if(arr[i] ==0){
            if(i-1 >= 1 && arr[i-1] == 2){
                arr[i-1]--;
                arr[i]++;
                answer++;
            }
            else if(i+1 <= n && arr[i+1] == 2){
                arr[i+1]--;
                arr[i]++;
                answer++;
            }
        }
    }
    return answer;
}
