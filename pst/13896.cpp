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
int par[MAXN][20]; 
const int L = 20; 

int N; 
vector<int> adj[MAXN]; 
int child[MAXN]; 
int h[MAXN]; 

void dfs(int v, int p){
  par[v][0] = p; 
  h[v] = h[p] + 1; 
  child[v] = 1; 
  for(int i=1; i<L; i++) par[v][i] = par[par[v][i-1]][i-1]; 
  for(auto ne : adj[v]) if(ne!=p) dfs(ne,v), child[v] += child[ne]; 
  dbg(v,child[v])
}

int lca(int a, int b){
  if(h[a]<h[b]) swap(a,b); 
  if(h[a]!=h[b]){
    int diff = h[a]-h[b];
    rep(i,L) if((diff>>i)&1) a = par[a][i];  
  }
  if(a==b) return a; 
  for(int i=L-1;i>=0;i--) if(par[a][i]!=par[b][i]) {
    a = par[a][i], b = par[b][i]; 
  }
  return par[a][0]; 
}

void solve(){
  cin >> N; int Q, p; cin >> Q >> p; 
  rrep(i,N) adj[i].clear(); 
  rep(i,N-1){
    int a,b; cin >> a >> b; adj[a].pb(b); adj[b].pb(a); 
  }
  par[1][1] = 1; 
  h[1] = 0; 
  dfs(1,1); 
  while(Q--){
    int s,u; cin >> s >> u; 
    if(s==0) p=u; 
    else {
      // u -> p 사이 내부 간선 수 
      if(u==p) {
        cout << N << "\n"; continue; 
      }
      int d = lca(u,p); 
      dbg(u,p,d)
      if(d!=u) cout << child[u] << "\n"; 
      else {
        int x = p; 
        int diff = h[x] - h[u] - 1; 
        rep(i,L) if((diff>>i)&1) x = par[x][i]; 
        cout << N - child[x] << "\n"; 
      }
    }
  }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  cin >> t;
  rrep(i,t){
    cout << "Case #" << i << ":" << "\n"; 
    solve(); 
  }
  return 0;
}
