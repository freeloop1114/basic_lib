#include "loser_tree.h"
using namespace basic_lib;
using namespace std;

class TestDocList {
public:
    TestDocList() : m_offset(0) {
        m_values.clear();
    }

    int getNext() {
        if (m_offset < m_values.size()) {
            return m_values[m_offset++];
        } else {
            return 0;   
        }
    }

    vector<int> m_values;
    int m_offset;
};

// unittest for loser tree
int main()
{
    LoserTree<TestDocList, int> tree;
    TestDocList doclist1;
    doclist1.m_values.push_back(1);

    TestDocList doclist2;
    doclist2.m_values.push_back(2);

    TestDocList doclist3;
    doclist3.m_values.push_back(3);
    vector<TestDocList*> input;
    input.push_back(&doclist1);
    input.push_back(&doclist2);
    input.push_back(&doclist3);

    tree.createTree(input);
    tree.printTree();
    return 0;
}
