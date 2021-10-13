#include <string>
#include <vector>

using namespace std;
//line이 주어지면, 정수 교점 좌표들을 구하여라.
//구한 것들 중 최소 y좌표, 최대 y좌표, 최소 x좌표, 최대 x좌표를 구해서 최소 사각형을 구한다.
//line의 길이는 1000.

//직선과 직선은 단 하나의 교점을 갖는다
//(무수히 많은 교점이 생기는 직선 쌍은 주어지지 않는다고 되어 있음.)
//2x+3y+4=0
//-4
const long long MAX = 9876543210;
class Line {
public:
    Line(long long coX, long long coY, long long c) {
        this->coX = coX;
        this->coY = coY;
        this->c = c;
    }
    long long coX, coY, c;
};
//2x-y+4 = 5x - 8y - 12
//x의 lca계산 -> 10.
//10x-10y+40 = 10x - 16y - 24
//-10 + 16 = -24 - 40
//-64 % 6 != 0.
//어느 한 좌표라도 정수가 아니면 pass
long long gcd(long long a, long long b) {
    if (a == b) return 1;
    return gcd(b, a % b);
}
long long lca(long long a, long long b) {
    return a * b / gcd(a, b);
}
pair<long long, long long> get_Intersection_Point(Line* l1, Line* l2) {
    pair<long long, long long> ret;
    ret.first = MAX;
    ret.second = MAX;
    if (l1->coX == 0 || l2->coX == 0) {
        //둘 중에 어떤건 y = k꼴임. k가 정수가 아니라면 넘어가면 됨.
        long long checkY = (l1->c % (l1->coY * -1));
        if (l1->coX == 0 && l2->coX != 0) {//l1의 x계수가 0인경우
            if (checkY != 0)
                return ret;
            else {
                ret.second = (l1->c / (l1->coY * -1));
                long long checkX = (l2->coY * ret.second * -1 - l2->c) % l2->coX;
                if (checkX != 0)
                    return ret;
                ret.first = (l2->coY * ret.second * -1 - l2->c) / l2->coX;
            }
        }
        else if(l1->coX != 0 && l2->coX == 0){
            if (checkY != 0)
                return ret;
            else {
                ret.second = (l2->c / (l2->coY * -1));
                long long checkX = (l1->coY * ret.second * -1 - l1->c) % l1->coX;
                if (checkX != 0)
                    return ret;
                ret.first = (l1->coY * ret.second * -1 - l1->c) / l1->coX;
            }
        }
        else {//둘다 0이면 평행함.
            return ret;
        }
    }
    else if (l1->coY == 0 || l2->coY == 0) {
        long long checkX = (l1->c % (l1->coX * -1));
        if (l1->coY == 0 && l2->coY != 0) {//l1의 x계수가 0인경우
            if (checkX != 0)
                return ret;
            else {
                ret.second = (l1->c / (l1->coX * -1));
                long long checkY = (l2->coX * ret.second * -1 - l2->c) % l2->coY;
                if (checkY != 0)
                    return ret;
                ret.first = (l2->coX * ret.second * -1 - l2->c) / l2->coY;
            }
        }
        else if(l1->coY != 0 && l2->coY == 0){
            if (checkX != 0)
                return ret;
            else {
                ret.second = (l2->c / (l2->coX * -1));
                long long checkY = (l1->coX * ret.second * -1 - l1->c) % l1->coY;
                if (checkY != 0)
                    return ret;
                ret.first = (l1->coX * ret.second * -1 - l1->c) / l1->coY;
            }
        }
        else {
            return ret;
        }
    }
    else {//둘 다 0이 아닌 경우. 둘 다 0인 경우는 없다.
        long long lcaY = lca(l1->coY, l2->coY);//Y의 최소공배수 구한다.
        long long multiNum_l1 = (lcaY / l1->coY);
        long long multiNum_l2 = (lcaY / l2->coY);
        long long left_co_X = (l1->coX * multiNum_l1 - l2->coX * multiNum_l2);
        long long right_c = (l2->c * multiNum_l2 - l1->c * multiNum_l1);
        if (right_c % left_co_X != 0) {
            return ret;
        }
        else {
            ret.first = (right_c / left_co_X);//X좌표 구했음
            long long left_c = (l1->coX * ret.first + l1->c);
            if (left_c % (l1->coY * -1) != 0)
                return ret;
            ret.second = left_c / (l1->coY * -1);
        }
    }
    return ret;
}
vector<string> solution(vector<vector<int>> line) {
    vector<string> answer;
    vector<Line*> Lines;
    for (int i = 0; i < line.size(); i++) {
        Line* newLine = new Line(line[i][0], line[i][1], line[i][2]);
        Lines.push_back(newLine);
    }
    vector<pair<long long, long long>> intersec_pos;
    for (int i = 0; i < Lines.size(); i++) {
        for (int j = i + 1; j < Lines.size(); j++) {
            pair<long long, long long>ret = get_Intersection_Point(Lines[i], Lines[j]);
            if (ret.first != MAX && ret.second != MAX)
                intersec_pos.push_back(ret);
        }
    }
    long long minY = MAX + 1, minX = MAX + 1, maxY = MAX * -1, maxX = MAX * -1;

    for (int i = 0; i < intersec_pos.size(); i++) {
        if (intersec_pos[i].first > maxX)
            maxX = intersec_pos[i].first;
        if (intersec_pos[i].second > maxY)
            maxY = intersec_pos[i].second;
        if (intersec_pos[i].first < minX)
            minX = intersec_pos[i].first;
        if (intersec_pos[i].second < minY)
            minY = intersec_pos[i].second;
    }
    answer.resize(maxX - minX + 1);
    for (long long i = 0; i < maxX - minX + 1; i++)
        answer[i].resize(maxY - minY + 1, '.');
    for (int i = 0; i < intersec_pos.size(); i++) {
        long long pos_X = intersec_pos[i].first;
        long long pos_Y = intersec_pos[i].second;
        answer[pos_X][pos_Y] = '*';
    }
    return answer;
}
int main() {
    solution({ { 2, -1, 4}, {-2, -1, 4}, {0, -1, 1}, {5, -8, -12}, {5, 8, 12} });
}
