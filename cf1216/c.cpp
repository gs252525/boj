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
  //cout << "fuck?" << endl;
  string s;
  cin >> s;
  //cout << s;
  //debug(s);
  ll k;
  cin >> k;
  ll n = s.size();
  vector<ll> id;
  s = s + "`";
  debug(s);
  //cout << s << "\n";
  rep(i, n) {
    if (i >= 1 && s[i] < s[i - 1])
      id.push_back(i);
  }
  
  id.push_back(n);
  vector<int> in(n, 1);
  vector<int> p(n+1,0); 
  rep(i,n+1) p[i] = i-1; 
  p[0] = 0; 
  ll m = n;
  ll erase_now = 0;
  int u = id[0];
  while (k > m) {
    debug(k);
    debug(u);
    k -= m;
    m--;

    if(p[u]==p[p[u]]) {
      p[u] = u; 
      erase_now++; 
      u = id[erase_now]; 
      continue; 
    }
    p[u] = p[p[u]]; 
    if(s[p[u]] <= s[u]){
      erase_now++; 
      u = id[erase_now]; 
    }
  }
  // in 의 누적합이 k 인 때
  ll sum = 0;
  // 길이 m 의 k 번째 
  int st = n; 
  rep(i, m+1-k) st=p[st]; 
  cout << s[st];  
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