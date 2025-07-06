#include<iostream>
#include<vector>

using namespace std;

class ST
{
    vector<int> seg, lazy;

    public: 
    ST(int n)
    {
        seg.resize(n);
        lazy.resize(n, 0);
    }

    void build(int idx, int cl, int ch, vector<int> &arr)
    {
        // if this is the last
        if(cl==ch)
        {
            seg[idx] = arr[cl];
            return;
        }

        int mid = (cl+ch) >> 1;

        build(2*idx+1, cl, mid, arr);
        build(2*idx+2, mid+1, ch, arr);

        seg[idx] = seg[2*idx+1] + seg[2*idx+2];
    }

    // This will update the old query
    void update(int idx, int cl, int ch, int sl, int sh, int val) // cl = current Low, ch = current High, sl = Search Low, sh = Search High
    {
        // Firstly Update the last lazy if avaliable
        if(lazy[idx]!=0)
        {
            seg[idx] += (ch-cl+1) * lazy[idx];

            // if this is the not the lower leaf 
            if(cl != ch)
            {
                lazy[2*idx+1] = lazy[idx];
                lazy[2*idx+2] = lazy[idx];
            }
            lazy[idx] = 0;
        }

        // No overlapping  || cl ch sl sh or sl sh cl ch
        if(ch<sl || sh < cl) return;

        // Complete Overlap || sl cl ch sh
        if(sl<=cl && ch <= sh)
        {
            seg[idx] += (ch-cl+1) * val;

            // Check if it is leaf do not propogate else we must
            if(cl!=ch)
            {
                lazy[2*idx+1] += val;
                lazy[2*idx+2] += val;
            }

            return ;
        }

        // Partial overlap
        int mid = (ch+cl) >> 1;

        update(2*idx+1, cl, mid, sl, sh, val);
        update(2*idx+2, mid+1, ch, sl, sh, val);

        seg[idx] = seg[2*idx+1] + seg[2*idx+2];
    }

    int query(int idx, int cl, int ch, int sl, int sh)
    {

        // First update the existing array
        if(lazy[idx]!=0)
        {
            seg[idx] += (ch-cl+1) * lazy[idx];

            if(ch!=cl)
            {
                lazy[2*idx+1] += lazy[idx];
                lazy[2*idx+2] += lazy[idx];
            }

            lazy[idx] = 0;
        }
        
        // Check no overlap || cl ch sl sh cl ch
        if(ch<sl || sh<cl)
        {
            return 0;
        }

        // Completely overlap
        if(sl<=cl && ch<=sh)
        {
            return seg[idx];
        } 

        // partial overlap
        int mid = (ch+cl) >> 1;

        int left = query(2*idx+1, cl, mid, sl, sh);
        int right = query(2*idx+2, mid+1, ch, sl, sh);

        return left+right;
    }
};
