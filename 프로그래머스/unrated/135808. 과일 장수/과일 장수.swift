import Foundation

func solution(_ k:Int, _ m:Int, _ s:[Int]) -> Int {
    if m > s.count{
        return 0
    }
    var answer = 0
    var score = s
    score.sort(by : >)
    var idx = 0
    while(score.count - idx >= m){
        var minScore = score[idx + m-1]
        var maxPropit = minScore * m
        answer += maxPropit
        idx += m
    }
    return answer
}