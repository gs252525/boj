#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll, ll> pii;
#define ff first
#define ss second
#define pb push_back

ll n, m;

vector<ll> v[1010101];
vector<pii> vs;
ll arr[1010101];
ll chk[1010101];

bool sf(ll a, ll b) { return a > b; }

int main() {
  cin >> n >> m;
  for (ll i = 1; i <= n; i++)
    cin >> arr[i];
  sort(arr + 1, arr + 1 + n, sf);
  ll pos = 0;

  for (ll i = 1; i <= n; i++) {
    if (i * arr[i] > m)
      pos = i;
  }

  if (pos) {
    cout << "Bernardo" << endl;
    ll x = arr[pos];
    for (ll i = 1; i <= n; i++) {
      ll a, b;
      cin >> a >> b;
      swap(a, b);
      b = (b + a - 1);
      if (b / x != a / x) {
        cout << (ll)(b / x) * x << endl;
      } else
        cout << a << endl;
    }
  } else {
    cout << "Alessia" << endl;
    for (ll i = 1; i <= n; i++) {
      for (ll j = 1; j <= m; j++) {
        ll fl = 0;
        for (ll k = j; k < j + arr[i]; k++) {
          if (chk[k]) {
            fl = 1;
            j = k;
            break;
          }
        }
        if (fl == 0) {
          cout << arr[i] << ' ' << j << endl;
          break;
        }
      }
      ll x;
      cin >> x;
      chk[x] = 1;
    }
  }
}