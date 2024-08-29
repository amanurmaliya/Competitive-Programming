#include <iostream>
#include <vector>
using namespace std;

// Radhe Radhe Jai Saraswati Mata Jai Lakshmi Mata
// Siya pati Ram Chandra ki Jay Uma Pati Mahadev ki Jay

class DisjointSetByRank
{
public:
    vector<int> rank, parent;

    DisjointSetByRank(int n)
    {
        // This will work for both the graphs i.e., 0 & 1 Based both
        rank.resize(n + 1);
        parent.resize(n + 1);

        for (int i = 0; i <= n; i++)
        {
            rank[i] = 0;
            parent[i] = i;
        }
    }

    int findUltimateParent(int node)
    {
        // Agar Sabse Top Element pe hain mtlb woh khud ka parent khud hai
        if (parent[node] == node)
            return node;

        return parent[node] = findUltimateParent(parent[node]);
    }

    void unionByRank(int u, int v)
    {
        // Pahle Dono ke Parent ko Dhudh ke le aao
        int ultimateParentU = findUltimateParent(u);
        int ultimateParentV = findUltimateParent(v);

        // Agar Dono ke Ultimate Parent same hain mtlb dono already Connected hain So Do Not Do Any Thing
        if (ultimateParentU == ultimateParentV)
            return;

        // Agar Same nahi hain toh Rank ke hissab se join kar do
        if (rank[ultimateParentV] > rank[ultimateParentU])
        {
            // chote ko bade se join kar do aur rank pe koi bhi changes nahi aayenge
            parent[ultimateParentU] = ultimateParentV;
        }

        // Agar V Chota hai U se toh
        else if (rank[ultimateParentV] < rank[ultimateParentU])
        {
            parent[ultimateParentV] = ultimateParentU;
        }

        // Agar Dono Barabar hai toh V ko U Se attach kar do aur rank change ho jayegi qki same rank ka add huaa hai
        else
        {
            parent[ultimateParentV] = ultimateParentU;
            rank[ultimateParentU]++;
        }
    }
};