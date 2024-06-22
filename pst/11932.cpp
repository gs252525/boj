#include <bits/stdc++.h>
#include <array>
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define rep(i, n) for (int i = 0; i < n; ++i)
#define rrep(i, n) for (int i = 1; i <= n; ++i)
#define ff first
#define ss second
using namespace std;
typedef long long ll;

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char* x) { cerr << '\"' << x << '\"'; }
void __print(const string& x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V> void __print(const pair<T, V>& x) {
    cerr << '{';
    __print(x.first);
    cerr << ", ";
    __print(x.second);
    cerr << '}';
}
template <typename T> void __print(const T& x) {
    int f = 0;
    cerr << '{';
    for (auto& i : x)
        cerr << (f++ ? ", " : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V> void _print(T t, V... v) {
    __print(t);
    if (sizeof...(v))
        cerr << ", ";
    _print(v...);
}

#ifdef LOCAL
#define dbg(...)                                                               \
  cerr << "\e[91m" << __func__ << ":" << __LINE__ << " [" << #__VA_ARGS__      \
       << "] = [";                                                             \
  _print(__VA_ARGS__);                                                         \
  cerr << "\e[39m" << endl;
#else
#define dbg(...)
#endif

#define int ll

const int MAXN = 800000;

struct fuck {
    int s, e, len;
    fuck(int s, int e, int len) : s(s), e(e), len(len) {}
    fuck() {
        s = 0; e = 0; len = 0;
    }
    fuck operator =(const fuck& o) {
        s = o.s; e = o.e; len = o.len;
        return *this;
    }
};

fuck seg[MAXN];
fuck lz[MAXN];

int n, m;
bool flag = false;


void pro(int node, int s, int e) {
    if (lz[node].len == 0) return; 
    seg[node] = lz[node];
    if (s != e) {
        int m = s + e >> 1;
        lz[2 * node] = lz[node];
        lz[2 * node + 1] = lz[node];
    }
    lz[node] = fuck();
    return;
}

void update(int node, int s, int e, int l, int r, fuck val) {
    if (l == 1 && r == 1) {
        e = e;
    }
    // l~r += val
    if (l > r)
        return;
    
    if (r < s || l > e)
        return;
    pro(node, s, e);
    int m = s + e >> 1;
    if (l <= s && e <= r) {
        lz[node] = val;
        return;
    }
    update(2 * node, s, m, l, r, val);
    update(2 * node + 1, m + 1, e, l, r, val);
}

int tmp;
set<array<int, 3>> s;

void update(int l, int r) {
    int len;
    if (r >= l) len = r - l + 1;
    else len = n + r - l + 1;
    s.insert({ l,r,len });
    tmp += len / 2;
    fuck val(l, r, len);
    if (l <= r) update(1, 0, n - 1, l, r, val);
    else {
        update(1, 0, n - 1, 0, r, val);
        update(1, 0, n - 1, l, n - 1, val);
    }
}

fuck query(int node, int s, int e, int pos) {
    pro(node, s, e);
    if (s == e) return seg[node];
    int m = s + e >> 1;
    if (pos <= m) return query(2 * node, s, m, pos);
    else return query(2 * node + 1, m + 1, e, pos);
}

int a[MAXN];
int cnt[MAXN];

vector<int> v[MAXN];
int b[MAXN];

void solve() {
    cin >> n >> m;
    rep(i, n) {
        cin >> a[i];
        v[a[i]].pb(i);
    }
    rep(i, n) {
        b[i] = 1;
    }
    rep(i, n) {
        update(1, 0, n - 1, i, i, fuck(i, i, 1));
    }
    dbg(seg[8].len, lz[8].len);
    rrep(i, m) {
        if (v[i].empty()) {
            cout << -1 << " "; continue;
        }
        vector<int>& cur = v[i];
        //dbg(s); 
        for (int x : cur) {
            fuck er = query(1, 0, n - 1, x);
            b[x] = 0;
            int s = er.s, e = er.e, len = er.len;
            tmp -= len / 2;
            if (flag) {
              update((x + 1) % n, (x - 1 + n) % n); flag = false;
            }
            else {
                if (s != x) update(s, (x - 1 + n) % n);
                if (e != x) update((x + 1) % n, e);
            }
        }
        //dbg(s); 
        cout << n - cur.size() + tmp << " ";
        for (int x : cur) {
            // 0 -> -1 
            b[x] = -1;
            int r = x, l = x;
            if (b[(x + 1) % n] == 1) {
                fuck er = query(1, 0, n - 1, (x + 1) % n);
                r = er.e;
                tmp -= er.len / 2;
                //s.erase({er.s,er.e,er.len}); 
                if (r == (x - 1 + n) % n) {
                    flag = true;
                    tmp = 0;
                    //tmp = n/2; 
                    update(0, n - 1);
                    break; 
                }
            }
            if (b[(x - 1 + n) % n] == 1) {
                fuck er = query(1, 0, n - 1, (x - 1 + n) % n);
                l = er.s;
                tmp -= er.len / 2;
            }
            update(l, r);
        }
        //dbg(s);
    }

};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}
