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

const int MAXN = 2000;
ll dp[MAXN][MAXN];
const ll mod = 10007;

string s;

ll f(int x, int y) {
  if (dp[x][y])
    return dp[x][y];
  ll &re = dp[x][y];
  if (x == y)
    return re = 1;
  if(y==x+1) return re = 2+(s[x]==s[y]);

  if (s[x] == s[y]) {
    re += f(x + 1, y - 1) + 1;
    re %= mod;
    re += f(x, y - 1) + f(x + 1, y) - f(x + 1, y - 1);
    re %= mod;
    re = (re + mod) % mod;
    debug(x,y,re); 
    return re;
  }
  re += f(x, y - 1) + f(x + 1, y) - f(x + 1, y - 1);
  re %= mod;
  re = (re + mod) % mod;
  debug(x,y,re); 
  //dbg(y);
  
  return re;
}

void solve() {
  // string s;
  cin >> s;
  cout << f(0, s.size() - 1) << "\n";
  //cout << dp[1][2];
};

int main(void) {
  // freopen("C:\Users\User\Downloads\prob3_gold_dec22\19.in", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int tc = 1;
  // cin >> tc;
  while (tc--)
    solve();
}