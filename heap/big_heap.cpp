#include "big_heap.hpp"

#define MAX(a, b) (((a) >= (b)) ? (a) : (b))

inline int get_max(int a, int b) {
    return a >= b ? a : b;
}

static int get_parent_idx(int idx) {
    return idx > 0 ? (idx - 1) >> 1 : 0;
}

static int get_left_child_idx(int idx) {
    return (idx << 1) + 1;
}

static int get_right_child_idx(int idx) {
    return (idx << 1) + 2;
}

SelfHeap::BigHeap* SelfHeap::create_heap() {
    return new SelfHeap::BigHeap{};
}

SelfHeap::BigHeap* SelfHeap::create_heap(std::vector<int> items) {
    return new SelfHeap::BigHeap{ items };
}

void SelfHeap::delete_heap(SelfHeap::BigHeap* heap_ptr) {
    if (heap_ptr != nullptr) {
        delete (heap_ptr);
    }
}

// BigHeap
// private
int SelfHeap::BigHeap::_get_size() {
    return this->_size;
}

void SelfHeap::BigHeap::_insert_item(int item) {
    this->_items.push_back(item);
    ++this->_size;

    int child_idx = this->_get_size() - 1;
    int parent_idx = get_parent_idx(child_idx);
    assert(child_idx >= 0);
    assert(parent_idx >= 0);

    while (this->_items[child_idx] > this->_items[parent_idx]) {
        exchange_item(this, child_idx, parent_idx);

        child_idx = parent_idx;
        parent_idx = get_parent_idx(child_idx);
    }
}

void SelfHeap::BigHeap::_replace_root() {
    assert(this->_size > 0);
    exchange_item(this, 0, this->_size - 1);
}

void SelfHeap::BigHeap::_fit_from_root() {
    assert(this->_size >= 0);
    if (this->_size == 0) {
        return;
    }

    int parent_idx = 0;
    int left_child_idx = get_left_child_idx(parent_idx);
    int right_child_idx = get_right_child_idx(parent_idx);
    while (left_child_idx < this->_size) {
        if (right_child_idx < this->_size) {
            int max_item =
                get_max(get_max(this->_items[left_child_idx], this->_items[right_child_idx]),
                    this->_items[parent_idx]);
            if (max_item == this->_items[parent_idx]) {
                break;
            }
            if (max_item == this->_items[left_child_idx]) {
                exchange_item(this, parent_idx, left_child_idx);
                parent_idx = left_child_idx;
            }
            else { // max_item == right_item
                exchange_item(this, parent_idx, right_child_idx);
                parent_idx = right_child_idx;
            }
            left_child_idx = get_left_child_idx(parent_idx);
            right_child_idx = get_right_child_idx(parent_idx);
        }
        else {
            if (this->_items[parent_idx] >= this->_items[left_child_idx]) {
                break;
            }
            // parent < left_child
            exchange_item(this, parent_idx, left_child_idx);
            parent_idx = left_child_idx;
            left_child_idx = get_left_child_idx(parent_idx);
            right_child_idx = get_right_child_idx(parent_idx);
        }
    }
}

// private

// public
void SelfHeap::BigHeap::insert_item(int item) {
    this->_insert_item(item);
}

int SelfHeap::BigHeap::pop_item() {
    assert(this->_size > 0);
    this->_replace_root();
    int ret = this->_items[--this->_size];
    this->_items.pop_back();
    this->_fit_from_root();
    return ret;
}

int SelfHeap::BigHeap::get_size() {
    return this->_get_size();
}

bool SelfHeap::BigHeap::empty() {
    return this->_size == 0;
}

void SelfHeap::BigHeap::clear() {
    this->_size = 0;
    this->_items.clear();
}

void SelfHeap::exchange_item(SelfHeap::BigHeap* big_heap, int idx1, int idx2) {
    int size = big_heap->_size;
    assert(idx1 >= 0);
    assert(idx2 >= 0);
    assert(idx1 < size);
    assert(idx2 < size);
    int tmp = big_heap->_items[idx1];
    big_heap->_items[idx1] = big_heap->_items[idx2];
    big_heap->_items[idx2] = tmp;
}
// public

// BigHeap