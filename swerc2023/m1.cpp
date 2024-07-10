#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pii;
#define ff first
#define ss second
#define pb push_back

ll n, m;

vector<ll> v[1010101];
vector<ll> chd[1010101];
ll sz[1010101];

void dfs(ll x){
  sz[x]=1;
  for(auto k:v[x]){
    if(sz[k]) continue;
    chd[x].pb(k);
    dfs(k);
    sz[x]+=sz[k];
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin>>n;
  for(ll i=1;i<n;i++){
    ll a,b;
    cin>>a>>b;
    v[a].pb(b);
    v[b].pb(a);
  }
  dfs(1);

  if(n%2==0){
    cout<<n<<'\n';
    return 0;
  }
  for(ll i=n;i>=1;i--){
    //cout<<i<<'\n';
    for(auto k:chd[i]){
      if(sz[k]%2==0){
        cout<<i;
        return 0;
      }
    }
    if((n-sz[i])%2==0){
      cout<<i;
      return 0;
    }
  }

}