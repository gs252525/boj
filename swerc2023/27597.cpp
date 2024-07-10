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
#define pi pair<int,int> 
int area(pi& a, pi& b, pi&c){ 
  //cout << a.ff << " " << a.ss << " " << b.ff << " " << b.ss << " " << c.ff << " " << c.ss << "\n"; 
  int x1 = a.ff - b.ff, y1 = a.ss-b.ss; 
  int x2 = a.ff - c.ff, y2 = a.ss-c.ss; 
  return abs(x1*y2 - y1*x2); 
}

int get(){
  int x; cin >> x; 
  return x; 
}

void send(int x){
  cout << x << endl; 
  return ; 
}

void solve(){
  int n; cin >> n; 
  vector<pi> v(n+1); 
  vector<int> remain; 
  rrep(i,n) cin >> v[i].ff >> v[i].ss; 
  rrep(i,n) remain.pb(i); 
  if(n%2==1){
    cout << "Beatrice" << endl; 
    int t = get(); 
    remain.erase(remove(all(remain),t),remain.end()) ; 
  }
  else {
    cout << "Alberto" << endl; 
  }
  
  int t = (n-2)/2; 
  while(t--){
    int sz = remain.size(); 
    //cout << sz << "\n"; 
    int m = 1e18, midx = 0; 
    rep(i,sz){
      int j = remain[(i-1+sz)%sz] , k = remain[(i+1)%sz]; 
      int tmp = area(v[remain[i]],v[j],v[k]); 
      //cout << remain[i] << " " << tmp << "\n"; 
      if(m>tmp){
        m = tmp; midx = remain[i]; 
      }
    }
    send(midx); 
    remain.erase(remove(all(remain),midx),remain.end()) ; 
    remain.erase(remove(all(remain),get()),remain.end()); 
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
