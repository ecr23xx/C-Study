# Beauty_coding
#### Ecr23
---

## 1. Kings' order  
About one month ago, I went to a lecture from a MS engineer which named **Beauty_coding**. During the lecture, he showed a very easy program.
```cpp
int main(){  
    BYTE i=81;  
    while(i--){  
        if(i/9%3==i%9%3) continue;  
        printf("A=%d,B=%d\n",i/9+1,i%9+1);  
    }  
    return 1;  
}  
```
This program could output all kings' orders in Chinese chess. It uses only one variable, and it's so brief and beautiful. `i/9` and `i%9` was for different king, and `/3` was for different column.  
In my opinion, an ordinary program just copy what people do. Like the problem above, we ordinary people will count one by one rather than using `i = 81`. The beauty of coding was doing something special that only computer can do. It's fast and tricky.

---

## 2. Matrix determination
How to compute a matrix's determination? Maybe we'll use methods introduced in textbook, but it's a little bit difficult for us to program (at least for me). But look at the code below
```cpp
int det(int** m, int size) {
  if (size == 2) return m[0][0] * m[1][1] - m[0][1] * m[1][0];
  int temp = 0;
  for (int i = 0; i < size; i++) {
    int** m0 = new int*[size - 1];
    for (int v = 0; v < size - 1; v++) m0[v] = new int[size - 1];
    // the way it decides if it's sub-matrix is tricky.
    for (int p = 0; p < size - 1; p++) {
      for (int q = 0; q < size - 1; q++)
      // p+1 to avoid i-row. when q<i, q to avoid i-column, and when q==i, q+1 to avoid i-column.
        if (q < i)
          m0[p][q] = m[p + 1][q];
        else
          m0[p][q] = m[p + 1][q + 1];
    }
    // positive for even position and negative for odd position.
    if (i % 2 == 0)
      temp += m[0][i] * det(m0, size - 1);
    else
      (i % 2 == 1) temp -= m[0][i] * det(m0, size - 1);
    // delete the int** we new before.
    for (int v = 0; v < size - 1; v++) delete[] m0[v];
    delete[] m0;
  }
  return temp;
}
```
**1**, 2, 3|| **1**, 2, 3||**1**, 2, 3  
 4, 5, 6||  4, **5**, 6||4, 5, 6  
 7, 8, 9|| 7, 8, 9||7, **8**, 9  

============================

1, **2**, 3|| 1, **2**, 3||1, **2**, 3  
4, 5, 6|| **4**, 5, 6||4, 5, 6  
7, 8, 9|| 7, 8, 9||**7**, 8, 9  

---
## 3. construct the max number
Given some numbers, how to construct them to get a biggest one? For `54`, `59`, `9`, the biggest one is `95954`.
I thought it's difficult for human to solve this problem if the amount of numbers is huge. But if those number are all one-digit, we can easily get the answer. The way we use is decide which one is bigger, or in fact, which one is bigger when constructed with others. 95 is bigger than 59, so 9 should be out first. Then we can get the answer.
```cpp
// use sort() in <algorithm>
bool cmp(string a, string b) {
    return a+b > b+a;
}
```

You can view raw code in [C-Study](https://github.com/ECer23/C-Study/tree/master/beauty_coding)
