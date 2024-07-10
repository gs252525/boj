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

const int MAXN = 10000;
int aa[MAXN]; 

void send(int x){
  cout << x << endl; 
}

void send(int y, int a){
  cout << y << " " << a << endl; 
}

void solve(){
  int n,m; cin >> n >> m; 
  vector<int> x(n); 
  rep(i,n) cin >> x[i]; 
  sort(all(x),[](int a, int b){
    return a>b; 
  }); 
  bool flag = false; int id; 
  for(int i=1; i<n; i++){
    //cout << i << " " << x[i] << " " << m/(i+1) << endl; 
    if(x[i]>m/(i+1)){
      flag = true; id = i; break; 
    }
  }
  // x[id] 
  if(flag){
    // B 
    cout << "Bernardo" << endl; 
    //cout << x[id] << endl; 
    rep(i,n){
      int y,a; cin >> y >> a; 
      if(y>=x[id]){
        int t = ((a+y-1)/x[id])*x[id]; 
        cout << t << endl; 
      }
      else {
        cout << a << endl; 
      }
    }
  } 
  else {
    cout << "Alessia" << endl; 
    rep(i,n){
      for(int j=1; j<=m; j+=x[i]){
        int t = 0; 
        for(int k=j; k<j+x[i]; k++) t += aa[k]; 
        if(t==0) {
          cout << x[i] << " " << j << endl; 
          break; 
        }
      }
      int p; cin >> p; 
      aa[p] = 1; 
    }
  }
};


int main() {
  int t = 1;
  // cin >> t;
  while(t--) solve(); 
  return 0;
}
