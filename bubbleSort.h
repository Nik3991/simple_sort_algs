#ifndef BUBBLESORT_H
#define BUBBLESORT_H

template <typename T>
void bubbleSort(unsigned long long& _compares, unsigned long long& _swaps, int _length, T* _data_ptr = nullptr)
{
    bool data_sorted = true;
    for (int ix = 0; ix < _length; ++ix)
    {
        for (int iy = 1; iy < _length - ix; ++iy)
        {
            if (_data_ptr[iy] < _data_ptr[iy - 1])
            {
                data_sorted = false;
                swap(_data_ptr[iy], _data_ptr[iy - 1]);
                ++_swaps;
            }
            ++_compares;
        }
        if (data_sorted)
        {
            break;
        }
    }
}

#endif // BUBBLESORT_H
