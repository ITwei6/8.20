#include <iostream>
using namespace std;
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> v;
        TreeNode* cur = root;
        //��cur��ʾҪһ��ʼҪ���ʵ���
        //��ջ�ﻹ��Ԫ�أ�����������·��Ҫ����
        while (cur || !st.empty())
        {
            //������Ҫ����·��㲻����ջ
            while (cur)
            {
                st.push(cur);
                v.push_back(cur->val);
                cur = cur->left;
            }

            //ջ��������������·��
            //���Ƚ�ջ��Ԫ��ȡ������Ȼ��pop��
            TreeNode* Top = st.top();
            st.pop();

            //��������ķ�ʽȥ������·
            cur = Top->right;
        }
        return v;
    }
};
//����������ô���� ������ ������������
 //ͨ�������ĿL:��� ͨ��Find����������̣��ڼ���һ��ջ�� ���Խ�һ����ͨ��������·�������
class Solution {
public:
    //����ĳ������ͬʱ���ý���·������ջ��
    bool Path(TreeNode* root, TreeNode* node, stack<TreeNode*>& st)
    {
        if (root == nullptr)
            return false;

        //��ǰ��㲻Ϊ�գ�������Ҫ��ջ
        st.push(root);
        //��ջ�Ժ��ٽ��бȽ�
        if (root == node)
            return true;

        //�ߵ������������ǰ��㲢�������ҵĽ�㣬��ô����Ҫ�ݹ鵽������ȥ��
        if (Path(root->left, node, st))//���Ϊ�棬��˵���ý����������,���Ϊ�ٵģ��Ͳ�������ݹ鵽������ȥ��
        {
            return true;
        }
        if (Path(root->right, node, st))//���Ϊ�棬��˵���ý���������������Ϊ�ٵģ���˵���ý�㲻��������
        {
            return true;
        }

        //���ߵ�����˵������ǰ��������������û����Ҫ�ҵĽ�㣬��˵���ý�㲻���������ҽ��·��
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
    void Inoder(TreeNode* cur, TreeNode*& prev)//prev������¼��ǰ����ǰһ�����
    {
        if (cur == nullptr)
            return;

        //���������
        Inoder(cur->left, prev);
        //�� ->����
        cur->left = prev;//��ǰ������ָ��������֪���ģ�����ָ���ǲ�֪����

        //��ǰ������޷�֪����һ��ָ��ָ������ģ����ҿ��Դ�Խ��ǰһ����㣬��ǰһ��������ָ��ָ�����Լ�����ôǰһ��������ָ�����������

        if (prev != nullptr)
            prev->right = cur;
        //prevҪ��ı䣬�������ݹ���ֻ����һ��prev

      //��ÿ�εݹ�֮ǰ����¼��ǰ����λ��
        prev = cur;
        //��Ҫ����һ�εݹ鿴����һ�εĸı䣬����Ҫ�����ã���Ȼ������

     //��ָ��ָ�����ڵ�ǰ�����ɵģ�����ָ���ָ�����ں�һ�������ɵġ�
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
