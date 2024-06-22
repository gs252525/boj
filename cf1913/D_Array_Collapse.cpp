#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/stdc++.h>
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
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V> void __print(const pair<T, V> &x) {
  cerr << '{';
  __print(x.first);
  cerr << ", ";
  __print(x.second);
  cerr << '}';
}
template <typename T> void __print(const T &x) {
  int f = 0;
  cerr << '{';
  for (auto &i : x)
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
#define dbg(x...)                                                              \
  cerr << "\e[91m" << __func__ << ":" << __LINE__ << " [" << #x << "] = [";    \
  _print(x);                                                                   \
  cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif


 
template<typename T>
class SegmentTree {
private:
    vector<T> tree;
    int n;

    // Function to merge two nodes
    T merge(T a, T b) {
        return a + b;
    }

    // Build the tree recursively
    void build(const vector<T>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(arr, v*2, tl, tm);
            build(arr, v*2+1, tm+1, tr);
            tree[v] = merge(tree[v*2], tree[v*2+1]);
        }
    }

    // Query the sum in the range [l, r]
    T sum(int v, int tl, int tr, int l, int r) {
        if (l > r) 
            return 0;
        if (l == tl && r == tr) 
            return tree[v];
        int tm = (tl + tr) / 2;
        return merge(sum(v*2, tl, tm, l, min(r, tm)), 
                     sum(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    SegmentTree(const vector<T>& arr) {
        n = arr.size();
        tree.assign(n * 4, 0);
        build(arr, 1, 0, n - 1);
    }

    // Query the sum in the range [l, r]
    T query(int l, int r) {
        return sum(1, 0, n-1, l, r);
    }
};

template<typename T>
class SegmentTree {
private:
    vector<T> tree;
    int n;

    T merge(T a, T b) {
        return a + b;
    }

    void build(const vector<T>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(arr, v*2, tl, tm);
            build(arr, v*2+1, tm+1, tr);
            tree[v] = merge(tree[v*2], tree[v*2+1]);
        }
    }

    T sum(int v, int tl, int tr, int l, int r) {
        if (l > r) 
            return 0;
        if (l <= tl && tr <= r) // Check if the current segment is fully within the query range
            return tree[v];
        int tm = (tl + tr) / 2;
        return merge(sum(v*2, tl, tm, l, min(r, tm)), 
                     sum(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    SegmentTree(const vector<T>& arr) {
        n = arr.size();
        tree.assign(n * 4, 0);
        build(arr, 1, 0, n - 1);
    }

    T query(int l, int r) {
        return sum(1, 0, n-1, l, r);
    }
};



struct SegmentTree {
    int n;
    vector<int> tree;
    vector<int> array;

    // 초기화
    SegmentTree(const vector<int>& array) {
        n = array.size();
        this->array = array;
        tree.resize(n * 4);
        init(0, n - 1, 1);
    }

    // 세그먼트 트리 구성
    int init(int left, int right, int node) {
        if (left == right) return tree[node] = left;
        int mid = (left + right) / 2;
        int leftIndex = init(left, mid, node * 2);
        int rightIndex = init(mid + 1, right, node * 2 + 1);
        return tree[node] = (array[leftIndex] <= array[rightIndex]) ? leftIndex : rightIndex;
    }

    // 구간 최소값의 인덱스 쿼리
    int query(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (right < nodeLeft || nodeRight < left) return -1;
        if (left <= nodeLeft && nodeRight <= right) return tree[node];
        int mid = (nodeLeft + nodeRight) / 2;
        int leftIndex = query(left, right, node * 2, nodeLeft, mid);
        int rightIndex = query(left, right, node * 2 + 1, mid + 1, nodeRight);
        if (leftIndex == -1) return rightIndex;
        if (rightIndex == -1) return leftIndex;
        return (array[leftIndex] <= array[rightIndex]) ? leftIndex : rightIndex;
    }

    // 외부에서 호출할 수 있는 쿼리 함수
    int query(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }
};

ll mod = 998244353; 
ll modmul(ll a, ll b) {
  a %= mod; b%=mod; 
  return (a*b)%mod; 
}

ll modadd(ll a, ll b){
  return (a+b)%mod; 
}

int n; 

ll f(int l, int r, SegmentTree& RMQ, int lc, int rc){
  if(l>r) return 1; 
  if(l==r) 1+(lc||rc); 
  int m = RMQ.query(l,r); 
  ll v1 = f(l,m-1, RMQ, lc,1), v2 = f(m+1,r,RMQ,1,rc); 
  ll ans = modmul(v1,v2); 
  if(lc) ans = modadd(ans,v2); 
  if(rc) ans = modadd(ans,v1); 
  if(lc&&rc) ans = modadd(ans,mod-1); 
  return ans; 
}


void solve(){
  cin >> n; 
  vector<int> a(n); 
  for(auto &ai : a) cin >> ai; 
  SegmentTree RMQ(a); 
  cout << f(0,n-1,RMQ,0,0) << "\n"; 
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  cin >> t;
  while(t--) solve(); 
  return 0;
}
