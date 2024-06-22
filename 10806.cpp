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
int N; 
int low[MAXN]; 
int dfn[MAXN]; 

int pv; 

int dfs(int v, int p){
  int re = dfn[v] = ++pv; 
  int cnt = 0; 
  for(auto ne : adj[v]){
    if(ne==p){
      cnt ++; 
      if(cnt==1) continue; 
    } 
    if(dfn[ne]!=0) re = min(dfn[ne],re); 
    else {
      re = min(dfs(ne,v),re); 
    }
  }
  low[v] = re; 
  return re; 
}

int vis[MAXN]; 
int col[MAXN]; 

int col_v[MAXN]; 
int col_deg[MAXN]; 

vector<int> adj1[MAXN]; 


int cpiv; 
void dfs1(int v, int c){
  dbg(v,c);
  vis[v] = 1; 
  col[v] = c; 
  for(auto ne : adj[v]){
    if(!vis[ne]){
      if(low[ne]>dfn[v]) {
        cpiv += 1; 
        adj1[c].pb(cpiv); 
        adj1[cpiv].pb(c); 
        
        col_deg[c] += 1; 
        col_deg[cpiv] += 1; 
        col_v[cpiv] = ne; 
        dfs1(ne,cpiv); 
      }
      else dfs1(ne,c); 
    }
  }
}

vector<int> child[MAXN]; 
int cpv; 
int root;
vector<int> joo;  
void dfs2(int v, int p){
  for(auto ne : adj1[v]){
    if(ne==p) continue; 
    dfs2(ne,v);  
  }
  if(adj1[v].size()==1) joo.pb(col_v[v]); 
}


void solve(){
  int m; cin >> N >> m; 
  while(m--){
    int a,b; cin >> a >> b; 
    adj[a].pb(b); adj[b].pb(a); 
  }
  dfs(1,1); 
  dfs1(1,0); 
  col_v[0] = 1; 
  if(cpiv==0){
    cout << 0; return; 
  }
  else {
    int cnt = 0; 
    if(cpiv==2)
    for(int i=0; i<=cpiv; i++) if(col_deg[i]>=2) root = i; 
    dfs2(root, root);   
    dbg(root);
    cout << (joo.size()+1)/2 << "\n";
    int m = joo.size()/2; 
    for(int i=m; i<joo.size(); i++) cout << joo[i] << " " << joo[i-m] << "\n";
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
