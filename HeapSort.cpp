#include "HeapSort.h"

#include <queue>
#include <string>

using namespace std;

HeapSort::~HeapSort() {
    queue <treenode*> q;
    if (root_) {q.push(root_);}
    while (!q.empty()) {
        treenode *current = q.front();
        if (current->left) {q.push(current->left);}
        if (current->right) {q.push(current->right);}
        q.pop();
        delete current;
    }
}

void HeapSort::Create(int height, int row, int column) {
    treenode *root = new treenode();
    root->height = height;
    root->row = row;
    root->column = column;
    root->left = NULL;
    root->right = NULL;
    root_ = root;
    number_of_nodes_++;
}

void HeapSort::Add(int height, int row, int column) {
    number_of_nodes_++;
    treenode *current_node = root_;
    treenode *previous_node = NULL;
    bool is_it_left = true; // true for left, false for right 
    treenode *node_to_swapped_in = new treenode();
    node_to_swapped_in->height = height;
    node_to_swapped_in->row = row;
    node_to_swapped_in->column = column;
    node_to_swapped_in->left = NULL;
    node_to_swapped_in->right = NULL;
    while (current_node) {
        // need to swap with this current_node
        if (node_to_swapped_in->height < current_node->height) {
            node_to_swapped_in->left = current_node->left;
            node_to_swapped_in->right = current_node->right;
            current_node->left = NULL;
            current_node->right = NULL;
            if (previous_node == NULL) {
                root_ = node_to_swapped_in;
            } 
            else {
                if (is_it_left) {
                    previous_node->left = node_to_swapped_in;
                }
                else {
                    previous_node->right = node_to_swapped_in;
                }
            }
            treenode *temp = node_to_swapped_in;
            node_to_swapped_in = current_node;
            current_node = temp;
        }

        else if (current_node->left == NULL) {
            current_node->left = node_to_swapped_in;
            return;
        }
        else if (current_node->right == NULL) {
            current_node->right = node_to_swapped_in;
            return;
        }
        else if (node_to_swapped_in->height < current_node->left->height) {
            previous_node = current_node;
            current_node = current_node->left;
            is_it_left = true;
        }
        else if (node_to_swapped_in->height < current_node->right->height) {
            previous_node = current_node;
            current_node = current_node->right;
            is_it_left = false;
        }
        else if (current_node->left->height < current_node->right->height) {
            previous_node = current_node;
            current_node = current_node->right;
            is_it_left = false;
        }
        else { // (current_node->left->height >= current_node->right->height)
            previous_node = current_node;
            current_node = current_node->left;
            is_it_left = true;
        }
    }
    if (previous_node == NULL) {
        root_ = node_to_swapped_in;
    } 
    else {
        if (is_it_left) {
            previous_node->left = node_to_swapped_in;
        }
        else {
            previous_node->right = node_to_swapped_in;
        }
    }
    return;
}

vector<int> HeapSort::Pop() {
    if (number_of_nodes_==0) {
        vector<int> v;
        v.push_back(-1);
        v.push_back(-1);
        v.push_back(-1);
        return v;
    }
    else {
        vector<int> integer_vector_to_return;
        integer_vector_to_return.push_back(root_->height);
        integer_vector_to_return.push_back(root_->row);
        integer_vector_to_return.push_back(root_->column);
        treenode *parent = NULL;
        bool is_it_left = true; // true for left, false for right 
        treenode *left_child = root_->left;
        treenode *right_child = root_->right;
        number_of_nodes_--;
        while (true) {
            if (left_child==NULL && right_child==NULL) {
                break;
            }
            else if (left_child==NULL) {
                if (parent==NULL) {
                    root_ = right_child;
                }
                else {
                    if (is_it_left) {
                        parent->left = right_child;
                    }
                    else {
                        parent->right = right_child;
                    }
                }
                break;
            }
            else if (right_child==NULL) {
                if (parent==NULL) {
                    root_ = left_child;
                }
                else {
                    if (is_it_left) {
                        parent->left = left_child;
                    }
                    else {
                        parent->right = left_child;
                    }
                }
                break;
            }
            else {
                if (left_child->height <= right_child->height) {
                    treenode *new_left_child = left_child->left;
                    treenode *new_right_child = left_child->right;
                    if (parent==NULL) {
                        root_ = left_child;
                    }
                    else {
                        if (is_it_left) {
                            parent->left = left_child;
                        }
                        else {
                            parent->right = left_child;
                        }
                    }
                    left_child->right = right_child;
                    left_child->left = NULL;
                    parent = left_child;
                    is_it_left = true;
                    left_child = new_left_child;
                    right_child = new_right_child;
                }
                else { // (left_child->height > right_child->height)
                    treenode *new_left_child = right_child->left;
                    treenode *new_right_child = right_child->right;
                    if (parent==NULL) {
                        root_ = right_child;
                    }
                    else {
                        if (is_it_left) {
                            parent->left = right_child;
                        }
                        else {
                            parent->right = right_child;
                        }
                    }
                    right_child->left = left_child;
                    right_child->right = NULL;
                    parent = right_child;
                    is_it_left = false;
                    left_child = new_left_child;
                    right_child = new_right_child;
                }
            }
        }
        return integer_vector_to_return;
    }
}

vector<int> HeapSort::Peep() {
    if (number_of_nodes_==0) {
        vector<int> v;
        v.push_back(-1);
        v.push_back(-1);
        v.push_back(-1);
        return v;
    }
    else {
        vector<int> integer_vector_to_return;
        integer_vector_to_return.push_back(root_->height);
        integer_vector_to_return.push_back(root_->row);
        integer_vector_to_return.push_back(root_->column);
        return integer_vector_to_return;
    }
}