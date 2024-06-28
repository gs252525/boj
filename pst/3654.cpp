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

const int MAXN = 1000*500 + 20; 

int a[600][600]; 

vector<int> adj[MAXN]; 
int A[MAXN], B[MAXN]; 

int dx[4] = {-1,1,0,0}; 
int dy[4] = {0,0,1,-1}; 


bool visited[MAXN];
 
// A그룹에 속한 정점 a를 이분 매칭시켜서 성공하면 true
bool dfs(int a){
    visited[a] = true;
    for(int b: adj[a]){
        if(B[b] == -1 || !visited[B[b]] && dfs(B[b])){
            A[a] = b;
            B[b] = a;
            return true;
        }
    }
    // 매칭 실패
    return false;
}

void solve(){
  int n,m; cin >> n >> m; 
  int b=0,w=0; 
  rep(i,n){
    rep(j,m){
      char c; cin>> c; 
      if(c=='.') a[i][j] = 0; 
      if(c=='B') a[i][j] = 1,b++; 
      if(c=='W') a[i][j] = 2,w++; 
    }
  }
  if(w!=2*b){
    cout << "NO\n"; return; 
  }
  vector<int> can; 
  rep(i,n){
    rep(j,m){
      if(a[i][j]==1){
        can.pb(2*(m*i+j)); 
        can.pb(2*(m*i+j)+1); 
        adj[2*(m*i+j)].clear(); 
        adj[2*(m*i+j)+1].clear(); 
        rep(k,2){
          int di = i+dx[k],dj = j+dy[k]; 
          if(di>=0 && di<n && dj>=0 && dj<m && a[di][dj]==2){
            int p = 2*(m*i+j), q = di*m+dj; 
            adj[p].pb(q); 
          }
        }
        for(int k=2; k<4; k++){
          int di = i+dx[k],dj = j+dy[k]; 
          if(di>=0 && di<n && dj>=0 && dj<m && a[di][dj]==2){
            int p = 2*(m*i+j)+1, q = di*m+dj; 
            adj[p].pb(q); 
          }
        }
      }
    }
  }
  sort(all(can)); 
  fill(A,A+MAXN,-1); 
  fill(B,B+MAXN,-1); 
  can.erase(unique(all(can)),can.end()); 
  for(auto x : can){
    if(A[x]==-1){
      fill(visited,visited+MAXN,false); 
      if(!dfs(x)){
        cout << "NO\n"; return; 
      }
    }
  }
  cout << "YES\n"; 
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
