#include <string>
#include <vector>
#include <limits>
#include <queue>
#include <set>
using namespace std;

//징검다리를 건널 수 있는 인원수를 구한다.
//== 연속된 0의 개수가 k인 구간이 존재할 때 까지 전체 배열의 요소를 1씩 뺀다.
//
//1. 시뮬레이션으로 구현 -> stones는 2억이 최대이고, 배열 크기는 20만. 당연히 시간초과
//2. 구간을 k개씩 보면서, 그 구간합이 최소인 구간에서 최대 요소를 반환한다. -> 사이즈가 20만 배열이고, k가 10만일 경우 시간초과.
//2-1. 만약 구간합이 최소인 구간이 여러개일 경우 최대 요소가 적은 것을 반환하게 한다. -> 해보니까 정확성도 안나옴. 근데 이건 자료형 문제일 수도 있음.
//3. 


int solution(vector<int> stones, int k) {
    int answer = 0;
    
    long long rangeSum = 0;
    long long minRangeSum = numeric_limits<long long>::max();
    int maxElement = numeric_limits<int>::min();//window에서의 최대값.
   
    //sliding-window
    multiset<int> rangeSet;
    for (int i = 0; i < stones.size(); i++) {
        if (i < k) {
            rangeSum += (long long)stones[i];
            if (maxElement < stones[i])
                maxElement = stones[i];
            
            rangeSet.insert(stones[i]);
            minRangeSum = rangeSum;
            continue;
        }
        rangeSum += stones[i];
        rangeSum -= stones[i - k];
        
        rangeSet.insert(stones[i]);
        rangeSet.erase(rangeSet.find(stones[i - k]));
        
        
        if(minRangeSum > rangeSum){//새로운 최소 구간 합 window가 나올 경우
            minRangeSum = rangeSum;
            maxElement = *(--rangeSet.end());
        }
        else if(minRangeSum == rangeSum)//최소 구간 합은 같은데, 그 구간의 최대값이 더 작은 경우
            if(*(--rangeSet.end()) < maxElement)
                maxElement = *(--rangeSet.end());
        
        
    }
    return answer = maxElement;
}
int main() {
    solution({ 2, 4, 5, 3, 2, 1, 4, 2, 5, 1 }, 3);
}
