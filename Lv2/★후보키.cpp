#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


int solution(vector<vector<string>> relation) {
    int answer = 0;

    string table[21][9];
    for (int i = 0; i < relation.size(); i++)
        for (int j = 0; j < relation[i].size(); j++)
            table[i][j] = relation[i][j];

    //총 학생의 개수 = 튜플의 개수
    int total_Student = relation.size();
    int number_Column = relation[0].size();
    map<vector<int>, bool> candidate_Keys;

    for (int i = 1; i <= number_Column; i++) {//키의 개수만큼 조합을 뽑는다.
        vector<bool> v(number_Column - i, false);
        v.insert(v.end(), i, true);


        do {
            vector<int> column_key;
            for (int j = 0; j < v.size(); j++)
                if (v[j]) column_key.push_back(j);

            bool isMinimal = true;
            //column_key 중에서 최소성을 만족하는 key의 조합이 있는가를 찾는것.
            //최소 1개 ~ column_key-1개를 선택한 것들의 조합을 따져보자
            for (int j = 1; j < column_key.size(); j++) {
                vector<bool> v1(column_key.size() - j, false);
                v1.insert(v1.end(), j, true);//v1.insert(v.end(), j, true)라고 했다가 런타임 에러떴음.. 진짜 .. 이런 실수..
                do {
                    vector<int> column_key1;
                    for (int k = 0; k < column_key.size(); k++)
                        if (v1[k]) column_key1.push_back(column_key[k]);//이 부분도 column_key[k]를 넣어주어야 함.

                    if (!candidate_Keys.empty() && candidate_Keys.find(column_key1) != candidate_Keys.end()) {
                        isMinimal = false;
                        break;
                    }
                } while (next_permutation(v1.begin(), v1.end()));
                if (!isMinimal)
                    break;
            }

            if (!isMinimal)
                continue;



            map<vector<string>, int> result;
            //이제 table에서 키들의 정보로 뽑아서 맵에다 저장한다.
            for (int j = 0; j < relation.size(); j++) {//row 순회
                vector<string> temp;
                for (int k = 0; k < column_key.size(); k++) //col 순회
                    temp.push_back(relation[j][column_key[k]]);//relations의 j번째행, column_key[k] 열의 요소를 temp에다 넣는다. 키를 구하는 과정임.

                if (result.empty() || result.find(temp) == result.end())
                    result.insert(make_pair(temp, 1));
            }
            if (result.size() == total_Student)
                candidate_Keys.insert(make_pair(column_key, true));

        } while (next_permutation(v.begin(), v.end()));
    }
    answer = candidate_Keys.size();

    return answer;
}
int main() {
    vector<vector<string>>relations;
    relations = { {"100","ryan","music","2"},{"200","apeach","math","2"},{"300","tube","computer","3"},{"400","con","computer","4"},{"500","muzi","music","3"},{"600","apeach","music","2"}
    };
    solution(relations);
}
