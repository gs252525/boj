#include <bits/stdc++.h> 
#include <array>
#define pb push_back 

using namespace std; 

typedef long long ll; 

const int MAXN = 300100; 
ll tree[MAXN]; 

int n,m;  

void init(){
  fill(tree, tree+m+1, 0); 
}

void update(int pos, ll val){
  while(pos<=m) {
    tree[pos] += val; pos += pos&-pos; 
  }
}

ll query(int pos){
  ll re = 0; 
  while(pos){
    re += tree[pos]; pos -= pos&-pos; 
  }
  return re; 
}

ll pi[MAXN]; 
vector<int> oi[MAXN]; 

int L[MAXN], R[MAXN], ans[MAXN]; 

int32_t main(void){
  ios::sync_with_stdio(false); 
  cin.tie(nullptr); 
  cout.tie(nullptr);
  cin >> n >> m; 
  for(int i=1; i<=m; i++){
    int x; cin >> x; 
    oi[x].push_back(i); 
  }
  for(int i=1; i<=n; i++) cin >> pi[i]; 
  int Q; cin >> Q; 
  vector<array<int,3>> q(Q+1); 
  for(int i=1; i<=Q; i++) for(int j=0; j<3; j++) cin >> q[i][j]; 
  for(int i=1; i<=n; i++) L[i] = 1, R[i] = Q, ans[i] = Q+1; 
  while(1){
    bool flag = false; 
    init(); 
    vector<int> chk[MAXN]; 
    for(int i=1; i<=n; i++){
      if(L[i]<=R[i]){
        flag = true; 
        int m = L[i]+R[i]>>1; 
        chk[m].pb(i); 
      }
    }
    if(!flag) break; 
    for(int i=1; i<=Q; i++){
      auto& [l,r,a] = q[i]; 
      if(l<=r){
        update(l,a); update(r+1,-a); 
      }
      else {
        // l>r
        update(l,a); update(1,a); update(r+1,-a); 
      }
      for(auto &id : chk[i]){
        ll tmp = 0; 
        for(auto &o : oi[id]){
          tmp += query(o);
          if(tmp>=pi[id]) break; 
        }
        if(tmp>=pi[id]){
          ans[id] = min(ans[id],i); 
          R[id] = i-1; 
        }
        else {
          L[id] = i+1; 
        }
      }
    }
  }
  for(int i=1; i<=n; i++){
    if(ans[i]==Q+1) cout << "NIE\n"; 
    else cout << ans[i] << "\n"; 
  }
}

