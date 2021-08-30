#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    map<string, pair<int, int>> ranges;
    for(int i=0; i<gems.size(); i++)
        if(ranges.find(gems[i]) == ranges.end())
            ranges.insert(make_pair(gems[i], make_pair(i+1, i+1)));
        else
            ranges[gems[i]].second=i+1;
    
    for(auto it : ranges)
        cout << it.first << " (" << it.second.first << ", " << it.second.second << ")\n"; 
    
    return answer;
}
