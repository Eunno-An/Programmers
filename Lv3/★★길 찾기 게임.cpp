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
//1. 트리를 완성한다.
//트리를 어떻게 완성할 것인지? 
//배열에 좌표 표시? 그럼 10만 * 10만 배열 잡아야 하므로 배열은 안됨.
//벡터로 표시? nodeInfo 정보를 받아서 다시 새로운 정보 {nodeNum, x, y}가 들어 있는 벡터를 만든다. = newNodeInfo
//newNodeInfo를 y좌표에 내림차순 정렬을 하고, y좌표가 같을 경우 x좌표에 오름차순 정렬을 한다.

//그리고 newNodeInfo는 현재 균형 이진 트리가 아니고, x축 좌표의 값으로 나누는 이진트리 이다!
//현재 parent의 x좌표보다 작은 애들을 leftSubtree, 큰 애들을 rightSubtree로 분류한다.

//leftSubtree에서 부모를 찾는다, rightSubtree도 마찬가지이다.
//2. 전위, 후위 순회를 한다.

//y값은 내림차순, y값이 같을 경우 x좌표는 오름차순으로 정렬
bool compare(vector<int> a, vector<int> b) {
    if (a[2] == b[2])
        return a[1] < b[1];
    return a[2] > b[2];
}

//x값에 오름차순으로 정렬
bool compare2(vector<int> a, vector<int> b) {
    return a[1] < b[1];
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
class Node {
public :
    int nodeNum;
    int nodeX;
    int nodeY;
    int left, right;
    Node(int N, int x, int y, int l, int r) {
        this->nodeNum = N;
        this->nodeX = x;
        this->nodeY = y;
        this->left = l;
        this->right = r;
    }
};
vector<Node*> adj_list;

vector<int> ret_preOrder, ret_postOrder;
void makeBinaryTree(int parentNodeNum, vector<vector<int>> Tree) {
    Node* root = new Node(Tree[0][0], Tree[0][1], Tree[0][2], -1, -1);
    int rootNum = Tree[0][0];
    int rootX = Tree[0][1];
    //leftSubTree, rightSubTree 분류
    vector<vector<int>> leftSubTree, rightSubTree;
    for (int i = 1; i < Tree.size(); i++) {
        if (Tree[i][1] < rootX)
            leftSubTree.push_back(Tree[i]);
        else
            rightSubTree.push_back(Tree[i]);
    }
   
    //leftSubTree에서 부모노드 찾기
    if (leftSubTree.size() != 0) {
        sort(leftSubTree.begin(), leftSubTree.end(), compare);
        int midNodeNum_left = leftSubTree[0][0];
        root->left = midNodeNum_left;
        makeBinaryTree(midNodeNum_left, leftSubTree);
    }

    //rightSubTree에서 부모노드 찾기.
    if (rightSubTree.size() != 0) {
        sort(rightSubTree.begin(), rightSubTree.end(), compare);
        int midNodeNum_right = rightSubTree[0][0];
        root->right = midNodeNum_right;
        makeBinaryTree(midNodeNum_right, rightSubTree);
    }
    adj_list[rootNum] = root;
    return;
}

void preOrder(int parentNodeNum) { // 전위 순회
    ret_preOrder.push_back(parentNodeNum);
    if (adj_list[parentNodeNum]->left * adj_list[parentNodeNum]->right == 1)
        return;
    
    
    if(adj_list[parentNodeNum]->left != -1)
        preOrder(adj_list[parentNodeNum]->left);
    if (adj_list[parentNodeNum]->right != -1)
        preOrder(adj_list[parentNodeNum]->right);
}
void postOrder(int parentNodeNum) { // 후위 순회
    if (adj_list[parentNodeNum]->left * adj_list[parentNodeNum]->right == 1) {
        ret_postOrder.push_back(parentNodeNum);
        return;
    }
    if (adj_list[parentNodeNum]->left != -1)
        postOrder(adj_list[parentNodeNum]->left);
    if (adj_list[parentNodeNum]->right != -1)
        postOrder(adj_list[parentNodeNum]->right);
    ret_postOrder.push_back(parentNodeNum);
    
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;

    memset(parent, 0, sizeof(parent));
    adj_list.resize(nodeinfo.size() + 1);
    oldNodeInfo = nodeinfo;
    newNodeInfo.clear();
    ret_preOrder.clear();
    ret_postOrder.clear();
    
    vector<int> temp;
    for (int i = 0; i < nodeinfo.size(); i++) {
        temp = { i + 1, nodeinfo[i][0], nodeinfo[i][1] };
        newNodeInfo.push_back(temp);
    }
    sort(newNodeInfo.begin(), newNodeInfo.end(), compare);
    for (int i = 0; i < newNodeInfo.size(); i++)
        cout << newNodeInfo[i][0] << ' ' << newNodeInfo[i][1] << ' ' << newNodeInfo[i][2] << '\n';

    makeBinaryTree(newNodeInfo[0][0], newNodeInfo);
    
    preOrder(newNodeInfo[0][0]);
    answer.push_back(ret_preOrder);
    
    postOrder(newNodeInfo[0][0]);
    answer.push_back(ret_postOrder);


    return answer;
}

int main() {
    solution({{5, 3}, {11, 5}, {13, 3}, {3, 5}, {6, 1}, {1, 3}, {8, 6}, {7, 2}, {2, 2}} );
}
