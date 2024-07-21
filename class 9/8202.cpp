#include <bits/stdc++.h>

using namespace std; 

const int MAXN = 5010;
int cnt[MAXN]; 
int chk[MAXN]; 
int shit[MAXN]; 

int ncr(int n, int r){
  int re =1; if(r>n/2) r = n-r; 
  for(int i=1; i<=r; i++) re = re*(n+1-i) / i; 
  return re; 
}

int main(void){
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); 
  int n; cin >> n; 
  vector<int> v; 
  int b = 0; 
  for(int i=1; i<=n; i++){
    int x; cin >> x; v.push_back(x); int y; cnt[x]++; b+=x; 
    while(x--){
      cin >> y; 
    }
  }
  sort(v.begin(),v.end(),[](int x,int y){
    return x>y;
  }); 
  int a = 0, ans = 0; 
  for(int i=0; i<n; i++){
    // a - b = k*(k-1)/2 
    a += v[i]; b -= v[i]; 
    //cerr << i << " " << a << " " << b << endl; 
    shit[v[i]]++; 
    if(a-b==(i+1)*i && i!=n-1){
      ans+= ncr(cnt[v[i]],shit[v[i]]); chk[i] = 1; 
    }
  }
  cout << ans; 
} 