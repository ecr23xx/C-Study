# 题目描述
Tom最近在研究一个有趣的排序问题。如图所示，通过2个栈S1和S2，Tom希望借助以下4种操作实现将输入序列升序排序。
- 操作a: 如果输入序列不为空，将第一个元素压入栈S1 
- 操作b: 如果栈S1不为空，将S1栈顶元素弹出至输出序列 
- 操作c: 如果输入序列不为空，将第一个元素压入栈S2 
- 操作d : 如果栈S2不为空，将S2栈顶元素弹出至输出序列

如果一个1~n的排列P可以通过一系列操作使得输出序列为1, 2,…,(n-1), n，Tom就称P是一个"可双栈排序排列"。例如(1, 3, 2, 4)就是一个"可双栈排序序列"，而(2, 3, 4, 1)不是。下图描述了一个将(1, 3, 2, 4)排序的操作序列：`<a, c, c, b, a, d, d, b>` 

当然，这样的操作序列有可能有几个，对于上例(1, 3, 2, 4)，<a, c, c, b, a, d, d, b>是另外一个可行的操作序列。Tom希望知道其中字典序最小的操作序列是什么。

## 输入格式
输入有多个样例，以EOF结束。
输入的第一行是一个整数n。第二行有n个用空格隔开的正整数，构成一个1~n的排列。

## 输出格式
输出共一行，如果输入的排列不是"可双栈排序排列"，输出数字0；否则输出字典序最小的操作序列，每两个操作之间用空格隔开，行尾没有空格。

## 输入样例
3 
2 3 1
4
1 3 2 4
4
2 3 4 1

## 输出样例
a c a b b d
a b a a b b a b
0

# 分析
题目分为两个部分：判断是否有解和找出最小字典序列
## 判断是否有解

### 引理
考虑对于任意两个数q1[i]和q1[j]来说,它们不能压入同一个栈中的充要条件是：(注意没有必要使它们同时存在于同一个栈中,只是压入了同一个栈)存在一个k,使得`i < j < k` 且 `q1[k] < q1[i] < q1[j]`
证明略

### 判断过程
我们的目标是要判断一个序列是否是“能双栈排序”序列，如果直接利用引理来遍历整个序列，那么我们需要`O(n^3)`的时间。但是在枚举的过程中，我们发现可以先判断`q1[i] < q1[j]`是否满足，其次再判断所有`k > j`是否满足`q1[k] < q1[i]`。也就是说，我们可以先得到一个**序号大于i但值小于q[i]的最小值**序列，再用这个序列来判断引理是否成立，那么复杂度会大大降低。

> 设F[i]为Min{S[i],S[i+1],S[i+2]..S[n-1],S[n]},状态转移方程为F[i]=Min{S[i] , F[i+1]}.边界为F[N+1]=极大的值。

找到F后，我们再思考**能否放入同一个栈**这个性质。我们很（bu）自然的就想到了二分图——如果不能进入同一个栈则连上一条边，最后我们就把这个问题转化成了图色问题。
建立临接表过程比较简单，就是只要满足引理条件就连上。
图色的过程如果熟悉图论也比较简单，可是我们并不熟悉，所以还是说一下。我们从第0个数开始图色，图了第0个之后再图和他有关系的点（即不能进入同一个栈的数）。找完了所有有关系的数那么就图下一个。

> 如果在图色的过程中出现冲突，则图色失败，表示不符合条件。

## 找出字典序最小的组合

> 因为a、b都是在第一个栈操作，所以我们尽量都先进入第一个栈，即默认先图颜色一。

然后就找到了最小的组合？！！

## 输出
输出的时候我们只需要按照已经图好的颜色，按照序列顺序压栈即可。
弹出的过程不要想的太复杂，实际上只是按照最后的结果1234弹出就行了。我们设置一个变量count = 1，如果发现两个栈中任意一个的顶端元素是等于count，那么就把这个数弹出，并且自增count
因为要输出成一些比较漂亮的样子，所以再考虑下空格就好了。

# 源码
```cpp
#include <iostream>
#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX = 1001;
const int INF = 99999999;

int S[MAX], F[MAX], bel[MAX];
bool adj[MAX][MAX];
int T;
int flag = 1;

void init() {
  for (int i = 0; i < T; i++) {
    scanf("%d", &S[i]);
  }
}

void noanswer() {
  cout << "0";
  flag = 0;
}

void color(int i, int c) {
  if (flag == 0) return;
  bel[i] = c;
  for (int j = 0; j < T; j++) {
    if (adj[i][j]) {
      if (bel[j] == c) {
        noanswer();  // conflict
        return;
      }
      if (flag == 0) return;
      if (!bel[j]) {
        color(j, 3 - c);  // color the opposite color 1<->2
        if (flag == 0) return;
      }
    }
  }
}

void addedge() {
  F[T] = INF;
  for (int i = T - 1; i >= 0; i--) {
    F[i] = min(F[i + 1], S[i]);
  }
  for (int i = 0; i < T - 1; i++) {
    for (int j = i + 1; j < T; j++) {
      if (S[i] < S[j] && F[j + 1] < S[i]) {
        adj[i][j] = adj[j][i] = true;
      }
    }
  }
  for (int i = 0; i < T; i++) {
    if (!bel[i]) {
      color(i, 1);
    }
  }
}

void solve() {
  if (flag == 0) return;
  int s, should = 1;
  stack<int> s1, s2;
  for (int i = 0; i < T; i++) {
    s = bel[i];
    if (s == 1) {
      s1.push(S[i]);
      cout << "a ";
    } else {
      s2.push(S[i]);
      cout << "c ";
    }

    while ((!s1.empty() && s1.top() == should) ||
           (!s2.empty() && s2.top() == should)) {
      if (s1.top() == should) {
        s1.pop();
        cout << "b";
        if (should != T) cout << " ";
        should++;
      } else {
        s2.pop();
        cout << "d";
        if (should != T) cout << " ";
        should++;
      }
    }
  }
}

int main() {
  while (cin >> T) {
    init();
    addedge();
    solve();
    cout << endl;
    for (int i = 0; i < T; i++) {
      S[i] = F[i] = bel[i] = 0;
      for (int j = 0; j < T; j++) {
        adj[i][j] = false;
      }
    }
    flag = 1;
  }
  return 0;
}
```
