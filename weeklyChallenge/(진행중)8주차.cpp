#include <string>
#include <vector>

using namespace std;
int Length;
vector<int> widths, heights;
int getMinWallet(int idx, int maxH, int maxW, vector<vector<int>> sizes){
    if(idx == Length){
        return maxH * maxW;
    }
    int nowH = sizes[idx][0];
    int nowW = sizes[idx][1];
    return min(getMinWallet(idx+1, max(maxH, nowH), max(maxW, nowW), sizes), getMinWallet(idx+1, max(maxH, nowW), max(maxW, nowH), sizes));
    
}
int solution(vector<vector<int>> sizes) {
    int answer = 0;
    Length = sizes.size();
    answer = getMinWallet(0, 0, 0, sizes);
    return answer;
}
//10 7
//12 3 3 12 -> 12 7, 10 12
//8 15 15 8 -> 12 15, 15 12
