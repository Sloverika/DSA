#include <iostream>
#include <vector>

using namespace std;

class SegTree{
private:
	vector<int> sgt;
	int n;
public:
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
			sgt[i] = sgt[i << 1] + sgt[1+(i<<1)];
	}

	int query(int i, int j)
	{
		int ans = 0;
		for (i+=n, j+=n+1; i < j; i >>=1, j>>=1){
			if (i & 1) ans += sgt[i++];
			if (j & 1) ans += sgt[--j];
		}

		return ans;
	}
};

//another imp (from https://codeforces.com/blog/entry/18051)

const int N = 1e5;  // limit for array size
int n;  // array size
int t[2 * N];

void build() {  // build the tree
  for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // sum on interval [l, r)
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}


int main()
{
	vector<int> arr = {4, 5, 7, 8, 9, 12, 13, 15, 1, 45};
	SegTree st(arr);

	cout << st.query(1, 2) << "\n";

	return 0;
}

