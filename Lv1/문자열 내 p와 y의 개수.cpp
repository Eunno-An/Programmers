//12번째 줄 참고.
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

bool solution(string s)
{
    bool answer = true;

    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    cout << "Hello Cpp" << endl;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    int p_num = 0, y_num = 0;
    for(int i=0; i<s.size(); i++){
        if(s[i] == 'p'){
            p_num++;
        }
        else if(s[i] == 'y'){
            y_num++;
        }
    }
    
    return p_num == y_num;
}
