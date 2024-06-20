#include "tree.h"
#include <iostream>

void printTests(const hwt::HwtTree& tree) {
    std::cout << "num less " << tree.getNumLess(-1000) << std::endl;
    std::cout << "num less " << tree.getNumLess(0) << std::endl;
    std::cout << "num less " << tree.getNumLess(5) << std::endl;
    std::cout << "num less " << tree.getNumLess(-5) << std::endl;
    std::cout << "num less " << tree.getNumLess(1000) << std::endl;
    std::cout << tree.getOrderStatistic(1) << std::endl;
    std::cout << tree.getOrderStatistic(4) << std::endl;
    std::cout << tree.getOrderStatistic(6) << std::endl;
    std::cout << tree.getOrderStatistic(100) << std::endl;
    std::cout << "===============================================================" << std::endl;
}

int main() {
    hwt::HwtTree tree;
    tree.addKey(0);
    tree.addKey(-1);
    tree.addKey(-2);
    tree.addKey(-3);
    tree.addKey(1);
    tree.addKey(2);
    tree.addKey(3);
    tree.addKey(-4);
    tree.addKey(-5);
    tree.addKey(4);
    tree.addKey(5);
    tree.addKey(101);
    printTests(tree);
    hwt::HwtTree tree2{tree};
    printTests(tree2);
    tree = tree2;
    printTests(tree);
    return 0;
}
