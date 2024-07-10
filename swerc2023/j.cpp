#include <bits/stdc++.h>
using namespace std;

int C[256];
int D[256][256];

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int n, m, kkk;
  cin >> n >> m >> kkk;
  for (int i = 1; i <= n; i++)
    cin >> C[i];
  memset(D, 0x37, sizeof D);
  while (m--) {
    int x, y;
    cin >> x >> y;
    if (C[x] != C[y])
      y ^= 128;
    D[x][y] = D[y][x] = 1;
    x ^= 128;
    y ^= 128;
    D[x][y] = D[y][x] = 1;
  }
  for (int k = 0; k < 256; k++)
    for (int i = 0; i < 256; i++)
      for (int j = 0; j < 256; j++)
        D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
  int res = 0;
  for (int i = 1; i <= n; i++)
    for (int j = i+1; j <= n; j++) {
      int x = D[i][j];
      int y = D[i][j ^ 128];
      if (x >= y + kkk)
        res = max(res, y + kkk);
      else if (y >= x + kkk)
        res = max(res, x + kkk);
      else
        res = max(res, (x + y + kkk) / 2);
    }
  cout << res;
}