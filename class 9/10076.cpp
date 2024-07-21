#include <bits/stdc++.h>
/*
pointer is for noobs. (gs25)
*/

using namespace std; 

typedef long long ll; 

const int MAXN = 100100; 
int pv = 0; 
int L[MAXN*30], R[MAXN*30], cnt[MAXN*30];
ll sum[MAXN*30]; 
vector<int> tmp; 
int a[100100]; 
int n,d; 
int st; 

void build(int n, int s, int e){
  if(s!=e){
    L[n] = ++pv; 
    int m = s+e>>1; 
    build(L[n],s,m); 
    R[n] = ++pv;
    build(R[n],m+1,e); 
  }
}

void update(int prv, int now, int s, int e, int pos){
  cnt[now] = cnt[prv] + 1; 
  sum[now] = sum[prv] + tmp[pos]; 
  int m = s+e>>1; 
  if(s!=e){
    if(pos<=m){
      L[now] = ++pv; 
      update(L[prv],L[now],s,m,pos); 
      R[now] = R[prv]; 
    }
    else {
      R[now] = ++pv; 
      update(R[prv], R[now], m+1, e, pos); 
      L[now] = L[prv]; 
    }
  }
}

ll query(int a, int b, int s, int e, int k){
  int c = cnt[b] - cnt[a];
  if(k>=c) return sum[b] - sum[a]; 
  if(s==e){
    return (ll)tmp[s]*k; 
  }
  int m = s+e>>1; 
  c = cnt[R[b]] - cnt[R[a]]; 
  if(k<=c) return query(R[a],R[b],m+1,e,k); 
  return sum[R[b]] - sum[R[a]] + query(L[a],L[b],s,m,k-c); 
}
ll ans = 0; 


int N[MAXN]; 

void dnc(int s, int e, int l, int r){
  if(s>e || l>r) return; 
  int m = s+e>>1; 
  if(2*(m-st)>d) return dnc(s,m-1,l,r); 
  ll M = -1, idx = -1; 
  for(int i=l; i<=r; i++){
    int L = d - (m-st+m-i);
    ll shit = query(N[i-1],N[m],0,n,max(0,L));
    if(shit>M) M=shit,idx = i; 
  }
  ans = max(ans,M); 
  dnc(s,m-1,l,idx); dnc(m+1,e,idx,r); 
} 

// m <= st 
void dnc1(int s, int e, int l, int r){
  if(s>e || l>r) return; 
  int m = s+e>>1; 
  if(2*(st-m)>d) return dnc1(m+1,e,l,r); 
  ll M=-1, idx = -1; 
  for(int i=l; i<=r; i++){
    int L = d - (st-m+i-m);
    ll shit = query(N[m-1],N[i],0,n,max(0,L)); 
    if(shit>M) M=shit,idx = i; 
  }
  ans = max(ans,M); 
  dnc1(s,m-1,l,idx); dnc1(m+1,e,idx,r); 
}

int32_t main(void){
  ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  cin >> n >> st >> d; 
  st++; 
  for(int i=1; i<=n; i++){
    cin >> a[i]; tmp.push_back(a[i]); 
  }
  sort(tmp.begin(),tmp.end()); 
  tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end()); 
  N[0] = 0;
  build(N[0],0,n); 
  for(int i=1; i<=n; i++){
    a[i] = lower_bound(tmp.begin(),tmp.end(),a[i]) - tmp.begin(); 
    N[i] = ++pv; 
    update(N[i-1],N[i],0,n,a[i]); 
  }
  for(int i=0; i<=d; i++){
    int l = max(st-i,1), r = min(st+i,n); 
    ans = max(ans,query(N[l-1],N[st],0,n,d-i)); 
    ans = max(ans,query(N[st-1],N[r],0,n,d-i)); 
  }
  dnc(st,n,1,st); 
  dnc1(1,st,st,n); 
  cout << ans; 
}
