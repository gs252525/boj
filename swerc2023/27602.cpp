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


const int MAXN = 400; 
vector<int> adj[MAXN]; 
int c[MAXN]; 
int dist[MAXN][MAXN]; 
int vis[MAXN]; 

void dij(int n, int i){
  // n vertices i point 
  rrep(j,n) dist[i][j] = 1e9,vis[j]=0;  
  dist[i][i]=0; 
  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq; 
  pq.push({0,i}); 
  
  while(!pq.empty()){
    auto [d,j] = pq.top(); 
    pq.pop(); 
    if(vis[j]) continue; 
    if(i==2){
      dbg(d,j)
    }
    vis[j] = 1; 
    dist[i][j] = d; 
    for(auto ne : adj[j]){
      if(d+1 < dist[i][ne]){
        dist[i][ne] = d+1; 
        pq.push({d+1,ne}); 
      }
    }
  }
  return ; 
}

void solve(){
  int n,m,k; cin >> n >> m >> k; 
  rrep(i,n) cin >> c[i]; 
  if(k==0){
    rrep(i,m){
      int a,b; cin >>a >> b; 
      adj[a].pb(b); adj[b].pb(a); 
    }
    rrep(i,n) dij(n,i); 
    int M = 0; 
    rrep(i,n) rrep(j,n) M = max(M,dist[i][j]); 
    cout << M; return; 
  }
  rrep(i,m){
    int a,b; cin >> a >> b; 
    if(c[a]!=c[b]) adj[a].pb(b+n), adj[b].pb(a+n), adj[a+n].pb(b), adj[b+n].pb(a); 
    else adj[a].pb(b), adj[b].pb(a), adj[a+n].pb(b+n), adj[b+n].pb(a+n); 
  }
  rrep(i,n*2) dij(2*n,i); 
  int M = 0; 
  rrep(i,n){
    rrep(j,n){
      int a = dist[i][j], b = dist[i][j+n]; 
      dbg(i,j,a,b)
      if(a>=b+k) M = max(M,b+k); 
      else if (b>=a+k) M = max(M,a+k); 
      else M = max(M,(a+b+k)/2); 
    }
  }
  cout << M; 
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
