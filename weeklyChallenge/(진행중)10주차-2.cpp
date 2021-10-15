#include <string>
#include <vector>
#include <cstring>
using namespace std;

//무수히 많은 교점이 생기는 직선 쌍은 주어지지 않는다.
//A=0 && B=0인 경우는 주어지지 않는다.
//정담은 1000 * 10000 크기 이내에서 표현 가능하다.
//별이 한 개 이상 그려지는 입력만 주어진다.

//a직선과 b직선의 관계를 파악한다.
//앞에서부터 x, y의 계수, 그리고 상수

bool checkIntersection(vector<int> a, vector<int> b) {
    if (a[0] == 0 && b[0] == 0) //y = k 형태
        return false;
    if (a[1] == 0 && b[1] == 0) //x = k 형태
        return false;
    //기울기가 같은 경우
    double tilt_a = (a[0] * -1) / a[1];
    double tilt_b = (b[0] * -1) / b[1];
    if (tilt_a == tilt_b)
        return false;
    return true;
}
bool getIntersection_Point(vector<int> a, vector<int> b, pair<int, int>& ret) {
     
}
bool getIntersection_Point2(bool type, int a, vector<int> b, pair<int, int>& ret) {//type false : y=k 또는 type true: x=k와 어떤 직선과의 교점

}
bool getIntersection_Point3(int a, int b, pair<int, int>& ret) {//y=k와 x=l의 교점

}

vector<string> solution(vector<vector<int>> line) {
    bool visit[1001];//이미 처리한 배열 확인
    memset(visit, false, sizeof(visit));
    vector<string> answer;
    vector<pair<int, int>> intersection_points;
    

    //x의 계수가 0이거나, y의계수가 0인 것들을 미리 계산해서 빼놓는다. 함수 구현할 때 너무 불편함.
    for (int i = 0; i < line.size(); i++) {
        pair<int, int> ret;
        if (line[i][0] == 0 && (line[i][2] * -1) % line[i][1] != 0) {//y=k그래프이면서 k가 정수인 경우
            visit[i] = true;
            int y = (line[i][2] * -1) / line[i][1];
            for (int j = i+1; j < line.size(); j++) {
                if (line[j][0] == 0) //y축에 평행한 그래프임. 만날 일 없음
                    continue;
                else if (line[j][1] == 0) {//x축에 평행한 그래프
                    int x = (line[j][2] * -1) / line[j][0];
                    if (getIntersection_Point3(y, x, ret))
                        intersection_points.push_back(ret);
                }
                else 
                    if (getIntersection_Point2(false, y, line[j], ret))
                        intersection_points.push_back(ret);
            }
        }
        else if (line[i][1] == 0 && (line[i][1] * -1) % line[i][2] != 0) {//x=k그래프 이면서 k개 정수인 경우
            visit[i] = true;
            int x = (line[i][2] * -1) / line[i][0];
            for (int j = i + 1; j < line.size(); j++) {
                if (line[j][1] == 0) //x축에 평행한 그래프임. 만날 일 없음
                    continue;
                else if (line[j][0] == 0) {//y축에 평행한 그래프
                    int y = (line[j][2] * -1) / line[j][1];
                    if (getIntersection_Point3(y, x, ret))
                        intersection_points.push_back(ret);
                }
                else
                    if (getIntersection_Point2(false, x, line[j], ret))
                        intersection_points.push_back(ret);
            }
        }
    }

    for (int i = 0; i < line.size(); i++) {
        if (visit[i]) continue;
        for (int j = i + 1; j < line.size(); j++)
            if (checkIntersection(line[i], line[j]) == true) {//한 점에서 만나는 경우
                pair<int, int> ret;
                if(getIntersection_Point(line[i], line[j], ret))
                    intersection_points.push_back(ret);
            }
    }
    
    return answer;
}
