import Foundation

func solution(_ data:[[Int]], _ col:Int, _ row_begin:Int, _ row_end:Int) -> Int {
    var copyData = data
    copyData = copyData.sorted(by: {$0[col-1] == $1[col-1] ? $0[0] > $1[0] : $0[col-1] < $1[col-1]})
    //print(copyData)
    var ret = 0
    for tupleIdx in 0..<copyData.count{
        var temp = 0
        for colIdx in 0..<copyData[tupleIdx].count{
            temp += copyData[tupleIdx][colIdx] % (tupleIdx+1)
        }
        if row_begin <= tupleIdx + 1 && tupleIdx+1 <= row_end{
            ret ^= temp
            //print(temp)
        }
    }
    return ret
}