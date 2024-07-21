#include <bits/stdc++.h>
#include <array> 
#define rrep(i,n) for(int i=1; i<=n; i++)
#define rep(i,n) for(int i=0; i<n; i++)

using namespace std; 

struct fuck{
  int lmost, rmost, M;
  bool isfull = false;  
  fuck(int lmost, int rmost, int M): lmost{lmost}, rmost{rmost}, M{M} {}
  fuck(){
    lmost = rmost = M = 0; 
    isfull = false; 
  }
};

fuck merge(fuck a, fuck b){
  fuck re(0,0,0); 
  if(a.isfull && b.isfull) re.isfull = true; 
  if(a.isfull) re.lmost = a.M + b.lmost; 
  else re.lmost = a.lmost; 
  if(b.isfull) re.rmost = b.M + a.rmost; 
  else re.rmost = b.rmost; 
  re.M = max({a.M,b.M,re.lmost,re.rmost,a.rmost+b.lmost}); 
  return re; 
}


struct seg{
  int n; vector<fuck> v; 
  seg(int n): n{n} {
    v.resize(4*n+10); 
  }
  void update(int node, int s, int e, int pos){
    if(pos<s||pos>e) return; 
    if(s==e){
      v[node].lmost = v[node].rmost = v[node].M = 1; 
      v[node].isfull = true; 
      return; 
    } 
    int m = s+e>>1; 
    if(pos<=m) update(2*node,s,m,pos); 
    else update(2*node+1,m+1,e,pos); 
    v[node] = merge(v[2*node],v[2*node+1]); 
  }
  fuck query(int node, int s, int e, int l, int r){
    int m = s+e>>1; 
    if(e<l||s>r) return fuck(); 
    if(l<=s && e<=r) return v[node]; 
    if(r<=m) return query(2*node,s,m,l,r); 
    if(l>=m+1) return query(2*node+1,m+1,e,l,r); 
    return merge(query(2*node,s,m,l,r),query(2*node+1,m+1,e,l,r)); 
  }
};

const int MAXN = 100100; 
int h[MAXN]; 
int L[MAXN], R[MAXN], ans[MAXN]; 
vector<int> add[MAXN]; 

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr); 
  cout.tie(nullptr);
  vector<int> tmp; 
  int n; cin >> n; 
  rrep(i,n){
    cin >> h[i]; tmp.push_back(h[i]); 
  }
  sort(tmp.begin(),tmp.end()); 
  tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end()); 
  rrep(i,n){
    h[i] = lower_bound(tmp.begin(),tmp.end(),h[i]) - tmp.begin(); 
    add[h[i]].push_back(i); 
  }
  int q; cin >> q; 
  vector<array<int,3>> query(q); 
  rep(i,q) rep(j,3) cin >> query[i][j]; 
  int sz = tmp.size(); 
  //rep(i,sz) cerr << tmp[i] << endl; 
  rep(i,q) L[i] = 0, R[i] = sz-1; 
  while(1){
    bool flag = false; 
    vector<int> chk[MAXN]; 
    seg S(n+1);
    rep(i,q){
      if(L[i]<=R[i]){
        flag = true; 
        int m = L[i]+R[i]>>1; 
        chk[m].push_back(i);
      }
    }
    if(!flag) break; 
    for(int i=sz-1; i>=0; i--){
      for(auto ne : add[i]) S.update(1,1,n,ne);
      //cerr << i << endl;
      for(auto id : chk[i]){
        auto& [l,r,w] = query[id]; 
        //cerr << l << " " << r << " " << w << "seg query start fuckkkk " << endl;
        int x = S.query(1,1,n,l,r).M; 
        //cerr << l << " " << r << " " << i << " " << x << endl;
        if(x>=w){
          ans[id] = max(ans[id],i);
          L[id] = i+1;
        }
        else {
          R[id] = i-1; 
        }
      }
    }
  }
  rep(i,q) cout << tmp[ans[i]] << "\n"; 
  return 0; 
}