#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a%b);
}
int solution(vector<int> A, vector<int> B) {
    int answer = 0;
    int a = A[0], b = B[0];
    for(int i=1; i<A.size(); i++){
        a = gcd(A[i], a);
        b = gcd(B[i], b);
    }
    answer = a;
    for(int i=0; i<B.size(); i++){
        if(B[i] % a == 0){
            answer = 0;
            break;
        }
    }
    for(int i=0; i<A.size(); i++){
        if(A[i] % b == 0){
            if(answer == 0)
                return 0;
        }
    }
    return max(a, b);
}