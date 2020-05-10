#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

template <typename T>
int binarySearch(int _length, const T& _value, unsigned long long& _compares, T* _data_ptr = nullptr)
{
    int middle = _length / 2;

    if (_length > 0)
    {
        ++_compares;
        if (_data_ptr[middle] != _value)
        {
            ++_compares;
            if (_data_ptr[middle] < _value)
            {
                return middle + 1 + binarySearch((_length & 1) ? middle : middle - 1, _value, _compares, _data_ptr + middle + 1);
            } else
            {
                return binarySearch(middle, _value, _compares, _data_ptr);
            }
        }
    }

    return middle;
}

template <typename T>
void insertionSort(unsigned long long& _compares, unsigned long long& _swaps, int _length, T* _data_ptr = nullptr)
{
    for (int ix = 1; ix < _length; ++ix)
    {
        int index = binarySearch(ix, _data_ptr[ix], _compares, _data_ptr);
        if (index != ix)
        {
            T tmp = _data_ptr[ix];
            memcpy(_data_ptr + index + 1, _data_ptr + index, (ix - index) * sizeof (T));
            _data_ptr[index] = tmp;
            ++_swaps;
        }
    }
}

#endif // INSERTIONSORT_H
