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

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V> void __print(const pair<T, V> &x) {
  cerr << '{';
  __print(x.first);
  cerr << ", ";
  __print(x.second);
  cerr << '}';
}
template <typename T> void __print(const T &x) {
  int f = 0;
  cerr << '{';
  for (auto &i : x)
    cerr << (f++ ? ", " : ""), __print(i);
  cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V> void _print(T t, V... v) {
  __print(t);
  if (sizeof...(v))
    cerr << ", ";
  _print(v...);
}
#ifdef LOCAL
#define dbg(x...)                                                              \
  cerr << "\e[91m" << __func__ << ":" << __LINE__ << " [" << #x << "] = [";    \
  _print(x);                                                                   \
  cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

const int MAXN = 30;
vector<int> adj[MAXN];
int dist[MAXN];
int n;
int par[MAXN];

int fuck(long long x) { return 64 - __builtin_clzll(x); }

pair<int, int> get_cnt(void) {
  rep(i, n) dist[i] = 50, par[i] = -1;
  dist[0] = 0;
  queue<int> q;
  q.push(0);
  par[0] = 0;
  int mx = 0, s = 0;
  while (!q.empty()) {
    int t = q.front();
    q.pop();
    for (auto ne : adj[t]) {
      if (par[ne] == -1) {
        par[ne] = t;
        dist[ne] = dist[t] + 1;
        if (dist[ne] > mx)
          mx = dist[ne], s = ne;
        q.push(ne);
      }
    }
  }
  mx = 0;
  int e = 0;
  rep(i, n) par[i] = -1;
  par[s] = s;
  dist[s] = 0;
  q.push(s);
  while (!q.empty()) {
    int t = q.front();
    q.pop();
    for (auto ne : adj[t]) {
      if (par[ne] == -1) {
        par[ne] = t;
        dist[ne] = dist[t] + 1;
        if (dist[ne] > mx)
          mx = dist[ne], e = ne;
        q.push(ne);
      }
    }
  }
  if (mx % 2 == 0) {
    int re = e;
    rep(k, mx / 2) re = par[re];
    return {re, re};
  } else {
    int re = e;
    rep(k, mx / 2) re = par[re];
    return {par[re], re};
  }
}

ll get(int v, int p) {
  vector<ll> tmp;
  for (auto ne : adj[v]) {
    if (ne != p) {
      tmp.pb(get(ne, v));
    }
  }
  if (tmp.empty())
    return 2;
  sort(all(tmp));
  ll re = tmp[0];
  for (int i = 1; i < tmp.size(); i++) {
    re <<= fuck(tmp[i]);
    re |= tmp[i];
  }
  re <<= 1;
  re |= (1LL << fuck(re));
  return re;
}

void solve() {
  int nn;
  cin >> nn;
  set<ll> s;
  rep(i, nn) {
    cin >> n;
    rep(i, n) adj[i].clear();
    rep(i, n - 1) {
      int a, b;
      cin >> a >> b;
      adj[a].pb(b);
      adj[b].pb(a);
    }
    auto [p, q] = get_cnt();
    dbg(p, q) ll g1 = get(p, p);
    dbg(p, g1) if (q != p) g1 = min(g1, get(q, q));
    s.insert(g1);
  }
  cout << s.size();
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--)
    solve();
  return 0;
}
