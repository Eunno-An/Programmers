//★★★list의 erase, deque의 erase는 O(n)타임이 걸린다! 특히 리스트는 내 생각으로는.. 상수 타임이 될 줄 알았는데... 그게 아니라서 ... 좀 놀랐음.
//linkedlist는 복원 명령과 찰떡이다!! 그렇지 않다고 생각할 수 있겠지만.. 소름돋았다.
#include <string>
#include <vector>
#include <stack>
using namespace std;
int arr[1000001];
class Node {
public:
    Node(int v) { value = v; }
    int value;
    Node* next;
    Node* prev;

};
class LinkedList {
public:
    Node* head;
    Node* tail;
    LinkedList() {
        head = NULL;
        tail = NULL;
    }
    void addNode(Node* node) {
        node->next = NULL;
        if (head == NULL) {
            node->prev = NULL;
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
    Node* getNextNode(Node* node) {
        return node->next;
    }
    Node* getPrevNode(Node* node) {
        return node->prev;
    }
};
string solution(int n, int k, vector<string> cmd) {
    string answer = "";
    stack<Node*> erased;
    LinkedList linkedList;
    for (int i = 0; i < n; i++) {
        Node* node = new Node(i);
        linkedList.addNode(node);
    }
    Node* nowNode = linkedList.head;
    for (int i = 0; i < k; i++)
        nowNode = nowNode->next;
    for (int i = 0; i < cmd.size(); i++) {
        if (cmd[i] == "C") {//현재 선택된 행 삭제, 바로 아래 행 선택.
            erased.push(nowNode);
            if (nowNode->prev == NULL && nowNode->next == NULL) {
                nowNode = NULL;
                continue;
            }
            if (nowNode->next == NULL && nowNode->prev != NULL) {
                nowNode->prev->next = NULL;
                nowNode = nowNode->prev;
                continue;
            }
            nowNode->prev->next = nowNode->next;
            nowNode->next->prev = nowNode->prev;
            
            
        }
        else if (cmd[i] == "Z") {//
            Node* recur = erased.top();
            erased.pop();
            recur->prev->next = recur;
            recur->next->prev = recur;
        }
        else {
            int X = stoi(cmd[i].substr(2, cmd[i].size() - 2));
            if (cmd[i][0] == 'U') {
                while (X--) 
                    nowNode = nowNode->prev;
                
            }
            else {
                while (X--)
                    nowNode = nowNode->next;
            }
        }
    }
    while (!erased.empty()) {
        int num = erased.top()->value;
        erased.pop();
        arr[num] = 1;
    }
    for (int i = 0; i < n; i++)
        if (arr[i] == 1)
            answer.push_back('X');
        else
            answer.push_back('O');
    return answer;
}
int main() {
    solution(8, 2, { "D 2","C","U 3","C","D 4","C","U 2","Z","Z","U 1","C" });
}
