// This is the segment tree class template for the getting online queries sum

class Segment
{
    vector<int> seg;
    public:
    Segment(int n)
    {
        seg.resize(4*n);
    }
    
    void build(int idx, int low, int high, int arr[])
    {
        if(low==high)
        {
            seg[idx] = arr[low];
            return;
        }
        
        int mid = (low+high)/2;
        build(idx*2+1, low, mid, arr);
        build(idx*2+2, mid+1, high, arr);
        
        seg[idx] = sum(seg[2*idx+1], seg[2*idx+2]);
    }
    
    int sum(int a, int b)
    {
        return a+b;
    }
    
    void show()
    {
        for(auto it: seg) cout<<it<<" ";
    }
    int getSum(int idx, int low, int high, int l, int r)
    {
        // No over lap
        if(high<l || low>r) return 0;
        
        // Complete over lap 
        if(l<=low && r>=high) return seg[idx];
        
        // partial over lap
        int mid = (low+high)/2;
        int left = getSum(2*idx+1, low, mid, l, r);
        int right = getSum(2*idx+2, mid+1, high, l, r);
        return left+right;
    }
};
