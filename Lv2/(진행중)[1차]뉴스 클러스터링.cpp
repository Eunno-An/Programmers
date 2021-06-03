#include <string>
#include<map>
#include<vector>
using namespace std;

//자카드 유사도: 두 집합의 교집합 크기 / 두 집합의 합집합 크기

int solution(string str1, string str2) {
    int answer = 0;
    
    map<string, int> m1, m2;
    for(int i=0; i<str1.size()-1; i++){
        if(!isalpha(str1[i]) || !isalpha(str1[i+1]) )
            continue;
        string temp = "";
        temp += str1[i];
        temp += str1[i+1];
        if(m1.find(temp) == m1.end()){
            m1.insert(make_pair(temp, 1));
        }else{
            m1[temp]++;
        }
    }
    for(int i=0; i<str2.size()-1; i++){
        if(!isalpha(str2[i]) || !isalpha(str2[i+1]) )
            continue;
        string temp = "";
        temp += str2[i];
        temp += str2[i+1];
        if(m2.find(temp) == m2.end()){
            m2.insert(make_pair(temp, 1));
        }else{
            m2[temp]++;
        }
    }
    
    map<string, int> union_map, sub_map;
    //below = 분모, 합집합
    
    //다중 집합에 대해서도 생각해 주어야 한다.
    for(auto it = m1.begin(); it != m1.end(); it++){
        for(auto it2 = m2.begin(); it2 != m2.end(); it2++){
            if(it->first == it2->second){
                
            }
            else{
                below +=  
            }
        }
    }
    
    
    return answer;
}
