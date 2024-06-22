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

int V,E; 

const int MAXN = 403000; 

struct edge{
  int s,e,x; 
  edge(int s, int e, int x) :s(s), e(e), x(x) {}
}; 

vector<pair<int,int>> adj[MAXN]; 
int par[MAXN]; 
int dfsn[MAXN]; 
map<pair<int,int>,int> M; 
stack<edge> st; 
int pv; 

int bccpv; 

int dfs(int v, int p){
  dbg(v,p); 
  par[v] = p; 
  int re = dfsn[v] = ++pv; 
  for(auto [ne,cost] : adj[v]){
    if(ne==p) continue; 
    if(dfsn[ne]<dfsn[v]){
      st.push(edge(v,ne,cost));
    }
    if(dfsn[ne]!=0) re = min(re,dfsn[ne]); 
    else {
      int tmp = dfs(ne,v); 
      re = min(tmp,re); 
      if(tmp>=dfsn[v]){
        dbg(v,ne);
        vector<int> fuck; 
        vector<pair<int,int>> E; 

        while(!st.empty()&&!(st.top().s==v && st.top().e==ne)){
          auto [s,e,x] = st.top(); 
          st.pop(); 
          fuck.pb(x); 
          E.pb({s,e}); 
        }
        auto [s,e,x] = st.top(); 
        st.pop(); 
        fuck.pb(x); 
        E.pb({s,e}); 
        dbg(E,fuck); 
        sort(all(fuck)); 
        int ans = (fuck.size()==1 ? fuck[0] : fuck[0] + fuck[1]); 
        for(auto lol : E) M[lol] = ans; 
      }
    }
  }
  return re; 
}

void solve(){
  cin >> V >> E; 
  while(E--){
    int a,b,c;cin >> a >> b >>c; 
    adj[a].pb({b,c}); 
    adj[b].pb({a,c}); 
  }
  dfs(1,1); 
  int ans = M[{par[V],V}]; 
  int a = par[V], b = V; 
  while(1){
    dbg(a,b);
    ans = min(ans, max(M[{b,a}],M[{a,b}])); 
    if(a==1) break; 
    b = a; 
    a = par[b]; 
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
