// src/memory/memory_index.cpp — YOU IMPLEMENT. Spec §4.3.

#include "memory/memory_index.h"

MemoryIndex::~MemoryIndex() {
    // TODO: free every node (post-order: both children before the node).
    clear();
}

bool MemoryIndex::insert(MemoryRecord rec) {
    // TODO: walk down from root_ (smaller ids left, larger right). Equal id:
    // return false and change nothing. Otherwise attach a new Node where the
    // walk fell off the tree, ++count_, return true.
    // Clue: memory ids arrive as 1, 2, 3, ..., so the tree is one long right
    // spine. A loop handles 5,000 nodes easily; so does recursion.
    if (root_ == nullptr){
        root_ = new Node{rec};
        count_++;
        return true;
    }
    Node *nowNode = root_;
    while (1){
        if (nowNode->rec.id == rec.id){
            return false;
        }
        if (nowNode-> rec.id > rec.id){
            if (nowNode->left == nullptr){
                nowNode->left = new Node{rec};
                count_++;
                return true;
            } else {
                nowNode = nowNode->left;
            }
        } else {
            if (nowNode->right == nullptr){
                nowNode->right = new Node{rec};
                count_++;
                return true;
            } else {
                nowNode = nowNode->right;
            }
        }
    }
}

const MemoryRecord* MemoryIndex::find(std::uint64_t id) const {
    // TODO
    //(void)id;
    if (root_ == nullptr){
        return nullptr;
    }
    Node *findNode = root_;
    while (1){
        if (findNode->rec.id == id){
            return &findNode->rec;
        } else {
            if ((findNode->rec.id < id)&&(findNode->right == nullptr)){
                return nullptr;
            }
            if ((findNode->rec.id > id)&&(findNode->left == nullptr)){
                return nullptr;
            }
            if (findNode->rec.id > id){
                findNode = findNode->left;
            }
            else if ((findNode->rec.id < id)){
                findNode = findNode->right;
            }
        }
    }
    return nullptr;
}

bool MemoryIndex::remove(std::uint64_t id) {
    // TODO: leaf, one child, two children (use the in-order successor or
    // predecessor). Spec Appendix C draws all three.
    // Clue: the successor (leftmost node of the right subtree) has no left
    // child but MAY have a right child: that child takes its place.
    // Clue: --count_ exactly once per successful remove. Counting inside
    // the helper AND here double-counts the two-children case.
    // Clue: when the removed node is the root, root_ itself must change.

    // if (find(id) == nullptr){
    //     return false;
    // } else {
    //     Node *removeNode = root_;
    //     while (1){
    //         if (removeNode->rec.id == id){
    //             if ((removeNode->right == nullptr) && (removeNode->left == nullptr)){ //leaf 
    //                 removeNode = nullptr;
    //             }
    //             if ((removeNode->right == nullptr) && !(removeNode->left == nullptr)){ //1 child 
    //                 if (findNode->rec.id > id){
    //                     findNode = findNode->left;
    //                 }
    //             }
    //             if (!(removeNode->right == nullptr) && (removeNode->left == nullptr)){  //1 child 
    //                 if (findNode->rec.id > id){
    //                     findNode = findNode->left;
    //                 }
    //             } else {  // 2 children
    //                 if (findNode->rec.id > id){
    //                     findNode = findNode->left;
    //                 }
    //             }
    //         } else {
    //         if ((findNode->rec.id < id)&&(findNode->right == nullptr)){
    //             return nullptr;
    //         }
    //         if ((findNode->rec.id > id)&&(findNode->left == nullptr)){
    //             return nullptr;
    //         }
    //         if (findNode->rec.id > id){
    //             findNode = findNode->left;
    //         }
    //         else if ((findNode->rec.id < id)){
    //             findNode = findNode->right;
    //         }
    //     }
    //     }
    // }
    (void)id;
    return false;


}

std::size_t MemoryIndex::size() const noexcept { return count_; }

std::size_t MemoryIndex::height() const {
    return heightNode(root_);

}

std::size_t MemoryIndex::heightNode(const Node* n){
    if (n == nullptr){
        return 0;
    }
    std::size_t leftHeight = heightNode(n->left);
    std::size_t rightHeight = heightNode(n->right);
    std::size_t max = 0;

    if (leftHeight > rightHeight){
        max = leftHeight + 1;
    } else {
        max = rightHeight + 1;
    }

    return max;
}

void MemoryIndex::for_each_in_order(const std::function<void(const MemoryRecord&)>& fn) const {
    // TODO: left subtree, then fn(node->rec), then right subtree.
    std::function<void(const MemoryRecord&)> walk;

    walk = & const (Node*n){
        if (n == nullptr){
            return;
        } 
        for_each_in_order(n->left);
        fn(n->rec)
        for_each_in_order(n->right);
    }
    walk(root_);


    //
}

void MemoryIndex::clear() {
    // TODO
    // Clue: after freeing the nodes, set root_ = nullptr and count_ = 0, or
    // the destructor frees them a second time.
    destroy(root_); 
    root_ = nullptr;
    count_ = 0;
}

void MemoryIndex::destroy(const Node* n){
    if (n == nullptr){
        return;
    }
    destroy(n->left);
    destroy(n->right);
    delete n;
}
