#ifndef SHELLSORT_H
#define SHELLSORT_H

template <typename T, typename F>
void shellSort(unsigned long long& _compares, unsigned long long& _swaps, int _length, T* _data_ptr, int _step, F step_updater)
{
    if (_step > 0)
    {
        for (int ix = 0; ix < _step; ++ix)
        {
            for (int ik = ix; ik < _length; ik += _step)
            {
                T tmp = _data_ptr[ik];
                for (int iy = ik - _step; iy >= 0; iy -= _step)
                {
                    ++_compares;
                    if (_data_ptr[iy + _step] < _data_ptr[iy])
                    {
                        _data_ptr[iy + _step] = _data_ptr[iy];
                        _data_ptr[iy] = tmp;
                        ++_swaps;
                    } else
                    {
                        break;
                    }
                }
            }
        }
    }
    if (_step > 1)
    {
        shellSort(_compares, _swaps, _length, _data_ptr, step_updater(_step), step_updater);
    }
}

#endif // SHELLSORT_H
