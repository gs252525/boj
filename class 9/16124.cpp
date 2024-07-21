#include <bits/stdc++.h>

using namespace std; 

typedef long long ll;


struct node{
  int lz[10]; 
  ll fuck; 
  ll shit[10]; 
};  

node v[4010101]; 
const ll mod = 998244353; 

ll po[1010101]; 

string num; 

void build(int n, int s, int e){
  node& now = v[n]; 
  for(int i=0; i<10; i++) now.lz[i] = i;
  if(s==e){
    int k = num[s]-'0';
    now.shit[k] = 1; 
    now.fuck = k; return; 
  }
  int m = s+e>>1; 
  build(2*n,s,m); build(2*n+1,m+1,e); 
  for(int i=0; i<10; i++) {
    now.shit[i] = po[e-m]*v[n*2].shit[i] + v[n*2+1].shit[i]; 
    now.shit[i] %= mod; 
  }
  now.fuck = po[e-m]*v[n*2].fuck + v[n*2+1].fuck; 
  now.fuck %= mod; 
}

void pro(int n, int s, int e){
  node& now = v[n]; 
  bool flag = false; 
  ll tmp[10] = {0,};
  for(int i=0; i<10; i++) if(now.lz[i]!=i) flag = true; 
  if(!flag) return; 
  for(int i=0; i<10; i++){
    tmp[now.lz[i]] += now.shit[i]; 
  }
  if(s!=e){
    int tmp1[10] = {0,}; 
    for(int i=0; i<10; i++) tmp1[i] = now.lz[v[n*2].lz[i]];
    for(int i=0; i<10; i++) v[n*2].lz[i] = tmp1[i]; 
    for(int i=0; i<10; i++) tmp1[i] = now.lz[v[n*2+1].lz[i]];
    for(int i=0; i<10; i++) v[n*2+1].lz[i] = tmp1[i]; 
  }
  ll f = 0; 
  for(int i=0; i<10; i++) now.shit[i] = tmp[i]%mod, now.lz[i]=i; 
  for(int i=0; i<10; i++) f += now.shit[i] * i; 
  now.fuck = f%mod; 
} 

void update(int n, int s, int e, int l, int r, int a, int b){
  // l~r a->b 
  pro(n,s,e); 
  if(r<s || l>e) return; 
  if(l<=s && e<=r){
    v[n].lz[a] = b; 
    pro(n,s,e); 
    return; 
  }
  int m = s+e>>1; 
  update(2*n, s, m, l, r, a, b); 
  update(2*n+1, m+1, e, l, r, a, b); 
  v[n].fuck = v[n*2].fuck * po[e-m] + v[n*2+1].fuck; 
  v[n].fuck %= mod; 
  for(int i=0; i<10; i++) v[n].shit[i] = (v[n*2].shit[i]*po[e-m] + v[n*2+1].shit[i])%mod; 
}

ll query(int n, int s, int e, int l, int r){
  pro(n,s,e); 
  if(r<s || l>e) return 0; 
  if(l<=s && e<=r){
    return v[n].fuck; 
  } 
  int m = s+e>>1; 
  if(r<=m) return query(2*n,s,m,l,r); 
  if(l>m) return query(2*n+1,m+1,e,l,r); 
  ll re = po[r-m] * query(2*n,s,m,l,m) + query(2*n+1,m+1,e,m+1,r); 
  re %= mod; 
  if(re<0) re += mod; 
  return re; 
}

int main(void){
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); 
  cin >> num; 
  int n = num.size(); 
  po[0] = 1; 
  for(int i=1; i<=n; i++) po[i] = po[i-1]*10LL % mod; 
  build(1,0,n-1); 
  int Q; cin >> Q; 
  while(Q--){
    int op,i,j; cin >> op >> i >> j; i--; j--;
    if(op==1){
      int f,t; cin >> f >> t; if(f==t) continue; 
      update(1,0,n-1,i,j,f,t); 
    }
    else {
      cout << (query(1,0,n-1,i,j)+mod)%mod << "\n";
    }
  }
}