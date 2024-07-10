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

const int MAXN = 700; 
vector<int> adj[MAXN]; 
int cap[MAXN][MAXN]; 
int cost[MAXN][MAXN]; 
int flow[MAXN][MAXN]; 
int src,sink; 
int dist[MAXN]; 

int par[MAXN]; 
bool inqueue[MAXN]; 

void addEdge(int i,int j, int co, int ca){
  cap[i][j] = ca; 
  cost[i][j] = co; 
  cost[j][i] = -co; 
  adj[i].pb(j); 
  adj[j].pb(i); 
}


int N; 
int mcmf(){
  int re = 0; 
  int t=0; 
  while(1){
    memset(inqueue,false,sizeof(inqueue)); 
    memset(par,-1,sizeof(par)); 
    fill(dist,dist+MAXN,1e9); 
    dist[src] = 0; 
    par[src] = src; 
    queue<int> q; 
    q.push(src); 
    while(!q.empty()){
      int t = q.front(); q.pop(); 
      inqueue[t] = 0; 
      for(auto ne : adj[t]){
        if(flow[t][ne]<cap[t][ne] && dist[ne] > dist[t] + cost[t][ne]) {
          dist[ne] = dist[t] + cost[t][ne]; 
          par[ne] = t; 
          if(!inqueue[ne]){
            q.push(ne); 
            inqueue[ne] = true; 
          }
        }
      }
    }
    if(par[sink]==-1) break; 
    int fl = 1e9; 
    for(int i=sink; i!=src; i=par[i]){
      dbg(i); 
    }
    for(int i = sink; i!=src; i=par[i]) fl = min(fl,cap[par[i]][i] - flow[par[i]][i]); 
    for(int i=sink; i!=src; i=par[i]){
      dbg(fl,i,cost[par[i]][i]); 
      re += fl*cost[par[i]][i]; 
      flow[par[i]][i] += fl; 
      flow[i][par[i]] -= fl; 
    }
    t++;
    assert(fl==1);
  }
  assert(t==N-1);
  return re; 
}

int a[MAXN]; 
int h[MAXN]; 
int l[MAXN]; 

void solve(){
 int n; cin >> n; N = n; 
 src = 0; sink = 2*n+1; 
 // 1~n 
 rrep(i,n) cin >> a[i]; 
 rrep(i,n) cin >> h[i]; 
 rrep(i,n) cin >> l[i]; 
 // cost cap 
 rrep(i,n) addEdge(src,i,0,1); 
 rrep(i,n){
  rrep(j,n){
    if(a[i]<a[j]){
      addEdge(i,j+n,-(a[i]^a[j])+h[i]+h[j],1); 
    }
  }
 }
 int mx = 0; 
 rrep(i,n) if(a[i]>a[mx]) mx = i; 
 rrep(i,n){
  if(i!=mx) addEdge(i+n,sink,0,l[i]-1); 
  else addEdge(i+n,sink,0,l[i]); 
 }
 cout << -mcmf(); 
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
