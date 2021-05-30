#include <string>
#include<cstring>
#include <vector>
#include <deque>
#include <set>
#include<iostream>
using namespace std;

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;
    if(cacheSize == 0){
        return cities.size() * 5;
    }
    vector<string> cache;
    
    for(int i=0; i<cities.size(); i++){
        string cityName = cities[i];
        if(cache.empty()){
            cache.push_back(cityName);
            answer+=5;
            continue;
        }   
        int count =0 ;
        bool flag = false;
        for(int j=0; j<cache.size(); j++){
            if(strcasecmp(cityName.c_str(),cache[j].c_str()) == 0){
                cache.erase(cache.begin() + j);
                cache.push_back(cityName);
                answer+=1;
                flag = true;
                break;
            }
            count++;
        }
        if(count == cache.size() && !flag){
            cache.push_back(cityName);
            if(cache.size() > cacheSize){
                cache.erase(cache.begin());
            }
            answer+=5;
        }
       
        
    }
    return answer;
}
