#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
//2020 카카오 인턴쉽
//pair로 하면 진짜 쉽게 풀리는 문제를.. 그냥 거리로만 계산하려다가!
//만약 왼손가락이 4, 오른손가락이 3 일때 5를 누르려면 거리를 계산하다가 이상하게 꼬여버리게 짜버려서..

pair<int, int> keypad[12]; 
int get_distance(pair<int, int> a, pair<int, int> b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}
string solution(vector<int> numbers, string hand) {
    string answer = "";
    int count = 0;
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            keypad[count] = make_pair(i, j);
            count++;
        }
    }
    pair<int, int> left_thumb = make_pair(3, 0);
    pair<int, int> right_thumb = make_pair(3, 2);
    
    for(int i=0; i<numbers.size(); i++){
        pair<int, int> number_point;
        if(numbers[i] == 0)
            number_point = make_pair(3, 1);
        else
            number_point = keypad[numbers[i]-1];
        
        if(numbers[i] == 1 || numbers[i] == 4 || numbers[i] == 7){
            answer += 'L';
            left_thumb = number_point;
        }
        else if(numbers[i] == 3 || numbers[i] == 6 || numbers[i] == 9){
            answer += 'R';
            right_thumb = number_point;
        }
        else{
            if(get_distance(left_thumb, number_point) < get_distance(right_thumb, number_point)){
                answer += 'L';
                left_thumb = number_point;
            }else if(get_distance(left_thumb, number_point) > get_distance(right_thumb, number_point)){
                answer += 'R';
                right_thumb = number_point;
            }else{
                if(hand == "left"){
                    answer += 'L';
                    left_thumb = number_point;
                }else{
                    answer += 'R';
                    right_thumb = number_point;
                }
            }
        }
    }
    return answer;
}
