//fail.. 도대체 어떤 부분이 잘못된걸까.
//시간초과에다가 거의 다 틀렸다고 뜨는 풀이.
#include <string>
#include <vector>
#include <cstring>

#include<iostream>
using namespace std;


int gcd(int a, int b) {
    if (b == 0) return 1;
    return gcd(b, a % b);
}
int lca(int a, int b) {
    return a * b / gcd(a, b);
}
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
    int lcaX = lca(a[0], b[0]);
    int lcaY = lca(a[1], b[1]);
    //lcaX로 접점 찾기
    //Y계수만 남기는 과정
    int multiX1 = lcaX / a[0];
    int multiX2 = lcaX / b[0];
    for (int i = 1; i <= 2; i++) {
        a[i] *= multiX1;
        b[i] *= multiX2;
    }
    
    int left = a[1] - b[1];//Y의 계수
    int right = b[2] - a[2];//상수
    if (left == 0) return false;
    else {
        if (right % left == 0) {
            ret.second = right / left; // Y좌표.
            int left1 = a[0];//X의 계수
            if ((a[2] + a[1] * ret.second) * -1 % a[0] == 0) {
                //X좌표가 정수라면
                ret.first = ((a[2] + a[1] * ret.second) * -1 / (a[0] * multiX1));
                return true;
            }
            else
                return false;
        }
    }
}
bool getIntersection_Point2(bool type, int a, vector<int> b, pair<int, int>& ret) {
    //type false : y=k 또는 type true: x=k와 어떤 직선과의 교점
    int left;//left: 상수
    if (type == false) {
        left = (b[1] * a + b[2]) * -1;
        if (left % b[0] == 0) {//나머지가 0인 경우, 즉 가능한 경우
            ret.first = left / b[0];
            ret.second = a;
            return true;
        }
        else
            return false;
    }
    else {
        left = (b[0] * a + b[2]) * -1;
        if (left % b[1] == 0) {
            ret.first = left / b[1];
            ret.second = a;
            return true;
        }
        else
            return false;
    }
}
bool getIntersection_Point3(int a, int b, pair<int, int>& ret) {//y=k와 x=l의 교점
    ret.first = b;
    ret.second = a;
    return true;
}

vector<string> solution(vector<vector<int>> line) {
    bool visit[1001];//이미 처리한 배열 확인
    memset(visit, false, sizeof(visit));
    vector<string> answer;
    vector<pair<int, int>> intersection_points;
    

    //x의 계수가 0이거나, y의계수가 0인 것들을 미리 계산해서 빼놓는다. 함수 구현할 때 너무 불편함.
    for (int i = 0; i < line.size(); i++) {
        pair<int, int> ret;
        if (line[i][0] == 0) {
            visit[i] = true;
            if ((line[i][2] * -1) % line[i][1] == 0) {//y=k그래프이면서 k가 정수인 경우
                int y = (line[i][2] * -1) / line[i][1];
                for (int j = i + 1; j < line.size(); j++) {
                    if (line[j][0] == 0) //y축에 평행한 그래프임. 만날 일 없음
                        continue;
                    else if (line[j][1] == 0) {//x축에 평행한 그래프
                        if ((line[j][2] * -1) % line[j][0] != 0)
                            continue;
                        int x = (line[j][2] * -1) / line[j][0];
                        if (getIntersection_Point3(y, x, ret))
                            intersection_points.push_back(ret);
                    }
                    else
                        if (getIntersection_Point2(false, y, line[j], ret))
                            intersection_points.push_back(ret);
                }
            }
        }
        else if (line[i][1] == 0){
            visit[i] = true;
            if ((line[i][1] * -1) % line[i][2] == 0) {//x=k그래프 이면서 k개 정수인 경우
                int x = (line[i][2] * -1) / line[i][0];
                for (int j = i + 1; j < line.size(); j++) {
                    if (line[j][1] == 0) //x축에 평행한 그래프임. 만날 일 없음
                        continue;
                    else if (line[j][0] == 0) {//y축에 평행한 그래프
                        if ((line[j][2] * -1) % line[j][1] != 0)
                            continue;
                        int y = (line[j][2] * -1) / line[j][1];
                        if (getIntersection_Point3(y, x, ret))
                            intersection_points.push_back(ret);
                    }
                    else
                        if (getIntersection_Point2(true, x, line[j], ret))
                            intersection_points.push_back(ret);
                }
            }
        }
    }

    for (int i = 0; i < line.size(); i++) {
        if (visit[i]) continue;
        for (int j = i + 1; j < line.size(); j++) {
            if (visit[j]) continue;
            if (checkIntersection(line[i], line[j]) == true) {//한 점에서 만나는 경우
                pair<int, int> ret;
                if (getIntersection_Point(line[i], line[j], ret))
                    intersection_points.push_back(ret);
            }
        }
    }
    int minY = intersection_points[0].second;
    int maxY = intersection_points[0].second;
    int minX = intersection_points[0].first;
    int maxX = intersection_points[0].first;
    for (int i = 1; i < intersection_points.size(); i++) {
        int y = intersection_points[i].second;
        int x = intersection_points[i].first;
        if (minY > y)
            minY = y;
        if (minX > x)
            minX = x;
        if (maxY < y)
            maxY = y;
        if (maxX < x)
            maxX = x;
    }
    for (int i = 0; i < intersection_points.size(); i++) {
        intersection_points[i].second -= minY;
        intersection_points[i].first -= minX;
    }
    int height = maxY - minY + 1;
    int width = maxX - minX + 1;
    answer.resize(height);
    for (int i = 0; i < answer.size(); i++)
        answer[i].resize(width, '.');
    for (int i = 0; i < intersection_points.size(); i++) {
        int y = intersection_points[i].second;
        int x = intersection_points[i].first;
        answer[height - y - 1][x] = '*';
    }
    return answer;
}
int main() {
    vector<string> ret = solution({ {2, -1, 4},{-2, -1, 4},{0, -1, 1},{5, -8, -12},{5, 8, 12} });
    //solution({ {0, 1, -1},{1, 0, -1},{1, 0, 1} });
    for (int i = 0; i < ret.size(); i++){
        for (int j = 0; j < ret[i].size(); j++)
            cout << ret[i][j];
        cout << endl;
    }
}
