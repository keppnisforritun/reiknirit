#include <bits/stdc++.h>
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (decltype(a) i=(a); i<(b); ++i)
#define iter(it,c) for (decltype((c).begin()) it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
typedef unsigned long long ull;
const int INF = ~(1<<31);

const double EPS = 1e-9;
const double pi = acos(-1);
typedef unsigned long long ull;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
template <class T> T smod(T a, T b) {
  return (a % b + b) % b; }

#define P(p) const point3d &p
#define L(p0, p1) P(p0), P(p1)
#define PL(p0, p1, p2) P(p0), P(p1), P(p2)
struct point3d {
  double x, y, z;
  point3d() : x(0), y(0), z(0) {}
  point3d(double _x, double _y, double _z)
    : x(_x), y(_y), z(_z) {}
  point3d operator+(P(p)) const {
    return point3d(x + p.x, y + p.y, z + p.z); }
  point3d operator-(P(p)) const {
    return point3d(x - p.x, y - p.y, z - p.z); }
  point3d operator-() const {
    return point3d(-x, -y, -z); }
  point3d operator*(double k) const {
    return point3d(x * k, y * k, z * k); }
  point3d operator/(double k) const {
    return point3d(x / k, y / k, z / k); }
  double operator%(P(p)) const {
    return x * p.x + y * p.y + z * p.z; }
  point3d operator*(P(p)) const {
    return point3d(y*p.z - z*p.y,
                   z*p.x - x*p.z, x*p.y - y*p.x); }
  double length() const {
    return sqrt(*this % *this); }
  double distTo(P(p)) const {
    return (*this - p).length(); }
  double distTo(P(A), P(B)) const {
    // A and B must be two different points
    return ((*this - A) * (*this - B)).length() / A.distTo(B);}
  double signedDistTo(PL(A,B,C)) const {
    point3d N = (B-A)*(C-A);
    double D = A%N;
    return ((*this)%N - D)/N.length();
  }
  point3d normalize(double k = 1) const {
    // length() must not return 0
    return (*this) * (k / length()); }
  point3d getProjection(P(A), P(B)) const {
    point3d v = B - A;
    return A + v.normalize((v % (*this - A)) / v.length()); }
  point3d rotate(P(normal)) const {
    //normal must have length 1 and be orthogonal to the vector
    return (*this) * normal; }
  point3d rotate(double alpha, P(normal)) const {
    return (*this) * cos(alpha) + rotate(normal) * sin(alpha);}
  point3d rotatePoint(P(O), P(axe), double alpha) const{
    point3d Z = axe.normalize(axe % (*this - O));
    return O + Z + (*this - O - Z).rotate(alpha, O); }
  bool isZero() const {
    return abs(x) < EPS && abs(y) < EPS && abs(z) < EPS; }
  bool isOnLine(L(A, B)) const {
    return ((A - *this) * (B - *this)).isZero(); }
  bool isInSegment(L(A, B)) const {
    return isOnLine(A, B) && ((A - *this) % (B - *this))<EPS;}
  bool isInSegmentStrictly(L(A, B)) const {
    return isOnLine(A, B) && ((A - *this) % (B - *this))<-EPS;}
  double getAngle() const {
    return atan2(y, x); }
  double getAngle(P(u)) const {
    return atan2((*this * u).length(), *this % u); }
  bool isOnPlane(PL(A, B, C)) const {
    return
      abs((A - *this) * (B - *this) % (C - *this)) < EPS; } };
int line_line_intersect(L(A, B), L(C, D), point3d &O){
  if (abs((B - A) * (C - A) % (D - A)) > EPS) return 0;
  if (((A - B) * (C - D)).length() < EPS)
    return A.isOnLine(C, D) ? 2 : 0;
  point3d normal = ((A - B) * (C - B)).normalize();
  double s1 = (C - A) * (D - A) % normal;
  O = A + ((B - A) / (s1 + ((D - B) * (C - B) % normal))) * s1;
  return 1; }
int line_plane_intersect(L(A, B), PL(C, D, E), point3d & O) {
  double V1 = (C - A) * (D - A) % (E - A);
  double V2 = (D - B) * (C - B) % (E - B);
  if (abs(V1 + V2) < EPS)
    return A.isOnPlane(C, D, E) ? 2 : 0;
  O = A + ((B - A) / (V1 + V2)) * V1;
  return 1; }
bool plane_plane_intersect(P(A), P(nA), P(B), P(nB),
    point3d &P, point3d &Q) {
  point3d n = nA * nB;
  if (n.isZero()) return false;
  point3d v = n * nA;
  P = A + (n * nA) * ((B - A) % nB / (v % nB));
  Q = P + n;
  return true; }

point3d get_plane(point3d& a, point3d& b, point3d& c)
{
    return (a-b)*(a-c);
}

ostream& operator<<(ostream& outs, point3d& p)
{
    outs << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return outs;
}

double mixed(const point3d& a, const point3d& b, const point3d& c)
{
    return a % (b * c);
}

// compare y values
bool cmpy(point3d& a, point3d& b)
{
    if(abs(a.y-b.y) < EPS)
    {
        if(abs(a.x-b.x) < EPS) return a.z < b.z;
        else return a.x < b.x;
    }
    return a.y < b.y;
}

point3d slp; // The origin point, to calculate vector
// compare slopes relative to XZ plane, normal = (0,1,0)
bool cmpsl(point3d& a, point3d& b)
{
    // vectors
    point3d ad = a-slp, bd = b-slp;
    // x/z vector lengths
    double al = sqrt(ad.x*ad.x + ad.z*ad.z),
           bl = sqrt(bd.x*bd.x + bd.z*bd.z);
    // angles
    double aa = atan2(ad.y, al), ba = atan2(bd.y, bl);
    return aa < ba;
}


// Gift Wrapping Algorithm (3D Convex Hull)
// Returns a set of vector<int> denoting the indices of the
// points of the triangular faces.
// Time Complexity O(nh)
// - n: number of points
// - h: number of points in the convex hull
// TODO: Handle k>3 coplanar points
//       Can be done by discovering triangles in same way
//       as is already implemented but then collecting all
//       coplanar points. After collecting find the 2d
//       convex hull of those points and store them in 
//       counterclockwise order, lowest index first.
//       This may add a O(log h) factor.
set<vi> gift_wrap(vector<point3d> points)
{
    int n = size(points);
    set<vi> res; // TODO: avoid creating duplicates so res can be a vector
    // degenerate case
    if(n < 3) return res;

    // first find the lowest point P
    int lowi = 0;
    rep(i,1,n)
    {
        if(cmpy(points[i], points[lowi])) lowi = i;
    }

    // next we find the point Q, such that the angle of (Q-P)
    // with the XZ plane is minimized;
    slp = points[lowi];
    int lowj = 0;
    if(lowj == lowi) lowj++;
    rep(j,lowj+1,n)
    {
        if(j == lowi) continue;
        if(cmpsl(points[j], points[lowj])) lowj = j;
    }

    // order the tuple
    if(lowi > lowj) swap(lowi, lowj);
    
    // the edge from P to Q is guaranteed to be part
    // of the convex hull, the rest of the algorithm
    // functions like a breadth first search
    set<ii> vis; // visited edges
    queue<ii> q; // bfs queue
    q.push(ii(lowi, lowj)); // starting edge
    while(!q.empty())
    {
        ii cur = q.front();
        q.pop();
        if(vis.find(cur) != vis.end()) continue;
        vis.insert(cur);
        int mxi = 0, mni = 0;
        while(mni == cur.first || mni == cur.second) mni++;
        while(mxi == cur.first || mxi == cur.second) mxi++;
        rep(i,0,n)
        {

            if(i == cur.first || i == cur.second) continue;

            // Imagine you are the edge PQ, your feet are at Q and your head is at P.
            // In your vision (180°) there is a leftmost (innermost) and a rightmost (outermost) point.
            // Find either of those (or both), for simplicity we will use one and call it T
            // This mixed product is similar to using the sign of cross product (2D) to find counterclockwise turns
            if(mixed(points[cur.second] - points[cur.first],
                     points[mni] - points[cur.first],
                     points[i] - points[cur.first]) < 0)
            {
                mni = i;
            }
            if(mixed(points[cur.second] - points[cur.first],
                     points[mxi] - points[cur.first],
                     points[i] - points[cur.first]) > 0)
            {
                mxi = i;
            }
        }
        
        vi a(2), b(2); // helper lists to loop through edges to add
        a[0] = cur.first, a[1] = cur.second, b[0] = mni, b[1] = mxi;
        rep(i,0,2)
        {
            if(b[i] == -1) continue;
            bool either = false;
            rep(j,0,2)
            {
                // Now we push both the edges PT and QT
                ii st = ii(b[i], a[j]);
                if(st.first > st.second) swap(st.first, st.second);
                either = true;
                q.push(st);
            }
            vi v;
            v.push_back(a[0]);
            v.push_back(a[1]);
            v.push_back(b[i]);
            // order indices for uniqueness
            sort(v.begin(), v.end()); 
            res.insert(v);
        }


    }


    return res;
}


// FIELD TESTING: https://open.kattis.com/problems/worminapple
int main()
{
    cin.sync_with_stdio(false);
    int n;
    cin >> n;
    vector<point3d> points;
    rep(i,0,n)
    {
        double x, y, z;
        cin >> x >> y >> z;
        points.push_back(point3d(x,y,z));
    }

    set<vi> res = gift_wrap(points);
    
    int q;
    cin >> q;
    cout << setprecision(9) << fixed;
    rep(i,0,q)
    {
        point3d O;
        cin >> O.x >> O.y >> O.z;
        double mn = numeric_limits<double>::infinity();
        iter(it, res)
        {
            mn = min(mn, abs(O.signedDistTo(points[(*it)[0]], points[(*it)[1]], points[(*it)[2]])));
        }
        cout << mn << endl;
    }

    return 0;
}
