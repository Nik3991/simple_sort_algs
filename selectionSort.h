#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H
#include <iostream>

template <typename T>
void selectionSort(unsigned long long& _compares, unsigned long long& _swaps, int _length, T* _data_ptr = nullptr)
{
    for (int ix = 0; ix < _length - 1; ++ix)
    {
        int min_element_index = ix;
        for (int iy = ix + 1; iy < _length; ++iy)
        {
            if (_data_ptr[iy] < _data_ptr[min_element_index])
            {
                min_element_index = iy;
            }
            ++_compares;
        }
        if (ix != min_element_index)
        {
            swap(_data_ptr[ix], _data_ptr[min_element_index]);
            ++_swaps;
        }
    }
}

#endif // SELECTIONSORT_H
