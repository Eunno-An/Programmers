#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;

void print_dict_bully_Info(map<string, set<string>> dict_bully){
    for(auto it : dict_bully){
        for(auto it2 : dict_bully[it.first])
            cout << it2 << ' ';
        cout << endl;
    }
}
bool customCompare(string a, string b){//a가 userId, b가 bullyUserId
    if(a.size() != b.size())
        return false;
    for(int i=0; i<a.size(); i++)
        if(b[i] != '*' && a[i]!=b[i])
            return false;
    return true;
}
void get_number_of_cases_list(vector<string> banned_id, int idx, map<string, set<string>> dict_bully, set<string> tempBullys, set<set<string>>& Bullys){
    if(idx == banned_id.size()){
        Bullys.insert(tempBullys);
        return ;
    }
    
    for(auto it : dict_bully[banned_id[idx]]){
        string tempUser = it;
        if(tempBullys.find(it) != tempBullys.end())
            continue;
        tempBullys.insert(it);
        get_number_of_cases_list(banned_id, idx+1, dict_bully, tempBullys, Bullys);
        tempBullys.erase(tempBullys.find(tempUser));
    }
    
    return ;
}
int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;
    map<string, set<string>> dict_bully;
    for(int i=0; i<banned_id.size(); i++){
        string bullyUser=banned_id[i];
        for(int j=0; j<user_id.size(); j++){
            string user = user_id[j];
            if(customCompare(user, bullyUser)){
                if(dict_bully.find(bullyUser)==dict_bully.end()){
                    set<string> s1;
                    s1.insert(user);
                    dict_bully.insert(make_pair(bullyUser, s1));
                }
                else
                    dict_bully[bullyUser].insert(user);
            }
        }
    }
    set<set<string>> Bullys;
    set<string> tempBullys;
    get_number_of_cases_list(banned_id, 0, dict_bully, tempBullys, Bullys);
    
    for(auto it : Bullys)
        if(it.size() == banned_id.size())
            answer++;
    
    return answer;
}
int main(){
    solution({"frodo", "fradi", "crodo", "abc123", "frodoc"}, {"*rodo", "*rodo", "******"});
}
