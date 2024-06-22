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

const int MAXN = 200010;

int adj[MAXN];
int visited[MAXN];
int incyc[MAXN];

bool dfs(int x, int k) {
  int st = x;
  int ne;
  while (1) {
    debug(x);
    visited[x] = 1;
    ne = adj[x];
    if (incyc[ne]) {
      while (!incyc[st]) {
        incyc[st] = 1;
        st = adj[st];
      }

      return true;
      debug(ne);
    }

    if (visited[ne])
      break;
    x = ne;
  }
  // ne cycle
  int j = ne;
  int cnt = 0;
  do {
    debug(j);
    j = adj[j];
    cnt++;
  } while (j != ne);
  debug(cnt);
  if (cnt != k) {
    return false;
  }
  while (1) {
    incyc[st] = 1;
    st = adj[st];
    if (incyc[st])
      return true;
  }
}

void solve() {
  int n, k;
  cin >> n >> k;
  rrep(i, n) { visited[i] = 0, incyc[i] = 0; }

  rrep(i, n) {
    cin >> adj[i];
    debug(adj[i]);
  }
  if (k == 1) {
    bool flag = true;
    rrep(i, n) if (adj[i] != i) flag = false;
    cout << (flag ? "YES\n" : "NO\n");
    return;
  }
  if (k != 1) {
    bool flag = true;
    rrep(i, n) if (adj[i] == i) {
      debug(i);
      debug(adj[i]);
      flag = false;
      break;
    }
    if (!flag) {
      cout << "NO\n";
      return;
    }
  }
  bool flag = true;
  rrep(i, n) {
    if (visited[i] == 0)
      flag = dfs(i, k);
    if (!flag) {
      break;
    }
  }
  cout << (flag ? "YES\n" : "NO\n");
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