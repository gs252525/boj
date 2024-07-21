#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, n) for (int i = 0; i < n; ++i)
using namespace std;
typedef long long ll;

int pv; 
const int MAXN = 200100; 
int l[MAXN*30],r[MAXN*30]; 

void init(){
  for(int i=0; i<=pv; i++)l[i]=r[i]=0;
  pv = 0; 
}

void insert(int node, int x, int bit){
  if(bit==-1) return; 
  if((x>>bit)&1){
    if(r[node]==0) r[node] = ++pv; 
    insert(r[node],x,bit-1); 
  }
  else{
    if(l[node]==0) l[node] = ++pv; 
    insert(l[node],x,bit-1); 
  }
}

int query(int node, int x, int bit){
  if(bit==-1) return 0; 
  if((x>>bit)&1){
    if(r[node]==0) return (1<<bit)+query(l[node],x,bit-1); 
    return query(r[node],x,bit-1); 
  }
  else{
    if(l[node]==0) return (1<<bit)+query(r[node],x,bit-1);
    return query(l[node],x,bit-1); 
  }
}

int a[MAXN]; 
ll ans = 0; 
void f(int i,int j, int bit){
  if(bit==-1) return; 
  if( (a[i]>>bit&1) == (a[j]>>bit&1)){
    f(i,j,bit-1); return;
  }
  init(); 
  int k = i; 
  while((a[k]>>bit&1)==0) insert(0,a[k],bit),k++; 
  int tmp = 1<<30; 
  for(int l=k;l<=j;l++) tmp = min(tmp,query(0,a[l],bit)); 
  ans += tmp; 
  f(i,k-1,bit-1); 
  f(k,j,bit-1); 
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n; cin >> n; 
  rep(i,n) cin >> a[i];
  sort(a,a+n); 
  f(0,n-1,29); 
  cout << ans; 
  return 0; 
}