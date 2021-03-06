# THU2017 4-1-1 Magician

------

### **题目描述**

　　怪盗基德的真名是黑羽快斗，他的父亲黑羽盗一是举世闻名的魔术师。从小快斗就跟着父亲学习变魔术的技巧。

　　众所周知熟练地摆弄扑克牌是一位魔术师的基本功。盗一自然少不了教快斗操作扑克的技巧。作为举世闻名的魔术师，盗一的强大之处在于他可以瞬间反转数百万张顺次排列在桌上的扑克牌。有一天，盗一将一叠扑克顺次排成一行放在桌上，全部正面朝上。盗一之后每一次操作都会反转一连串的扑克以改变其正反朝向。为了考验快斗的心算能力，盗一会随时向快斗提问：目前从第i张扑克牌到第j张扑克牌中（包含第i和第j张扑克牌），有几张正面朝上？

### **输入**

　　第一行包含两个正整数n、m，其中n表示扑克牌的数量

　　接下来共m行，每行包含一个操作，操作分为2种：

```
H i j	//盗一挥一挥手，改变了第i张牌到第j张牌的正反（包括第i和第j张扑克牌）
Q i j	//盗一向快斗提问：截至目前，第i张到第j张牌中有多少张正面朝上（包括第i和第j张扑克牌）
```

　　H操作和Q操作的范围均包含边界（即第i张和第j张牌）。

　　对于每个操作，输入保证1 ≤ i ≤ j ≤ n。

### **输出**

　　对于每次Q操作，输出一行，包含一个整数，表示问题的答案。

#### **输入样例**

```
7 5
H 2 4
Q 1 6
H 3 6
Q 2 5
Q 1 7
```

#### **输出样例**

```
3
2
4
```

### **限制**

　　1 ≤ n ≤ 10^6

　　1 ≤ m ≤ 10^5

　　时间限制：1 sec

　　内存限制：256 MB

### **提示**

#### **一级提示**

　　●线段树：http://baike.baidu.com/view/670683.htm

#### **二级提示**

　　●参考课件08.ABST.XB1.Kd-Tree.1D中“BBST：查找”。虽然课件上查询复杂度O(r + logn)，但由于我们不需要报告所有命中的扑克牌的翻转状态，只需要报告正面朝上的总数，因此只需要在每个节点附加一些信息（与正面朝上的牌的总数有关的信息），就可以做“大块地”修改和报告。如果修改和查询一个节点信息只需要有限次操作，那么就能保证在树的每一层都只做有限次操作，复杂度不会超过树高。

　　●如果对于每段编号区间的牌，维护两条记录：区间内的牌是否被整体翻转，子区间有多少张牌的翻转情况与区间的整体情况不一致。请思考维护这两条记录是否足以得出答案，以及维护这两条记录是否在每一层都只需有限次操作。

　　●对于完全二叉树，使用数组模拟树结构，既方便又节省空间。参考资料：10.2.1节“基于向量的紧凑表示”。