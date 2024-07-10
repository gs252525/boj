#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll x[1010];
ll y[1010];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int n;cin>>n;
  for(int i=1;i<=n;i++)
    cin>>x[i]>>y[i];
  set<int> II;
  for(int i=1;i<=n;i++)II.insert(i);
  if(n%2){
    cout<<"Beatrice"<<endl;
    int i;cin>>i;
    II.erase(i);
  }
  else{
    cout<<"Alberto"<<endl;
  }
  while(II.size()>2){
    vector<int> I;
    for(int i:II)I.push_back(i);
    int m=I.size(); I.push_back(I[0]); I.push_back(I[1]);
    ll ri=0, rs=0x7070707070707070ll;
    for(int j=1;j<=m;j++){
      ll xi=x[I[j-1]];
      ll yi=y[I[j-1]];
      ll xj=x[I[j]];
      ll yj=y[I[j]];
      ll xk=x[I[j+1]];
      ll yk=y[I[j+1]];
      ll s=(xi-xj)*(yi-yk)-(yi-yj)*(xi-xk);
      s=abs(s);
      if(s<rs){
        ri=I[j];
        rs=s;
      }
    }
    cout<<ri<<endl;
    II.erase(ri);
    if(II.size()>2){
      int i;cin>>i;
      II.erase(i);
    }
  }
}