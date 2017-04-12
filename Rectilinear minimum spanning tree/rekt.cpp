#include <bits/stdc++.h>
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (decltype(a) i=(a); i<(b); ++i)
#define iter(it,c) for (decltype((c).begin()) \
  it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
typedef pair<int, pair<ll,ll> > point;
const int INF = ~(1<<31);

const double EPS = 1e-9;
const double pi = acos(-1);
typedef unsigned long long ull;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }

#define MAXN 1000000

struct union_find {
  vi p; union_find(int n) : p(n, -1) { }
  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  bool unite(int x, int y) {
    int xp = find(x), yp = find(y);
    if (xp == yp) return false;
    if (p[xp] > p[yp]) swap(xp,yp);
    p[xp] += p[yp], p[yp] = xp;
    return true; }
  int size(int x) { return -p[find(x)]; } };

ll diag(point a)
{
    return a.second.first + a.second.second;
}

ll diag2(point a)
{
    return a.second.first - a.second.second;
}

ll dist(point a, point b)
{
    return abs(a.second.first-b.second.first) + abs(a.second.second-b.second.second);
}

bool cmp(point a, point b)
{
    return a.second.second == b.second.second ? a.second.first > b.second.first : a.second.second < b.second.second;
}

point best[MAXN];
point arr[MAXN], tmp[MAXN];

void rek(int l, int r)
{
    if(l >= r) return; // base case
    int m = (l+r)/2;
    rek(l,m);
    rek(m+1,r);
    point bst;
    bst.first = -1;
    for(int i = l, j = m+1, k = l; i <= m || j <= r; k++)
    {
        if(j > r || i <= m && diag(arr[i]) < diag(arr[j]))
        {
            tmp[k] = arr[i++];
            if(bst.first != -1 && (best[tmp[k].first].first == -1 
                        || diag2(best[tmp[k].first]) < diag2(bst)))
                best[tmp[k].first] = bst;
        }
        else
        {
            tmp[k] = arr[j++];
            if(bst.first == -1 || diag2(bst) < diag2(tmp[k])) bst = tmp[k];
        }
    }
    rep(i,l,r+1)
    {
        arr[i] = tmp[i];
    }
}

int main()
{
    int n;
    cin >> n;
 
    rep(i,0,n)
    {
        arr[i].first = i;
        cin >> arr[i].second.first >> arr[i].second.second;
    }

    vector<pair<ll, ii> > es;
    rep(p,0,2)
    {
        rep(q,0,2)
        {
            sort(arr, arr+n, cmp);
            //cout << "new rotation" << endl;
            rep(i,0,n)
            {
                best[i].first = -1;
                //cout << arr[i].first << " " << arr[i].second.first << " " << arr[i].second.second << endl;    
            }
            rek(0,n-1);
            //cout << "the best array" << endl;
            rep(i,0,n)
            {
                //cout << i << " " << arr[i].first << " " << best[arr[i].first].first << endl;
                if(best[arr[i].first].first != -1)
                    es.push_back(make_pair(dist(arr[i], best[arr[i].first]),
                                make_pair(arr[i].first, best[arr[i].first].first)));
                swap(arr[i].second.first, arr[i].second.second);
                arr[i].second.first *= -1;
                arr[i].second.second *= -1;
            }
        }
        rep(i,0,n)
        {
            arr[i].second.first *= -1;
        }
    }

    sort(es.begin(), es.end());
    union_find uf(n);
    ll res = 0;
    vector<pair<ll, ii> > mst;
    iter(it, es)
    {
        //cout << it->first << " " << it->second.first << " " << it->second.second << endl;
        if(uf.find(it->second.first) == uf.find(it->second.second)) continue;
        uf.unite(it->second.first, it->second.second);
        res += it->first;
        mst.push_back(*it);
    }

    assert(size(mst) == n-1);

    //cout << "MST:" << endl;
    iter(it, mst)
    {
        //cout << it->first << " " << it->second.first << " " << it->second.second << endl;
    }

    cout << res << endl;

    return 0;
}
