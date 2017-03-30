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
// int par[MAXV],
//     height[MAXV],
//     root[MAXV];
// bool marked[MAXV],
//      emarked[MAXV][MAXV];

vi find_augmenting_path(const vector<vi> &adj, const vi &mate) {
//     cout << endl;
// rep(i,0,size(adj)) {
//     cout << i << ": ";
//     iter(it,adj[i]) {
//         cout << *it << " ";
//     }
//     cout << endl;
// }
// rep(i,0,size(mate)) cout << mate[i] << " ";
// cout << endl;

    int n = size(adj);
    vi par(n,-1),
       height(n),
       root(n,-1);
    vector<bool> marked(n);
    vector<vector<bool> > emarked(n, vector<bool>(n));

    // int par[MAXV],
    //     height[MAXV],
    //     root[MAXV];
    // bool marked[MAXV],
    //     emarked[MAXV][MAXV];
    //
    // memset(par,-1,MAXV * sizeof(int));
    // memset(height,0,MAXV * sizeof(int));
    // memset(root,-1,MAXV * sizeof(int));
    // memset(marked,0,MAXV * sizeof(bool));
    // memset(emarked,0,MAXV * MAXV * sizeof(bool));
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

                    vi a, b;
                    int c = v;
                    while (c != -1) a.push_back(c), c = par[c];
                    c = w;
                    while (c != -1) b.push_back(c), c = par[c];
                    // reverse(a.begin(), a.end());
                    // reverse(b.begin(), b.end());
                    while (!a.empty() && !b.empty() && a.back() == b.back()) c = a.back(), a.pop_back(), b.pop_back();

                    // cout << "a: ";
                    // iter(it,a) cout << *it << " ";
                    // cout << endl;
                    // cout << "b: ";
                    // iter(it,b) cout << *it << " ";
                    // cout << endl;
                    // cout << "c: " << c << endl;


                    // rep(i,0,n) cout << par[i] << " ";
                    // cout << endl;
                    // rep(i,0,n) cout << mate[i] << " ";
                    // cout << endl;
                    // cout << "meow " << v << " " << w << " " << c << endl;


                    fill(marked.begin(), marked.end(), false);
                    // memset(marked,0,MAXV*sizeof(bool)); // marked[i] means that i has been connected to S
                    fill(par.begin(), par.end(), 0);
                    // memset(par,0,MAXV*sizeof(int));

                    // cout << "meow" << endl;
                    // iter(it,a) cout << *it << " ";
                    // cout << endl;
                    // cout << "meow" << endl;

                    iter(it,a) par[*it] = 1;
                    iter(it,b) par[*it] = 1;
                    par[c] = 1;
                    int m = 1;

                    rep(i,0,n) root[par[i] = par[i] ? 0 : m++] = i;

                    // par[i] er nýja id-ið (sér í lagi 0 ef það er súpernóðan)

                    // TODO: clean up
                    vector<vi> adj2(m);
                    rep(i,0,n) {
                        iter(it,adj[i]) {
                            if (par[*it] == 0) continue;
                            if (par[i] == 0) {
                                if (!marked[par[*it]])  {
                                    adj2[par[i]].push_back(par[*it]);
                                    adj2[par[*it]].push_back(par[i]);
                                    marked[par[*it]] = true;
                                }
                            } else {
                                adj2[par[i]].push_back(par[*it]);
                            }
                        }
                    }

                    vi mate2(m, -1);
                    // assert(mate[c] != -1 && par[c] == 0 && par[mate[c]] != 0);
                    if (mate[c] != -1) {
                        mate2[0] = par[mate[c]];
                        mate2[par[mate[c]]] = 0;
                    }

                    rep(i,0,n) {
                        // cout << i << " " << mate[i] << endl;
                        if (par[i] == 0 || mate[i] == -1 || par[mate[i]] == 0) continue;
                        mate2[par[i]] = par[mate[i]];
                    }


                    // cout << "down" << endl;
                    vi p = find_augmenting_path(adj2, mate2);
                    // cout << "up" << endl;
                    // cout << "p: ";
                    // iter(it,p) cout << *it << " ";
                    // cout << endl;
                    int idx = 0;
                    while (idx < size(p) && p[idx] != 0) idx++;
                    if (idx == size(p)) {
                        rep(i,0,size(p)) p[i] = root[p[i]];
                        return p;
                    }

                    if (p[0] == 0 || (mate[c] != -1 && p[idx+1] != par[mate[c]])) reverse(p.begin(), p.end()), idx = size(p) - idx - 1;
                    vi q;
                    rep(i,0,idx) q.push_back(root[p[i]]);

                    assert(idx-1 >= 0);
                    iter(it,adj[root[p[idx-1]]]) {
                        if (par[*it] != 0) continue;

                        // cout << root[p[idx-1]] << " " << *it << endl;

                        a.push_back(c);
                        reverse(b.begin(), b.end());
                        iter(jt,b) a.push_back(*jt);

                        int jdx = 0;
                        while (a[jdx] != *it) jdx++;

                        // cout << "cycle: ";
                        // iter(it,a) cout << *it << " ";
                        // cout << endl;

                        // if (height[*it] % 2 == 0) { // TODO: WAT
                        // cout << (height[*it] & 1) << " " << (jdx < size(a)) << endl;
                        if (1 ^ (height[*it] & 1) ^ (jdx < size(a) - size(b))) {
                            // cout << "reversed" << endl;
                            reverse(a.begin(), a.end());
                            jdx = size(a) - jdx - 1;
                        }

                        while (a[jdx] != c) {
                            q.push_back(a[jdx]);
                            jdx = (jdx+1) % size(a);
                        }

                        q.push_back(c);
                        rep(i,idx+1,size(p)) q.push_back(root[p[i]]);
                        return q; // TODO
                    }
                    assert(false);
                }
            }
            emarked[v][w] = emarked[w][v] = true;
        }
        marked[v] = true;
    }
    return vi();
}

vii max_matching(const vector<vi> &adj) {
    vi mate(size(adj), -1), ap; vii res;
    do { ap = find_augmenting_path(adj, mate);
        // iter(it,ap) assert(0 <= *it && *it < size(adj));
        // cout << "ap: ";
        // iter(it,ap) cout << *it << " ";
        // cout << endl;
        assert(size(ap) % 2 == 0);
        // cout << "wat ";
        // cout << size(ap) << endl;
        // iter(it,ap) cout << *it << " ";
        // cout << endl;
         rep(i,0,size(ap)) mate[mate[ap[i^1]] = ap[i]] = ap[i^1];
    } while (!ap.empty());
    rep(i,0,size(mate)) if (i < mate[i]) res.emplace_back(i, mate[i]);
    return res; }

int main() {
    int n; // , m;
    cin >> n; // >> m;
    vector<vi> adj(n);
    int a,b;
    while (cin >> a >> b) {
    // rep(i,0,m) {
        // int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // cout << size(max_matching(adj)) << endl;
    vii res = max_matching(adj);
    cout << 2*size(res) << endl;
    rep(i,0,size(res)) {
        cout << res[i].first+1 << " " << res[i].second+1 << endl;
    }
    return 0;
}

