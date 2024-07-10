#include <bits/stdc++.h>
 
#define rrep(i,n) for(int i=1; i<=n; i++)
#define rep(i,n) for(int i=0; i<n; i++) 
 
using namespace std; 
 
char board[2000][2000]; 
 
char s[2000]; 
int chk[2000][2000] ;
bool vis[2000][2000]; 
char tmp[2000]; 
 
int r,c; 
 
int dfs(int i, int j){
	assert(chk[i][j]); 
	vis[i][j] = 1; 
	if(i==r-1) return 1; 
	int l = (j-1+c)%c, r = (j+1)%c; 
	int re = 0; 
	if(chk[i][l] && !vis[i][l]) re += dfs(i,l); 
	if(chk[i][r] && !vis[i][r]) re += dfs(i,r); 
	if(chk[i+1][j] && !vis[i+1][j]) re += dfs(i+1,j); 
	if(i>=1 && chk[i-1][j] && !vis[i-1][j]) re += dfs(i-1,j); 
	if(re==0) return 0; 
	else return 1; 
}	
 
int test(void){
	rep(i,r) rep(j,c){
		// s[i] 를 j 번 rotate 
		bool flag = true; 
		for(int k=0; k<c; k++){
			if(board[i][k]=='1' && s[k+j]=='1') flag = false;
		} 
		if(flag) chk[i][j] = 1; 
	} 
	rep(i,r) rep(j,c) cout << chk[i][j] << " \n"[j==c-1]; 
	rep(i,c) {
		if(!vis[0][i] && chk[0][i]) {
			int a = dfs(0,i); 
			if(a!=0) {
				return 1; 
			}
		}
	}
	return 0; 
}
 
 
 
int main(void){
	cin >> r >> c; 
	rep(i,c){
		cin >> s[i]; s[i+c] = s[i]; tmp[i] = s[i]; 
	}  
  rep(i,r) rep(j,c) cin >> board[i][j]; 
  int a = test(); 
	rep(i,c){
		s[i] = tmp[c-1-i]; 
    cout << i << " " << s[i] << "\n";
		s[i+c] = s[i]; 
	}
	
	
	int b = test(); 
	if(a||b) cout << "Y"; 
	else cout << "N"; 
}