#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> temp;
int solution(vector<int> people, int limit) {
    int answer = 0;
    sort(people.begin(), people.end());
    
    for(int i=1; i< people.size(); i++){
        if(people[i] + people[0] > limit){
            answer++;
        }else{
            temp.push_back(people[i]);
        }
    }
    //temp에 있는 것들끼리 구명보트를 최대한 적게 사용하여 모든 사람을 구출하면 됨.
    //적절한 방법으로, 두명씩 짝지었을 때, 짝의 개수를 줄이면 됨.
    //temp의 길이가 홀수라면, 한명은 반드시 혼자 타야함.
    //temp의 길이가 짝수라면, ? 이건 또 모름.
    
    //최적화 문제를 푸는 방법
    //모든 경우에 대해 생각해야 한다.
    //그럼 N^2이 걸리는데, 그럼 안되고, 어떤 무게 W를 골랐을 때, limit >= W + Choice
    //즉, limit-W와 가장 가까운 같거나 작은 값을 이분탐색으로 골라야 한다.
    //만약 해당 식을 만족하는 Choice가 있으면 W와 Choice는 선택에서 제외되고, 구명보트 개수는 ++.
    //그렇지 않다면 +=2
    
    //근데 우린 지금 사람의 최대 몸무게가 240키로니까, 
    
    //구명보트의 개수는 최소 n/2(n이 짝수), n/2+1(n이 홀수)개에서 
    //최대 n개 까지 필요하다.
    //구명보트의 개수가 i일 때 구출할 수 있는가 없는가의 결정문제로 바꿔야 하나?
    
    vector<bool> visit(temp.size(), false);
    for(int i=0; i<temp.size(); i++){
        int W = temp[i];
        int idx = lower_bound(temp.begin()+i, v.end(), limit-W) - temp.begin();
    }
    return answer;
}
