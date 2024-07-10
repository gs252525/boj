#include <bits/stdc++.h>
using namespace std;

vector<tuple<int, int, int>> res;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int a, b, c, l;
  cin >> a >> b >> c >> l;
  int t = 2;
  int pq = 0, pq2=0;
  if (a) {
    a--;
    res.emplace_back(1, 0, 2);
  } else
    pq=1;
  t = 3;
  if (b) {
    b--;
    res.emplace_back(2, 0, 3);
  } else if (a) {
    a--;
    res.emplace_back(2, 1, 3);
  } else
    pq2=1;
  t = 4;
  if (c) {
    c--;
    res.emplace_back(3, 0, 4);
  } else if (b) {
    b--;
    res.emplace_back(3, 1, 4);
  } else if (a) {
    a--;
    res.emplace_back(3, 2, 4);
  }
  int x = 1, y = 2, z = 3;
  if(pq2 && c){
    t++;c--;
    res.emplace_back(2,1,5);
    x=1;
    y=3;
    z=2;
    if(c){
      t++;c--;
      res.emplace_back(x,2,6);
      x=3;
      y=2;
      z=1;
    }
  }
  else if (pq && c) {
    t++;
    c--;
    pq--;
    res.emplace_back(x, t - 4, t);
    swap(x, y);
    swap(y, z);
  }
  
  while (b) {
    t++;
    b--;
    res.emplace_back(x, t - 3, t);
    swap(x, y);
    swap(y, z);
  }
  while (a && c) {
    t += 2;
    a--;
    c--;
    res.emplace_back(y, t - 3, t - 1);
    res.emplace_back(x, t - 4, t);
    swap(x, z);
  }
  while (a) {
    t++;
    a--;
    res.emplace_back(x, t - 2, t);
    swap(x, y);
    swap(y, z);
  }
  while (c) {
    t += 2;
    c--;
    res.emplace_back(x, t - 4, t);
    if (!c)
      break;
    t++;
    c--;
    res.emplace_back(y, t - 4, t);
    if (!c)
      break;
    t++;
    c--;
    res.emplace_back(z, t - 4, t);
  }

  int rrr = 0;
  for (auto [q, ts, te] : res)
    if (te <= l)
      rrr++;
  cout << rrr << '\n';

  for (auto [q, ts, te] : res) {
    if (te > l)
      return 0;
    cout << q << ' ' << ts << ' ' << te << '\n';
  }
}