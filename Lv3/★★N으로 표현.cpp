//fail
//문제도 이해하고, 전체적인 알고리즘도 이해 했으나, (8, 5800)의 예시를 통과하지 못함. 왜 그런지 모르겠음.
#include<vector>
#include<map>
#include<unordered_set>
#include<iostream>
using namespace std;
int getNs(int N, int idx) {
	int result = N;
	for (int i = 1; i < idx; i++)
		result = result * 10 + N;
	return result;
}
int solution(int N, int number) {
	if (N == number)
		return 1;
	vector<unordered_set<int>> DP(9);
	DP[1].insert(N);
	for (int use_N = 2; use_N < 9; use_N++) {
		for (int i = 1; i < use_N; i++)
			for (int element : DP[i])
				for (int element2 : DP[use_N - i]) {
					
					DP[use_N].insert(element + element2);
					if (element - element2 > 0)
						DP[use_N].insert(element - element2);
					DP[use_N].insert(element * element2);
					if (element / element > 0 && element2 != 0)
						DP[use_N].insert(element / element2);
				}
		DP[use_N].insert(getNs(N, use_N));
		if (DP[use_N].count(number))
			return use_N;
	}
	return -1;
}
int main() {
	solution(5, 12);
	solution(5, 31168);
	solution(4, 17);
	solution(3, 18);
}
