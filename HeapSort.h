#include <vector>

using namespace std;

struct treenode {
    int height;
    int row;
    int column;
    treenode *left;
    treenode *right;
};

class HeapSort {
private:
    treenode *root_;
    int number_of_nodes_ = 0;
public:
    HeapSort():root_(NULL) {}
    HeapSort(int height, int row, int column):root_(NULL) {Create(height, row, column);}
    ~HeapSort();
    int get_number_of_nodes() {return number_of_nodes_;}
    void Create(int height, int row, int column);
    void Add(int height, int row, int column);
    vector<int> Peep();
    vector<int> Pop();
};

