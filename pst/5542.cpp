#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/stdc++.h>
#include <array> 
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

const int MAXN = 100010; 

vector<pair<int,int>> adj[MAXN]; 
int dist[MAXN]; 

struct UF{
  int n; vector<int> par; 
  UF(int n): n(n){
    par.resize(n+1); 
    rrep(i,n) par[i] = i; 
  }
  int find(int x){
    if(x==par[x]) return x; 
    return par[x] = find(par[x]); 
  }
  int merge(int x, int y){
    x = find(x); y = find(y); 
    if(x==y) return true; 
    par[y] = x; return false; 
  }
};

bool visited[MAXN]; 
int ans[MAXN]; 
int l[MAXN]; 
int r[MAXN]; 

void solve(){
  int n; cin >> n; 
  int m,k,Q; cin >> m >> k >> Q; 
  vector<pair<int,int>> E; 
  while(m--){
    int a,b,c; cin >> a >> b >> c; adj[a].pb({b,c}); adj[b].pb({a,c}); 
    E.pb({a,b}); 
  }
  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq; 
  rrep(i,n) dist[i] = 1e9; 
  rep(i,k){
    int x; cin >> x; pq.push({0,x}); 
  }
  while(!pq.empty()){
    auto [d,i] = pq.top(); pq.pop(); 
    if(visited[i]) continue; 
    dbg(i,d); 
    visited[i] = true; dist[i] = d; 
    for(auto [ne,cost] : adj[i]){
      if(dist[ne]>d+cost){
        pq.push({d+cost,ne}); dist[ne] = d+cost; 
      }
    }
  }

  // 
  vector<int> tmp; 
  rrep(i,n) tmp.pb(dist[i]); 
  sort(all(tmp)); 
  tmp.erase(unique(all(tmp)),tmp.end()); 
  rrep(i,n) dist[i] = lower_bound(all(tmp),dist[i]) - tmp.begin(); 
  // n 부터 0까지 merge a,b 에서 dist[a]>=k &&dist[b]>=k 
  sort(all(E), [](auto x, auto y){
    return min(dist[y.ff],dist[y.ss]) > min(dist[x.ff],dist[x.ss]); 
  }); 
  dbg(E); 
  vector<pair<int,int>> query(Q); 
  rep(i,Q) cin >> query[i].ff >> query[i].ss; 
  rep(i,Q) l[i] = 0, r[i] = tmp.size()-1; 
  // g[i]. { query, idx} 
  // i를 tmp.sz()-1 부터 0까지 내려가면서 E[j].ff>=i && E[j].ss>=i -> 
  while(1){
    bool flag = true; 
    vector<array<int,3>> g[MAXN]; 
    rep(i,Q) {
      if(l[i]>r[i]) continue; 
      else {
        g[l[i]+r[i]>>1].pb({query[i].ff,query[i].ss,i}); flag = false; 
      }
    }
    UF uf(n); 
    if(flag) break; 
    dbg(tmp.size())
    for(int i=tmp.size()-1,j=E.size()-1; i>=0; i--){
      while(j && min(dist[E[j].ff],dist[E[j].ss])>=i){
        dbg(i,j,E[j].ff,E[j].ss)
        uf.merge(E[j].ff,E[j].ss); j--; 
      }
      for(auto [a,b,idx]:g[i]){
        dbg(a,b,idx,i); 
        if(uf.find(a)==uf.find(b)){
          ans[idx] = max(ans[idx],i); 
          l[idx] = i+1; 
        }
        else {
          r[idx] = i-1; 
        }
      }
    }
  }
  rep(i,Q) cout << tmp[ans[i]] << "\n"; 

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
