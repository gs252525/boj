#include <bits/stdc++.h>

using namespace std;  

int n,m; 

int board[1600][1600]; 
int l[1600][1600]; 
int r[1600][1600];
int pb[1600][1600]; 
int pl[1600][1600]; 
int pr[1600][1600]; 

void cw(int x, int y, int xx, int yy, bool flag){
  //cerr << x << " " << y << " " << xx << " " << yy << " " << flag << endl; 
  if(flag) l[xx][yy] = 1; 
  else r[xx][yy] = 1; 
  if(flag && xx==n && yy==m) return; 
  if(!flag && xx==1 && yy==1) return; 
  if(yy==y+1){
    if(board[xx+1][yy]) return cw(xx+1,yy,xx,yy,flag); 
    if(board[x+1][y]) return cw(x+1,y,xx+1,yy,flag); 
    if(flag) l[x+1][y+1] = 1; 
    else r[x+1][y+1] = 1;
    return cw(x,y,x+1,y,flag); 
  }
  if(x==xx+1){
    if(board[xx][yy+1]) return cw(xx,yy+1,xx,yy,flag); 
    if(board[x][y+1]) return cw(x,y+1,xx,yy+1,flag); 
    if(flag) l[x-1][y+1] = 1; 
    else r[x-1][y+1] = 1;
    return cw(x,y,x,y+1,flag); 
  }
  if(y==yy+1){
    if(board[xx-1][yy]) return cw(xx-1,yy,xx,yy,flag); 
    if(board[x-1][y]) return cw(x-1,y,xx-1,yy,flag); 
    if(flag) l[x-1][y-1] = 1; 
    else r[x-1][y-1] = 1;
    return cw(x,y,x-1,y,flag);
  }
  if(xx==x+1){
    if(board[xx][yy-1]) return cw(xx,yy-1,xx,yy,flag); 
    if(board[x][y-1]) return cw(x,y-1,xx,y-1,flag); 
    if(flag) l[x+1][y-1] = 1; 
    else r[x+1][y-1] = 1;
    return cw(x,y,x,y-1,flag); 
  }
}

int main(void){
  ios_base::sync_with_stdio(false); 
  cin.tie(nullptr); cout.tie(nullptr);
  cin >> m >> n; 
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++) {
      char c; cin >> c; if(c=='#') board[i][j] = 1; 
    }
  }
  for(int i=0; i<=n+1; i++) board[i][0] = board[i][m+1] = 1; 
  for(int i=0; i<=m+1;i++) board[0][i] = board[n+1][i] = 1;
  cw(1,0,1,1,1);
  cw(n,m+1,n,m,0);
  board[1][1] = 1, board[n][m] = 1; 
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      pb[i][j] = pb[i-1][j] + pb[i][j-1] - pb[i-1][j-1] + board[i][j]; 
      pl[i][j] = pl[i-1][j] + pl[i][j-1] - pl[i-1][j-1] + l[i][j]; 
      pr[i][j] = pr[i-1][j] + pr[i][j-1] - pr[i-1][j-1] + r[i][j]; 
      //cerr << i << " " << j  << " pb fuckkk " << pb[i][j] << endl;
    }
  }
  int x,y,d=1000000;
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      if(board[i][j]) continue;
      int l = 1, r = min(n-i+1,m-j+1); int dM=1; 
      while(l<=r){
        int mid = l+r>>1;
        int k = pb[i+mid-1][j+mid-1] - pb[i-1][j+mid-1] - pb[i+mid-1][j-1] + pb[i-1][j-1]; 
        assert(k>=0); 
        if(k==0) dM = max(dM,mid), l=mid+1; 
        else r=mid-1; 
      }
      int fd = 1000000; 
      l = 1, r = dM; 
      while(l<=r){
        int mid = l+r>>1;
        int k = pl[i+mid-1][j+mid-1] - pl[i-1][j+mid-1] - pl[i+mid-1][j-1] + pl[i-1][j-1]; 
        int kk = pr[i+mid-1][j+mid-1] - pr[i-1][j+mid-1] - pr[i+mid-1][j-1] + pr[i-1][j-1]; 
        //if(i==3 && j==6) cerr << mid << " " << k << " " << kk << endl;
        if(k >=1 && kk>=1) fd = min(fd,mid), r=mid-1; 
        else l = mid+1; 
      }
      if(fd!=1000000 && fd<d){
        x = i, y = j, d = fd; 
      }
    }
  }
  if(d!=1000000) cout << d << " " << y << " " << x; 
  else cout << "Impossible";
}