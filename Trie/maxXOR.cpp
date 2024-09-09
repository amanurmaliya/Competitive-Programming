#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// You can use both the structure and the class for making this and both the things have the similar Time Complexity except that the struct has default public access specifier aur class ke pass private access specifier hai by defualt

struct Node
{
    Node *links[2] = {nullptr, nullptr};

    void put(int bit, Node *node)
    {
        links[bit] = node;
    }

    Node *get(int bit)
    {
        return links[bit];
    }

    bool contains(int bit)
    {
        // agar us node pe koi bhi value nahi hogi toh by default NULL hoga aur uska mtlb hai false
        return links[bit] != nullptr;
    }
};

class Trie
{
    // By default Private
    Node *root;

public:
    // This is the constructor that will set the node once the object is initialized
    Trie() : root(new Node()) {}

    void insert(int num)
    {
        Node *node = root;
        for (int i = 31; i >= 0; i--)
        {
            // Ye check kar lo ki 31st bit pe kya pada hai 0 or 1
            int bit = (num >> i) & 1;

            // Agar bit nahi contain kar rahi hai toh Node daal do
            if (!node->contains(bit))
            {
                node->put(bit, new Node());
            }

            // Agar contain kar li hogi toh usme  nayi value daal diye hain
            // toh ab contain aur non contain dono condition me aage badhna hai
            node = node->get(bit);
        }
    }

    int getMax(int num)
    {
        Node *node = root;

        int max = 0;
        for (int i = 31; i >= 0; i--)
        {
            int bit = (num >> i) & 1;

            // Ab yaha ye check karna hai ki current wali bit ka opposite set hai ki nahi hai
            // qki yaha hum Xor ^ operation perform kar rahe hain

            /* yaha 1-bit mtlb opposite jaise :
                agar 1 huaa toh 1-1 = 0 aur
                agar 0 huaa toh 1-0 = 1;
                toh yaha chahe !bit use kar lo ya 1-bit use kar lo both arre same
            */
            if (node->contains(1 - bit))
            {
                // Agar contain karta hai toh Xor karke move karo
                /* Agar max me ye pada hai
                    10000000000000000000000000000000
                    aur abhi hum 24th index me hai toh | OR aise karenge
                    00000000100000000000000000000000

                    10000000000000000000000000000000
                OR  00000000100000000000000000000000
                    10000000100000000000000000000000
                */
                max = max | (1 << i);
                // Opposite bit se Xor kiya hai toh move ab opposite bit me hikarenge
                node = node->get(1 - bit);
            }

            // Agar opposite bit hai hi nahi toh usse or kar denge toh same hi digit milegi toh isliye aage badho
            else
            {
                // bit me isliye move kiye hain qki 1 hi node hai jo hai bit baki opposite toh exist hi nhi karti hai
                node = node->get(bit);
            }
        }
        return max;
    }
};

int maximumXor(vector<int> A)
{
    // Radhe Radhe
    if (A.size() == 0)
        return 0;

    int maxi = 0;
    Trie trie;
    for (int i = 0; i < A.size(); i++)
    {
        trie.insert(A[i]);
    }

    for (int i = 0; i < A.size(); i++)
    {
        int Xor = trie.getMax(A[i]);
        maxi = std::max(maxi, Xor);
    }
    return maxi;
}

int main()
{
    int n = 3;
    vector<int> A = {2, 1, 4};
    cout << maximumXor(A) << endl;
}