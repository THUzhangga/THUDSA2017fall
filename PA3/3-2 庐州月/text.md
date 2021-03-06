# THU2017 3-2 庐州月

------

![img](https://dsa.cs.tsinghua.edu.cn/oj/attachment/2a8b/2a8b158f2e5af03c31fe775a622a736725bb4c6d.png)

### **题目来源**

　　Tsinghua Online Judge 原创，出题人 wyx528、jiguanglizipao

### **描述**

　　小 G 是出生在庐州的一位同学，当他高中毕业后，回到了自己的家乡。然而家乡已不复当年模样，在高中表现优秀的小 G 决定承担起家乡的一件重任，那就是修理已经破烂不堪的石桥。

　　家乡中共有 n 个石桥等待修理，对于第 i 个石桥，我们定义两个参数 pi，vi，其中 pi 表示修理石桥的最小花费值，vi 表示石桥需要的最小美化需求度。今天，小 G 已了解到修理厂共有 m 种不同的修理原料，对于第 i 种原料，可以对任意一个石桥的美化度增加 di，当然这也需要花费 hi 的费用。由于发货场的修理原料有限，对于任意一种修理原料，只有一件，也就是说小 G 只能选择购买和不购买，对于第 i 种修理材料能成功修理第 j 个石桥的条件是：当且仅当 hi ≥ pj，di ≥ vj。现在，已知这 n 个石桥修理的最小花费值，最小美化需求度，以及 m 种修理原料的费用，可对石桥增加的美化度值，请你帮助小 G 完成这个修理任务。

### **输入**

　　第一行包括两个正整数，n，m。

　　接下来 n 行中，每行包括两个正整数 pi，vi。

　　接下来 m 行中，每行包括两个正整数 hi，di。

### **输出**

　　只有一个整数，为最小修理花费，输入数据保证存在至少一种可行的方案。

### **样例输入**

```
2 3
2 3
5 9
3 10
3 5
6 11
```

### **样例输出**

```
9
```

### **样例说明**

　　其中一种可行的方案是：使用第 1 种材料，修理第 1 个石桥，使用第 3 种材料，修理第 2 个石桥，最小修理花费为 3 + 6 = 9。

### **数据范围**

　　1 <= m <= 500,000

　　0.5 m <= n <= 0.7 m

　　1 <= pi, vi, di, hi <= 2,000,000,000

### **资源限制**

　　时间限制：1 sec

　　空间限制：256 MB

### **提示**

　　● 贪心、平衡二叉树。