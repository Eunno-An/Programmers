import Foundation

func getDivCnt(_ val: Int) -> Int{
    var tmp = val
    var ret = 0
    var num = 1
    while num*num < val{
        if val % num == 0{
            ret+=2
        }
        num += 1
    }
    if num*num == val{
        ret += 1
    }
    //print(ret)
    return ret
}
func solution(_ number:Int, _ limit:Int, _ power:Int) -> Int {
    var ret = 0
    for i in 1...number{
        let divCnt = getDivCnt(i)
        if divCnt <= limit{
            ret += divCnt
        }else{
            ret += power
        }
    }
    return ret
}