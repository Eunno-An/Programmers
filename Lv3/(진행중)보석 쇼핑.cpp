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
	for (int i = num_gems; i < new_gems.size(); i++) {
		if (window.size() == num_gems) {
			end_idx = i - 1;
			start_idx = end_idx - num_gems + 1;
			break;
		}
		string name_gem_now = new_gems[i].first;//new_gems에서 i번째 젬 이름
		string name_gem_before = new_gems[i - num_gems].first;//new_gems에서 i-num_gems번째 젬 이름.

		//window에서 name_gem_before를 제거해준다.
		window[name_gem_before] -= new_gems[i - num_gems].second;
		if (window[name_gem_before] == 0)
			window.erase(name_gem_before);
		//window에서 name_gem_now를 추가해 준다.
		if (window.find(name_gem_now) == window.end())
			window.insert(make_pair(name_gem_now, 1));
		else
			window[name_gem_now]++;


	}

	if (start_idx == 0 && end_idx == 0) {//전체를 봐야할 때
		answer.push_back(new_gems[start_idx].second);
		answer.push_back(original_gems.size() - new_gems.back().second + 1);
	}
	else {
		int s = 0, e = 0;
		for (int i = 0; i <= start_idx; i++)
			s += new_gems[i].second;
		for (int i = 0; i < end_idx; i++)
			e += new_gems[i].second;
		e += 1;
		answer.push_back(s);
		answer.push_back(e);
	}

	return answer;
}
int main() {
	solution({ "DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA" });
}
