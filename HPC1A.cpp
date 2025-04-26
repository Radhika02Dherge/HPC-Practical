#include <iostream>
#include <queue>
#include <omp.h>
using namespace std;

class node {
public:
    int data;
    node *left, *right;
    node(int val) : data(val), left(NULL), right(NULL) {}
};

class Breadthfs {
public:
    node* insert(node* root, int data) {
        if (!root) return new node(data);
        if (data < root->data)
            root->left = insert(root->left, data);
        else
            root->right = insert(root->right, data);
        return root;
    }
};

void bfs(node* root) {
    if (!root) return;
    queue<node*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            node* curr;
            #pragma omp critical
            {
                curr = q.front();
                q.pop();
                cout << "\t" << curr->data;
            }
            #pragma omp critical
            {
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
    }
}

int main() {
    node* root = NULL;
    Breadthfs tree;
    int data;
    char ans;
    do {
        cout << "\nEnter data: ";
        cin >> data;
        root = tree.insert(root, data);
        cout << "Insert more? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    
    double start = omp_get_wtime();
    bfs(root);
    double end = omp_get_wtime();

    cout << "\nExecution Time: " << (end - start) << " seconds\n";

    return 0;
}
