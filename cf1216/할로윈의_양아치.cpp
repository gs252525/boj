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


ll dp[30020];
ll tmp[30020]; 

ll C[30020]; // 캔디 합 
ll n[30020]; // 사람수 

int N,M,K; 

int p[30020]; 

int find(int x){
  if(x==p[x]) return x; 
  return p[x] = find(p[x]); 
}

void merge(int x, int y){
  x = find(x), y = find(y); 
  if(x==y) return; 
  p[y] = x; 
  C[x] += C[y]; 
  n[x] += n[y]; 
}

void solve(){
  cin >> N >> M >> K; 
  K--; 
  rrep(i,N){
    p[i] = i; n[i] = 1; cin >> C[i]; 
  }
  rep(i,M){
    int x,y; cin >> x >> y; merge(x,y); 
  }
  vector<int> v; 
  rrep(i,N) v.push_back(find(i)); 
  sort(all(v)); 
  v.erase(unique(all(v)),v.end()); 
  int t = v.size(); 
  rep(i,t){
    dbg(C[v[i]],n[v[i]]); 
    memcpy(tmp,dp,sizeof(dp)); 
    // C[v[i]], n[v[i]] 
    for(int j=0; j<=K-n[v[i]]; j++) dp[j+n[v[i]]] = max(tmp[j+n[v[i]]], tmp[j] + C[v[i]]); 
  }
  ll M = 0; 
  for(int j=0; j<=K; j++) M = max(M, dp[j]); 
  cout << M; 
};


int main(void) {
  // freopen("C:\Users\User\Downloads\prob3_gold_dec22\19.in", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int tc = 1;
  //cin >> tc;
  while(tc--) solve();
}