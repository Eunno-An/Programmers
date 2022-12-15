#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <numeric>
using namespace std;

int solution(vector<int> elements) {
    vector<int> round = elements;
    for(int i=0; i<elements.size(); i++)
        round.push_back(elements[i]);
    int firstSum = 0;
    unordered_set<int> bucket;
    bucket.insert(accumulate(elements.begin(), elements.end(), 0));
    //7 9 1 1 4 7 9 1 1 4
    //7 9 1 1 4
    //79 91 11 14 47
    //791 911 114 147 479
    //7911 9114 1147 1479 4791
    
    //1 2 3 4 5 1 2 3 4 5
    //1 2 3 4 5
    //(1, 2) (2, 3) (3, 4) (4, 5) (5, 1)
    //(1, 2, 3) (2, 3, 4) (3, 4, 5) (4, 5, 1) ( 5, 1, 2)
    //(1, 2, 3, 4) (2, 3, 4, 5) (3,4, 5,1)(4,5,1,2)(5,1,2,3)
    for(int size = 1; size < elements.size();size++){
        //size: 1, 2, 3, ... , n-1
        for(int i=0; i<elements.size(); i++){
            //i: 0, 1, 2, ..., n-1
            int tempSum = 0;
            for(int j=0; j<size; j++){
                //j: 
                tempSum += round[i + j];
            }
            bucket.insert(tempSum);
        }
    }
    return bucket.size();
}