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

vector<int> palindrome(string s) {
  int n = s.size();
  vector<int> p(n);
  int r = -1, k = -1;
  rep(i, n) {
    if (i <= r)
      p[i] = min(p[2 * k - i], r - i);
    while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n &&
           s[i - p[i] - 1] == s[i + p[i] + 1])
      p[i]++;
    if (r < i + p[i])
      r = i + p[i], k = i;
  }
  return p;
}

int main(void) {
  // freopen("C:\Users\User\Downloads\prob3_gold_dec22\19.in", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  string s;
  cin >> s;
  string ss;
  for (auto &cc : s) {
    ss.pb(cc);
    ss.pb('#');
  }
  auto tmp = palindrome(ss);
  ll ans = 0;
  int n = tmp.size();
  rep(i, n) {
    debug(tmp[i]);
    if (i % 2)
      ans += (tmp[i] + 1) / 2;
    else
      ans += (tmp[i]) / 2;
  }
  cout << ans + s.size();
}
