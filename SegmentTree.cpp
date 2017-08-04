//
// Created by kapildd on 8/4/17.
//

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

//Segment tree for storing minimum of a range
class SegmentTree{
    vector<int> data;
    int n;
public:
    SegmentTree(int n) : n(n) {
        // There will be 2^k leaves for least value of k, such that 2^k>=n
        // So, entire tree would take 2^(k+1) values. We know 2*n>=2^k
        // and (4*n>=2^(k+1), and we are saved from Segmentation faults!
        data.resize(4*n);
    }
    //index denotes sequence number of node, in a level ordered traversal (1-indexed)
    //range_start is the starting of range for which node is responsible
    //range_end is the ending for same
    //A is vector, whose data should be used to construct tree values, assumes A.size() == n
    int buildTree(int index, int range_start, int range_end, vector<int>& A) {
        if(range_start == range_end) {
            data[index] = A[range_end];
            return data[index];
        }
        int mid = (range_start + range_end)/2;
        int left = buildTree(index*2, range_start, mid, A);
        int right = buildTree(index*2+1, mid+1, range_end, A);
        data[index] = min(left, right);
        return data[index];
    }
    //query_start is the starting of range asked in query
    //query_end is the ending of same
    int queryTree(int index, int range_start, int range_end, int query_start, int query_end) {
        if(query_end < range_start || query_start > range_end) {
            return INT_MAX;
        }
        if(query_start <= range_start && range_end <= query_end) {
            return data[index];
        }
        int mid = (range_start + range_end)/2;
        int left = queryTree(index*2, range_start, mid, query_start, query_end);
        int right = queryTree(index*2+1, mid+1, range_end, query_start, query_end);
        return min(left, right);
    }
};
int main() {
    int n, k;
    cin>>n;
    vector<int> v(n);
    for(int i=0; i<n; i++)
        cin>>v[i];
    cin>>k;
    SegmentTree* segtree = new SegmentTree(n);
    segtree->buildTree(1, 0, n-1, v);
    for(int i=k-1; i<n; i++) {
        cout << segtree->queryTree(1, 0, n-1, i-k+1, i) << " ";
    }
    cout << endl;
    return 0;
}