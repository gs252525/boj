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

const int MAXN = 100100; 
vector<int> adj[MAXN]; 
int deg[MAXN]; 
int col[MAXN]; 
int chk[MAXN]; 
vector<int> child[MAXN]; 
int par[MAXN]; 

int m; 

void dfs(int v, int p){
  par[v] = p; 
  for(auto ne : adj[v]){
    if(ne!=p) {
      dfs(ne,v); 
      child[v].pb(ne); 
    }
  }
}

void dfs1(int v){
  col[v] = col[par[v]] ^ 1; 
  for(auto ne : child[v]){
    dfs1(ne); 
    if(ne>=m || chk[ne]) chk[v]++; 
  }
}

void solve(){
  int n; cin >> n; 
  rep(i,n-1){
    int a, b; cin >> a >> b; 
    deg[a]++; deg[b]++; 
    adj[a].pb(b); adj[b].pb(a); 
  }
  if(n%2==0){
    cout << n; return; 
  }
  if(deg[n]==1){
    cout << n; return; 
  }
  int l =1, r = n; 
  int ans = 0; 
  dfs(n,n); 
  while(l<=r){
    m = l+r>>1; 
    memset(chk,0,sizeof(chk)); 
    memset(col,0,sizeof(col)); 
    dfs1(n); 
    // all m<= col is 1 && deg>=3 then col is 0 자식중 m 이상인 deg 개수 
    bool flag = true; 
    // flag : B win 
    for(int k=m; k<=n; k++){  
      if(col[k]==0 || deg[k]==1) flag = false; 
    }
    if(flag){
      if(m==8){
        rrep(i,n){
          dbg(i,chk[i])
        }
      }
      if(chk[n]>=3){
        flag = false; 
      }
      for(int i=1; i<=n-1; i++){
        if(m==4){
          dbg(i,chk[i],col[i])
        }
        if(chk[i]>=2 && col[i]==1) flag = false; 
      }
    }
    if(flag){
      r = m-1; 
    }
    else {
      ans = max(ans,m); l = m+1; 
    }
  }
  cout << ans; 
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
