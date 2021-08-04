#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> primes;
bool isPrime(int number){
    if(number < 2)
        return false;
    for(int i=2; i<=sqrt(number); i++) // 반드시 등호
        if(number % i == 0)
            return false;
    return true;
}
void choiceNumbers(int idx, int numbersSize, vector<bool>& choices, string numbers){
    if(idx == numbersSize){
        string choiceNumbers="";
        for(int i=0; i<choices.size(); i++)
            if(choices[i]) choiceNumbers.push_back(numbers[i]);
        if(choiceNumbers == "")
            return;
        
        do{
            //choiceNumbers의 앞에 0이 있으면 빼준다.
            int idx_nonZero=0;
            for(int i=0; i<choiceNumbers.size(); i++){
                if(choiceNumbers[i] != '0'){
                    idx_nonZero = i;
                    break;
                }    
            }
            string tempChoiceNumbers = "";
            tempChoiceNumbers = choiceNumbers.substr(idx_nonZero, choiceNumbers.size()-idx_nonZero);
            //011에서 0이 없어진 채로 순열을 돌리게 되므로, 임시변수를 사용한다.
            
            int int_ChoiceNumbers = stoi(tempChoiceNumbers);
            //int_ChoiceNumbers가 소수인지 확인한다. 
            if(isPrime(int_ChoiceNumbers))
                primes.push_back(int_ChoiceNumbers);
           
            
            //그렇지 않다면 소수에 추가한다.
            
        }while(next_permutation(choiceNumbers.begin(), choiceNumbers.end()));
        return;
    }
    
    choices[idx] = true;
    choiceNumbers(idx+1, numbersSize, choices, numbers);
    choices[idx] = false;
    choiceNumbers(idx+1, numbersSize, choices, numbers);
    
    return;
}
int solution(string numbers) {
    int answer = 0;
    vector<bool> choices(numbers.size(), false);
    sort(numbers.begin(), numbers.end());
    choiceNumbers(0, numbers.size(), choices, numbers);
    
    sort(primes.begin(), primes.end());
    primes.erase(unique(primes.begin(), primes.end()), primes.end());
    
    return answer = primes.size();
}
int main(){
    solution("25");
}
