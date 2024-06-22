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
vector<int> v; 
int n; 

const ll inf = (ll)1e9; 

ll dp[5][5][100010]; 
ll cost[5][5] = {
  {inf,2,2,2,2},{inf,1,3,4,3},{inf,3,1,3,4},{inf,4,3,1,3},{inf,3,4,3,1}
}; 

ll f(int x, int y, int n){
  // x,y 위치에 n번째를 가야되는 정의 
  // x y 중 하나가 v[n-1] 
  ll &re = dp[x][y][n]; 
  if(re!=-1) return re;
  if(n==0){
    if(x==0&&y==0) return re = 0; 
    else return re = inf; 
  }
  if(x==y) return re=inf;
  if(x!=v[n-1]&&y!=v[n-1]) return re=inf; 
  //if(re!=inf) return re; 
  re = inf; 
  rep(i,5){
    re = min(f(i,y,n-1)+cost[i][x],re); 
    re = min(f(x,i,n-1)+cost[i][y],re); 
  }
  dbg(x,y,n,re);
  return re; 
}

void solve(){
  while(1){
    int t; cin >> t; if(t==0) break; v.push_back(t); 
  }
  n = v.size(); 
  dbg(n,v);
  memset(dp,-1,sizeof(dp)); 
  dp[0][0][0] = 0; 
  ll m = inf; 
  rep(i,5) rep(j,5) m = min(m,f(i,j,n)); 
  //dbg(dp[1][0][0]);
  cout << m;
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
