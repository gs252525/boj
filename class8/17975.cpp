#include <bits/stdc++.h> 

#define rep(i,n) for(int i=0; i<n; i++)
#define pb push_back 
#define all(v) (v).begin(), (v).end() 

using namespace std; 

int board[2200][2200]; 

struct node{
  int sum, M, lM, rM; 
  node(int sum, int M, int lM, int rM): sum{sum}, M{M}, lM{lM}, rM{rM} {} 
  node(){
    sum=M=lM=rM=0; 
  }
}; 

node merge(node& l, node& r){
  node n; 
  n.sum = l.sum + r.sum; 
  n.lM = max(l.sum+r.lM, l.lM); 
  n.rM = max(r.sum+l.rM, r.rM); 
  n.M = max({n.lM,n.rM,l.rM+r.lM,l.M,r.M}); 
  return n; 
}

struct seg{
  int n; 
  vector<node> v; 
  seg(int n): n{n}{
    v.resize(4*n+20,node()); 
  }
  void update(int node, int l, int r, int pos, int val){
    if(pos<l || pos>r) return; 
    if(l==r){
      v[node].sum += val; 
      v[node].lM = max(0,v[node].sum); 
      v[node].rM = max(0,v[node].sum); 
      v[node].M = max(0,v[node].sum); 
      return; 
    }
    int m = l+r>>1; 
    if(pos<=m) update(2*node,l,m,pos,val); 
    else update(2*node+1,m+1,r,pos,val); 
    v[node] = merge(v[2*node],v[2*node+1]); 
  }
}; 

int main(void){
  vector<pair<int,int>> v; 
  vector<int> x,y; 
  int a; cin >> a; 
  rep(i,a){
    int p,q; cin >> p >> q; 
    v.pb({p,q}); 
    x.pb(p); y.pb(q); 
  }
  int b;
  cin >> b; 
  vector<pair<int,int>> vv; 
  rep(i,b){
    int p,q; cin >> p >> q; 
    vv.pb({p,q}); 
    x.pb(p); y.pb(q); 
  }
  sort(x.begin(),x.end()); 
  x.erase(unique(x.begin(),x.end()),x.end()); 
  sort(all(y)); 
  y.erase(unique(all(y)),y.end()); 
  int c1=0,c2; cin >> c1 >> c2; 
  rep(i,a){
    auto& [p,q] = v[i]; 
    p = lower_bound(all(x),p) - x.begin(); 
    q = lower_bound(all(y),q) - y.begin(); 
    board[p][q] += c1; 
  }
  rep(i,b){
    auto& [p,q] = vv[i]; 
    p = lower_bound(all(x),p) - x.begin(); 
    q = lower_bound(all(y),q) - y.begin(); 
    board[p][q] -= c2 ; 
  }
  int m = x.size(), n = y.size(); 
  //cerr << m << " " << n << endl; 
  sort(all(v)); 
  sort(all(vv)); 
  int ans = 0; 
  rep(i,m){
    int s = 0, ss = 0; 
    seg S(n);  
    while(s<v.size() && v[s].first < i)s++; 
    while(ss<vv.size() && vv[ss].first < i) ss++; 
    for(int j=i; j<m; j++){
      while(s<v.size() && v[s].first<=j){
        S.update(1,0,n-1,v[s].second,board[j][v[s].second]); 
        //cerr << j << " " << v[s].second << " " << board[j][v[s].second] << endl; 
        s++; 
      }
      while(ss<vv.size() && vv[ss].first<=j){
        S.update(1,0,n-1,vv[ss].second,board[j][vv[ss].second]); 
        //cerr << j << " " << vv[ss].second << " " << board[j][vv[ss].second] << endl; 
        ss++; 
      }
      ans = max(ans,S.v[1].M); 
    }
  }
  cout << ans; 
}