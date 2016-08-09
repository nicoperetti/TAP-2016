#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<char> vc;

#define LSOne(S) (S & (-S))
#define PLUS '+'
#define MINUS '-'
#define ZERO '0'

#define CHANGE 'C'
#define QUERY 'P'

class FenwickTree {
private:
  vi ft;
  vi ft_zero;

public:
  FenwickTree() {}
  // initialization: n + 1 zeroes, ignore index 0
  FenwickTree(int n) { 
    ft.assign(n + 1, 1);
    ft_zero.assign(n + 1, 0);
  }


  int rsq(int b) {                                     // returns RSQ(1, b)
    int prod = 1;
    for (; b; b -= LSOne(b))
      prod *= ft[b];
    return prod;
  }

  int rsq_zero(int b) {
    int zeros = 0;
    for (; b; b -= LSOne(b))
      zeros += ft_zero[b];
    return zeros;
  }

  int rsq(int a, int b) {                              // returns RSQ(a, b)
    int rsqb = rsq(b);
    int rsq_zerob = rsq_zero(b);
    if (a == 1) return ((rsq_zerob != 0) ? 0 : rsqb);
    int rsqa = rsq(a - 1);
    int rsq_zeroa = rsq_zero(a - 1);
    if (rsq_zeroa != 0 && (rsq_zerob == rsq_zeroa)) return rsqa * rsqb;
    return ((rsq_zerob != 0) ? 0 :  rsqa * rsqb);
  }

  int rsq_zero(int a, int b) {
    return rsq_zero(b) - (a == 1 ? 0 : rsq_zero(a - 1));
  }

  // adjusts value of the k-th element by v (v can be +ve/inc or -ve/dec)
  void adjust(int k, int v) {                    // note: n = ft.size() - 1
    for (; k < (int)ft.size(); k += LSOne(k)) {
      ft[k] *= v;
    }
  }

  // adjusts value of the k-th element by v (v can be +ve/inc or -ve/dec)
  void adjust_zero(int k, int v) {                    // note: n = ft.size() - 1
    for (; k < (int)ft.size(); k += LSOne(k)){
      ft_zero[k] += v;
    }
  }

};

int sign(int x) {
  return (x > 0) - (x < 0);
}

char toSymbol(int x) {
  if (x==1) return PLUS;
  if (x==-1) return MINUS;
  return ZERO;
}

int main() {
  int N, K;
  int num;
  int a, b; // interval for query or idx, value for change.
  char type;
  vi signs(1<<20, 1);
  vc answers;
  FenwickTree* fen;
  while (scanf("%d %d", &N, &K) != EOF) {
    answers.clear();
    fen = new FenwickTree(N);
    // fill signs and fill fen
    for (int i=1; i<=N; i++) {
      scanf("%d", &num);
      signs[i] = sign(num);
      if (num != 0) {
        fen->adjust(i, sign(num));
      } else {
        fen->adjust_zero(i, 1);
      }
    }
    // queries
    while (K--) {
      scanf(" %c %d %d", &type, &a, &b);
      if (type == CHANGE) {
        if (b == 0) {
          if (signs[a] != 0) {
            fen->adjust_zero(a, 1);
            fen->adjust(a, signs[a]);
          }
        } else {
          if (signs[a] == 0) {
            fen->adjust_zero(a, -1);
          } else {
            fen->adjust(a, signs[a]);
          }
          fen->adjust(a, sign(b));
        }
        signs[a] = sign(b);  // update sign of element at index a!
      } else {
        answers.push_back(toSymbol(fen->rsq(a,b)));
      }
    }
    for (int i=0; i < answers.size(); i++) {
      printf("%c", answers[i]);
    }
    printf("\n");
    delete fen;
  }
}

