#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

/**
 * A simple test driver for the BST class template.
 * P1 CSE 100 2013
 * Author: P. Kube (c) 2013
 */
int main() {
    int i = 10;

    BST<int> b;

    for (int j = 0; j <= i; j++) {
        int num = rand() % 100;
        cout << num << " ";
        b.insert(num);
    }
    cout << endl;

    cout << b.size() << " , " << b.height() << endl;

    b.inorder();
    cout << endl;
}
