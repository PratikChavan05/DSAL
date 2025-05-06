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