#include <bits/stdc++.h>
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = 2147483647;

#define MAXV 1000
int par[MAXV],
    height[MAXV],
    root[MAXV];
bool marked[MAXV],
     emarked[MAXV][MAXV];

vi find_augmenting_path(vector<vi> adj, vi mate) {
    int n = size(adj);
    memset(par,-1,sizeof(par));
    memset(height,0,sizeof(height));
    memset(root,-1,sizeof(root));
    memset(marked,0,sizeof(marked));
    memset(emarked,0,sizeof(emarked));
    rep(i,0,n) if (mate[i] >= 0) emarked[i][mate[i]] = true;
               else root[i] = i;
    while (true) {
        int v = 0;
        while (v < n && (marked[v] || root[v] == -1 || height[v] % 2 != 0)) v++;
        if (v == n) break;
        iter(it,adj[v]) {
            int w = *it;
            if (emarked[v][w]) continue;
            if (root[w] == -1) {
                int x = mate[w];
                par[w] = v, root[w] = root[v], height[w] = height[v]+1;
                par[x] = w, root[x] = root[w], height[x] = height[w]+1;
            } else if (height[w] % 2 == 0) {
                if (root[v] != root[w]) {
                    vi res;
                    while (v != -1) res.push_back(v), v = par[v];
                    reverse(res.begin(), res.end());
                    while (w != -1) res.push_back(w), w = par[w];
                    return res;
                } else {
                    assert(false);
                }
            }
            emarked[v][w] = emarked[w][v] = true;
        }
        marked[v] = true;
    }
    return vi();
}

vii max_matching(vector<vi> adj) {
    vi mate(size(adj), -1), ap; vii res;
    do { ap = find_augmenting_path(adj, mate);
         rep(i,0,size(ap)) mate[mate[ap[i^1]] = ap[i]] = ap[i^1];
    } while (!ap.empty());
    rep(i,0,size(mate)) if (i < mate[i]) res.emplace_back(i, mate[i]);
    return res; }

int main() {
    int n, m;
    cin >> n >> m;
    vector<vi> adj(n);
    rep(i,0,m) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cout << size(max_matching(adj)) << endl;
    return 0;
}

