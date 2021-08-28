//부족한게 많았던 부분.
//0.
//시간복잡도. 문제에 분명 "cmd에 등장하는 모든 X들의 값을 합친 결과가 1,000,000 이하인 경우만 입력으로 주어집니다."
//이건 얼핏하면 낚이기 쉬운 문제임. cmd 최대 원소 개수가 20만이고, 20만 * 백만으로 계산해서 절대 안될거라고 생각했음.
//근데 말장난임. 20만 + 백만으로 계산해야하는 문제임. 따라서 Up 또는 Down 명령은 링크드 리스트의 순차 탐색으로 충분히 가능한 문제였음. 
//1. 
//list의 erase, deque의 erase는 O(n)타임이 걸린다! 특히 리스트는 내 생각으로는.. 상수 타임이 될 줄 알았는데... 그게 아니라서 ... 좀 놀랐음.
//2.
//doublelylinkedlist는 '복원' 명령과 찰떡이다!! 그렇지 않다고 생각할 수 있겠지만.. 소름돋았다. 왜냐하면, 기존에 prev와 next를 저장해 둔 상태기 때문에.

#include <string>
#include <vector>
#include <stack>
using namespace std;
int arr[1000001];
class Node {
public:
    Node(int v) { value = v; next = NULL; prev = NULL; }
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
        if (head == NULL) {//list에 들어있는 노드가 없을 때
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
            if (nowNode->next == NULL) {//현재 행이 가장 마지막 행인 경우
                if (nowNode->prev == NULL)//표에 한개의 행 밖에 없는 경우
                    nowNode = NULL;
                else {
                    nowNode->prev->next = NULL;
                    nowNode = nowNode->prev;
                }
            }
            else {
                //바로 아래 행을 선택
                if (nowNode->prev == NULL) {//표에서 가장 첫번째 항일 경우
                    nowNode = nowNode->next;
                    nowNode->prev = NULL;
                }
                else {
                    nowNode->prev->next = nowNode->next;
                    nowNode->next->prev = nowNode->prev;
                    nowNode = nowNode->next;
                }


            }


        }
        else if (cmd[i] == "Z") {
            Node* recur = erased.top(); erased.pop();
            Node* prevNode = recur->prev;
            Node* nextNode = recur->next;
            if (prevNode == NULL && nextNode == NULL)
                nowNode = recur;
            else if (prevNode != NULL && nextNode == NULL) 
                prevNode->next = recur;
            else if (prevNode == NULL && nextNode != NULL) 
                nextNode->prev = recur;
            else {
                prevNode->next = recur;
                nextNode->prev = recur;
            }
            
            
        }
        else {
            int X = stoi(cmd[i].substr(2, cmd[i].size() - 2));
            if (cmd[i][0] == 'U')
                while (X--) {
                    if (nowNode->prev == NULL)
                        break;
                    nowNode = nowNode->prev;
                }

            else
                while (X--) {
                    if (nowNode->next == NULL)
                        break;
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
