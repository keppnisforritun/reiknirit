#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) \
  it = (c).begin(); it != (c).end(); ++it)
#define fs first
#define sc second
#define pb push_back
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1<<31);

const double EPS = 1e-9;
const double pi = acos(-1);
typedef unsigned long long ull;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }

#define P(p) const point &p
#define L(p0, p1) P(p0), P(p1)
#define C(p0, r) P(p0), double r
#define PP(pp) pair<point,point> &pp
typedef complex<double> point;
double dot(P(a), P(b)) { return real(conj(a) * b); }
double cross(P(a), P(b)) { return imag(conj(a) * b); }
point rotate(P(p), double radians = pi / 2,
             P(about) = point(0,0)) {
  return (p - about) * exp(point(0, radians)) + about; }
point reflect(P(p), L(about1, about2)) {
  point z = p - about1, w = about2 - about1;
  return conj(z / w) * w + about1; }
point proj(P(u), P(v)) { return dot(u, v) / dot(u, u) * u; }
point normalize(P(p), double k = 1.0) {
  return abs(p) == 0 ? point(0,0) : p / abs(p) * k; }
double ccw(P(a), P(b), P(c)) { return cross(b - a, c - b); }
bool collinear(P(a), P(b), P(c)) {
  return abs(ccw(a, b, c)) < EPS; }
double angle(P(a), P(b), P(c)) {
  return acos(dot(b - a, c - b) / abs(b - a) / abs(c - b)); }
double signed_angle(P(a), P(b), P(c)) {
  return asin(cross(b - a, c - b) / abs(b - a) / abs(c - b)); }
double angle(P(p)) { return atan2(imag(p), real(p)); }
point perp(P(p)) { return point(-imag(p), real(p)); }
double progress(P(p), L(a, b)) {
  if (abs(real(a) - real(b)) < EPS)
    return (imag(p) - imag(a)) / (imag(b) - imag(a));
  else return (real(p) - real(a)) / (real(b) - real(a)); }
bool in_circle(P(a), P(b), P(c), P(d)) {
    return norm(a) * ccw(b,c,d) - norm(b) * ccw(a,c,d) +
           norm(c) * ccw(a,b,d) - norm(d) * ccw(a,b,c) > 0;
}
bool on_segment(P(p), L(a, b)) {
    double x = progress(p, a, b);
    return collinear(a,p,b) && 0-EPS < x && x < 1+EPS;
}

////////////////////////// QUAD EDGE DATA STRUCTURE ///////////////////////////////////
// First we define the Quad Edge data structure (Guibas and Stofli 1985)
// however, without flips since it is not required for the use case of 
// Delaunay Triangulation
struct QuadEdge;

struct Edge
{
    int n;
    point* data;
    Edge* next;
    Edge() : data(NULL) {}
    // Edge algebra, we refer to the current edge as e, it has an origin and a destination
    // We move in counterclockwise order, next = CCW, prev = CW
    // The next edge with the same origin as e
    inline Edge* Onext() { return next; }
    // The edge from the right face to the left face of e
    inline Edge* Rot() { return n < 3 ? this + 1 : this - 3; }
    // The edge from the destination of e to the origin of e
    inline Edge* Sym() { return n < 2 ? this + 2 : this - 2; }
    // The edge from the left face of e to the right face of e
    inline Edge* RotInv() { return n < 1 ? this + 3 : this - 1; }
    // The previous (next clockwise) edge with the same origin as e
    inline Edge* Oprev() { return Rot()->Onext()->Rot(); }
    // The next edge with the same left face as e
    inline Edge* Lnext() { return RotInv()->Onext()->Rot(); }
    // The next edge with the same right face as e
    inline Edge* Rnext() { return Rot()->Onext()->RotInv(); }
    // The next edge with the same destination as e
    inline Edge* Dnext() { return Sym()->Onext()->Sym(); }
    // The previous edge with the same left face as e
    inline Edge* Lprev() { return Onext()->Sym(); }
    // The previous edge with the same right face as e
    inline Edge* Rprev() { return Sym()->Onext(); }
    // The previous edge with the same destionatino as e
    inline Edge* Dprev() { return RotInv()->Onext()->RotInv(); }
    // Additionally we have the edge rings Org, Left, Right and Dest in CCW order
    // e Org   = {e, e Onext, e Onext Onext, ..., e Oprev Oprev, e Oprev}
    // e Left  = {e, e Lnext, e Lnext Lnext, ..., e Lprev Lprev, e Lprev}
    // e Right = {e, e Rnext, e Rnext Rnext, ..., e Rprev Rprev, e Rprev}
    // e Dest  = {e, e Dnext, e Dnext Dnext, ..., e Dprev Dprev, e Dprev}
    inline point* Org() { return data; }
    inline point* Dest() { return Sym()->data; }
    inline void SetOrg(point* val) { data = val; }
    inline void SetDest(point* val) { Sym()->SetOrg(val); }
    QuadEdge* Quad() { return (QuadEdge*)(this - n); }
};

struct QuadEdge
{
    // The edges e, (e Rot), (e Sym) and (e RotInv)
    Edge e[4];
    QuadEdge() { rep(i,0,4) e[i].n = i, e[i].next = i%2 ? &(e[4-i]) : &(e[i]); }
};

// Returns an edge e. It will not be a loop, the following will hold:
// - e Org != e Dest
// - e Left == e Right
// - e Lnext == e Rnext == e Sym
// - e Onext == e Oprev == e
// To construct a loop instead we can use e Rot since
// - e Rot Org == e Rot Dest
// - e Rot Left != e Rot Right
// - e Rot Lnext == e Rot Rnext == e Rot
// - e Rot Onext == e Rot Oprev == e Rot Sym
Edge* make_edge()
{
    QuadEdge* qe = new QuadEdge();
    return qe->e;
}

// This operation affects the two edge rings a Org and b Org and,
// independently the two edge rings a Left and b Left. In each case,
// (a) if the two rings are distinct, splice will combine them into one;
// (b) if the two are exactly the same ring, Splice wil break it in two separate pieces;
// (c) if the two are the same ring taken with opposite orientation, 
//     Splice will Flip (and reverse the order) of a segment of that ring.
// The parameters a and b determine the place where the edge rings wqill be cut and joined.
// For the rings a Org and b Org, the cuts will occur immediately after a and b (CCW);
// for the rings a Left and b Left, the cuts will occur immediately before a Rot and b Rot.
//  
// We only need to consider (a) and (b) since we don't have flips
void splice(Edge* a, Edge* b)
{
    Edge  *alpha = a->Onext()->Rot(),
          *beta = b->Onext()->Rot(),
    
          *aOnextPrime = b->Onext(),
          *bOnextPrime = a->Onext(),
          *alphaOnextPrime = beta->Onext(),
          *betaOnextPrime = alpha->Onext();

    a->next = aOnextPrime;
    b->next = bOnextPrime;
    alpha->next = alphaOnextPrime;
    beta->next = betaOnextPrime;
}

void delete_edge(Edge* e)
{
    splice(e, e->Oprev());
    splice(e->Sym(), e->Sym()->Oprev());
    delete e->Quad();
}



/////////////////// TOPOLOGICAL OPERATORS FOR DELAUNAY DIAGRAMS /////////////////////////////

Edge* connect(Edge* a, Edge* b)
{
    Edge* e = make_edge();
    e->SetOrg(a->Dest());
    e->SetDest(b->Org());
    splice(e, a->Lnext());
    splice(e->Sym(), b);
    return e;
}


void swap(Edge* e)
{
    Edge* a = e->Oprev();
    Edge* b = e->Sym()->Oprev();
    // first remove old edge
    splice(e, a);
    splice(e->Sym(), b);
    // then add the new one
    splice(e, a->Lnext());
    splice(e->Sym(), b->Lnext());
    e->SetOrg(a->Dest());
    e->SetDest(b->Dest());
}

//////////////// INCREMENTAL DELAUNAY TRIANGULATION /////////////////////

inline bool right_of(point X, Edge *e)
{
    return ccw(X, *(e->Dest()), *(e->Org())) > 0; 
}

inline bool left_of(point X, Edge *e)
{
    return ccw(X, *(e->Org()), *(e->Dest())) > 0;
}


struct Subdivision
{
    Edge* start_edge;
    Subdivision(P(a), P(b), P(c))
    {
        point *pa = new point(a), *pb = new point(b), *pc = new point(c);
        Edge* ab = make_edge();
        Edge* bc = make_edge();
        Edge* ca = make_edge();
        ab->SetOrg(pa);
        ab->SetDest(pb);
        bc->SetOrg(pb);
        bc->SetDest(pc);
        ca->SetOrg(pc);
        ca->SetDest(pa);
        splice(ab->Sym(), bc);
        splice(bc->Sym(), ca);
        splice(ca->Sym(), ab);
        start_edge = ab;
    }

    Edge* locate(point X)
    {
        Edge *e = start_edge;
        while(true)
        {
            if (X == *(e->Org()) || X == *(e->Dest())) return e;
            else if (right_of(X, e)) e = e->Sym();
            else if (!right_of(X, e->Onext())) e = e->Onext();
            else if (!right_of(X, e->Dprev())) e = e->Dprev();
            else return e;
        }
    }

    void insert_site(point X)
    {
        Edge *e = locate(X);
        if (X == *(e->Org()) || X == *(e->Dest())) return;
        else if (on_segment(X, *(e->Org()), *(e->Dest())))
        {
            Edge* temp = e->Oprev();
            delete_edge(e);
            e = temp;
        }
        Edge *base = make_edge();
        point* first = e->Org();
        base->SetOrg(first);
        base->SetDest(new point(X));
        splice(base, e);
        do {
            base = connect(e, base->Sym());
            e = base->Oprev();
        } while (e->Dest() != first);
        e = base->Oprev();

        while(true)
        {
            Edge *t = e->Oprev();
            if (right_of(*(t->Dest()), e) && in_circle(*(e->Org()), *(t->Dest()), *(e->Dest()), X)) 
            {
                swap(e);
                e = t;
            }
            else if (*(e->Org()) == *first) return; // done
            else e = e->Onext()->Lprev(); // next suspect edge
        }
    }
};


// TODO: Iterator for vertices/faces/edges 

int main()
{
    ios_base::sync_with_stdio(false);

    // The supertriangle is a boundary for the entire point set, make sure it is large enough
    Subdivision supertriangle(point(0,0), point(1000, 0), point(0,1000));

    int n;
    cin >> n;
    vector<point> points(n);
    rep(i,0,n)
    {
        double x, y;
        cin >> x >> y;
        point p(x,y);
        points.push_back(p);
        supertriangle.insert_site(p);
    }

    return 0;
}
