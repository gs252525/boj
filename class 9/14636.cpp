#include <bits/stdc++.h> 

using namespace  std; 

typedef pair<int,int> pi; 
typedef long long ll; 
#define x first 
#define y second 

vector<pi> pro; vector<pi> con; 
ll ans = 0; 

void dnc(int s, int e, int l, int r){
  if(s>e || l>r) return; 
  int m = l+r>>1; 
  int s1,e1; 
  if(pro[e].y>=con[m].y) e1 = e+1; 
  else {
    e1 = e; 
    while(e1>=s && pro[e1].y<con[m].y) e1--; 
    e1++; 
  }
  if(pro[s].x >= con[m].x) s1 = -1; 
  else {
    s1 = s; 
    while(s1<=e && pro[s1].x<con[m].x) s1++; 
    s1--; 
  }
  if(e1<=s1){
    ll M = -1, idx = -1; 
    for(int i=e1; i<=s1; i++){
      ll t = (ll)(con[m].x - pro[i].x)*(con[m].y-pro[i].y); 
      if(t>M){
        M = t; idx = i; 
      }
    }
    ans = max(ans,M); 
    dnc(s,idx,l,m-1); 
    dnc(idx,e,m+1,r);
    return; 
  }
  dnc(s,s1,l,m-1); 
  dnc(e1,e,m+1,r); 
}

int main(void){
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); 
  int m,n; cin >> m >> n; 
  vector<pi> tmp(m); 
  for(int i=0; i<m; i++) cin >> tmp[i].x >> tmp[i].y; 
  sort(tmp.begin(),tmp.end(),[](auto a, auto b){
    if(a.x!=b.x) return a.x<b.x; 
    return a.y<b.y; 
  });
  int ymin = 2e9; 
  for(int i=0; i<m; i++){
    if(tmp[i].y<ymin) pro.push_back(tmp[i]), ymin = tmp[i].y; 
  }
  vector<pi> tmp1(n); 
  for(int i=0; i<n; i++) cin >> tmp1[i].x >> tmp1[i].y; 
  sort(tmp1.begin(),tmp1.end(),[](auto a, auto b){
    if(a.x!=b.x) return a.x > b.x; 
    return a.y>b.y; 
  }); 
  int yM = -1; 
  for(int i=0; i<n; i++){
    //cerr << i << " " << tmp1[i].x << " " << tmp1[i].y << endl;
    if(tmp1[i].y>yM) con.push_back(tmp1[i]), yM = tmp1[i].y; 
  }
  reverse(con.begin(),con.end()); 
  dnc(0,pro.size()-1,0,con.size()-1); 
  cout << ans; 
}