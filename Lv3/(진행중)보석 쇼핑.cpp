#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
void printGems(vector<pair<string, int>>& gems) {
	for (int i = 0; i < gems.size(); i++)
		cout << gems[i].first << ' ' << gems[i].second << '\n';
}
bool compare(pair<int, int>a, pair<int, int>b) {
	if (a.second - a.first == b.second - b.first)
		return a.first < b.first;
	return a.second - a.first < b.second - b.first;
}
vector<int> solution(vector<string> gems) {
	vector<int> answer;
	vector<string> original_gems = gems;
	vector<pair<string, int>> new_gems;
	new_gems.push_back(make_pair(gems.front(), 1));
	for (int i = 1; i < gems.size(); i++)
		if (gems[i] != gems[i - 1])
			new_gems.push_back(make_pair(gems[i], 1));
		else
			new_gems.back().second++;

	int num_gems;
	sort(gems.begin(), gems.end());
	gems.erase(unique(gems.begin(), gems.end()), gems.end());
	
	num_gems = gems.size();
	if (num_gems == 1) {//하나만 봐도 될 경우
		answer.push_back(1);
		answer.push_back(1);
		return answer;
	}
	if (num_gems == original_gems.size()) {//보석 진열장에 있는 보석들이 서로 다를 경우
		answer.push_back(1);
		answer.push_back(original_gems.size());
		return answer;
	}
	int start_idx = 0, end_idx = 0;
	map<string, int> window;

	for (int i = 0; i < num_gems; i++) {
		if (window.find(new_gems[i].first) == window.end())
			window.insert(make_pair(new_gems[i].first, new_gems[i].second));
		else
			window[new_gems[i].first]+=new_gems[i].second;
	}
	vector<pair<int, int>> answers;//답의 후보가 여러개 일 수도 있다.
	//그리고 반드시 중요한건, 우리는 중복을 줄인 상태에서 인덱스를 뽑았으니 
	//그리디하게 풀린다는 보장이 없다.
	//예를 들어, new_gems를 window로 순회했을 때, window size와 일치하는 구간이 총 두개 있다고 가정하자.
	//근데, 실제 original_gems에서의 길이가 더 짧을수도 있다.
	for (int i = num_gems; i < new_gems.size(); i++) {
		if (window.size() == num_gems) {
			end_idx = i - 1;
			start_idx = end_idx - num_gems + 1;
			answers.push_back(make_pair(start_idx, end_idx));
		}
		string name_gem_now = new_gems[i].first;//new_gems에서 i번째 젬 이름
		string name_gem_before = new_gems[i - num_gems].first;//new_gems에서 i-num_gems번째 젬 이름.

		//window에서 name_gem_before를 제거해준다.
		window[name_gem_before] -= new_gems[i - num_gems].second;
		if (window[name_gem_before] == 0)
			window.erase(name_gem_before);
		//window에서 name_gem_now를 추가해 준다.
		if (window.find(name_gem_now) == window.end())
			window.insert(make_pair(name_gem_now, new_gems[i].second));
		else
			window[name_gem_now]+=new_gems[i].second;


	}

	if (start_idx == 0 && end_idx == 0) {//전체를 봐야할 때
		answer.push_back(new_gems[start_idx].second);
		answer.push_back(original_gems.size() - new_gems.back().second + 1);
	}
	else {
		
		for (int i = 0; i < answers.size(); i++) {
			int s = 0, e = 0;
			for (int j = 0; j <= answers[i].first; j++)
				s += new_gems[j].second;
			for (int k = 0; k < answers[i].second; k++)
				e += new_gems[k].second;
			e += 1;
			answers[i].first = s;
			answers[i].second = e;

		}
		
		sort(answers.begin(), answers.end(), compare);
		answer.push_back(answers.front().first);
		answer.push_back(answers.front().second);
	}

	return answer;
}
int main() {
	solution({ "AA", "AB", "AC", "AA", "AC" });
}
