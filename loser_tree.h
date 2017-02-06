/*
 * loser tree impl
 * */
#ifndef BASIC_LIB_LOSER_TREE_H
#define BASIC_LIB_LOSER_TREE_H
#include <iostream>
#include <vector>
using namespace std;

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
    void printTree();

private:
    bool createIndexNode(const vector<TreeNode*>& input,
                        vector<TreeNode*>* output);
    void clearIndexNodes(const vector<TreeNode*>& nodes);
    void clearIndexNode(TreeNode* node);
    void printTreeNodes(const vector<TreeNode*>& nodes,
                        vector<TreeNode*>* next_level) const;
    //void printTreeNode(const TreeNode* node) const;
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
        if (!this->createIndexNode(tree_nodes, &output_nodes)) {
            this->clearIndexNodes(tree_nodes);
            return false;
        }
        if (output_nodes.empty()) {
            this->clearIndexNodes(tree_nodes);
            return false;
        }
        // if output size is 1, means this is root node
        if (1 == output_nodes.size()) {
            m_root = output_nodes[0]; 
            break;
        }
        tree_nodes = output_nodes;
    } while (true);
    
    this->printTree();
}



template<class Leaf, class Value>
void LoserTree<Leaf, Value>::printTree()
{
    vector<TreeNode*> src;
    vector<TreeNode*> next_level;
    src.push_back(m_root);
    do {
        next_level.clear();
        this->printTreeNodes(src, &next_level);
        src = next_level;
    } while (!src.empty());
}


/*
 *
 * private function impl
 *
 * */
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
void LoserTree<Leaf, Value>::clearIndexNodes(
                    const vector<TreeNode*>& nodes)
{
    for (auto iter = nodes.begin(); 
                    iter != nodes.end(); ++iter) {
        this->clearIndexNode(*iter);
    }
}


template<class Leaf, class Value>
void LoserTree<Leaf, Value>::clearIndexNode(
                    TreeNode* node)
{
    if (nullptr == node) {
        return;
    }

    if (nullptr != node->left) {
        this->clearIndexNode(node->left);
    }

    if (nullptr != node->right) {
        this->clearIndexNode(node->right);
    }

    delete node;
    node = nullptr;
} 


template<class Leaf, class Value>
void LoserTree<Leaf, Value>::printTreeNodes(
                    const vector<TreeNode*>& nodes,
                    vector<TreeNode*>* next_level) const
{
    if (nullptr == next_level) {
        return;
    }

    next_level->clear();
    for (int i = 0; i < nodes.size(); ++i) {
        cout << nodes[i]->loser_leaf << " ";
        next_level->push_back(nodes[i]->left);
        next_level->push_back(nodes[i]->right);
    }
    cout << endl;
}

/*
template<class Leaf, class Value>
void LoserTree<Leaf, Value>::printTreeNode(
                    TreeNode* node)
{
    if (nullptr != node) {
    }
}
*/

}

#endif
