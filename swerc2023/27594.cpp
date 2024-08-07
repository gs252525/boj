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

const int MAXN = 200; 
long double dp[MAXN][MAXN]; 
long double dpm[MAXN][MAXN]; 

void solve(){ 
  int n,m; cin >> n >> m; 
  vector<int> s(m); 
  rep(i,m){
    cin >> s[i]; s[i] = n-s[i]; 
  }
  // dp construct 
  rrep(i,n-1) dp[i][1] = dpm[i][1] = (long double)1.0/(i); 
  for(int j=2; j<=n; j++){
    for(int i=1; i<=n; i++){
      for(int k=1; k<i; k++) dp[i][j] += ((long double)1.0 /i) * dp[k][j-1]; 
      dpm[i][j] = dpm[i][j-1] + dp[i][j]; 
    }
  }
  cout << fixed; 
  cout.precision(10); 
  rep(i,m){
    long double ans = 0; 
    for(int t=1; t<=n; t++){
      long double tmp = dp[s[i]][t]; 
      rep(j,m) if(j!=i) tmp *= ((long double)1.0 - dpm[s[j]][t-1]); 
      ans += tmp; 
    }
    cout <<  ans << " "; 
  }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  // cin >> t;
  while(t--) solve(); 
  return 0;
}
