#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/stdc++.h>
#define pb push_back
#define pf push_front 
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

int Q=300; 
int N,K; 

struct query{
  int l,r,idx; 
  bool operator< (query& t) const{
    if(l/Q==t.l/Q) return r<t.r; 
    return l<t.l; 
  }
};

const int MAXN = 100100; 
int a[MAXN]; 
list<int> bucket[MAXN]; 
int ans[MAXN]; 


struct big_{
  int cnt[MAXN] = {}; 
  int cnt2[MAXN] = {}; 

  void insert(int x){
    cnt[x]++; cnt2[x/Q]++; 
  }

  void erase(int x){
    cnt[x]--; cnt2[x/Q]--; 
  }

  int query(){
    for(int i=400;i>=0; i--){
      if(cnt2[i]>0){
        int s = (i+1)*Q; 
        while(cnt[s]==0) s--; 
        return s; 
      }
    }
  }
}big; 

void add(int i){
  auto& lis = bucket[a[i]]; 
  if(lis.empty()){
    lis.pb(i); 
    big.insert(0); 
  }
  else{
    if(i>lis.back()){
      int prv = lis.back() - lis.front(); 
      lis.pb(i); 
      int now = lis.back() - lis.front(); 
      big.erase(prv); 
      big.insert(now); 
    }
    else {
      assert(i<lis.front()); 
      int prv = lis.back() - lis.front(); 
      lis.pf(i); 
      int now = lis.back() - lis.front(); 
      big.erase(prv); 
      big.insert(now); 
    }
  }
}

void erase(int i){
  auto& lis = bucket[a[i]]; 
  assert(!lis.empty()); 
  if(i==lis.front()){
    int prv = lis.back() - lis.front(); 
    lis.pop_front(); 
    big.erase(prv); 
    if(!lis.empty()){
      int now = lis.back() - lis.front(); 
      big.insert(now); 
    }
  }
  else {
    assert(i==lis.back()); 
    int prv = lis.back() - lis.front(); 
    lis.pop_back(); 
    big.erase(prv); 
    assert(!lis.empty());
    int now = lis.back() - lis.front(); 
    big.insert(now); 
  }
}

void solve(){
  cin >> N >> K; 
  rrep(i,N) cin >> a[i]; 
  int m;cin>>m; 
  vector<query> Q(m);
  rep(i,m){
    cin >> Q[i].l >> Q[i].r; 
    Q[i].idx = i; 
  }
  sort(all(Q)); 
  int lx = 1, rx = 1;
  bucket[a[1]].pb(1);  big.insert(0); 
  rep(i,m){
    int l = Q[i].l, r = Q[i].r, idx = Q[i].idx; 
    while(lx>l) add(--lx); 
    while(r>rx) add(++rx); 
    while(r<rx) erase(rx--); 
    while(lx<l) erase(lx++); 
    ans[idx] = big.query(); 
  }
  rep(i,m) cout << ans[i] << "\n";
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
