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

int N,M;
const int MAXN = 1000020;  
int adj[MAXN]; 
int f(int x,int y){
  return M*x+y; 
}

int incyc[MAXN]; 
int visited[MAXN]; 
int cnt = 0; 

void dfs(int x){
  int ne = x; 
  while(!visited[ne]){ 
    visited[ne] = cnt+1; ne = adj[ne]; 
  }
  if(visited[ne]!=cnt+1){
    int c = visited[ne]; 
    while(visited[x]!=c){
      visited[x] = c; x = adj[x]; 
    }
    return; 
  }
  cnt++; 
}


void solve(){
  cin >> N >> M; 
  rep(i,N){
    rep(j,M){
      char c; cin >> c; 
      if(c=='D') adj[f(i,j)] = f(i+1,j); 
      if(c=='R') adj[f(i,j)] = f(i,j+1); 
      if(c=='L') adj[f(i,j)] = f(i,j-1); 
      if(c=='U') adj[f(i,j)] = f(i-1,j); 
    }
  }
  rep(i,M*N) if(!visited[i]) dfs(i); 
  cout << cnt;
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
