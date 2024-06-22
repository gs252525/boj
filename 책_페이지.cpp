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
#ifndef ONLINE_JUDGE
#define dbg(x...)                                                              \
  cerr << "\e[91m" << __func__ << ":" << __LINE__ << " [" << #x << "] = [";    \
  _print(x);                                                                   \
  cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

#define int ll 

struct uf{
	vector<int> par; 
	vector<int> sz; 
	uf(int n){
		par.resize(n+1,0); 
		sz.resize(n+1,0); 
		rrep(i,n) par[i] = i; 
		rrep(i,n) sz[i] = 1; 
	}
	
	int find(int x){
		return x==par[x] ? x : par[x] = find(par[x]); 
	}
	
	bool merge(int x, int y){
		x = find(x), y = find(y); 
		if(x==y) return false; 
		par[y] = x; 
		sz[x] += sz[y]; 
		return true; 
	}
	
};

struct edge{
	int s, e, x; 
	edge(int s, int e, int x): s(s), e(e), x(x) {} 
	bool operator <(const edge& t) const {
		return x < t.x; 
	}
};

const int MAXN = 100100; 

int l[MAXN], r[MAXN], a[MAXN], b[MAXN], ans[MAXN], sz[MAXN], m[MAXN];  
vector<int> g[MAXN]; 


void solve(){
	 int n,m; 
   cin >> n >> m;
	 vector<edge> E; 
	 rep(i,m){
	 	int s,e,x; cin >> s >> e >> x; 
	 	E.pb(edge(s,e,x)); 
	 }
	 sort(all(E)); 
	 int Q; cin >> Q; 
  rep(i,Q) cin >> a[i] >> b[i]; 
  rep(i,Q) l[i] = 0, r[i] = m+1; 
  // m[i] 마다 uf 에서 연결여부 확인 
  // vector<int> g[]
  // g[m[i]].pb(i) 

  while(1){
    rep(i,m+1) g[i].clear(); 
    dbg("FUCK");
    bool flag = false; 
    rep(i,Q){
      dbg(i,l[i],r[i]);
      if(l[i]+1==r[i]) continue; 
      flag = true; 
      int mid = l[i]+r[i] >> 1; 
      g[mid].pb(i); 
    }
    if(!flag) break; 
    uf UF(n); 
    for(int i=0; i<=m; i++){
      dbg(i); 
      for(auto j : g[i]){
        if(UF.find(a[j])==UF.find(b[j])){
          r[j] = i; 
          dbg(j,i);
          ans[j] = E[i-1].x; 
          dbg(i,j,E[i].s,E[i].e,E[i].x);
          sz[j] = UF.sz[UF.par[a[j]]]; 
        }
        else {
          l[j] = i; 
          dbg(j,i); 
        }
      }
      if(i==m) break;
      UF.merge(E[i].s,E[i].e); 
    }
  }
	rep(i,Q){
    if(r[i]==m+1){
      cout << -1 << "\n";
    }
    else {
      cout << ans[i] << " " << sz[i] << "\n";
    }
  }
}

int32_t main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t=1; //cin >> t; 
    while(t--) solve(); 
    
    
}
