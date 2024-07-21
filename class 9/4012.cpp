#include <bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rrep(i, n) for (int i = 1; i <= n; ++i)
#define ff first
#define ss second
using namespace std;
typedef long long ll;

int n; 
const int MAXN = 500100; 

int pos[MAXN]; 
int dp[MAXN][20]; 

int f(int s, int e){
  if(e<0 || e<=s) return 0; 
  int chk = e; 
  if(pos[e]<s) return 0; 
  int re = 0; 
  for(int i=19; i>=0; i--){
    if(chk<=s) break; 
    if(dp[chk][i]<s) continue; 
    chk = dp[chk][i]-1; 
    re |= (1<<i); 
  }
  return re; 
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> n; 
  vector<pair<int,int>> v(n); 
  vector<int> tmp; 
  rep(i,n){
    cin >> v[i].ff >> v[i].ss; 
    tmp.pb(v[i].ff); tmp.pb(v[i].ss); 
  }
  sort(all(tmp)); 
  tmp.erase(unique(all(tmp)),tmp.end()); 
  rep(i,n) v[i].ff = lower_bound(all(tmp),v[i].ff) - tmp.begin(), v[i].ss = lower_bound(all(tmp),v[i].ss) - tmp.begin(); 
  int N = tmp.size(); 
  auto vv = v; 
  sort(all(v),[](auto &x, auto &y){
    return x.ss < y.ss; 
  });
  int mx = -1; int j = 0;
  rep(i,N){
    while(j<n && v[j].ss<=i){
      mx = max(mx,v[j].ff); j++; 
    } 
    pos[i] = mx; 
    dp[i][0] = pos[i]; 
    for(int k=1; k<20; k++){
      if(dp[i][k-1]<=0) dp[i][k] = -1; 
      else dp[i][k] = dp[dp[i][k-1]-1][k-1]; 
    }
  }
  int d = f(0,N-1); 
  cout << d << "\n"; 
  map<int,int> s;  
  s[0] = N-1; 
  rep(i,n){
    if(s.empty()) break; 
    int l = vv[i].ff, r = vv[i].ss; 
    auto lb = s.upper_bound(l); 
    if(lb==s.begin()) continue; 
    lb = prev(lb); 
    auto [ll,rr] = *lb; 
    if(rr<r) continue; 
    int cnt = f(ll,rr);
    int p=f(ll,l-1), q = f(r+1,rr);
    if(cnt == f(ll,l-1)+1+f(r+1,rr)){
      cout << i+1 << " "; 
      s.erase(lb); 
      if(l-1>ll && p!=0){
        s[ll] = l-1; 
      }
      if(r+1<rr && q!=0){
        s[r+1] = rr;  
      }
    }
  }
  return 0;
}
