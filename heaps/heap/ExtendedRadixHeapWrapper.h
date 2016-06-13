#ifndef HEAPS_EXTENDEDRADIXHEAPWRAPPER_H
#define HEAPS_EXTENDEDRADIXHEAPWRAPPER_H

#include <cstddef>
#include "util.h"

template <class T> class ExtendedRadixHeapWrapper {
public:
    ExtendedRadixHeapWrapper(size_t size=0) : heap(new T){ }
    ~ExtendedRadixHeapWrapper() { delete heap; }
    void insert(const Key x){
        heap->insert(x, heap);
    }
    Key delete_min(){
        return heap->delete_min();
    }
private:
    T * heap;
};


#endif //HEAPS_EXTENDEDRADIXHEAPWRAPPER_H
