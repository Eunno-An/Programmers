#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(int n, long long k) {
    vector<int> answer;
    for(int i=1; i<=n; i++)
        answer.push_back(i);
    int count = 1;
    do{
        if(count++ == k)
            break;
    }while(next_permutation(answer.begin(), answer.end()));
    return answer;
}
