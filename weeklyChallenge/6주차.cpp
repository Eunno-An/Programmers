#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Boxer {
public:
    int number;
    double winRate;
    int winCount_Heavy;
    int weight;

};
bool compare(Boxer* a, Boxer* b) {
    if (a->winRate == b->winRate) {
        if (a->winCount_Heavy == b->winCount_Heavy) {
            if (a->weight == b->weight)
                return a->number < b->number;
            return a->weight > b->weight;
        }
        return a->winCount_Heavy > b->winCount_Heavy;
    }
    return a->winRate > b->winRate;
}
vector<int> solution(vector<int> weights, vector<string> head2head) {
    vector<int> answer;
    vector<Boxer*> boxers;
    for (int i = 0; i < weights.size(); i++) {
        Boxer* boxer = new Boxer();
        boxer->weight = weights[i];
        boxer->number = i + 1;
        int winCount = 0, totalGameCount = 0;
        int winHeavier = 0;
        for (int j = 0; j < head2head[i].size(); j++) {
            if (head2head[i][j] == 'W') {
                winCount++;
                if (boxer->weight < weights[j])
                    winHeavier++;
            }
            if (head2head[i][j] != 'N') 
                totalGameCount++;
            
        }
        boxer->winCount_Heavy = winHeavier;
        if (totalGameCount == 0)
            boxer->winRate = 0;
        else
            boxer->winRate = (double)winCount / totalGameCount;
        boxers.push_back(boxer);
    }
    sort(boxers.begin(), boxers.end(), compare);
    for (int i = 0; i < boxers.size(); i++)
        answer.push_back(boxers[i]->number);
    return answer;
}
