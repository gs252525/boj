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

const int MAXN = 4010000; 

struct maxseg{
  ll lz[MAXN], v[MAXN]; 

  void build(int node, int s, int e){
    v[node] = e; 
    if(s==e) return; 
    int m = s+e>>1; 
    build(2*node,s,m); build(2*node+1,m+1,e); 
  }

  void pro(int node, int s, int e){
    if(!lz[node]) return; 
    if(s==e) {
      v[node] += lz[node]; lz[node]=0; return; 
    }
    lz[2*node] += lz[node]; 
    lz[2*node+1] += lz[node]; 
    v[node] += lz[node]; 
    lz[node] = 0; return; 
  }

  void update(int node, int s, int e, int l, int r, int val){
    pro(node,s,e);
    if(r<s||l>e) return; 
    if(l<=s && e<=r){
      lz[node] += val; 
      pro(node, s, e); 
      return; 
    }
    int m = s+e>>1; 
    pro(node,s,e); 
    update(2*node,s,m,l,r,val); update(2*node+1,m+1,e,l,r,val); 
    v[node] = max(v[2*node],v[2*node+1]); 
  }

  ll query(int node, int s, int e, int l, int r){
    pro(node,s,e); 
    if(r<s||l>e) return 0; 
    if(l<=s && e<=r) return v[node];
    int m = s+e>>1; 
    return max(query(2*node,s,m,l,r),query(2*node+1,m+1,e,l,r)); 
  }
}; 

struct BIT{
  ll v[MAXN]; 
  int n; 
  BIT(int n): n{n} {} 
  void update(int pos, ll val){
    while(pos<=n){
      v[pos] += val; pos += pos&-pos; 
    }
  }
  ll query(int pos){
    ll re = 0; 
    while(pos){
      re += v[pos]; pos -= pos&-pos; 
    }
    return re; 
  }
};

int t[MAXN];
int d[MAXN];  

void solve(){
  int q; cin >> q; 
  int n = 1000010; 
  maxseg seg; 
  seg.build(1,1,n); 
  BIT bt(n); 
  for(int i=1; i<=q; i++){
    char c; cin >> c; 
    if(c=='+'){
      cin >> t[i] >> d[i]; 
      bt.update(t[i],d[i]); 
      seg.update(1,1,n,1,t[i],d[i]); 
    }
    if(c=='-'){
      int id; cin >> id; 
      bt.update(t[id],-d[id]); 
      seg.update(1,1,n,1,t[id],-d[id]); 
    }
    if(c=='?'){
      int x; cin >> x; 
      ll ans = seg.query(1,1,n,1,x) - bt.query(n+1) + bt.query(x) - x; 
      cout << ans << "\n"; 
    }
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
