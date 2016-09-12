// Isenbaev's number
// About BFS and stl map
// Ecr23
// 2016/05/09

#include <iostream>
#include <map>
#include <queue>
#include <string>
using namespace std;

#define MAXN 50
int dis[MAXN] = {};
bool adj[MAXN][MAXN];

// find the distancce between ib and others
void ibfind(int beg, int size) {
  // queue for search
  queue<int> q;
  // array for avoidng dupilicated search
  int vis[MAXN] = {};
  // search ib first
  q.push(beg);
  while (!q.empty()) {
    // u is the one needs searching
    int u = q.front();
    for (int i = 0; i < size; i++) {
      if (adj[u][i] == 1 && vis[i] == 0) {
        dis[i] = dis[u] + 1;
        q.push(i);
        vis[i] = 1;
      }
    }
    // end searching and pop u
    q.pop();
  }
}

int main() {
  string palyer[MAXN][3];
  map<string, int> m;
  int T;
  cin >> T;
  // input names
  for (int i = 0; i < T; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> palyer[i][j];
      m.insert(make_pair(palyer[i][j], 0));
    }
  }
  // number each palyer
  int num = 0;
  for (map<string, int>::iterator it = m.begin(); it != m.end(); it++) {
    (*it).second = num++;
  }
  // build a undirected map
  for (int i = 0; i < T; i++) {
    int it1 = (*m.find(palyer[i][0])).second;
    int it2 = (*m.find(palyer[i][1])).second;
    int it3 = (*m.find(palyer[i][2])).second;
    adj[it1][it2] = adj[it2][it3] = adj[it1][it3] = 1;
    adj[it2][it1] = adj[it3][it2] = adj[it3][it1] = 1;
  }
  // find ib in the map
  if (m.find("Isenbaev") == m.end()) {
    for (map<string, int>::iterator it = m.begin(); it != m.end(); it++) {
      int i = (*it).second;
      if ((*it).first == "Isenbaev")
        cout << (*it).first << " 0" << endl;
      else if (dis[i] == 0)
        cout << (*it).first << " undefined" << endl;
      else
        cout << (*it).first << " " << dis[i] << endl;
    }
    return 0;
  } else {
    int ib = (*m.find("Isenbaev")).second;
    // find the distance, using bfs
    ibfind(ib, m.size());
    // output their distance
    for (map<string, int>::iterator it = m.begin(); it != m.end(); it++) {
      int i = (*it).second;
      if ((*it).first == "Isenbaev")
        cout << (*it).first << " 0" << endl;
      else if (dis[i] == 0)
        cout << (*it).first << " undefined" << endl;
      else
        cout << (*it).first << " " << dis[i] << endl;
    }
    return 0;
  }
}
