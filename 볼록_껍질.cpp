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
  cerr << "\e[" << __func__ << ":" << __LINE__ << " [" << #x << "] = [";    \
  _print(x);                                                                   \
  cerr << "\e[" << endl;
#else
#define dbg(x...)
#endif

struct point{
  ll x,y,p=0,q=0; 
  bool operator <(const point& P){
    if(q*(P.p)==p*(P.q)){
      if(x!=P.x) return x<P.x; 
      return y<P.y; 
    }
    return q*(P.p) < p*(P.q); 
  }
};

int ccw(point& p1, point& p2, point& p3){
  ll t = (p2.p-p1.p)*(p3.q-p1.q) - (p2.q-p1.q)*(p3.p-p1.p); 
  return (t>0LL) - (t<0LL); 
}



void solve(){
  int n; cin >> n; 
  vector<point> points(n); 
  rep(i,n) cin >> points[i].x >> points[i].y; 
  sort(all(points)); 
  int x0 = points[0].x, y0 = points[0].y; 
  rep(i,n) points[i].p = points[i].x - x0, points[i].q = points[i].y-y0; 
  sort(all(points)); 
  //dbg(points); 
  vector<int> convex; 
  convex.push_back(0); 
  convex.push_back(1); 
  for(int i=2; i<n;i++){
    dbg(i,points[i].p, points[i].q); 
    while(convex.size()>=2){
      int next = convex.back(); convex.pop_back(); 
      int t = convex.back(); 
      if(ccw(points[t],points[next],points[i])>0) {
        convex.push_back(next); break; 
      }
    }
    convex.push_back(i); 
  } 
  cout << convex.size(); 
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
