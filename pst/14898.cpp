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

struct node{
  node* l; node* r; 
  int v; 
  node(){
    l = NULL; r = NULL; v = 0; 
  }
};

const int MAXN = 1000100; 
node* ps[MAXN]; 

void build(node* n, int s, int e){
  if(s==e) return; 
  n->l = new node(); 
  n->r = new node();
  int m = s+e>>1;  
  build(n->l,s,m);
  build(n->r,m+1,e);  
}

void update(node* prv, node* now, int s, int e, int v){
  if(s==e){
    now->v = prv->v + 1; return; 
  }
  int m = s+e>>1; 
  now->v = prv->v+1; 
  if(v<=m){
    now->r = prv->r; 
    now->l = new node(); 
    update(prv->l,now->l,s,m,v); 
  }
  else {
    now->l = prv->l; 
    now->r = new node(); 
    update(prv->r,now->r,m+1,e,v); 
  }
}

int query(node* now, int s, int e, int l, int r){
  // l~r 까지 합 
  if(r<s || l>e) return 0; 
  if(l<=s && e<=r) return now->v; 
  int m = s+e>>1; 
  return query(now->l,s,m,l,r) + query(now->r,m+1,e,l,r); 
}

void solve(){
  int N,Q; cin >> N ; // >> Q; 
  vector<int> a(N+1), l(N+1); 
  map<int,int> M; 
  rrep(i,N){
    cin >> a[i]; 
    l[i] = M[a[i]]; 
    M[a[i]] = i; 
    dbg(i,l[i]); 
  }
  cin >> Q; 
  ps[0] = new node(); 
  build(ps[0],0,N); 
  rrep(i,N) {
    ps[i] = new node(); 
    update(ps[i-1],ps[i],0,N,l[i]); 
  } 
  dbg(query(ps[N],0,N,0,0)); 
  int prv = 0; 
  rrep(i,Q){
    int x,r; cin >> x >> r; 
    x += prv; 
    dbg(x,r) 
    // l~r 사이 left 가 l 이하인 것의 개수의 합 
    dbg(query(ps[r],0,N,0,x))
    dbg(query(ps[x-1],0,N,0,x))

    int ans = query(ps[r],0,N,0,x-1) - query(ps[x-1],0,N,0,x-1); 
    cout << ans << "\n"; 
    prv = ans; 
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
