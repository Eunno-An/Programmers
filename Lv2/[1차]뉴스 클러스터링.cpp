#include <string>
#include<map>
#include<cstring>
#include<vector>
#include<algorithm>
#include<iostream>
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
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);	// 소문자 변환
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
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);	// 소문자 변환
        if(m2.find(temp) == m2.end()){
            m2.insert(make_pair(temp, 1));
        }else{
            m2[temp]++;
        }
    }
    
    map<string, int> union_map, sub_map;
    //below = 분모, 합집합
    
    for(auto it = m1.begin(); it != m1.end(); it++){
        cout << it->first << ' ' << it->second << '\n';
    }
    for(auto it = m2.begin(); it != m2.end(); it++){
        cout << it->first << ' ' << it->second << '\n';
    }
    //다중 집합에 대해서도 생각해 주어야 한다.
    
    //union_map: 
    for(auto it = m1.begin(); it != m1.end(); it++){
        if(union_map.find(it->first) == union_map.end()){//it->first가 없을 때
            union_map.insert(make_pair(it->first, it->second));
        }
    }
    for(auto it = m2.begin(); it != m2.end(); it++){
        if(union_map.find(it->first) == union_map.end()){
            union_map.insert(make_pair(it->first, it->second));
        }
        else{
            if(union_map[it->first] < it->second){ // m2에 있는 it->first의 개수 > union_map[it->first]의 개수, 즉 중복 요소의 개수가, 기존 합집합에 있는게 더 적을 때 새로 추가해주어야 한다.
                union_map[it->first] = it->second;
            }
        }
    }
    
     for(auto it = union_map.begin(); it != union_map.end(); it++){
        cout << it->first << ' ' << it->second << '\n';
    }
    //sub_map:
    for(auto it1 = m1.begin(); it1 != m1.end(); it1++){
        for(auto it2 = m2.begin(); it2 != m2.end(); it2++){
            if(it1->first == it2->first && sub_map.find(it1->first) == sub_map.end()){
                sub_map.insert(make_pair(it1->first, it1->second < it2->second ? it1->second : it2->second ));
            } //두 개의 문자열이 같고, sub_map에 없을 때
        }
    }
     for(auto it = sub_map.begin(); it != sub_map.end(); it++){
        cout << it->first << ' ' << it->second << '\n';
    }
    int union_map_size = 0, sub_map_size = 0;
    for(auto it = union_map.begin(); it != union_map.end(); it++){
        union_map_size += it->second;
    }
    for(auto it = sub_map.begin(); it != sub_map.end(); it++){
        sub_map_size += it->second;
    }
    if(union_map.size() == 0){
        answer = 65536;
    }else{
        cout << "sub_map.size(): " << sub_map.size() << "\nunion_map.size(): " << union_map.size() << '\n';
        double d_answer = (double)sub_map_size / union_map_size;
        cout << d_answer << '\n';
        answer = d_answer * 65536;
    }
    
    return answer;
}
