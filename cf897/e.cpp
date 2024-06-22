#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rrep(i, n) for (int i = 1; i <= n; ++i)
#define ff first
#define ss second
using namespace std;
typedef long long ll;

string to_string(string s) { return '"' + s + '"'; }

string to_string(const char *s) { return to_string((string)s); }

string to_string(bool b) { return (b ? "true" : "false"); }

template <typename A, typename B> string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A> string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

void solve() {
  int n, k;
  cin >> n >> k;
  if (n % k == 0) {
    int i = 1;
    int ans = 0;
    while (i <= n - k + 1) {
      cout << "? " << i << endl;
      i += k;
      int x;
      cin >> x;
      ans ^= x;
    }
    cout << "! " << ans << endl;
    return;
  }
  if (n > 2 * k) {
    int s = n % k;
    int i = 2 * k + s + 1;
    debug(i);
    int ans = 0;
    
    while (i <= n - k + 1) {
      cout << "? " << i << endl;
      i += k;
      int x;
      cin >> x;
      ans ^= x;
    }
    n = 2*k+s; 
    int y = (n - k) / 2;
    i = 1;
    rep(j, 3) {
      cout << "? " << i << endl;
      i += y;
      int x;
      cin >> x;
      ans ^= x;
    }
    cout << "! " << ans << endl;
    return;
  }
  int ans = 0;
  rrep(i, n + 1 - k) {
    cout << "? " << i << endl;
    // i += k;
    int x;
    cin >> x;
    ans ^= x;
  }
  cout << "! " << ans << endl;
  return;
};

int main(void) {
  // freopen("C:\Users\User\Downloads\prob3_gold_dec22\19.in", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int tc = 1;
  cin >> tc;
  while (tc--)
    solve();
}