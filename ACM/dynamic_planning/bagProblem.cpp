#include <iostream>
#include <algorithm>
using namespace std;

int N, T;
int weight[1005], value[1005];
int bag[1005][1005];

void backpack() {
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= T; j++) {
      if (j < weight[i]) {  // 包不能放下这个物品
        bag[i][j] = bag[i-1][j];
      } else {  // 包能放下这个物品
        bag[i][j] = max(bag[i-1][j-weight[i]]+value[i], bag[i-1][j]);
      }
    }
  }
}

int main() {
  cout << "Please enter backpack's capacity"
       << " ";
  cin >> T;
  cout << "Please enter the number of goods"
       << " ";
  cin >> N;
  cout << "Please enter the weight and value for each good in one line" << " ";
  for (int i = 1; i <= N; i++) {
    cin >> weight[i];
    cin >> value[i];
  }
  backpack();
  cout << "The best value is " << bag[N][T] << endl;
  return 0;
}

/*
100 5
77 92
22 22
29 87
50 46
99 90
-------
133

200 8
79 83
58 14
86 54
11 79
28 72
62 52
15 48
68 62
--------
334

200 8
79 83
58 14
86 54
11 79
28 72
62 52
15 48
68 62
-------
334

1000 100
71 26
34 59
82 30
23 19
1 66
88 85
12 94
57 8
10 3
68 44
5 5
33 1
37 41
69 82
98 76
24 1
26 12
83 81
16 73
26 32
18 74
43 54
52 62
71 41
22 19
65 10
68 65
8 53
40 56
40 53
24 70
72 66
16 58
34 22
10 72
19 33
28 96
13 88
34 68
98 45
29 44
31 61
79 78
33 78
60 6
74 66
44 11
56 59
54 83
17 48
63 52
83 7
100 51
54 37
10 89
5 72
79 23
42 52
65 55
93 44
52 57
64 45
85 11
68 90
54 31
62 38
29 48
40 75
35 56
90 64
47 73
77 66
87 35
75 50
39 16
18 51
38 33
25 58
61 85
13 77
36 71
53 87
46 69
28 52
44 10
34 13
39 39
69 75
42 38
97 13
34 90
83 35
8 83
74 93
38 61
74 62
22 95
40 73
7 26
94 85

2614

1000 100
3 38
68 16
24 29
80 47
76 22
9 25
24 17
2 49
46 15
75 15
56 75
41 11
95 56
46 99
23 51
34 92
64 59
76 37
6 13
48 98
25 61
73 50
87 32
67 17
58 44
7 79
93 41
66 53
55 45
75 29
38 62
27 64
53 2
6 23
100 31
36 45
26 57
17 68
53 57
88 26
21 51
9 26
34 86
90 83
32 94
47 20
4 98
6 24
57 91
50 89
30 1
25 63
41 21
24 46
12 74
74 56
92 64
17 72
32 58
96 8
35 74
76 24
52 27
93 35
64 94
55 49
1 65
70 21
26 16
35 25
2 1
97 45
82 63
22 4
41 37
37 25
63 39
28 68
90 49
13 11
18 31
55 95
28 5
58 79
59 20
74 21
71 52
32 50
71 8
66 19
4 67
5 21
48 24
52 89
70 28
62 88
28 38
36 96
39 64
48 84

2558

1000 100
19 12
53 61
61 63
74 78
98 49
70 46
15 44
59 36
64 37
29 66
98 43
79 16
74 14
85 73
52 72
70 72
84 83
91 15
84 83
75 65
78 21
72 49
5 36
46 20
26 22
95 80
38 94
79 3
28 73
92 1
12 91
37 62
37 8
58 58
94 79
44 67
25 53
3 8
12 85
67 82
2 70
98 43
12 22
2 53
34 22
68 14
68 41
81 41
92 77
16 75
63 91
47 7
96 39
9 67
32 33
24 65
15 34
4 16
97 93
80 58
76 67
15 13
69 69
22 41
85 42
68 70
70 40
85 11
71 31
24 90
64 31
22 84
13 61
28 15
76 13
13 46
93 10
95 57
70 31
80 94
43 77
6 67
36 57
91 9
17 75
94 24
21 75
30 56
69 27
34 72
39 5
33 81
18 79
75 53
36 96
7 67
15 60
34 42
89 82
59 34

2617

1000 100
42 15
30 64
27 82
93 87
8 81
34 54
47 65
64 98
82 42
76 99
70 6
79 50
23 90
5 99
67 96
9 57
97 76
29 12
7 47
61 18
73 46
3 73
44 99
85 60
7 40
51 60
49 15
90 5
59 65
38 69
55 19
39 72
62 51
85 33
54 11
81 72
38 69
42 64
90 97
90 95
26 32
50 59
22 34
71 3
52 27
41 99
77 82
32 44
49 66
2 83
96 72
84 28
20 64
48 90
17 15
62 38
87 65
94 91
84 68
26 28
73 17
52 80
12 1
70 29
42 54
47 8
94 11
13 11
47 70
89 40
90 93
7 65
51 51
39 49
24 75
6 35
74 41
69 60
5 72
47 57
78 76
65 6
67 28
35 12
89 59
69 58
96 55
15 30
20 66
8 13
28 24
25 24
16 9
33 17
22 43
16 67
64 90
64 37
63 36
67 36

2461

1000 100
58 3
99 79
96 97
64 24
28 10
29 55
43 95
35 41
2 67
30 28
86 14
56 11
27 86
9 50
85 63
13 69
65 39
46 62
51 10
31 49
99 22
56 88
97 60
11 7
65 9
63 34
67 8
6 80
80 17
84 71
85 55
49 17
71 9
95 32
72 26
58 18
23 21
48 86
14 47
89 55
100 61
85 94
53 16
27 54
58 84
50 100
68 11
70 87
81 57
66 85
88 45
43 18
57 61
31 89
77 39
3 29
10 7
26 77
62 4
87 47
97 67
32 62
17 29
100 66
26 47
66 28
9 95
24 66
19 13
90 72
74 21
98 60
92 87
36 27
28 66
58 36
29 93
38 56
32 12
99 31
2 55
88 6
58 36
7 97
24 61
93 88
77 71
86 68
69 49
84 23
95 64
83 52
51 40
96 19
22 87
98 81
61 41
13 71
99 32
68 72

2397

1000 100
75 27
64 21
68 14
18 82
83 36
55 94
60 88
10 71
18 86
83 69
53 75
87 60
80 74
14 16
92 38
18 49
67 24
22 68
64 87
15 85
80 32
33 70
79 37
81 36
43 65
93 29
74 91
48 6
74 54
72 13
70 78
94 70
98 95
57 2
75 38
98 84
4 30
46 44
9 85
80 75
18 39
96 24
78 42
96 76
24 15
14 53
37 68
50 78
52 75
66 24
63 53
27 84
30 34
50 99
88 32
63 22
100 5
68 80
50 39
61 92
55 34
63 59
47 17
95 41
52 17
40 19
65 28
43 57
69 31
34 1
46 21
26 44
45 47
18 71
94 28
93 9
67 15
3 71
34 36
79 24
60 36
67 81
48 33
65 40
4 69
9 65
28 68
10 73
49 4
77 19
98 1
47 11
56 50
11 13
23 78
4 93
70 34
28 60
95 41
21 35

2460

1000 100
88 53
85 70
59 20
100 41
94 12
64 71
79 37
75 87
18 51
38 64
47 63
11 50
56 73
12 83
96 75
54 60
23 96
6 70
19 76
31 25
30 27
32 89
21 93
31 40
4 41
30 89
3 93
12 46
21 16
60 4
42 41
42 29
78 99
6 82
72 42
25 14
96 69
21 75
77 20
36 20
42 56
20 23
7 92
46 71
19 70
24 1
95 63
3 18
93 11
73 68
62 33
91 6
100 82
58 69
57 78
3 48
32 95
5 42
57 53
50 99
3 15
88 76
67 64
97 39
24 48
37 83
41 21
36 75
98 49
52 73
75 85
7 28
57 31
23 86
55 63
93 12
4 71
17 35
5 21
13 17
46 73
48 18
28 7
24 51
70 94
85 88
48 46
48 77
55 80
93 95
6 31
8 80
12 32
50 45
95 5
66 30
92 51
25 63
80 43
16 9
---------
2852
 本

 */