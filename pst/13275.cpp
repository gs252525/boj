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
  node() {
    l = NULL; r = NULL; v = 0; 
  }
};

void build(node* n, int s, int e){
  if(s==e) return; 
  int m = s+e>>1; 
  n->l = new node(); 
  n->r = new node(); 
  build(n->l,s,m); 
  build(n->r,m+1,e); 
}

void update(node* prv, node* now, int s, int e, int pos){
  if(pos<s||pos>e) return; 
  now->v = prv->v + 1; 
  int m = s+e>>1; 
  if(s!=e){
    if(pos<=m){
      now->r = prv->r; 
      now->l = new node(); 
      update(prv->l,now->l,s,m,pos); 
    }
    else { 
      now->l = prv->l; 
      now->r = new node(); 
      update(prv->r,now->r,m+1,e,pos); 
    }
  }
}

// 같은것 / 작은것
pair<int,int> query(node* l, node* r, int s, int e, int val){
  if(s==e) return {r->v-l->v,0}; 
  int m = s+e>>1; 
  if(val<=m) return query(l->l,r->l,s,m,val); 
  if(val>m){
    auto [x,y] = query(l->r,r->r,m+1,e,val); 
    return {x,y+r->l->v -l->l->v}; 
  }
}


const int MAXN = 2001000; 
node* A[MAXN]; 
node* B[MAXN];


vector<int> a; 
vector<int> b; 

int N,K; 

void solve(){
  cin >> K >> N; 
  A[0] = new node(); 
  B[0] = new node(); 
  vector<int> tmp1, tmp2; 
  a.resize(N); 
  b.resize(K); 
  build(B[0],0,K); 
  rep(i,K) {
    cin >> b[i]; 
    tmp2.pb(b[i]); 
  }
  sort(all(tmp2)); 
  tmp2.erase(unique(all(tmp2)),tmp2.end()); 
  rep(i,K) b[i] = lower_bound(all(tmp2),b[i]) - tmp2.begin(); 
  rep(i,K) {
    B[i+1] = new node(); 
    update(B[i],B[i+1],0,K,b[i]); 
  }
  
  rep(i,N) {
    cin >> a[i]; 
    tmp1.pb(a[i]); 
  }
  sort(all(tmp1)); 
  tmp1.erase(unique(all(tmp1)),tmp1.end()); 
  rep(i,N) a[i] = lower_bound(all(tmp1),a[i]) - tmp1.begin();  
  build(A[0],0,N); 
  rep(i,N) {
    A[i+1] = new node(); 
    update(A[i],A[i+1],0,N,a[i]); 
  }
  // a[i] = query(a[0],a[i],0,N,a[i])
  
  vector<int> pi(K,0); 
  for(int i=1,j=0; i<K; i++){
    while(j){
      // && b[j] != b[i] 
      if(query(B[0],B[j],0,K,b[j]) != query(B[i-j],B[i],0,K,b[i])) j = pi[j-1]; 
      else break; 
    }
    if(query(B[0],B[j],0,K,b[j]) == query(B[i-j],B[i],0,K,b[i])) pi[i] = ++j; 
  }
  vector<int> ans; 
  for(int i=0,j=0; i<N; i++){
    while(j){
      if(query(B[0],B[j],0,K,b[j]) != query(A[i-j],A[i],0,N,a[i])) j = pi[j-1];
      else break;  
    }
    if(query(B[0],B[j],0,K,b[j]) == query(A[i-j],A[i],0,N,a[i])){
      if(j==K-1) {
        ans.pb(i-K+2); 
        j = pi[j]; 
      }
      else j++; 
    }
  }
  if(!ans.empty()) for(auto i : ans) cout << i << ' '; 
  else cout << 0;
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
