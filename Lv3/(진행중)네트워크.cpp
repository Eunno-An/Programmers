#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int parent[201];
int find(int x){
    if(x == parent[x])
        return x;
    return find(parent[x]);
}
void u(int y, int x){
    y= find(y);
    x= find(x);
    if(y != x)
        parent[y] = x;
}
int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    for(int i=1; i<=n; i++)
        parent[i] = i;
    vector<pair<int, int>> pairs;
    for(int i=0; i<computers.size(); i++)
        for(int j = i + 1; j < computers[i].size(); j++)
            if(computers[i][j])
                pairs.push_back(make_pair(i, j));
    sort(pairs.begin(), pairs.end()); // 앞에 있는게 부모라고 해보자.
    for(int i=0; i<pairs.size(); i++)
        u(pairs[i].first, pairs[i].second);
    for(int i=1; i<=n; i++)
        cout << parent[i] << ' ';
    
    
    
    return answer;
}

/*
기본 네트워크의 개수 n개
만약 k개, 1의 덩어리들이 연결이 되어 있다? 그럼 네트워크의 개수는 
110
110
001

110
111
011


*/
