//문제에 보면 작은 수를 제거하라고 했다.
//작은 수들일 수도 있으니까.. 이런 트릭에 주의하자.
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> arr) {
    vector<int> answer;
    int min_int = numeric_limits<int>::max();
    int min_idx = 0;
    vector<int> min_vec;
    for(int i=0; i<arr.size(); i++){
        if(min_int > arr[i]){
            min_vec.clear();
            min_int = arr[i];
            min_idx = i;
            min_vec.push_back(i);
        }
        else if(min_int == arr[i]){
            min_vec.push_back(i);
        }
    }
    //cout << min_idx << '\n';
    if(arr.size() == 1){
        answer.push_back(-1);
    }else{
        for(int i=0; i<arr.size(); i++){
            bool flag = false;
            for(int j=0; j<min_vec.size(); j++){
                if(min_vec[j] == i){
                    flag = true;
                    break;
                }
            }
            if(!flag)
                answer.push_back(arr[i]);
            
        }
    }
    return answer;
}
