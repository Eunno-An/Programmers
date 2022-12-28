import Foundation

func isPrime(_ n: Int) -> Bool{
    if n == 1{
        return false
    }
    if n <= 3{
        return true
    }
    for num in 2...Int(sqrt(Double(n))){
        if n % num == 0{
            return false
        }
    }
    return true
}
func solution(_ n:Int, _ k:Int) -> Int {
    var radix = String(n, radix: k)
    var s: String = ""
    var ret = 0
    for idx in 0..<radix.length{
        if radix[idx] == "0"{
            if s != "" && isPrime(Int(s)!){
                ret += 1
            }
            s = ""
        }else{
            s.append(radix[idx])
        }
    }
    if s != "" && isPrime(Int(s)!){
        ret += 1
    }
    return ret
}

extension String{
    subscript(_ idx: Int) -> Character{
        return self[self.index(self.startIndex, offsetBy: idx)]
    }
}