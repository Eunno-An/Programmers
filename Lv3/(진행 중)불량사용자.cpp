#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;
    vector<vector<string>> users;
    users.resize(8);
    vector<vector<string>> list;
    list.resize(banned_id.size());
    for (int i = 0; i < user_id.size(); i++)
        users[user_id[i].size()].push_back(user_id[i]);

    for (int i = 0; i < banned_id.size(); i++) {
        string banned = banned_id[i];
        vector<int> pos_star;
        for (int j = 0; j < banned.size(); j++)
            if(banned[j] == '*')
                pos_star.push_back(j);
        
        int banned_size = banned.size();
        vector<string>& banned_list = users[banned_size];//user_id의 사이즈가 banned_id의 사이즈와 같은 것들
        
        for (int j = 0; j < banned_list.size(); j++) {
            string& userID = banned_list[j];
            string temp = userID;
            for (int k = 0; k < pos_star.size(); k++) {
                int star_pos = pos_star[k];
                userID[star_pos] = '*';
            }
            if(userID == banned){
                list[i].push_back(temp);
            }
            userID = temp;
        }
    }
    for(int i=0; i<list.size(); i++){
        for(int j=0; j<list[i].size(); j++)
            cout << list[i][j] << ' ';
        cout << '\n';
    }
    
    
    return answer;
}
