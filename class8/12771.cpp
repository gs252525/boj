#include <bits/stdc++.h>

using namespace std;

#define int long long
#define x first
#define y second
#define rep(i, n) for (int i = 0; i < n; i++)
#define all(v) (v).begin(), (v).end()

typedef pair<int, int> pi;
int ccw(pi &a, pi &b, pi &c) {
  // a -> b ->c is ccw?
  int xb = b.x - a.x, yb = b.y - a.y;
  int xc = c.x - a.x, yc = c.y - a.y;
  int u = xb * yc - yb * xc;
  return (u > 0) - (u < 0);
}

struct line {
  int x1, x2, y1, d;
  line(int x1_, int x2_, int y1_) {
    x1 = x1_, x2 = x2_, y1 = y1_;
    if (x1 < x2)
      swap(x1, x2);
    d = abs(x1 - x2);
  }
};

signed main() {
  int n;
  cin >> n;
  vector<line> v;
  rep(i, n) {
    int x1, x2, y1;
    cin >> x1 >> x2 >> y1;
    v.push_back(line(x1, x2, y1));
  }
  int ans = 0;
  vector<pair<pi, int>> tmp;
  rep(i, n) {
    // cerr << i << endl;
    int x1 = v[i].x1, x2 = v[i].x2, y = v[i].y1;
    tmp.clear();
    rep(j, n) {
      int xx1 = v[j].x1, xx2 = v[j].x2, yy = v[j].y1;
      int d = v[j].d;
      if (yy == y)
        continue;
      if (yy < y) {
        yy = 2 * y - yy;
        xx1 = 2 * x1 - xx1, xx2 = 2 * x1 - xx2;
        tmp.push_back({{xx2, yy}, d});
        tmp.push_back({{xx1, yy}, -d});
      } else {
        tmp.push_back({{xx1, yy}, d});
        tmp.push_back({{xx2, yy}, -d});
      }
    }
    pi p(x1, y);
    sort(all(tmp), [&](auto a, auto b) {
      auto ap = a.x;
      auto bp = b.x;
      return ccw(p, ap, bp) >= 0;
    });
    int fuck = 0, M = 0;
    for (int i = 0; i < tmp.size();) {
      int j = i;
      int P = 0, N = 0;
      while (j < tmp.size() && ccw(p, tmp[i].x, tmp[j].x) == 0) {
        if (tmp[j].y > 0)
          P += tmp[j].y;
        else
          N += tmp[j].y;
        j++;
      }
      i = j;
      fuck += P;
      M = max(M, fuck);
      fuck += N;
    }
    ans = max(ans, M + v[i].d);
  }
  cout << ans;
  return 0;
}