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


const int MAXN = 1000100; 
int l[MAXN], r[MAXN], op[MAXN]; 

int lz[4*MAXN]; 
int seg[4*MAXN]; 

void propogate(int node, int s, int e){
  if(lz[node]==0) return; 
  if(lz[node]==1 || lz[node]==-1){
    seg[node] = (lz[node]==1) * (e-s+1); 
    if(s!=e) lz[2*node] = lz[node], lz[2*node+1] = lz[node]; 
    lz[node] = 0; 
    return; 
  }
  seg[node] = e-s+1 - seg[node]; 
  for(auto c : {2*node, 2*node+1}){
    if(lz[c]==1 || lz[c]==-1) lz[c] = -lz[c]; 
    else lz[c] = 2-lz[c]; 
  }
  lz[node] = 0; return ;
}

void update(int node, int s, int e, int l, int r, int op){
  propogate(node, s, e);  
  if(l<=s && e<=r) {
    if(op==1) lz[node] = 1; 
    if(op==2) lz[node] = -1; 
    if(op==3) lz[node] = 2; 
    propogate(node,s,e); 
    return; 
  }
  if(r<s || l>e) return; 
  int m = s+e>>1; 
  update(2*node, s, m, l, r, op); 
  update(2*node+1,m+1,e,l,r,op); 
  seg[node] = seg[node*2] + seg[node*2+1]; 
}

int query(int node, int s, int e){
  propogate(node,s,e); 
  if(s==e) return s; 
  int m = s+e>>1; 
  propogate(2*node,s,m); 
  if(seg[2*node]<m-s+1) return query(2*node,s,m); 
  return query(2*node+1,m+1,e); 
}


void solve(){
  vector<int> tmp; 
  int n; cin >> n; 
  tmp.pb(1); 
  rep(i,n){
     cin >> op[i] >> l[i] >> r[i]; 
     tmp.pb(l[i]); tmp.pb(r[i]); 
     tmp.pb(l[i]+1); tmp.pb(r[i]+1); 
  }
  sort(all(tmp)); tmp.erase(unique(all(tmp)),tmp.end()); 
  rep(i,n) {
    l[i] = lower_bound(all(tmp),l[i]) - tmp.begin(); 
    r[i] = lower_bound(all(tmp),r[i]) - tmp.begin(); 
  }
  int sz = tmp.size(); 
  rep(i,n){
    update(1,0,sz,l[i],r[i],op[i]); 
    cout << tmp[query(1,0,sz)] << "\n"; 
  }
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
