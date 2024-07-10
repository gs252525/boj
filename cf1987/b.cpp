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

#define int ll 

const int MAXN = 5010; 
int dp[MAXN][MAXN]; 
int a[MAXN]; 
int p[MAXN]; 
vector<int> child[MAXN]; 
const int inf = 1e18; 
int h[MAXN]; 

void solve(){
  int n; cin >> n; 
  rrep(i,n) child[i].clear(); 
  rrep(i,n) rrep(j,n) dp[i][j] = 0; 
  rrep(i,n) cin >> a[i]; 
  int ans = 0; 
  for(int i=2; i<=n; i++){
    cin >> p[i]; 
    child[p[i]].pb(i); 
  }
  h[1] = 1;
  for(int i=2; i<=n; i++) h[i] = h[p[i]] + 1; 
  for(int i=n; i>=1; i--){
    if(child[i].empty()){
      dp[i][h[i]] = inf; continue; 
    }
    int x = a[i]; 
    for(auto ne : child[i]) x -= a[ne]; 
    
    int j; 
    for(j=h[i]+1; j<=n; j++){
      for(auto ne : child[i]) {
        //dp[i][j] += dp[ne][j]; 
        if(dp[ne][j]==inf){
          dp[i][j] = inf; 
          break; 
        }
        dp[i][j] += dp[ne][j]; 
      }
      if(dp[i][j]==inf) break; 
    }
    if(x<=0){
      dp[i][h[i]] = -x; continue; 
    }
    else {
      // h[i]+1~ j 까지 
      for(int k=h[i]+1; k<j; k++){
        if(dp[i][k]<x){
          ans += (k-h[i])*dp[i][k]; 
          x -= dp[i][k]; 
          dp[i][k] = 0; 
        }
        else {
          ans += x*(k-h[i]); 
          x = 0; 
          dp[i][k] -= x; 
          break; 
        }
      }
      if(x>0) ans += (j-h[i])*x; 
      dp[i][h[i]] = 0; 
    }
  }
  cout << ans << "\n"; 
};


int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  cin >> t;
  while(t--) solve(); 
  return 0;
}
