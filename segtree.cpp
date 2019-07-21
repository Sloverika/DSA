#include <iostream>
#include <vector>

using namespace std;

class SegTree{
private:
	vector<int> sgt;
	int n;
public:
	// 0-indexed - by default, RSQ
	SegTree(const vector<int>& arr)
	{
		int size = arr.size();
		for (n = 1; n < size; n*=2);
		sgt.assign(n*2, 0); //0 for sum
		for (int i = 0; i < size; i++)
			sgt[i+n] = arr[i];

		for (int i = n+size-1; i > 1; i--)
			sgt[i>>1] = sgt[i>>1] + sgt[i];//insert op here
	}

	void update(int i, int x)
	{
		sgt[i += n] = x;
		for (i >>= 1; i; i >>= 1)
			sgt[i] = sgt[i << 1] + sgt[1+(i<<1)]; //insert op here
	}

	//query on [i,j]
	int query(int i, int j)
	{
		int ans = 0;
		for (i+=n, j+=n+1; i < j; i >>=1, j>>=1){
			if (i & 1) ans += sgt[i++]; // insert op here
			if (j & 1) ans += sgt[--j];
		}

		return ans;
	}

	
	void rupdate(int i, int j, int x)
	{
		for (i += n, j+=n+1; i < j; i >>= 1, j >>= 1){
			if (i & 1) sgt[i++] += x; // op
			if (j & 1) sgt[--j] += x;
		}
	}
};

//another imp (from https://codeforces.com/blog/entry/18051)

const int N = 1e5;  // limit for array size, default = 100000
int n;  // array size
int t[2 * N]; // seg tree

void build() {  // build the tree
  for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1]; // p ^ 1 turns 2 * p into 2 * p + 1 and vice-versa
}

int query(int l, int r) {  // sum on interval [l, r)
  // 
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}


void interval_modify(int l, int r, int value) { // [l, r)
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) t[l++] += value;
    if (r&1) t[--r] += value;
  }
}

int pquery(int p) {
  int res = 0;
  for (p += n; p > 0; p >>= 1) res += t[p];
  return res;
}
/* example :
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", t + n + i);
  build();
  modify(0, 1);
  printf("%d\n", query(3, 11));
  return 0;
}
 */


int main()
{
	vector<int> arr = {4, 5, 7, 8, 9, 12, 13, 15, 1, 45};
	cout << "c-array:\n";
	// tests on the c-array segtree implementation from codeforces
	
	n = arr.size();
	for (int i = 0; i < n; i++)
		t[n+i] = arr[i];

	build();
	cout << query(1, 3) << "\n";

	// basic tests for the class based seg tree 
	cout << "class based:\n";	
	SegTree st(arr);

	cout << st.query(1, 1) << "\n";
	cout << st.query(1, 3) << "\n";
	st.rupdate(1, 3, 1);
	cout << st.query(1, 3) << "\n";
	cout << st.query(1, 1) << "\n";

	return 0;
}

