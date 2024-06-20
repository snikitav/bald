#include "tree.h"
#include <iostream>

namespace hwt {

void HwtTree::addKey(int key) {
    if (getHead() == nullptr) {
        setHead(new Node(key));
        return;
    }

    Node* cur_node = getHead();
    Node* new_node = new Node(key);

    while (new_node->getParent() == nullptr) {
        if (cur_node->getKey() > key) {
            if (cur_node->getLeft() == nullptr) {
                cur_node->setLeft(new_node);
                new_node->setParent(cur_node);
            }
            cur_node = cur_node->getLeft();
        } else {
            if (cur_node->getRight() == nullptr) {
                cur_node->setRight(new_node);
                new_node->setParent(cur_node);
            }
            cur_node = cur_node->getRight();
        }
    }

    while(new_node != nullptr) {
        new_node->balance();
        setHead(new_node);
        new_node = new_node->getParent();
    }
}

int HwtTree::getOrderStatistic(int num) const {
    if ((num < 1) || (getHead() == nullptr)) {
        return 0;
    }

    Node* cur_node = getHead();

    while (num != cur_node->getLeftSubtreeSize() + 1) {
        while (num > cur_node->getLeftSubtreeSize() + 1) {
            num -= cur_node->getLeftSubtreeSize() + 1;
            if (cur_node->getRight()) {
                cur_node = cur_node->getRight();
            }
        }

        while (num <= cur_node->getLeftSubtreeSize()) {
            cur_node = cur_node->getLeft();
        }
    }

    return cur_node->getKey();
}

int HwtTree::getNumLess(int key) const {
    if (getHead() == nullptr) {
        return 0;
    }

    Node* cur_node = getHead();

    int memo = 0;

    while((cur_node != nullptr) && (cur_node->getKey() != key)) {
        while ((cur_node != nullptr) && (cur_node->getKey() < key)) {
            memo += cur_node->getLeftSubtreeSize() + 1;
            cur_node = cur_node->getRight();
        }

        while ((cur_node != nullptr) && (cur_node->getKey() > key)) {
            cur_node = cur_node->getLeft();
        }
    }

    int remain = cur_node != nullptr ? cur_node->getLeftSubtreeSize() : 0;

    return memo + remain;
}

HwtTree::~HwtTree() {
    Node *cur_node = *head_;
    while (cur_node != nullptr) {
        while (cur_node->getRight()) {
            cur_node = cur_node->getRight();
        }

        while (cur_node->getLeft()) {
            cur_node = cur_node->getLeft();
        }

        if (cur_node->getLeft() == nullptr && cur_node->getRight() == nullptr) {
            Node* parent = cur_node->getParent();
            if (parent != nullptr) {
                if (parent->getLeft() == cur_node) {
                    parent->setLeft(nullptr);
                } else {
                    parent->setRight(nullptr);
                }
            }
            delete cur_node;
            cur_node = parent;
        }
    }
}

}  // namespace hwt p *(*tree->head_)
