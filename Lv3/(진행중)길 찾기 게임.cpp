#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
//1. 트리를 완성한다.
//트리를 어떻게 완성할 것인지? 
//배열에 좌표 표시? 그럼 10만 * 10만 배열 잡아야 하므로 배열은 안됨.
//벡터로 표시? nodeInfo 정보를 받아서 다시 새로운 정보 {nodeNum, x, y}가 들어 있는 벡터를 만든다. = newNodeInfo
//newNodeInfo를 y좌표에 내림차순 정렬을 하고, y좌표가 같을 경우 x좌표에 오름차순 정렬을 한다.

//그리고 newNodeInfo는 현재 균형 이진 트리가 아니고, x축 좌표의 값으로 나누는 이진트리 이다!
//현재 parent의 x좌표보다 작은 애들을 leftSubtree, 큰 애들을 rightSubtree로 분류한다.

//leftSubtree에서 부모를 찾는다, rightSubtree도 마찬가지이다.
//2. 전위, 후위 순회를 한다.
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
