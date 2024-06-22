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

#ifndef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

double dist(pair<int, int> p1, pair<int, int> p2) {
  double d = (double)(p1.ff - p2.ff) * (p1.ff - p2.ff) +
             (double)(p1.ss - p2.ss) * (p1.ss - p2.ss);
  return sqrt(d);
}

void solve() {
  int px, py, ax, ay, bx, by;
  cin >> px >> py >> ax >> ay >> bx >> by;
  pair<int, int> O = make_pair(0, 0); pair<int, int> A = make_pair(ax, ay);
                 pair<int, int> B = make_pair(bx, by);
                 pair<int, int> P = make_pair(px, py);
  double d = min({max(dist(O,A),dist(A,P)) , max(dist(O,B),dist(B,P)),
  max({dist(O,A),dist(A,B)/2,dist(B,P)}),
  max({dist(O,B),dist(A,B)/2,dist(A,P)}) });
  //double d = min(max(dist(O, A), dist(A, P)), max(dist(O, B), dist(B, P)));
  //d = min(d, max(max(dist(O, A), dist(A, B) / 2.0), dist(B, P)));
  //d = min(d, max(max(dist(O, B), dist(A, B) / 2.0), dist(A, P)));

  cout.precision(10);
  cout << fixed;
  cout << d << "\n";
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