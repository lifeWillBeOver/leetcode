#include <iostream>
#include <queue>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "big_heap.hpp"

void test();

int main() {
    test();
}

void test() {
    const int BEGIN = 1000;
    const int END = 10000;
    const int STEP = 500;

    SelfHeap::BigHeap* heap = SelfHeap::create_heap();
    for (int i = BEGIN; i <= END; i += STEP) {
        std::priority_queue<int, std::vector<int>, std::less<int>> pq;
        heap->clear();
        srand((unsigned)time(NULL));
        for (int j = 0; j < i; j++) {
            int random = rand();
            pq.push(random);
            heap->insert_item(random);
        }

        fprintf(stderr, "## Case-%d\n", (i - BEGIN) / STEP + 1);
        if (pq.size() != heap->get_size()) {
            fprintf(stderr, "size(raw)=%d, size(pq)=%lu size(heap)=%d\n", i, pq.size(), heap->get_size());
            continue;
        }

        for (int j = 0; j < i; j++) {
            int heap_pop = heap->pop_item();
            if (pq.top() != heap_pop) {
                fprintf(stderr, "i=%d, j=%d, pqtop=%d, heappop=%d\n", i, j, pq.top(), heap_pop);
            }
            pq.pop();
        }

        // fprintf(stdout, "## pq  :");
        // while (!pq.empty()) {
        //     printf("%d, ", pq.top());
        //     pq.pop();
        // }

        // fprintf(stdout, "\n## heap:");
        // while (!heap->empty()) {
        //     fprintf(stdout, "%d, ", heap->pop_item());
        // }
        // fprintf(stdout, "\n");
    }
}