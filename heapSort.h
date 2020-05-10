#ifndef HEAPSORT_H
#define HEAPSORT_H

//               root
// index * 2 + 1     index * 2 + 2

// 4,5,3,6,1,2,9,7,0,8
//            4
//       5         3
//    6     1   2     9
//  7  0  8

template <typename T>
void down(unsigned long long& _compares, unsigned long long& _swaps, int _length, int _root, T* _data_ptr = nullptr)
{
    int newRootIndex = _root;
    int L = _root * 2 + 1;
    int R = _root * 2 + 2;
    if (L < _length && _data_ptr[L] > _data_ptr[newRootIndex]) newRootIndex = L;
    if (R < _length && _data_ptr[R] > _data_ptr[newRootIndex]) newRootIndex = R;

    _compares += 2;

    if (newRootIndex != _root)
    {
        _swaps++;
        swap(_data_ptr[_root], _data_ptr[newRootIndex]);
        down(_compares, _swaps, _length, newRootIndex, _data_ptr);
    }
}

template <typename T>
void heapSort(unsigned long long& _compares, unsigned long long& _swaps, int _length, T* _data_ptr = nullptr)
{
// - - - - - - - build heap - - - - - - - -
    for (int ix = _length - 2; ix >= 0; --ix)
    {
        down(_compares, _swaps, _length, ix, _data_ptr);
    }
// - - - - - - - - - - - - - - - - - - - -

    for (int ix = _length - 1; ix >= 0; --ix)
    {
        ++_swaps;
        swap(_data_ptr[ix], _data_ptr[0]);
        down(_compares, _swaps, ix, 0, _data_ptr);
    }
}


#endif // HEAPSORT_H
