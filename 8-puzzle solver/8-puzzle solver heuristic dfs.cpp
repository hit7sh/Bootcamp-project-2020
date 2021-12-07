#include<bits/stdc++.h>
using namespace std;

vector<vector<short>> END = {{1, 2, 3},
                             {4, 5, 6},
                             {7, 8, -1}}; // END state
map<pair<short, short>, char> dir;
map<vector<vector<short>>, char> vis;
const pair<short, short> DD[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void dfs(vector<vector<short>> now) { // NOTE:: ans is not guaranteed to be shortest, but ans is always generated
  vector<pair<short, pair<short, short>>> S;
  int px, py;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (now[i][j] == -1) px = i, py = j;
    }
  }

  for (auto [dx, dy] : DD) {
    int x = px + dx, y = py + dy;

    if (x >= 0 && y >= 0 && x < 3 && y < 3) {
      swap(now[x][y], now[px][py]);

      if (vis.count(now)) {
        swap(now[x][y], now[px][py]);
        continue;
      }
      int cnt = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          cnt += now[i][j] != END[i][j]; // heuristic value = number of mismatch
        }
      }
      S.push_back({cnt, {dx, dy}});
      swap(now[x][y], now[px][py]);
    }
  }

  sort(S.begin(), S.end());


  for (auto [p, q] : S) {
    int dx = q.first, dy = q.second;
    int x = px + dx, y = py + dy;

    swap(now[x][y], now[px][py]);
    vis[now] = dir[q];

    if (now == END) {
      string ans = "";
      int px = 2, py = 2;
      while (vis[END] != '0') {
        ans += vis[END];
        if (vis[END] == 'D') {
          swap(END[px][py], END[px - 1][py]), px -= 1;
        } else if (vis[END] == 'U') {
          swap(END[px][py], END[px + 1][py]), px += 1;
        } else if (vis[END] == 'R') {
          swap(END[px][py], END[px][py - 1]), py -= 1;
        } else {
          swap(END[px][py], END[px][py + 1]), py += 1;
        }
      }
      reverse(ans.begin(), ans.end());
      cout << ans.size() << '\n';
      for (char move : ans) cout << move << '\n';
      exit(0);
    }

    dfs(now);
    swap(now[x][y], now[px][py]);    
  }
}

int main(){

  dir[{-1, 0}] = 'U';
  dir[{0, -1}] = 'L';
  dir[{1, 0}] = 'D';
  dir[{0, 1}] = 'R';

  vector<vector<short>> now = {{-1, 7, 6},
                               {4, 1, 3},
                               {8, 5, 2}}; // start state

  vis[now] = '0';

  dfs(now);  
  return 0;
}
