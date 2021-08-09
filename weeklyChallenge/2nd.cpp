#include <string>
#include <vector>
#include <algorithm>
using namespace std;

char getGrade(double score){
    if(score>=90)
        return 'A';
    else if(score>=80)
        return 'B';
    else if(score>=70)
        return 'C';
    else if(score>=60)
        return 'D';
    else
        return 'F';
}
string solution(vector<vector<int>> scores) {
    string answer = "";
    
    
    for(int me = 0; me<scores.size(); me++){
        vector<int> scores_me;
        int my_score = scores[me][me];
        for(int other=0; other<scores.size(); other++)
            scores_me.push_back(scores[other][me]);
        sort(scores_me.begin(), scores_me.end());
        if(my_score == scores_me[0] && scores_me[0] != scores_me[1])
            scores_me.erase(scores_me.begin());
        else if(my_score == scores_me.back() && scores_me.back() != scores_me[scores_me.size()-2])
            scores_me.pop_back();
        double totalScore = 0;
        for(int i=0; i<scores_me.size(); i++)
            totalScore+=scores_me[i];
        totalScore /= scores_me.size();
        answer += getGrade(totalScore);
    }
    return answer;
}
