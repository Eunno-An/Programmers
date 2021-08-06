//fail	
//그리디 문젠데, 한번더 풀어보자.
  #include <string>
	#include <algorithm>
	 
	using namespace std;
	 
	int solution(string name)
	{
	    int answer = 0;
	    int shift = name.length() - 1; //커서를 좌 또는 우 한 쪽 방향만으로 이동했을 때
	    for(int i = 0; i < name.length(); i++)
	    {
	        if(name[i] == 'A')
	        {
	            int target = i;
	            while(target < name.length() && name[target] == 'A') 
	            	target += 1; //A로만 이루어진 문자열 찾기
	            int left = i == 0 ? 0 : i - 1; //찾은 문자열 왼쪽에서의 이동횟수
	            int right = name.length() - target;  //찾은 문자열 오른쪽에서의 이동횟수
	            shift = min(shift, left + right + min(left, right)); //가장 작은값 찾기
	        }
	    }
	    answer += shift;
	    for(auto c : name) 
	    	answer += min(c - 'A', 'Z' - c + 1); //상하 이동횟수
	    return answer;
    }
