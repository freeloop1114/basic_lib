/*
 * loser tree impl
 * */
#ifndef BASIC_LIB_LOSER_TREE_H
#define BASIC_LIB_LOSER_TREE_H
#include <vector>
using std::vector;

namespace basic_lib {

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    int loser_leaf;
};


template<class Leaf, class Value>
class LoserTree {
public:
    LoserTree() {}
    ~LoserTree() {}

    bool createTree(const vector<Leaf*>& leafs);
    Value getNext(); 

private:
    bool createIndexNode(const vector<TreeNode*>& input,
                        vector<TreeNode*>* output);
    void clearIndexNode(const vector<TreeNode*>& nodes);
private:
    vector<Leaf*> m_leaf_nodes;
    TreeNode* m_root;
    bool m_desc;
};


template<class Leaf, class Value>
bool LoserTree<Leaf, Value>::createTree(
                    const vector<Leaf*>& leafs)
{
    if (leafs.empty()) {
        return false;
    }

    vector<TreeNode*> tree_nodes;
    for (int i=0; i<leafs.size(); ++i) {
        TreeNode* node = new TreeNode();
        tree_nodes.push_back(node);    
    }

    do {
        vector<TreeNode*> output_nodes;
        if (!this->createIndexNode(tree_nodes, output_nodes)) {
            this->clearIndexNode(tree_nodes);
            return false;
        }
        if (output_nodes.empty()) {
            this->clearIndexNode(tree_nodes);
            return false;
        }
        // if output size is 1, means this is root node
        if (1 == output_nodes.size()) {
            m_root = output_nodes[0]; 
            break;
        }
    } while (true);
}


template<class Leaf, class Value>
bool LoserTree<Leaf, Value>::createIndexNode(
                    const vector<TreeNode*>& input,
                    vector<TreeNode*>* output)
{
    if (nullptr == output || input.empty()) {
        return false;
    } 

    int size = input.size();
    int end = size % 2 == 1 ? size - 1 : size;
    for (int i=0; i<end; i+=2) {
        TreeNode* node = new TreeNode();
        node->left = input[i];
        node->right = input[i+1];
        output->push_back(node);
    }    

    if (end != size) {
        output->push_back(input[end]); 
    }

    return true;
}

template<class Leaf, class Value>
void LoserTree<Leaf, Value>::clearIndexNode(
                    const vector<TreeNode*>& nodes)
{
    
}


}

#endif
