//1. 종만북에서 나오는 왠만하면 실수 연산을 쓰지 말것
//2. check_overlap_section 함수에서 시간 비교하는 함수 로직 다시 볼것. 여기서 시간 많이 잡아먹음.
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>
using namespace std;
class Time {
public:
    int hour;
    int minute;
    int second;
    Time(int h, int m, int s) {
        hour = h;
        minute = m;
        second = s;
    }
};
Time getReplyStartTime(Time replyCompleteTime, int conditioningTime) {
    //추상적으로 표현: replyCompleteTime - conditioningTime + 0.001
    int& hour = replyCompleteTime.hour;
    int& minute = replyCompleteTime.minute;
    int& seconds = replyCompleteTime.second;

    //conditioningTime = round(conditioningTime * 1000) / 1000.0;
    seconds -= conditioningTime;
    //seconds = round(seconds * 1000) / 1000.0;
    if (seconds < 0) {
        minute -= 1;
        seconds += 60000;
        //seconds = ceil(seconds * 1000) / 1000.0;
        if (minute < 0) {
            hour -= 1;
            minute += 60;
        }
    }
    seconds += 1;
    //seconds = round(seconds * 1000) / 1000.0;
    if (seconds >= 60000) {
        seconds -= 60000;
        //seconds = ceil(seconds * 1000) / 1000.0;
        minute += 1;
        if (minute >= 60) {
            minute -= 60;
            hour += 1;
        }
    }

    return replyCompleteTime;
}
Time getTime_AfterOneSec(Time startTime) {
    //startTime + 1 - 0.001
    Time endTime(0, 0, 0.0);
    int hour = startTime.hour;
    int minute = startTime.minute;
    double second = startTime.second;

    second += 999;
    //second = round(second * 1000) / 1000;
    if (second >= 60000) {
        second -= 60000;
        //second = round(second * 1000) / 1000;
        minute += 1;
        if (minute >= 60) {
            minute -= 60;
            hour += 1;
        }
    }
    endTime.hour = hour;
    endTime.minute = minute;
    endTime.second = second;
    return endTime;
}
bool check_overlap_section(Time time1, Time time2) {
    //5:3:2  5: 4: 1
    if(time1.hour > time2.hour)
        return false;
    else if(time1.hour == time2.hour && time1.minute > time2.minute)
        return false;
    else if(time1.hour == time2.hour && time1.minute == time2.minute && time1.second > time2.second)
        return false;
    return true;
}
int solution(vector<string> lines) {
    int answer = 0;
    vector<Time> times_replyComplete;
    vector<int> times_conditioning;
    for (int data = 0; data < lines.size(); data++) {
        stringstream logData(lines[data]);
        vector<string> lines_info;
        string blank;
        while (getline(logData, blank, ' '))
            lines_info.push_back(blank);

        //응답 완료 시간인 lines_info[1]을 시: 분: 초로 쪼갬
        stringstream timeData(lines_info[1]);
        vector<string> time_info;
        while (getline(timeData, blank, ':'))
            time_info.push_back(blank);

        Time instance = Time(stoi(time_info[0]), stoi(time_info[1]), stod(time_info[2])*1000);
        times_replyComplete.push_back(instance);

        //처리시간인 lines_info[2]의 뒤의 s를 뺌.
        lines_info[2].pop_back();
        times_conditioning.push_back(stod(lines_info[2])*1000);
    }
    //vector<Time> times_replyComplete: 응답 완료 시간 저장
    //vector<double> times_conditioning: 처리 시간 저장

    //응답 시간을 저장한다.
    vector<Time> times_replyStart; //응답 시작 시간
    for (int i = 0; i < times_replyComplete.size(); i++)
        times_replyStart.push_back(getReplyStartTime(times_replyComplete[i], times_conditioning[i]));


    for (int i = 0; i < times_replyComplete.size(); i++) {
        Time processing_StartTime1 = times_replyComplete[i];
        Time processing_EndTime1 = getTime_AfterOneSec(processing_StartTime1);
        int temp_answer = 1;
        for (int j = i + 1; j < times_replyComplete.size(); j++) {
            Time processing_StartTime2(0, 0, 0), processing_EndTime2(0, 0, 0);
            processing_StartTime2 = times_replyStart[j];
            processing_EndTime2 = times_replyComplete[j];
            //
            if (check_overlap_section(processing_StartTime2, processing_EndTime1))
                temp_answer++;
        }
        if (answer < temp_answer)
            answer = temp_answer;
    }
    /*
    모든 log의 "응답 시작시간"을 구해야 한다.
    소수점 셋째 자리까지 기록한다는 것이 힌트이다.
    01:00:04.002가 어떤 응답 완료 시간이고, T가 2라면
    second에서 2를 빼 준다. 만약 second가 음수로 된다면 minute을 1 빼주고, 만약 minute도 음수라면 hour을 마이너스 해준다.
    쨌든 01:00:02.002가 될 것이고, 여기서 0.001을 더해주면 된다.
    따라서 01:00:02.003이 "응답 시작시간"이다.

    다른 예시로,
    01:00:04.001 2.0라면, 응답 시작시간은 01:00:02.002
    01:00:07.000 2 라면, 응답 시작시간은 01:00:05.001

    그리고 또 하나 유의할 점,
    04.001과 1초가 떨어진 지점은 05.001이 아닌 05.000이다.

    마찬가지로 어떤 지점의 끝점 + 1 - 0.001까지가 겹친다고 볼 수 있는 구간이다.

    그럼 이제 답을 구하는 과정이다.
    times_replyComplete(응답 완료 시간을 저장한 벡터)에서
    i번째의 응답 완료시간을 complete1이라고 하자.
    그럼 i+1번 부터의 "처리구간?"이 폐구간 (range1)[complete1, complete1 + 1 - 0.001]에 속한지 본다.

    i+1번 부터의 처리구간을 구하기 위해서, i+1번째 요소의 "응답 완료시간"을 complete2이라고 하자.
    start1 = complete2 - times_conditioning[i+1] + 0.001
    저 폐구간(range1)과 i+1번쨰의 폐구간 (range2)[start1, complete2]가 겹치는 부분이 있어야 한다.
    우리는 lines가 "응답완료시간"별로 오름차순 정렬되어 있는 것을 아니까, 반드시 complete1 <= complete2일 것이고
    그렇다면 start1 <= complete1+1-0.001라면 두 구간은 겹치게 된다.

    */
    return answer;
}
int main() {
    solution({ "2016-09-15 01:00:04.001 2.0s", "2016-09-15 01:00:07.000 2s" });
}
