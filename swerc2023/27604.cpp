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

int dp[400][400]; 
int dp1[400][400]; 
int dist[400]; 

int h; 

int g(int i, int j){
  int &re = dp1[i][j]; 
  if(re!=0) return re; 
  int l = dist[j]-dist[i]; l = (l+1)/2; 
  assert(h>=l); 
  if(i==j) return 0;
  if(j==i+1) 2*l-1; 
  re = 1e12;
  for(int k=i; k<j; k++){
    int x = g(i,k) + g(k+1,j); 
    int y = (dist[k]-dist[i]+1)/2, z = (dist[j]-dist[k+1]+1)/2; 
    x += (l-y) + (l-z) - 1; 
    re = min(re, x); 
  }
  return re; 
}

int f(int i, int j){
  int &re = dp[i][j]; 
  if(re!=0) return re; 
  if(i==j) return re = h; 
  int l = (dist[j]-dist[i]+1)/2; 
  dbg(i,j,l)
  if(l<=h) return g(i,j) + (h-l); 
  if(j==i+1) return re = h*2; 
  re = 1e12; 
  for(int k=i; k<j; k++) re = min(f(i,k)+f(k+1,j),re); 
  return re; 
}



void solve(){
  int n; cin >> n >> h; 
  rep(i,n) cin >> dist[i]; 
  if(h==0){
    cout << 0; return; 
  }
  cout << f(0,n-1); 
};


int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  // cin >> t;
  while(t--) solve(); 
  return 0;
}
