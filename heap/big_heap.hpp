#ifndef _BIG_HEAP_
#define _BIG_HEAP_

#include <vector>
namespace SelfHeap {
    class BigHeap {
    public:
        void insert_item(int);
        int  pop_item();
        int  get_size();
        void clear();
        bool empty();

    public:
        BigHeap()
            : _size(0)
            , _items(std::vector<int>()) {
        }

        BigHeap(std::vector<int> items)
            : BigHeap() {
            for (int item : items) {
                this->_insert_item(item);
            }
        }

        virtual ~BigHeap() {
            _size = 0;
        }

    public:
        friend void exchange_item(BigHeap* big_heap, int, int);

    private:
        void _replace_root();
        void _fit_from_root();

    private:
        int  _get_size();
        void _insert_item(int);

    private:
        int              _size;
        std::vector<int> _items;
    };

    BigHeap* create_heap();
    BigHeap* create_heap(std::vector<int>);
    void     delete_heap(BigHeap*);

}; // namespace SelfHeap

#endif