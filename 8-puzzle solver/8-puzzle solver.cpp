#include<bits/stdc++.h>
using namespace std;


int main(){
  map<pair<short, short>, char> dir;
  dir[{-1, 0}] = 'U';
  dir[{0, -1}] = 'L';
  dir[{1, 0}] = 'D';
  dir[{0, 1}] = 'R';
  const pair<short, short> DD[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};


  vector<vector<short>> now = {{1, 4, 5},
                               {2, 7, 8},
                               {-1, 3, 6}}; // start state

  vector<vector<short>> end = {{1, 2, 3},
                               {4, 5, 6},
                               {7, 8, -1}}; // end state

  queue<vector<vector<short>>> q;
  map<vector<vector<short>>, char> vis;
  q.push(now);
  vis[now] = '0';

  while (!q.empty()) {
    auto f = q.front();
    q.pop();
    if (f == end) break;

    int px, py;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) if (f[i][j] == -1) px = i, py = j;

    for (auto [dx, dy] : DD) {
      int x = px + dx, y = py + dy;
      if (x >= 0 && y >= 0 && x < 3 && y < 3) {
        swap(f[x][y], f[px][py]);
        if (vis.count(f)) {
          swap(f[x][y], f[px][py]);
          continue;
        }
        vis[f] = dir[{dx, dy}];
        q.push(f);
        swap(f[x][y], f[px][py]);
      }
    }
  }


  string ans = "";
  int px = 2, py = 2;

  while (vis[end] != '0') { // backtracking
    ans += vis[end];
    if (vis[end] == 'D') {
      swap(end[px][py], end[px - 1][py]), px -= 1;
    } else if (vis[end] == 'U') {
      swap(end[px][py], end[px + 1][py]), px += 1;
    } else if (vis[end] == 'R') {
      swap(end[px][py], end[px][py - 1]), py -= 1;
    } else {
      swap(end[px][py], end[px][py + 1]), py += 1;
    }
  }

  reverse(ans.begin(), ans.end());
  for (char move : ans) cout << move << '\n'; 
  
  return 0;
}
