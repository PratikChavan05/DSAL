#include<bits/stdc++.h>
using namespace std;

struct TreeNode{
    int key;
    TreeNode *left,*right;
    TreeNode(int val){
        key=val;
        left=nullptr;
        right=nullptr;
    }
};

class OBST{
    vector<int> keys;
    vector<float> p;
    vector<float> q;
    vector<vector<int>>r;
    int n;
    public:
    OBST(int size){
        n=size;
        keys.resize(size);
        p.resize(size);
        q.resize(size+1);
        r.resize(size+1,vector<int>(size+1,0));
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

    void optimalBST(){
        vector<vector<float>> w(n+1,vector<float>(n+1,0));
        vector<vector<float>> c(n+1,vector<float>(n+1,0));

        for(int i=0;i<=n;i++){
            w[i][i]=q[i];
        }

        for(int i=0;i<n;i++){
            w[i][i+1]=q[i]+p[i]+q[i+1];
            c[i][i+1]=w[i][i+1];
            r[i][i+1]=i+1;
        }

        for(int m=2;m<=n;m++){
            for(int i=0;i<=n-m;i++){
                int j=i+m;
                w[i][j]=w[i][j-1]+p[j-1]+q[j];
                int kmin=i+1;
                int mincost = c[i][kmin-1]+c[kmin][j];
                for(int k=i+2;k<j;k++){
                    int cost=c[i][k-1]+c[k][j];
                    if(cost<mincost){
                        mincost=cost;
                        kmin=k;
                    }
                }
                c[i][j]=mincost+w[i][j];
                r[i][j]=kmin;


            }
        }

        cout<<"Optimal BST Cost: " <<c[0][n]<<endl;
        cout << "Root of the tree: " << keys[r[0][n] - 1] << endl;
    }

    TreeNode *constructTree(int i,int j){
        if(i>=j){
            return nullptr;
        }
        int index= r[i][j]-1;
        if(index<0){
            return nullptr;
        }

        TreeNode *root = new TreeNode(keys[index]);
        root->left=constructTree(i,index);
        root->right=constructTree(index+1,j);
        return root;

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
    
}