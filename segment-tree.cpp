// Segment-tree with lazy propagation

#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree {
private:
    int n;
    vector<int> left, right, array, delta;

    void init(int i, int l, int r) {
        left[i] = l;
        right[i] = r;

        if (l == r)
            return;

        int m = l + (r-l)/2;
        init(2*i + 1, l, m);
        init(2*i + 2, m+1, r);
    }

    void prop(int i) {
        delta[2*i+1] += delta[i];
        delta[2*i+2] += delta[i];
        delta[i] = 0;
    }

    void update(int i) {
        array[i] = min(array[2*i+1] + delta[2*i+1], array[2*i+2] + delta[2*i+2]);
    }

    void increment(int i, int l, int r, int val) {
        if (right[i] < l || r < left[i])
            return;

        if (l <= left[i] && right[i] <= r) {
            delta[i] += val;
            return;
        }

        prop(i);
        increment(2*i + 1, l, r, val);
        increment(2*i + 2, l, r, val);
        update(i);
    }

    int minimum(int i, int l, int r) {
        if (right[i] < l || r < left[i])
            return numeric_limits<int>::max();

        if (l <= left[i] && right[i] <= r)
            return array[i] + delta[i];

        prop(i);
        int minLeft = minimum(2*i + 1, l, r);
        int minRight = minimum(2*i + 2, l, r);
        update(i);

        return min(minLeft, minRight);
    }

public:
    SegmentTree(int _n):
        n{_n},
        left(4*n - 1),
        right(4*n - 1),
        array(4*n - 1),
        delta(4*n - 1) {
        init(0, 0, n-1);
    }

    void increment(int l, int r, int val) {
        increment(0, l, r, val);
    }

    int minimum(int l, int r) {
        return minimum(0, l, r);
    }
};
