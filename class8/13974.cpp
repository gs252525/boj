#include <bits/stdc++.h> 
using namespace std; 

typedef long long ll; 

const int MAXN = 5010; 
int dp[MAXN][MAXN]; 
int opt[MAXN][MAXN]; 
int c[MAXN]; 
int psum[MAXN]; 

int main(void){
  ios::sync_with_stdio(false); 
  cin.tie(nullptr); cout.tie(nullptr); 
  int t; cin >> t; 
  while(t--){
    int n; cin >> n; 
    for(int i=1; i<=n; i++){
      cin >> c[i]; psum[i] = psum[i-1]+c[i]; 
    }
    for(int i=1; i<=n-1; i++) {
      opt[i][i+2] = i+1, dp[i][i+2] = psum[i+1] - psum[i-1]; 
      //cout << i << " " << i+2 << " " << dp[i][i+2] << " " << opt[i][i+2] << endl; 
    }
    for(int d=3;d<=n;d++){
      for(int i=1; i<=n+1-d; i++){
        // dp[i][i+d]    opt[i][i+d-1] ~  opt[i+1][i+d] 
        int m = 2e9; 
        for(int k=opt[i][i+d-1]; k<=opt[i+1][i+d]; k++) if(m>dp[i][k]+dp[k][i+d]+psum[i+d-1]-psum[i-1]){
          m=dp[i][k]+dp[k][i+d]+psum[i+d-1]-psum[i-1], opt[i][i+d] = k;  
        } 
        dp[i][i+d] = m; 
        //cout << i << " " << i+d << " " << dp[i][i+d] << " " << opt[i][i+d] << endl; 
      }
    }
    cout << dp[1][n+1] << "\n"; 
  }
}
