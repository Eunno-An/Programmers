//문제 소요: 한 3~4시간?
//까다로웠던 점
//좌표가 10만이라 2차원 배열 상에서 표시가 불가.
//compare함수는 y축에 대해 내림차순, x축에 오름차순으로 정렬한 함수임.
//재귀 함수를 돌면서 leftSubTree와 rightSubTree로 나눠가면서, compare함수를 사용하여 각 Tree를 정렬하면 맨 앞에 오는 요소가 루트임을 알 수 있음.
//이런식으로 붙여가면서 사용하면 됨.



#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

bool compare(vector<int> a, vector<int> b){
    if(a[2] == b[2])
        return a[1] < b[1];
    return a[2] > b[2];
}
int parent[10001];
vector<vector<int>> oldNodeInfo;
vector<vector<int>> newNodeInfo;
/*
newNodeInfo 정보
7 8 6
4 3 5
2 11 5
6 1 3
1 5 3
3 13 3
9 2 2
8 7 2
5 6 1
*/
vector<vector<int>> adj_list;

void makeBinaryTree(int parentNodeNum, int nodeIdx, vector<vector<int>> Tree, vector<vector<int>> leftSubTree, vector<vector<int>> rightSubTree){
    int x = oldNodeInfo[parentNodeNum][0];
    
    //leftSubTree, rightSubTree 분류
    vector<vector<int>> leftSubTree, rightSubTree;
    for(int i=0; i<Tree.size(); i++){
        if(Tree[i][1] < x)
            leftSubTree.push_back(Tree[i]);
        else
            rightSubTree.push_back(Tree[i]);
    }
    
    //leftSubTree에서 부모노드 찾기
    
    //rightSubTree에서 부모노드 찾기.
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    
    memset(parent, 0, sizeof(parent));
    oldNodeInfo = nodeinfo;
    newNodeInfo.clear();
    vector<int> temp;
    for(int i=0; i<nodeinfo.size(); i++){
        temp = {i+1, nodeinfo[i][0], nodeinfo[i][1]};
        newNodeInfo.push_back(temp);
    }
    sort(newNodeInfo.begin(), newNodeInfo.end(), compare);
    for(int i=0; i<newNodeInfo.size(); i++)
        cout << newNodeInfo[i][0] << ' ' << newNodeInfo[i][1] << ' ' <<newNodeInfo[i][2] << '\n';
    
    
    
    
    return answer;
}
