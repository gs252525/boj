#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/stdc++.h>
#include <array>
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

void solve(){
  int m,n; cin >> m >> n; 
  vector<array<int,3>> v(n);  
  rep(i,n) cin >> v[i][0]; 
  rep(i,n) cin >> v[i][1]; 
  if(m==2) rep(i,n) v[i][2] = v[i][0]; 
  else rep(i,n) cin >> v[i][2]; 
  sort(all(v)); 
  const int MAXN = 200100; 
  set<pair<int,int>> s[MAXN]; 
  int k = 0; 
  s[0].insert({v[0][1],v[0][2]}); 
  for(int i=1; i<n; i++){
    dbg(i,v[i][1],v[i][2]); 
    int tmp = -1; 
    int l = 0, r = k; 
    while(l<=r){
      int m = l+r>>1; 
      auto iv = s[m].lower_bound({v[i][1],v[i][2]}); 
      if(iv==s[m].begin()){
        r = m-1; continue; 
      }
      iv = prev(iv); 
      if((*iv).ss  <  v[i][2]){
        l = m+1; tmp = max(tmp,m); 
      }
      else {
        r = m-1; 
      }
    }
    s[tmp+1].insert({v[i][1],v[i][2]}); 
    if(tmp==k){
      k++; 
    }
    auto it = s[tmp+1].upper_bound({v[i][1],v[i][2]}); 
    while(it!=s[tmp+1].end() && (*it).ss > v[i][2]){
      auto ne = next(it); 
      s[tmp+1].erase(it); 
      it = ne; 
    }
  }
  cout << k+1; 
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
