#include <bits/stdc++.h>
#include <array>

using namespace std;

string s;
const int MAXN = 1000100;
int z[MAXN];

void get_z() {
  z[0] = 0;
  int n = s.size();
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i <= r)
      z[i] = min(z[i - l], r - i + 1);
    while (i + z[i] < n && s[i + z[i]] == s[z[i]])
      z[i]++;
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
    //cerr << i << " " << z[i] << endl;
  }
}

int ans = MAXN;

void chk(int k){
  int d = (1<<k) + 1; 
  int n = s.size(); assert(n%d==0); 
  int L = n/d; 
  //cerr << k << " " << L << endl; 
  queue<array<int,3>> Q; 
  Q.push({0,L,0}); 
  set<pair<int,int>> S; 
  while(!Q.empty()){
    auto [a,b,dist] = Q.front(); Q.pop(); 
    if(S.find({a,b})!=S.end()) continue; 
    S.insert({a,b}); 
    if(a==L && b==n){
      ans = min(ans,dist); return; 
    }
    if(a>=L || b>=n) continue; 
    if(s[a]==s[b]) Q.push({a+1,b+1,dist+1}); 
    if(z[a]>=a && z[b]>=b) Q.push({2*a,2*b,dist+1}); 
  }
}

int main(void) {
  int n;
  cin >> n;
  cin >> s;
  assert(s.size()==n);
  get_z();
  //cerr << "fuck" << endl;   
  if(n%2==0 && z[n/2]==n/2) ans = n/2; 
  for(int i=1; i<=20; i++){
    int k = (1<<i)+1; 
    if(n%k==0) chk(i); 
  }
  if(ans==MAXN) cout << -1; 
  else cout << ans; 
}