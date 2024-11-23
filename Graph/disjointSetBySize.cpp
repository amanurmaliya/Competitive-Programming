#include <iostream>
#include <vector>
using namespace std;

class DisjointSetBySize
{
  
  public:
  /* These are made public so that you can perform some oprations
    directly on them when needed */
  vector<int> parent, size;
  DisjointSetBySize(int n) {
      // initializing with n+1 size so that it can work even for the 1 based graphs too
      parent.resize(n+1);
      size.resize(n+1,0);
      
      for(int i = 0; i<=n; i++)
      parent[i] = i;
  }
  
  int findUltimateParent(int node)
  {
      if(parent[node] == node) return node;
      return parent[node] = findUltimateParent(parent[node]);
  }
  
  void unionBySize(int u, int v)
  {
      // Joining by size
      int ulp_u = findUltimateParent(u);
      int ulp_v = findUltimateParent(v);
      
      if(ulp_u==ulp_v) return;
      
      if(size[ulp_u]<size[ulp_v])
      {
          parent[ulp_u] = ulp_v;
          size[ulp_v] += size[ulp_u];
      }
      else 
      {
          parent[ulp_v] = ulp_u;
          size[ulp_u] += size[ulp_v];
      }
  }
};