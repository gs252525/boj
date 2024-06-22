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

string to_string(string s) { return '"' + s + '"'; }

string to_string(const char* s) { return to_string((string)s); }

string to_string(bool b) { return (b ? "true" : "false"); }

template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto& x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

struct point {
  int x,y,p,q; 
  //point(int X, int Y, int P=0, int Q=0) : x(X), y(Y), p(P), q(Q) {} 
  
  bool operator < (const point& t){ 
    if(1LL*p*t.q != 1LL*q*t.p) return 1LL*p*t.q > 1LL*q*t.p; 
    if(y!=t.y) return y < t.y; 
    return x < t.x; 
  }
};

int ccw(point &p1, point &p2, point &p3){
  ll re = 1LL*(p2.x-p1.x)*(p3.y-p1.y) - 1LL*(p3.x-p1.x)*(p2.y-p1.y); 
  return (re>0LL) - (re<0LL); 
}

vector<int> ConvecHull(vector<point> & v){
  int n = v.size(); 
  rep(i,n){
    v[i].p = v[i].x - v[0].x; 
    v[i].q = v[i].y - v[0].y; 
  }
  sort(all(v)); 
  if(n==1) return {0}; 
  vector<int> st; 
  st.push_back(0); st.push_back(1); 
  for(int i=2; i<n; i++){
    debug(st);
    while(st.size()>=2){
      int se = st.back(); st.pop_back(); int fi = st.back(); 
      if(ccw(v[fi],v[se],v[i])>0) {
        st.push_back(se); break; 
      }
    }
    st.push_back(i); 
  }
  return st; 
}

bool intersect(point a, point b, point c, point d){
  int lin_ab = ccw(a,b,c) * ccw(a,b,d); 
  int lin_cd = ccw(c,d,a) * ccw(c,d,b); 
  
  if(lin_ab==0 && lin_cd==0){
    int x1 = min(a.x,b.x), x2 = max(a.x,b.x), y1 = min(a.y,b.y), y2 = max(a.y,b.y); 
    int x3 = min(c.x,d.x), x4 = max(c.x,d.x), y3 = min(c.y,d.y), y4 = max(c.y,d.y); 
    debug(x1); debug(x2); debug(x3); debug(x4);
    if(x1!=x2){
      return x1<=x4 && x3<=x2; 
    }
    return y1<=y4 && y3<=y2;
  }
  return lin_ab<=0 && lin_cd<=0; 
}

void solve(){
  int B,W; cin >> B >> W; 
  vector<point> black(B); 
  vector<point> wight(W); 
  rep(i,B){
    int x,y; cin >> x >> y; black[i].x=x, black[i].y = y; 
  }
  rep(i,W){
    int x,y; cin >> x >> y; wight[i].x = x; wight[i].y = y; 
  }
  sort(all(black)); sort(all(wight)); 
  debug(black[0].x);
  auto convex_b = ConvecHull(black);
  auto convex_w = ConvecHull(wight); 
  if(B==1 && W==1) {
    cout << "YES\n"; return; 
  }
  // 안에 들어가는게 있는지 체크 
  bool flag = true; 
  if(convex_b.size()>=3){
    for(auto w : convex_w){
      flag = false;
      for(int i=0;i<convex_b.size();i++){
        if(ccw(black[convex_b[i]],black[convex_b[(i+1)%(convex_b.size())]],wight[w]) <0){
          flag = true; break; 
        }
      }
      if(!flag) break; 
    }
  }
  
  if(!flag){
    cout << "NO\n"; return;
  }

  if(convex_w.size()>=3){
    for(auto b : convex_b){
      flag = false;
      for(int i=0;i<convex_w.size();i++){
        if(ccw(wight[convex_w[i]],wight[convex_w[(i+1)%(convex_w.size())]],black[b]) <0){
          flag = true; break; 
        }
      }
      if(!flag) { 
        
        break;
      } 
    }
  }

  if(!flag){
    cout << "NO\n"; return; 
  }
  debug(flag);
  debug(convex_w); 
  // 돌아가면서 체크 
  for(int i=0; i<convex_b.size();i++){
    for(int j=0; j<convex_w.size(); j++){debug(i);
        debug(j);
      if(intersect(black[convex_b[i]], black[convex_b[(i+1)%(convex_b.size())]], wight[convex_w[j]], wight[convex_w[(j+1)%(convex_w.size())]])){
        debug(flag);

        flag = false; break; 
      }
    }
    if(!flag) {
      //debug(flag);
      break;
    } 
  }
  if(!flag){
    cout << "NO\n"; return; 
  }
  cout << "YES\n"; return; 
}

int main(void) {
  // freopen("C:\Users\User\Downloads\prob3_gold_dec22\19.in", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int tc =1; 
  cin >> tc; 
  while(tc--){
    solve(); 
  }
}