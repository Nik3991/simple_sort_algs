#include <iostream>
#include <chrono>

#include "VectorArray.h"
#include "bubbleSort.h"
#include "selectionSort.h"
#include "heapSort.h"
#include "insertionSort.h"
#include "shellSort.h"

using namespace std;
using namespace std::chrono;

template <typename T>
bool isArraySorted(int _length, T* _data_ptr)
{
    bool result = true;
    T value = _data_ptr[0];
    for (int ix = 1; ix < _length; ++ix)
    {
        if (_data_ptr[ix] < value)
        {
            result = false;
            break;
        }
        value = _data_ptr[ix];
    }
    cout << "isArraySorted = " << result << endl << endl;

    return result;
}

void shellSortWrapper(unsigned long long& _compares, unsigned long long& _swaps, int _length, int* _data_ptr)
{
//    // N / 2
//    // auto size_n_2 = [](int _size){return _size / 2;};

    // 1,4,10,23,57,132,301,701
    int result = 0;
    int array[] {1,4,10,23,57,132,301,701} ;
    int index = 0;

    auto size_n_2 = [&_length, &result, &array, &index](int _size)
    {
        (void)_size;
        result = index > 7 ? result * 2 : array[index];
        ++index;
        //cout << " result = " << result << endl;
        return _length / result;
    };

    // 1,3,5,9,17,33,65

//    int result = 0;
//    int array[] {1,3,5,9,17,33,65} ;
//    int index = 0;

//    auto size_n_2 = [&_length, &result, &array, &index](int _size)
//    {
//        (void)_size;
//        result = index > 6 ? result * 2 : array[index];
//        ++index;
//        //cout << " result = " << result << endl;
//        return _length / result;
//    };


    shellSort(_compares, _swaps, _length, _data_ptr, size_n_2(_length), size_n_2);
}

typedef void(*PointerToSortFunction)(unsigned long long&, unsigned long long&, int, int*);

template <typename Collection>
void testOnlineSorting(PointerToSortFunction abstractSortFunction, Collection& _c, const char* _name, int _count)
{
    unsigned long long compares = 0, swaps = 0;
    auto start = high_resolution_clock::now();
    for (int ix = _count; ix >= 0; --ix)
    {
        _c.add(ix, _c.size());
        abstractSortFunction(compares, swaps, _c.size(), _c.data());
    }
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end - start);
    cout << "Test online sorting:" << endl;
    cout << _name << ": time = " << time.count() << " ms" << " compares = " << compares << " swaps = " << swaps << endl;
    isArraySorted(static_cast<int>(_c.size()), _c.data());
}

template <typename Collection>
void testUnsortedArray(PointerToSortFunction abstractSortFunction, Collection& _c, const char* _name, int _count, int _sortedPart)
{
    int sortedCount = _count / 100 * _sortedPart;
    for (int ix = 0; ix < _count - sortedCount; ++ix)
    {
        _c.add(ix, 0);
    }

    for (int ix = 0, value = _count - sortedCount; ix < sortedCount; ++ix)
    {
        _c.add(value, _c.size());
        ++value;
    }

    unsigned long long compares = 0, swaps = 0;
    auto start = high_resolution_clock::now();
    abstractSortFunction(compares, swaps, static_cast<int>(_c.size()), _c.data());
    auto end = high_resolution_clock::now();

    auto time = duration_cast<milliseconds>(end - start);
    cout << "Test unsorted array sorting:" << endl;
    cout << _name << ": time = " << time.count() << " ms" << " compares = " << compares << " swaps = " << swaps << endl;
    isArraySorted(static_cast<int>(_c.size()), _c.data());

    _c.clear();
}

template <typename Collection>
void testSortedArray(PointerToSortFunction abstractSortFunction, Collection& _c, const char* _name, int _count)
{
    for (int ix = 0; ix < _count; ++ix)
    {
        _c.add(ix, _c.size());
    }

    unsigned long long compares = 0, swaps = 0;
    auto start = high_resolution_clock::now();
    abstractSortFunction(compares, swaps, static_cast<int>(_c.size()), _c.data());
    auto end = high_resolution_clock::now();

    auto time = duration_cast<milliseconds>(end - start);
    cout << "Test sorted array sorting:" << endl;
    cout << _name << ": time = " << time.count() << " ms" << " compares = " << compares << " swaps = " << swaps << endl;
    isArraySorted(static_cast<int>(_c.size()), _c.data());

    _c.clear();
}

int main()
{
    int countOfElements = 100000;
    int sortedPart = 0; // percents
    VectorArray<int> v(countOfElements);

    cout << " ------------ test unsorted array sorting ------------ " << endl << endl;

    testUnsortedArray(bubbleSort,       v, "bubble sort",    countOfElements, sortedPart);
    testUnsortedArray(selectionSort,    v, "selection sort", countOfElements, sortedPart);
    testUnsortedArray(insertionSort,    v, "insertion sort", countOfElements, sortedPart);
    testUnsortedArray(shellSortWrapper, v, "shell sort",     countOfElements, sortedPart);
    testUnsortedArray(heapSort,         v, "heap sort",      countOfElements, sortedPart);

    cout << " ------------ test 5% sorted array sorting ------------ " << endl << endl;

    sortedPart = 5;
    testUnsortedArray(bubbleSort,       v, "bubble sort",    countOfElements, sortedPart);
    testUnsortedArray(selectionSort,    v, "selection sort", countOfElements, sortedPart);
    testUnsortedArray(insertionSort,    v, "insertion sort", countOfElements, sortedPart);
    testUnsortedArray(shellSortWrapper, v, "shell sort",     countOfElements, sortedPart);
    testUnsortedArray(heapSort,         v, "heap sort",      countOfElements, sortedPart);

    cout << " ------------ test sorted array sorting ------------ " << endl << endl;

    testSortedArray(bubbleSort,       v, "bubble sort",    countOfElements);
    testSortedArray(selectionSort,    v, "selection sort", countOfElements);
    testSortedArray(insertionSort,    v, "insertion sort", countOfElements);
    testSortedArray(shellSortWrapper, v, "shell sort",     countOfElements);
    testSortedArray(heapSort,         v, "heap sort",      countOfElements);

    cout << " ------------ test online sorting ------------ " << endl << endl;

    testOnlineSorting(bubbleSort,       v, "bubble sort",    countOfElements / 10);
    testOnlineSorting(selectionSort,    v, "selection sort", countOfElements / 10);
    testOnlineSorting(insertionSort,    v, "insertion sort", countOfElements / 10);
    testOnlineSorting(shellSortWrapper, v, "shell sort",     countOfElements / 10);
    testOnlineSorting(heapSort,         v, "shell sort",     countOfElements / 10);

    return 0;
}
