#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = (a); i < (b); i++)
#define iter(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end();++it)
typedef long long ll;
typedef pair<ll,ll> ii;
typedef pair<ll,ii> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int INF = ~(1<<31);
const double pi = acos(-1);

struct union_find {
    vi p;
    union_find(ll n) : p(n) {
        rep(i,0,n) p[i] = i;
    }
    ll find(ll a) { 
        return p[a] == a ? a : p[a] = find(p[a]); 
    }
    void unite(ll a, ll b) {
        p[find(a)] = find(b);
    }
    bool joined(ll a, ll b) {
        return find(a) == find(b);
    }
};

ll manhattan(ii a, ii b) {
    return abs(a.first-b.first)+abs(a.second-b.second);
}

ll mst(ll n, vector<iii> edg) {
    union_find u(n);
    ll cost = 0;
    rep(i,0,edg.size()) {
        ll a = edg[i].second.first;
        ll b = edg[i].second.second;
        ll dist = edg[i].first;
        if(!u.joined(a,b)) {
            u.unite(a,b);
            cost += dist;
        }
    }
    return cost;
}

int main() {
    cin.sync_with_stdio(false);
    ll n;
    cin >> n;
    vii k;
    rep(i,0,n) {
        ll a,b;
        cin >> a >> b;
        k.push_back(ii(a,b));
    }
    vector<iii> edg;
    rep(i,0,n) {
        rep(a,i+1,n) {
            ll mandist = manhattan(k[i], k[a]);
            edg.push_back(iii(mandist, ii(i,a)));
        }
    }
    sort(edg.begin(), edg.end());
    ll totalweight = mst(n, edg);
    cout << totalweight << endl;
    return 0;
}
