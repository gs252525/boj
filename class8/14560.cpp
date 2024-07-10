#include <bits/stdc++.h> 

using namespace std; 

#define pb push_back 
#define rep(i,n) for(int i=0; i<n; i++)
#define rrep(i,n) for(int i=1; i<=n; i++)

typedef long long ll; 

ll a[36]; 

const int MAXN = 15348907; 
ll tmp1[4782969];
ll tmp2[4782969]; 
ll tmp3[4782969]; 
ll L[MAXN], R[MAXN]; 
const ll inf = 2e18; 

int main(void){
  ios::sync_with_stdio(false); 
  cin.tie(nullptr); cout.tie(nullptr); 
  int n; cin >> n; 
  rrep(i,n) cin >> a[i]; 
  int l = n>>1; int r = n-l; 
  int pv = 1;
  for(int i=1; i<=l; i++){
    rep(j,pv) tmp1[j] = L[j] - a[i], tmp2[j] = L[j], tmp3[j] = L[j] + a[i]; 
    tmp1[pv] = tmp2[pv] = tmp3[pv] = inf;
    int pu = 0; 
    for(int p=0, q=0, r=0; p<pv|| q<pv|| r<pv; ){
      // tmp1[p] tmp2[q] tmp3[r] 중 최소 
      if(tmp1[p]<=tmp2[q] && tmp1[p]<=tmp3[r]){
        L[pu] = tmp1[p]; pu++, p++; 
      }
      else if(tmp2[q]<=tmp1[p] && tmp2[q]<=tmp3[r]){
        L[pu] = tmp2[q]; pu++, q++; 
      }
      else {
        L[pu] = tmp3[r]; pu++; r++; 
      }
    }
    pv *= 3; 
  }
  int pv1 = 1;
  for(int i=l+1; i<=n; i++){
    rep(j,pv1) tmp1[j] = R[j] - a[i], tmp2[j] = R[j], tmp3[j] = R[j] + a[i]; 
    tmp1[pv1] = tmp2[pv1] = tmp3[pv1] = inf; 
    int pu = 0; 
    for(int p=0, q=0, r=0; p<pv1|| q<pv1|| r<pv1; ){
      // tmp1[p] tmp2[q] tmp3[r] 중 최소 
      if(tmp1[p]<=tmp2[q] && tmp1[p]<=tmp3[r]){
        R[pu] = tmp1[p]; pu++, p++; 
      }
      else if(tmp2[q]<=tmp1[p] && tmp2[q]<=tmp3[r]){
        R[pu] = tmp2[q]; pu++, q++; 
      }
      else {
        R[pu] = tmp3[r]; pu++; r++; 
      }
    }
    pv1 *= 3; 
  }
  ll D; cin >> D; 
  ll ans = 0; 
  for(int i=0,s=0,e=0; i<pv; i++){
    while(s<pv1 && L[i]-D > R[s])s++; 
    while(e<pv1 && L[i]+D >= R[e]) e++; 
    ans += e-s; 
  }
  cout << ans; 
  return 0; 
}