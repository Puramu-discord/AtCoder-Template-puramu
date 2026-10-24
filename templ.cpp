#if !__INCLUDE_LEVEL__
#include __FILE__

// 生成AI対策ルール20261014版に基づくテンプレートの開示
// https://github.com/Puramu-discord/AtCoder-Template-puramu/tree/main

bool hasAny(const string &S, const string &D) {
    return S.find_first_of(D) != string::npos;
}

bool prime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
}

#else
#include <bits/stdc++.h>
#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif
using namespace std;
struct Init { Init() { ios::sync_with_stdio(0); cin.tie(0); cout << setprecision(13); } }init;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

#define rep(i, x, limit) for (ll i = (ll)x; i < (ll)limit; i++)
#define REP(i, x, limit) for (ll i = (ll)x; i <= (ll)limit; i++)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define el '\n'
#define spa " "
#define Yes cout << "Yes" << el
#define No cout << "No" << el
#define YES cout << "YES" << el
#define NO cout << "NO" << el
#define eps (1e-10)
#define Equals(a,b) (fabs((a) - (b)) < eps )
#define debug(x) cerr << #x << " = " << x << el

const double pi = 3.141592653589793238;
const int inf = 1073741823;
const ll infl = 1LL << 60;
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string abc = "abcdefghijklmnopqrstuvwxyz";

template<typename T1, typename T2>
std::ostream &operator<< (std::ostream &os, std::pair<T1,T2> p){
    os << "{" << p.first << "," << p.second << "}";
    return os;
}

// 配列の要素を空白区切りで出力 第二引数をtrueにすると改行区切り
template<typename T> inline void print_vec(const vector<T> &v, bool split_line=false) {
    if(v.empty()){
        cout << "This vector is empty." << el;
        return;
    }
    constexpr bool isValue = is_integral<T>::value;
    for (int i = 0; i < (int)v.size(); i++) {
        if constexpr(isValue){
            if((v[i]==inf) || (v[i]==infl)) cout << 'x' << " \n"[split_line || i+1==(int)v.size()];
            else cout << v[i] << " \n"[split_line || i+1==(int)v.size()];
        }else cout << v[i] << " \n"[split_line || i+1==(int)v.size()];
    }
}

template<typename T1, typename T2> inline void print_vec(const vector<pair<T1,T2>> &v, bool split_line=false){
    if(v.empty()){
        cout << "This vector is empty." << el;
        return;
    }
    for(int i = 0; i < (int)v.size(); i++){
        cout << '{';
        auto [a,b] = v[i];
        constexpr pair<bool,bool> isValue = {is_integral<T1>::value, is_integral<T2>::value};
        if constexpr(isValue.first){
            if(a==inf || a==infl) cout << "x,";
            else cout << a << ",";
        }else cout << a << ",";
        if constexpr(isValue.second){
            if(b==inf || b==infl) cout << "x,";
            else cout << b;
        }else cout << b;
        cout << "}" << " \n"[split_line || i+1==(int)v.size()];
    }
}

template<typename T1, typename T2> inline bool chmax(T1 &a, T2 b) {
    bool compare = a < b;
    if(compare) a = b;
    return compare;
}
template<typename T1, typename T2> inline bool chmin(T1 &a, T2 b) {
    bool compare = a > b;
    if(compare) a = b;
    return compare;
}

// std::chronoを利用した時間計測用クラス
class Timer{
    chrono::system_clock::time_point start;
    public:
        Timer() : start(chrono::system_clock::now()) {}

        double count(){
            chrono::duration<double> Time_ = chrono::system_clock::now() - start;
            return Time_.count();
        }

        bool is_under(double x){
            return (this -> count()) < x;
        }
};

// std::uniform_int_distributionを利用した一様乱数生成クラス
class Random_Gen{
    random_device seed_gen;
    mt19937 engine;
    uniform_int_distribution<int64_t> dist;
    public:
        // Constructor [l,r]で生成する値の範囲を指定
        Random_Gen() : engine(seed_gen()) {}
        Random_Gen(int64_t l, int64_t r) : engine(seed_gen()), dist(l,r) {}

        // 現在の生成する値の範囲をstd::pairで返す
        pair<int64_t,int64_t> get_range(){
            return make_pair(dist.min(),dist.max());
        }
        // 生成する値の範囲を[l,r]に変更する
        void set_range(int64_t l, int64_t r){
            uniform_int_distribution<int64_t>::param_type Param(l,r);
            dist.param(Param);
        }
        // [l,r]内の一様分布の整数を返す
        int64_t gen(){
            return dist(engine);
        }
        int64_t operator()(){ return gen(); }
};

// ================= ここから追加分 =================

// ---- グリッド ----
// 4方向 (右,下,左,上) と 8方向
const int dx4[4] = {0, 1, 0, -1};
const int dy4[4] = {1, 0, -1, 0};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy8[8] = {1, 1, 0, -1, -1, -1, 0, 1};
// (x,y) が H行W列の盤面内か
inline bool in_grid(ll x, ll y, ll H, ll W) { return 0 <= x && x < H && 0 <= y && y < W; }

// グリッドBFS: 壁を'#'として start から各マスへの最短距離 (到達不可は -1)
vector<vector<int>> grid_bfs(const vector<string> &g, int sx, int sy, char wall = '#') {
    int H = g.size(), W = g[0].size();
    vector<vector<int>> d(H, vector<int>(W, -1));
    queue<pii> q;
    d[sx][sy] = 0;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = x + dx4[k], ny = y + dy4[k];
            if (!in_grid(nx, ny, H, W) || g[nx][ny] == wall || d[nx][ny] != -1) continue;
            d[nx][ny] = d[x][y] + 1;
            q.push({nx, ny});
        }
    }
    return d;
}

// ---- mod ----
const ll MOD998 = 998244353;
const ll MOD107 = 1000000007;

ll mod_pow(ll a, ll n, ll m) {
    ll r = 1 % m;
    a %= m; if (a < 0) a += m;
    while (n > 0) {
        if (n & 1) r = r * a % m;
        a = a * a % m;
        n >>= 1;
    }
    return r;
}
// mが素数のときの逆元
ll mod_inv(ll a, ll m) { return mod_pow(a, m - 2, m); }

// 階乗テーブルによる nCk, nPk (mは素数, n <= N)
struct Comb {
    ll m;
    vector<ll> f, fi;
    Comb(int N, ll m = MOD998) : m(m), f(N + 1), fi(N + 1) {
        f[0] = 1;
        for (int i = 1; i <= N; i++) f[i] = f[i - 1] * i % m;
        fi[N] = mod_inv(f[N], m);
        for (int i = N; i > 0; i--) fi[i - 1] = fi[i] * i % m;
    }
    ll C(int n, int k) const {
        if (k < 0 || k > n || n < 0) return 0;
        return f[n] * fi[k] % m * fi[n - k] % m;
    }
    ll P(int n, int k) const {
        if (k < 0 || k > n || n < 0) return 0;
        return f[n] * fi[n - k] % m;
    }
};

// ---- 整数論 ----
// エラトステネスの篩: is[i] が素数かどうか (0..N)
vector<bool> sieve(int N) {
    vector<bool> is(N + 1, true);
    is[0] = false;
    if (N >= 1) is[1] = false;
    for (ll i = 2; i * i <= N; i++)
        if (is[i]) for (ll j = i * i; j <= N; j += i) is[j] = false;
    return is;
}
// 約数列挙 (昇順)
vector<ll> divisors(ll n) {
    vector<ll> lo, hi;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            lo.push_back(i);
            if (i != n / i) hi.push_back(n / i);
        }
    }
    reverse(all(hi));
    lo.insert(lo.end(), all(hi));
    return lo;
}
// 素因数分解 {素因数, 指数} (昇順)
vector<pll> factorize(ll n) {
    vector<pll> r;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p) continue;
        ll c = 0;
        while (n % p == 0) { n /= p; c++; }
        r.push_back({p, c});
    }
    if (n > 1) r.push_back({n, 1});
    return r;
}

// ---- 累積和 ----
// 1次元: S[i] = a[0]+...+a[i-1]。区間 [l,r) の和は S[r]-S[l]
template<typename T> vector<T> prefix_sum(const vector<T> &a) {
    vector<T> S(a.size() + 1, 0);
    for (size_t i = 0; i < a.size(); i++) S[i + 1] = S[i] + a[i];
    return S;
}
// 2次元: 長方形 [x1,x2) x [y1,y2) の和は rect_sum で取得
template<typename T> struct Sum2D {
    vector<vector<T>> S;
    Sum2D(const vector<vector<T>> &a) {
        int H = a.size(), W = a[0].size();
        S.assign(H + 1, vector<T>(W + 1, 0));
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                S[i + 1][j + 1] = S[i][j + 1] + S[i + 1][j] - S[i][j] + a[i][j];
    }
    T rect_sum(int x1, int y1, int x2, int y2) const {
        return S[x2][y2] - S[x1][y2] - S[x2][y1] + S[x1][y1];
    }
};

// ---- 座標圧縮 ----
// 値を昇順の重複なし列に直し、各要素を0始まりの順位に置き換える。元の列は変更しない
template<typename T> vector<T> compress(vector<T> &a) {
    vector<T> u = a;
    sort(all(u));
    u.erase(unique(all(u)), u.end());
    for (auto &x : a) x = lower_bound(all(u), x) - u.begin();
    return u; // u[圧縮後の値] で元の値に戻せる
}

// ---- 二分探索 ----
// ok(x) が true になる最小の x を [lo, hi] から探す (単調: falseの後にtrue)。
// 見つからなければ hi+1 を返す
template<typename F> ll bin_search_min(ll lo, ll hi, F ok) {
    ll l = lo - 1, r = hi + 1; // l: false側, r: true側
    while (r - l > 1) {
        ll m = l + (r - l) / 2;
        if (ok(m)) r = m; else l = m;
    }
    return r;
}

// ---- ダイクストラ ----
// 隣接リスト g[v] = {(行き先, 重み)}。到達不可は infl
vector<ll> dijkstra(const vector<vector<pair<int,ll>>> &g, int s) {
    vector<ll> d(g.size(), infl);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    d[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [dv, v] = pq.top(); pq.pop();
        if (dv > d[v]) continue;
        for (auto [to, w] : g[v]) {
            if (d[to] > dv + w) {
                d[to] = dv + w;
                pq.push({d[to], to});
            }
        }
    }
    return d;
}

// ---- ソート ----
// 昇順・降順にソート (vector を書き換える)
template<typename T> void sort_asc(vector<T> &v) { sort(all(v)); }
template<typename T> void sort_desc(vector<T> &v) { sort(rall(v)); }

// key(要素) の昇順でソート。同じキーの要素は元の順序を保つ (安定)
// 例) pairを second の昇順に: sort_by_key(v, [](const pii &p){ return p.second; });
//     降順にしたいときは key の値に - を付ける: return -p.second;
template<typename T, typename F> void sort_by_key(vector<T> &v, F key) {
    stable_sort(all(v), [&](const T &a, const T &b) { return key(a) < key(b); });
}

// 値でソートしたときの添字の並びを返す (v 自体は変更しない)。同値は添字の小さい順
// 例) v = {30,10,20} → {1,2,0}   (v[1] < v[2] < v[0])
template<typename T> vector<int> argsort(const vector<T> &v, bool desc = false) {
    vector<int> id(v.size());
    iota(all(id), 0);
    stable_sort(all(id), [&](int a, int b) { return desc ? v[a] > v[b] : v[a] < v[b]; });
    return id;
}

// 転倒数: i<j かつ v[i]>v[j] となる組の数 (マージソート, O(n log n))。vは変更しない
template<typename T> ll inversion_count_rec(vector<T> &a, vector<T> &tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int m = (l + r) / 2;
    ll cnt = inversion_count_rec(a, tmp, l, m) + inversion_count_rec(a, tmp, m, r);
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else { tmp[k++] = a[j++]; cnt += m - i; }
    }
    while (i < m) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (int x = l; x < r; x++) a[x] = tmp[x];
    return cnt;
}
template<typename T> ll inversion_count(vector<T> v) {
    vector<T> tmp(v.size());
    return inversion_count_rec(v, tmp, 0, (int)v.size());
}

#endif
