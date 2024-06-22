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

int N, M;
const int MAXN = 1010;
int a[MAXN][MAXN] = {};

bool fuck(int x, int y) { return (x >= 0) && (x < N) && (y >= 0) && (y < M); }

int f(int x, int y) { return M * x + y; }

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};

int p[MAXN * MAXN];
int in[MAXN * MAXN];

int find(int x) {
  if (x == p[x])
    return x;
  return p[x] = find(p[x]);
}

void merge(int x, int y) {
  x = find(x), y = find(y);
  if (x == y)
    return;
  p[y] = x;
  in[x] += in[y];
  in[x] %= 10;
}

void solve() {
  cin >> N >> M;
  rep(i, N * M) {
    p[i] = i;
    in[i] = 1;
  }
  rep(i, N) rep(j, M) {
    char c;
    cin >> c;
    a[i][j] = c - '0';
  }
  int cnt = 1;
  rep(i, N - 1) rep(j, M) {
    if (a[i][j] == 0 && a[i + 1][j] == 0) {
      merge(f(i, j), f(i + 1, j));
    }
  }
  rep(i, N) rep(j, M - 1) {
    if (a[i][j] == 0 && a[i][j + 1] == 0)
      merge(f(i, j), f(i, j + 1));
  }
  rep(i, N) {
    rep(j, M) {
      if (a[i][j] == 0)
        cout << "0";
      else {
        vector<pair<int, int>> v;
        rep(k, 4) {
          int x1 = i + dx[k], y1 = j + dy[k];
          if (fuck(x1, y1) && a[x1][y1] == 0) {
            dbg(i, j, x1, y1);
            int t = find(f(x1, y1));
            v.push_back({p[t], in[t]});
            // dbg(x1,y1,p[f],in[f(x1,y1)]);
          }
        }
        sort(all(v));
        v.erase(unique(all(v)), v.end());
        int ans = 0;
        for (auto [p, q] : v)
          ans += q;
        ans %= 10;
        cout << (ans + 1) % 10;
      }
    }
    cout << "\n";
  }
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
