#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> arr) 
{
    vector<int> answer;

    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    cout << "Hello Cpp" << endl;
    int num = arr[0];
    for(int i=1; i<arr.size(); i++){
        if(arr[i] == -1){
            continue;
        }
        if(num != arr[i]){
            num = arr[i];
             
        }else{
            arr[i] = -1;
        }
    }
    for(int i=0; i<arr.size(); i++){
        if(arr[i] != -1){
            answer.push_back(arr[i]);
        }
    }
    return answer;
}
