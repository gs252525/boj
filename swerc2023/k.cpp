#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
ll n, m;
vector<ld> f(int r) {
  
}
vector<ld> D[105];

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    ll x;
    cin >> x;
    D[i] = f(m - x);
  }
}