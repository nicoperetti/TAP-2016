#include <cstdio>
#include <vector>
#include <cstring>

#define MAX_PIRATES (1 << 20)
#define toDigit(c) c - '0'

#define NOTHING 'N'
#define SET 'F'
#define CLEAR 'E'
#define FLIP 'I'
#define GOD 'S'

using namespace std;

typedef vector <int> vi;
typedef vector<char> vc;

class SegmentTree {         // the segment tree is stored like a heap array
private:
  vi st;  // segment tree with amount
  vc st_mark;  // segment tree with marks
  char* bs;
  int n;
  int left (int p) { return p << 1; }     // same as binary heap operations
  int right(int p) { return (p << 1) + 1; }

  void build(int p, int L, int R) {                           // O(n log n)
    if (L == R)                            // as L == R, either one is fine
      st[p] = toDigit(bs[L]);                                // store the index
    else {                                // recursively compute the values
      build(left(p) , L              , (L + R) / 2);
      build(right(p), (L + R) / 2 + 1, R          );
      int p1 = st[left(p)], p2 = st[right(p)];
      st[p] = p1 + p2;
  } }

  char flip(char old_type) {
    if (old_type == NOTHING) return FLIP;
    if (old_type == CLEAR) return SET;
    if (old_type == SET) return CLEAR;
    else return NOTHING;
  }

  void apply_mark(int p, int L, int R) {
    // apply mark of node
    if (st_mark[p] == SET) {
      st[p] = R - L + 1;
      if (L != R) {
        st_mark[left(p)] = SET;
        st_mark[right(p)] = SET;
      }
    } else if (st_mark[p] == CLEAR) {
      st[p] = 0;
      if (L != R) {
        st_mark[left(p)] = CLEAR;
        st_mark[right(p)] = CLEAR;
      }
    } else if (st_mark[p] == FLIP) {
      st[p] = (R - L + 1) - st[p];
      if (L != R) {
        st_mark[left(p)] = flip(st_mark[left(p)]);
        st_mark[right(p)] = flip(st_mark[right(p)]);
      }
    }
    st_mark[p] = NOTHING;
  }

  int rmq(int p, int L, int R, int i, int j) {                  // O(log n)
    if (i >  R || j <  L) return -1; // current segment outside query range
    // update mark & value

    apply_mark(p, L, R);

    if (L >= i && R <= j) {  // inside query range
      return st[p];
    }

     // compute the min position in the left and right part of the interval
    int p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
    int p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

    if (p1 == -1) return p2;   // if we try to access segment outside query
    if (p2 == -1) return p1;                               // same as above
    return p1 + p2; }          // as as in build routine

  int update_segment(int p, int L, int R, int a, int b, char type) {
    // this update code is still preliminary, i == j
    // must be able to update range in the future!
    int i = a, j = b;

    apply_mark(p, L, R);

    // if the current interval does not intersect 
    // the update interval, return this st node value!
    if (i > R || j < L)
      return st[p];

    // if the current interval is included in the update range,
    // update that st[node]
    if (L >= i && R <= j) {
      st_mark[p] = type;
      apply_mark(p, L, R);
      return st[p];
    }

    // compute the minimum pition in the 
    // left and right part of the interval
    int p1, p2;
    p1 = update_segment(left(p) , L              , (L + R) / 2, a, b, type);
    p2 = update_segment(right(p), (L + R) / 2 + 1, R          , a, b, type);

    // return the pition where the overall minimum is
    return st[p] = p1 + p2;
  }

public:
  SegmentTree(char _bs[], int &_n) {
    bs = _bs; n = _n;              // copy content for local usage
    st.assign(4 * n, 0);            // create large enough vector of zeroes
    st_mark.assign(4 * n, NOTHING);
    build(1, 0, n - 1);                                  // recursive build
  }

  int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }

  void update(int a, int b, char type) { update_segment(1, 0, n - 1, a, b, type); }
};

int main() {
  int TC;
  int pairs, N;
  int queries, queries_printed;
  int pirates_size, total_pirates;
  char pirates[64];
  char bs[MAX_PIRATES];  // char vector of MAX_PIRATES size.
  char type;
  SegmentTree* st;
  int a, b;

  scanf("%d", &TC);

  for (int i=1; i<=TC; i++) {
    printf("Case %d:\n", i);
    total_pirates = 0;
    queries_printed = 0;
    // description
    scanf("%d", &pairs);
    while(pairs--) {
      scanf("%d", &N);
      scanf("%s", pirates);
      pirates_size = strlen(pirates);
      for (int j=0; j<N; j++) {
        for (int i=0; i < pirates_size; i++) {
          bs[total_pirates++] = pirates[i];
        }
      }
    }
    // queries
    st = new SegmentTree(bs, total_pirates);
    scanf("%d", &queries);
    while(queries--) {
      scanf(" %c %d %d", &type, &a, &b);
      if (type == GOD) {
        queries_printed++;
        printf("Q%d: %d\n", queries_printed, st->rmq(a,b));
      } else {
        st->update(a, b, type);
      }
    }
    delete st;
  }

  return 0;
}

