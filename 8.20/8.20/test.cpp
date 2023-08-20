#include <iostream>
using namespace std;
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> v;
        TreeNode* cur = root;
        //用cur表示要一开始要访问的树
        //当栈里还有元素，表明还有右路需要访问
        while (cur || !st.empty())
        {
            //首先需要将左路结点不断入栈
            while (cur)
            {
                st.push(cur);
                v.push_back(cur->val);
                cur = cur->left;
            }

            //栈里结点是用来找右路的
            //首先将栈里元素取出来，然后pop掉
            TreeNode* Top = st.top();
            st.pop();

            //用子问题的方式去访问右路
            cur = Top->right;
        }
        return v;
    }
};
//特殊树会怎么样？ 三叉链 二叉搜索树？
 //通过这个题目L:理解 通过Find查找这个过程，在加入一个栈， 可以将一个普通二叉树的路径搞出来
class Solution {
public:
    //查找某个结点的同时将该结点的路径放入栈里
    bool Path(TreeNode* root, TreeNode* node, stack<TreeNode*>& st)
    {
        if (root == nullptr)
            return false;

        //当前结点不为空，首先需要入栈
        st.push(root);
        //入栈以后再进行比较
        if (root == node)
            return true;

        //走到这里表明，当前结点并不是所找的结点，那么就需要递归到左子树去找
        if (Path(root->left, node, st))//如果为真，则说明该结点在左子树,如果为假的，就不走这里。递归到右子树去找
        {
            return true;
        }
        if (Path(root->right, node, st))//如果为真，则说明该结点在右子树，如果为假的，则说明该结点不在右子树
        {
            return true;
        }

        //能走到这里说明，当前结点的左右子树都没有所要找的结点，则说明该结点不可能是所找结点路径
        st.pop();
        return false;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<TreeNode*> pPath, qPath;
        Path(root, p, pPath);
        Path(root, q, qPath);

        while (pPath.size() > qPath.size())
        {
            pPath.pop();
        }
        while (qPath.size() > pPath.size())
        {
            qPath.pop();
        }

        while (qPath.top() != pPath.top())
        {
            pPath.pop();
            qPath.pop();
        }

        return pPath.top();
    }
};
class Solution {
public:
    void Inoder(TreeNode* cur, TreeNode*& prev)//prev用来记录当前结点的前一个结点
    {
        if (cur == nullptr)
            return;

        //走中序遍历
        Inoder(cur->left, prev);
        //根 ->有序
        cur->left = prev;//当前结点的左指针我们是知道的，但右指针是不知道的

        //当前结点是无法知道后一个指针指向那里的，但我可以穿越到前一个结点，将前一个结点的右指针指向我自己，那么前一个结点的右指针就链接上了

        if (prev != nullptr)
            prev->right = cur;
        //prev要求改变，在整个递归中只有以一个prev

      //在每次递归之前，记录当前结点的位置
        prev = cur;
        //想要让下一次递归看到上一次的改变，就需要用引用，不然看不到

     //左指针指向是在当前结点完成的，而右指针的指向是在后一个结点完成的。
        Inoder(cur->right, prev);
    }
    TreeNode* Convert(TreeNode* pRootOfTree) {
        TreeNode* prev = nullptr;
        Inoder(pRootOfTree, prev);

        TreeNode* head = pRootOfTree;

        while (head && head->left)
        {
            head = head->left;
        }
        return head;
    }
};
