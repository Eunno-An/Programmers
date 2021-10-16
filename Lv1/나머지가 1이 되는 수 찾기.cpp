#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    for(int i=1; i<=n-1; i++)
        if(n%i == 1)
            return i;
}
