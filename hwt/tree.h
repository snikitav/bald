#ifndef __HWT_TREE_
#define __HWT_TREE_

#include "algorithm"

namespace hwt {

class HwtTree final {
private:
    class Node final {
    public:
        Node(int key): key_(key), height_(1), subtree_size_(1), parent_(nullptr),
                       left_(nullptr), right_(nullptr) {};

        Node(const Node& from): Node(from.key_) {};

        int getKey() {
            return key_;
        }

        int getHeight() {
            return height_;
        }

        int getHeightDiff() {
            return std::abs(getLeftHeight() - getRightHeight());
        }

        int getLeftHeight() {
            return hasLeft() ? left_->getHeight() : 0;
        }

        int getRightHeight() {
            return hasRight() ? right_->getHeight() : 0;
        }

        int getLeftSubtreeSize() {
            return hasLeft() ? left_->getSubtreeSize() : 0;
        }

        int getRightSubtreeSize() {
            return hasRight() ? right_->getSubtreeSize() : 0;
        }

        int getSubtreeSize() {
            return subtree_size_;
        }

        Node* getParent() {
            return parent_;
        }

        Node* getLeft() {
            return left_;
        }

        Node* getRight() {
            return right_;
        }

        bool hasLeft() {
            return getLeft() != nullptr;
        }

        bool hasRight() {
            return getRight() != nullptr;
        }

        bool hasParent() {
            return getParent() != nullptr;
        }

        void setParent(Node* new_parent) {
            parent_ = new_parent;
        }

        void setLeft(Node* new_left) {
            left_ = new_left;
            computeHeight();
        }

        void setRight(Node* new_right) {
            right_ = new_right;
            computeHeight();
        }

        void turnRight() {
            Node* parent = getParent();
            Node* left = getLeft();

            setLeft(left->getRight());
            if (getLeft()) {
                getLeft()->setParent(this);
            }
            left->setRight(this);
            left->setParent(parent);
            setParent(left);

            if (parent) {
                if (parent->getLeft() == this) {
                    parent->setLeft(left);
                } else {
                    parent->setRight(left);
                }
            }

        }

        void turnLeft() {
            Node* parent = getParent();
            Node* right = getRight();

            setRight(right->getLeft());
            if (getRight()) {
                getRight()->setParent(this);
            }
            right->setLeft(this);
            right->setParent(parent);
            setParent(right);

            if (parent) {
                if (parent->getLeft() == this) {
                    parent->setLeft(right);
                } else {
                    parent->setRight(right);
                }
            }
        }

        void balance() {
            computeHeight();

            while (getHeightDiff() > 1) {
                if (getLeftHeight() > getRightHeight()) {
                    turnRight();
                } else {
                    turnLeft();
                }
            }
        }

    private:
        void computeHeight() {
            Node* tmp = this;
            while (tmp != nullptr) {
                tmp->height_ = std::max(tmp->getLeftHeight(), tmp->getRightHeight()) + 1;
                tmp->subtree_size_ = tmp->getLeftSubtreeSize() + tmp->getRightSubtreeSize() + 1;
                tmp = tmp->getParent();
            }
        }

        int key_;
        int height_;
        int subtree_size_;
        Node* parent_;
        Node* left_;
        Node* right_;
    };
public:
    HwtTree() {};
    HwtTree(const HwtTree& from) {
        Node* cur_from = *from.head_;
        if (cur_from == nullptr) {
            return;
        }

        Node* cur_node = new Node(*cur_from);
        *head_ = cur_node;

        while (cur_from != nullptr) {
            while (cur_from->hasLeft() && !cur_node->hasLeft()) {
                cur_from = cur_from->getLeft();
                cur_node->setLeft(new Node(*cur_from));
                cur_node->getLeft()->setParent(cur_node);
                cur_node = cur_node->getLeft();
            }

            while (cur_from->hasRight() && !cur_node->hasRight()) {
                cur_from = cur_from->getRight();
                cur_node->setRight(new Node(*cur_from));
                cur_node->getRight()->setParent(cur_node);
                cur_node = cur_node->getRight();
            }

            cur_from = cur_from->getParent();
            cur_node = cur_node->getParent();
        }
    }
    HwtTree& operator=(const HwtTree& rhs) {
        HwtTree tmp(rhs);
        *head_ = tmp.head_underlying_;
        tmp.head_underlying_ = nullptr;
        return *this;
    }
    void addKey(int key);
    // key < 1 == 0
    // key >= max(Node.key) = max(Node.key)
    int getOrderStatistic(int key) const;
    int getNumLess(int key) const;
    void setHead(Node* node) {
        *head_ = node;
    }
    Node* getHead() const {
        return *head_;
    }
    ~HwtTree();
private:
    Node* head_underlying_ = nullptr;
    Node** head_ = &head_underlying_;
};

}  // namespace hwt

#endif // __HWT_TREE_
