# THU2017 4-4 Whistory

------

### **题目描述**

　　大黄一脚踹开602的大门，冲进来收缴军训广播稿，看到小煌的稿子开头赫然写道：“历史的车轮滚滚向前……”，当时就给跪了。

　　坊间仿作喷涌而出：历史的车轮缓缓碾过，碾过的历史刻在车轮上。

　　车轮上刻有一圈共n个英文小写字母，滚滚向前每碾过一圈就留下一条印迹，这类印迹都是长度为n的字符串。显然，从不同位置开始碾，可能得到不同的印迹。既然历史的车轮滚滚向前，故不必考虑向后碾的情况。于是，一个车轮最多对应于n条不同的印迹；反之，不同的印迹也可能来自相同的车轮。

　　也就是说，两条印迹若能通过循环移位相互转换，则它们来自同一条车轮。比如，所谓的循环左移k位，是指将字符串"`s1 ... sk` sk+1 ... sn"转换为"sk+1 ... sn `s1 ... sk`"。

　　现在，已知不同车轮的m条印迹，请你核对它们的所属的车轮。

### **输入**

　　第一行有两个正整数，即车轮周长n和印迹总数m。

　　接下来的m行分别给出m条印迹，长度均为n。

### **输出**

　　共m行，依次对应于m条印迹。

　　若第i条印迹与之前的第k条（0 < k < i）印迹来自同一车轮，则输出编号k；若存在多个这样的k，则输出最小者。否则（第i条印迹所来自的车轮不同于之前的所有车轮），则输出0。

### **输入样例**

```
8 5
whistory
historyw
farewell
wellfare
orywhist
```

　　*此样例是第1个测试点。

### **输出样例**

```
0
1
0
3
1
```

### **数据范围**

　　1 <= m <= 10000

　　1 <= n <= 1000

### **资源限制**

　　时间限制：1 sec

　　内存限制：256 MB

### **提示**

　　● 散列

　　● KMP