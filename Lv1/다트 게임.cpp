#include <string>
#include <vector>
#include <iostream>
using namespace std;
//예외처리가 좀 귀찮은 문제
//char형 int로 데이터 변환 : s[i] - '0';
//vector.back() -> 바로 요소를 반환
//vector.end() -> 벡터의 끝 보다 한칸 뒤의 주소를 반환.
//숫자 10에 대한 예외처리 -> i++ 시켜주기
int solution(string dartResult) {
    int answer = 0;
    //점수는 0에서 10 사이의 정수. 즉 0, 1, 2, ..., 10까지의 점수가 들어갈 수 있다.
    int temp_score=0;
    vector<int> vector_score;
    int prize_count = 1;
    for(int i=0; i<dartResult.size(); i++){
        if(isdigit(dartResult[i])){
            if(i != dartResult.size() - 1 && dartResult[i] == '1' && dartResult[i+1] == '0'){
                //dartResult에 들어간 점수가 10점일 경우
                temp_score = 10;
                i++;
            }else{
                temp_score = dartResult[i] - '0';
            }
            prize_count = 1;
        }
        else if(isalpha(dartResult[i])){
            if(dartResult[i] == 'D'){
                temp_score *= temp_score;    
            }else if(dartResult[i] == 'T'){
                temp_score = temp_score * temp_score * temp_score;
            }
            vector_score.push_back(temp_score);
        }
        else{
            if(dartResult[i] == '*'){
                if(vector_score.size() > 1){
                    *(vector_score.end() - 2) *= 2 * (prize_count);
                }
                vector_score.back() *= 2 * (prize_count);
                prize_count++;
            }else if(dartResult[i] == '#'){
                vector_score.back() *= -prize_count++;
            }
        
        } 
        for(int j=0; j<vector_score.size(); j++){
            cout << vector_score[j] << ' ' ;
        }
        cout << '\n';
    }
    for(int j=0; j<vector_score.size(); j++){
            answer += vector_score[j];
    }
    return answer;
}
