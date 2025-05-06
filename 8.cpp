#include <bits/stdc++.h>
using namespace std;

// Tree Node Structure
struct TreeNode
{
    int key;
    TreeNode *left, *right;
    TreeNode(int val) : key(val), left(nullptr), right(nullptr) {}
};

class OBST
{
    vector<int> keys;
    vector<float> p;
    vector<float> q;
    vector<vector<int>> r;
    int n;

public:
    OBST(int size) : n(size)
    {
        keys.resize(size);
        p.resize(size);
        q.resize(size + 1);
        r.resize(size + 1, vector<int>(size + 1, 0));
    }

    void insert()
    {
        cout << "Enter the keys: " << endl;
        for (int i = 0; i < n; i++)
            cin >> keys[i];

        cout << "Enter the Successful probability for keys: " << endl;
        for (int i = 0; i < n; i++)
            cin >> p[i];

        cout << "Enter the Unsuccessful probability: " << endl;
        for (int i = 0; i <= n; i++)
            cin >> q[i];
    }

    void optimalBST()
    {
        vector<vector<float>> w(n + 1, vector<float>(n + 1, 0));
        vector<vector<float>> c(n + 1, vector<float>(n + 1, 0));

        for (int i = 0; i <= n; i++)
            w[i][i] = q[i];

        for (int i = 0; i < n; i++)
        {
            w[i][i + 1] = q[i] + p[i] + q[i + 1];
            c[i][i + 1] = w[i][i + 1];
            r[i][i + 1] = i + 1;
        }

        for (int m = 2; m <= n; m++)
        {
            for (int i = 0; i <= n - m; i++)
            {
                int j = i + m;
                w[i][j] = w[i][j - 1] + p[j - 1] + q[j];

                int k_min = i + 1;
                float min_cost = c[i][k_min - 1] + c[k_min][j];

                for (int k = i + 2; k < j; k++)
                {
                    float cost = c[i][k - 1] + c[k][j];
                    if (cost < min_cost)
                    {
                        min_cost = cost;
                        k_min = k;
                    }
                }

                c[i][j] = min_cost + w[i][j];
                r[i][j] = k_min;
            }
        }

        cout << "Optimal BST Cost: " << c[0][n] << endl;
        cout << "Root of the tree: " << keys[r[0][n] - 1] << endl;
    }

    TreeNode *constructTree(int i, int j)
    {
        if (i >= j)
            return nullptr;

        int rootIndex = r[i][j] - 1;
        if (rootIndex < 0)
            return nullptr;

        TreeNode *root = new TreeNode(keys[rootIndex]);
        root->left = constructTree(i, rootIndex);
        root->right = constructTree(rootIndex + 1, j);

        return root;
    }

    void level_order(TreeNode *root)
    {
        if (!root)
            return;

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();

            cout << node->key << " ";

            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
        cout << endl;
    }
};

int main()
{
    cout << "Enter the number of nodes: ";
    int n;
    cin >> n;

    OBST obj(n);
    obj.insert();
    obj.optimalBST();

    TreeNode *root = obj.constructTree(0, n);
    cout << "Level Order Traversal: ";
    obj.level_order(root);
}