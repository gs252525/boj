#include <bits/stdc++.h>

using namespace std;

typedef long long ll; 

int n; 
const int MAXN = 1600; 
ll ans; 
struct BIT{
  int N; ll v[MAXN] = {0,}; 
  BIT(int N): N(N) {} 
  void update(int pos, int val){
    while(pos<=N) v[pos]+=val, pos += pos&-pos; 
  }
  ll query(int pos){
    if(pos<=0) return 0; 
    if(pos>N) pos = N;  
    ll re = 0; 
    while(pos){
     re += v[pos], pos -= pos&-pos; 
    }
    return re; 
  }
};
ll dp[MAXN][MAXN]; 
int a[MAXN][MAXN]; 
int chk[MAXN][2]; 
vector<BIT> dp1; 
const ll inf = 9999; 
ll f(int i,int j){
  return dp1[i].query(j); 
}

void upd(int i, int j, int val){
  int L = j, R = j+1; 
  while(R<=n){
    //cerr << R << " " << f(i,R-1)+val << " " << f(i-1,R) << endl;
    if(f(i,R-1)+val > f(i-1,R)) R++; 
    else break; 
  }
  chk[i][0] = L, chk[i][1] = R; 
  i=i+1; 
  while(i<=n){
    while(L<R){
      if(f(i-1,L)+val <= f(i,L-1)) L++; 
      else break; 
    }
    if(L>=R) break; 
    while(R<=n){
      if(f(i,R-1)+val > f(i-1,R)) R++; 
      else break; 
    }
    chk[i][0] = L, chk[i][1] = R; 
    i++;  
  }
  for(int k=1; k<=n; k++){
    if(chk[k][0]^chk[k][1]){
      //cerr << k << " " << chk[k][0] << " " << chk[k][1] << endl; 
      ans = ans + val*(chk[k][1] - chk[k][0]); 
      dp1[k].update(chk[k][0],val); 
      dp1[k].update(chk[k][1],-val); 
      chk[k][0] = chk[k][1] = 0; 
    }
  }
}

ll upd1(int i, int j, int val){
  a[i][j] += val; 
  ll ans = 0; 
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      dp[i][j] = max(dp[i-1][j],dp[i][j-1]) + a[i][j]; 
      cout << dp[i][j] << " \n"[j==n];
      //dp1[i].update(j,dp[i][j]-dp[i][j-1]); 
      ans += dp[i][j]; 
    }
  }
  return ans; 
}

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);
  freopen("input.txt", "r", stdin);
  cin >> n; 
  dp1.push_back(BIT(n+1)); 
  for(int i=1; i<=n; i++) dp1.push_back(BIT(n+1)); 
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      cin >> a[i][j]; dp[i][j] = max(dp[i-1][j],dp[i][j-1]) + a[i][j]; 
      dp1[i].update(j,dp[i][j]-dp[i][j-1]); 
      ans += dp[i][j]; 
    }
  }
  //cout << ans << "\n"; 
  for(int t=1; t<=n; t++){
    char c; int i,j; cin >> c >> i >> j; 
    ll ans1; 
    if(c=='U') ans1=upd1(i,j,1), upd(i,j,1); 
    else ans1=upd1(i,j,-1), upd(i,j,-1); 
    cout << ans << " " << ans1 << endl; 
  }
} 