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
bool compare(vector<int> a, vector<int> b) {
    if (a[2] == b[2])
        return a[1] < b[1];
    return a[2] > b[2];
}
vector<vector<int>> oldNodeInfo;
vector<vector<int>> newNodeInfo;
class Node {
public:
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


    if (adj_list[parentNodeNum]->left != -1)
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

    makeBinaryTree(newNodeInfo[0][0], newNodeInfo);

    preOrder(newNodeInfo[0][0]);
    answer.push_back(ret_preOrder);

    postOrder(newNodeInfo[0][0]);
    answer.push_back(ret_postOrder);


    return answer;
}

int main() {
    solution({ {5, 3}, {11, 5}, {13, 3}, {3, 5}, {6, 1}, {1, 3}, {8, 6}, {7, 2}, {2, 2} });
}
