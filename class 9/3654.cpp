#include <bits/stdc++.h>
#define rep(i,n) for(int i=0; i<n; i++)
#define rrep(i,n) for(int i=1; i<=n; i++) 
#define pb push_back 

using namespace std; 

const int MAXN = 1101000;
vector<int> adj[MAXN];
vector<int> readj[MAXN]; 

int vis[MAXN]; 
stack<int> st; 

void dfs(int x){
  if(vis[x]) return; 
  vis[x] = 1; 
  for(auto ne : adj[x]){
    if(vis[ne]) continue; 
    dfs(ne); 
  } 
  st.push(x); 
}

int pv; 
int scc[MAXN]; 
void dfs1(int x){
  if(vis[x]) return; 
  vis[x] = 1; 
  scc[x] = pv;
  for(auto ne : readj[x]){
    if(!vis[ne]) dfs1(ne); 
  }
}

char board[600][600]; 

int n,m; 

inline int getx(int i, int j){
  if(i==0||j==0||i==n||j==m) return 0; 
  return m*i+j; 
}
inline int gety(int i, int j){
  if(i==0||j==0||i==n||j==m) return 0; 
  return m*n+m*i+j; 
}
inline int rev(int x){
  if(x==0) return 0; 
  return 2*m*n+x; 
}

void addEdge(int i, int j){
  if(i==0 || j==0) return; 
  adj[i].pb(j); 
  readj[j].pb(i); 
}


void solve(){
  cin >> n >> m; 
  rrep(i,n) rrep(j,m) cin >> board[i][j]; 
  int B=0,W=0; 
  rrep(i,n){
    rrep(j,m){
      if(board[i][j]=='B') B++; 
      if(board[i][j]=='W') W++; 
    }
  }
  rrep(j,m) board[n+1][j] = '.'; 
  rrep(i,n) board[i][m+1] = '.';
  m++,n++; 
  //cerr << B << " " << W << endl; 
  if(W!=2*B) {
    cout << "NO\n"; return; 
  }
  if(B==0){
    cout << "YES\n"; return; 
  }
  if(n==2 || m == 2){
    cout << "NO\n"; return;  
  }
  rep(i,4*m*n+m+3) adj[i].clear(),readj[i].clear(),scc[i]=0, vis[i] = 0; 
  pv = 0; 
  rrep(i,n-1){
    rrep(j,m-1){
      if(board[i][j]=='B'){
        bool l = board[i][j-1]=='W', r = board[i][j+1]=='W', u = board[i-1][j]=='W', d = board[i+1][j]=='W'; 
        if(l==false && r==false){
          cout << "NO\n"; return; 
        }
        if(r==false){
          //adj[m*(i)+j-1].pb(2*m*n + m*(i)+j-1); 
          int k = getx(i,j-1); 
          addEdge(rev(k),k); 
        }
        else if(l==false){
          int k = getx(i,j); 
          addEdge(rev(k),k); 
        }
        else {
          int a=getx(i,j-1),b=getx(i,j); 
          int ra = rev(a), rb=rev(b); 
          addEdge(a,rb); addEdge(rb,a); 
          addEdge(ra,b); addEdge(b,ra); 
        }
        if(d==false && u==false) {
          cout << "NO\n"; return;
        }
        if(u==false){
          int k = gety(i,j); 
          addEdge(rev(k),k); 
        }
        else if(d==false){
          int k = gety(i-1,j); 
          addEdge(rev(k),k); 
        }
        else {
          int a = gety(i-1,j), b = gety(i,j); 
          int rb = rev(b); int ra = rev(a); 
          addEdge(a,rb); addEdge(rb,a); 
          addEdge(b,ra); addEdge(ra,b); 
        }
      }
      if(board[i][j]=='W'){
        int a = getx(i,j), b = getx(i,j-1), c = gety(i,j), d = gety(i-1,j);
        if(board[i][j+1]!='B') a = 0; 
        if(board[i][j-1]!='B') b = 0; 
        if(board[i-1][j]!='B') d = 0; 
        if(board[i+1][j]!='B') c = 0;  
        int ra = rev(a), rb = rev(b), rc = rev(c), rd = rev(d); 
        addEdge(a,rb); addEdge(a,rc); addEdge(a,rd); 
        addEdge(b,ra); addEdge(b,rc); addEdge(b,rd); 
        addEdge(c,ra); addEdge(c,rb); addEdge(c,rd); 
        addEdge(d,ra); addEdge(d,rb); addEdge(d,rc); 
      }
    }
  }
  rep(i,4*m*n+m+3) if(!vis[i] && !adj[i].empty()) dfs(i); 
  rep(i,4*m*n+m+3) vis[i] = 0; 
  pv = 1; 
  while(!st.empty()){
    int t = st.top(); st.pop(); if(!vis[t]){
        dfs1(t); pv++; 
    } 
  }
  for(int i=m+1; i<=2*m*n+m; i++) {
    if(scc[i]!=0 && scc[i]==scc[rev(i)]) {
    cout << "NO\n"; return; 
    }
  }
  cout << "YES\n"; 
}

int main(void){
  ios::sync_with_stdio(false); 
  cin.tie(nullptr); 
  cout.tie(nullptr); 
  int t; cin >> t; 
  while(t--){
    solve(); 
  }
}