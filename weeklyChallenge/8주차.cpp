//fail
//하나의 모서리를 그냥 가로라고 가정하고
//다른 모서리를 세로라고 가정함.
//각 변 중 가장 큰 것을 가로라고 하고, 작은 것을 세로라고 하면
//결국 가장 큰 값들끼리 짝을 지은게 필요한 최소 공통 명함의 길이가 될 것임
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> sizes) {
    int answer = 0;
    int bigWidth = 0, bigHeight = 0;
    for(int i=0; i<sizes.size();i++){
        if(sizes[i][0] < sizes[i][1])
            swap(sizes[i][0], sizes[i][1]);
        if(bigWidth < sizes[i][0])
            bigWidth = sizes[i][0];
        if(bigHeight < sizes[i][1])
            bigHeight = sizes[i][1];
    }
    answer = bigWidth * bigHeight;
    return answer;
}
