#include <bits/stdc++.h>

using namespace std; 

typedef long long ll; 
const int MAXN = 300100; 

int seg[MAXN*4]; 
int x[MAXN], y[MAXN], child[MAXN], L[MAXN], R[MAXN], vis[MAXN]; 

auto cmp = [](pair<ll,int> a, pair<ll,int> b){
  if(a.first!=b.first) return a.first < b.first; 
  return a.second > b.second; 
};

priority_queue<pair<ll,int>,vector<pair<ll,int>>, decltype(cmp)> pq(cmp); 
ll fuck[MAXN]; 

void build_rmq(int node, int s, int e){
  if(s==e){
    seg[node] = s; return; 
  }
  int m = s+e>>1; 
  build_rmq(2*node, s,m); build_rmq(2*node+1,m+1,e); 
  int a = seg[2*node], b = seg[2*node+1]; 
  seg[node] = (y[a]>y[b]) ? b : a; 
}

int query(int node, int s, int e, int l, int r){
  if(r<s || l>e) return -1; 
  if(l<=s && e<=r) return seg[node]; 
  int m = s+e>>1; 
  int a = query(2*node,s,m,l,r), b = query(2*node+1,m+1,e,l,r); 
  if(a==-1) return b; if(b==-1) return a; 
  return y[a]>y[b] ? b : a; 
}
int n; 
int pv; 
void build(int node, int s, int e, int h){
  int idx = query(1,1,n,s,e); 
  //cerr << idx << endl; 
  ll val = (ll)(x[e]-x[s-1])*(y[idx]-h); 
  //cerr << x[s-1] << endl; 
  L[node] = -1, R[node] = -1; 
  if(s<=idx-1){
    pv++; 
    L[node] = pv; 
    build(pv,s,idx-1,y[idx]); 
  }
  if(idx+1<=e){
    pv++; 
    R[node] = pv; 
    build(pv,idx+1,e,y[idx]); 
  }
  ll l = (L[node]!=-1 ? fuck[L[node]] : 0), r = (R[node]!=-1 ? fuck[R[node]] : 0); 
  fuck[node] = val + max(l,r); 
  if(l>r) child[node] = L[node]; 
  else if(r>l) child[node] = R[node]; 
  else{
    if(L[node]==-1 && R[node]==-1) child[node] = -1; 
    else if(L[node]!=-1) child[node] = L[node]; 
    else if(R[node]!=-1) child[node] = R[node]; 
  }
  pq.push({fuck[node],node}); 
}

int32_t main(void){
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); 
  cin >> n; n = (n-1)>>1; 
  cin >> x[0] >> y[0]; 
  for(int i=1; i<=n; i++){
    cin >> x[i] >> y[i]; cin >> x[i] >> y[i]; 
  }
  cin >> x[0] >> y[0]; 
  x[0] = 0, y[0] = 0; 
  build_rmq(1,1,n); 
  
  build(0,1,n,0); //cerr << "fuck" << endl; 
  int k; cin >> k; 
  ll ans = 0; int cnt = 0; 
  while(cnt<k && !pq.empty()){
    auto [val, i] = pq.top(); pq.pop(); 
    //cerr << val << " " << i << endl; 
    if(vis[i]) continue; ans += val; 
    //cerr << i << " " << val << endl;
    while(i!=-1) {
      vis[i] = 1; i = child[i]; 
    }
    cnt++; 
  }
  cout << ans; 
}

