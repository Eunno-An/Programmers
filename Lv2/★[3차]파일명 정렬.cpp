//success


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//중요한 점
//문자열이 100글자가 최대, 근데 모두 다 숫자일 경우, int로 하게 되면 오버플로우가 발생할 수 있음.
//문자열을 한글자씩 비교해줘야 함. 그게 16~20번째 줄.
bool compare(vector<string> a, vector<string> b){
    if(a[0] == b[0]){
        if(a[1].size() == b[1].size()){
            int idx = 0;
            while(a[1].size() != idx){
                if(a[1][idx] != b[1][idx])
                    return a[1][idx] < b[1][idx];
                idx++;
            }
            if(a[1] == b[1])
                return stoi(a[3]) < stoi(b[3]);
            }
        return a[1].size() < b[1].size();
    }
    return a[0] < b[0];
}
vector<string> splitPart(string fileName, int idx_file){//파일이 들어온 순서대로 정렬하기 위해, '파일이 들어온 순서'를 받았음.
    vector<string> ret;
    string head = "";
    int idx=0;
    for(int i=0; i<fileName.size(); i++){
        if(isdigit(fileName[i])){
            idx = i;
            break;
        }
        head += fileName[i];
    }
    string number = "";
    for(int i = idx; i<fileName.size(); i++){
        if(!isdigit(fileName[i])){
            idx = i;
            break;
        }
        number+=fileName[i];
    }
    
    string tail = fileName.substr(idx, fileName.size()-idx);
    ret.push_back(head);
    ret.push_back(number);
    ret.push_back(tail);
    ret.push_back(to_string(idx_file));
    return ret;
}
void normalize(vector<string>& file){
    //HEAD에 있는 문자들을 모두 소문자로 변경
    transform(file[0].begin(), file[0].end(), file[0].begin(), ::tolower);
    
    int idx = 0;
    for(int i=0; i<file[1].size(); i++){
        if(file[1][i] != '0'){
            idx = i;
            break;
        }
        idx++;
    }
    //NUMBER에 맨 앞에 있는 0들을 없앤다.
    file[1] = file[1].substr(idx, file[1].size()-idx);
}
void printInfo(vector<string> file){
    cout << file[0] << ' ' << file[1] << ' ' << file[2] << endl;
}

vector<string> solution(vector<string> files) {
    vector<string> answer;
    
    vector<vector<string>> temp;
    for(int i=0; i<files.size(); i++){
        //1.HEAD, NUMBER, TAIL부분으로 나눈다.
        vector<string> fileInfo = splitPart(files[i], i);
        //printInfo(fileInfo);
        
        //2.HEAD에 있는 대문자들을 모두 소문자로 바꿔주고, NUMBER에 있는 필요없는 0들을 없애준다.
        normalize(fileInfo);
        //printInfo(fileInfo);
        
        temp.push_back(fileInfo);
    }
    sort(temp.begin(), temp.end(), compare);
    
    for(int i=0; i<temp.size(); i++){
        int idx_files = stoi(temp[i][3]);
        answer.push_back(files[idx_files]);
    }
    return answer;
}
