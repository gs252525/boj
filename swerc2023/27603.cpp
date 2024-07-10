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

const int MAXN = 5000; 
int deg[MAXN]; 
pair<int,int> edge[MAXN];
int n,m; 
void color(int x){
  cout << 2 << "\n"; 
  rep(i,m){
    if(edge[i].ff != x && edge[i].ss != x) cout << "1 "; 
    else cout << "2 "; 
  }
  cout << "\n"; 
}

void solve(){
  cin >> n; 
  rrep(i,n) deg[i] = 0; 
  cin >> m; 
  rep(i,m) cin >> edge[i].ff >> edge[i].ss; 
  rep(i,m){
    deg[edge[i].ff]++; deg[edge[i].ss]++; 
  }
  rrep(i,n){
    dbg(i,deg[i])
    if(deg[i]!=n-1){
      color(i); return; 
    }
  }
  cout << 3 << "\n"; 
  rep(i,m){
    auto [x,y] = edge[i]; 
    if(x>y) swap(x,y); 
    if(x!=1 && y!=1) cout << "1 "; 
    else {
      if(y==n) cout << "2 "; 
      else cout << "3 "; 
    }
  }
  cout << "\n"; 
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  cin >> t;
  while(t--) solve(); 
  return 0;
}
