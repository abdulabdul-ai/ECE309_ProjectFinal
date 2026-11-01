// src/memory/memory_index.cpp — YOU IMPLEMENT. Spec §4.3.

#include "memory/memory_index.h"

MemoryIndex::~MemoryIndex() {
    // TODO: free every node (post-order: both children before the node).
    (void)root_;
}

bool MemoryIndex::insert(MemoryRecord rec) {
    // TODO: walk down from root_ (smaller ids left, larger right). Equal id:
    // return false and change nothing. Otherwise attach a new Node where the
    // walk fell off the tree, ++count_, return true.
    // Clue: memory ids arrive as 1, 2, 3, ..., so the tree is one long right
    // spine. A loop handles 5,000 nodes easily; so does recursion.
    if (root_ == nullptr){
        root_ = new Node(rec);
        count_++;
        return true;
    }
    Node *now = root_;
    while (1){
        if (now->rec.id == rec.id){
            return false;
        }
        if (now-> rec.id > rec.id){
            if (now->left == nullptr){
                now->left = new Node(rec);
                count_++;
                return true;
            } else {
                now = rec;
            }
        } else {
            if (now->right == nullptr){
                now->right = new Node(rec);
                count_++;
                return true;
            } else {
                now = rec;
            }
        }
    }
}

const MemoryRecord* MemoryIndex::find(std::uint64_t id) const {
    // TODO
    (void)id;
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
    (void)id;
    return false;
}

std::size_t MemoryIndex::size() const noexcept { return count_; }

std::size_t MemoryIndex::height() const {
    // TODO: empty tree = 0, one node = 1, otherwise 1 + the taller child.
    return 0;
}

void MemoryIndex::for_each_in_order(const std::function<void(const MemoryRecord&)>& fn) const {
    // TODO: left subtree, then fn(node->rec), then right subtree.
    (void)fn;
}

void MemoryIndex::clear() {
    // TODO
    // Clue: after freeing the nodes, set root_ = nullptr and count_ = 0, or
    // the destructor frees them a second time.
}
