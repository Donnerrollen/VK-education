//  2_3.Даны два массива неубывающих целых чисел, упорядоченные по возрастанию.A[0..n - 1]
//  и B[0..m - 1].  n >> m.Найдите их пересечение.
// 
//  Требования: Время работы : O(m* log k), где k - позиция элемента B[m - 1] в массиве A..В
//  процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента
//  B[i - 1].Внимание!В этой задаче для каждого B[i] сначала нужно определить диапазон для
//  бинарного поиска размером порядка k с помощью экспоненциального поиска, а потом уже
//  в нем делать бинарный поиск.
//
//  n, k ≤ 10000.
//  input:
//  5
//  3
//  1 2 3 4 5
//  1 3 5
// 
//  output:
//  1 3 5

#include <iostream>

// класс динамического массива
template <typename T>
class DynamicArray {
public:
    DynamicArray();
    DynamicArray(const DynamicArray& da_arr);
    ~DynamicArray();

    void Append(T el);
    const int GetLen();
    const int GetCapacity();
    T & operator[] (int index);
    DynamicArray& operator= (const DynamicArray& da_arr);

private:
    int capacity;
    int len;
    T * arr;
};

template <typename T>
DynamicArray<T>::DynamicArray() {
    this->capacity = 2;
    this->len = 0;
    this->arr = new T[2];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& da_arr) {
    delete[] arr;
    
    this->capacity = da_arr.capacity;
    this->len = da_arr.len;

    this->arr = new T[capacity];

    for (int i = 0; i < len; i++) {
        arr[i] = da_arr.arr[i];
    }
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] arr;
}

template <typename T>
void DynamicArray<T>::Append(T el) {
    if (len < capacity) {
        arr[len++] = el;
    }
    else {
        T * new_arr = new T[capacity * 2];
        
        for (int i = 0; i < len; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;

        capacity *= 2;
        arr = new_arr;
        arr[len++] = el;
    }
    return;
}

template <typename T>
const int DynamicArray<T>::GetCapacity() {
    return capacity;
}

template <typename T>
const int DynamicArray<T>::GetLen() {
    return len;
}

template <typename T>
T & DynamicArray<T>::operator[] (int index) {
    return arr[index];
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator= (const DynamicArray<T>& da_arr) {
    len = da_arr.len;
    capacity = da_arr.capacity;
    
    delete[] arr;
    arr = new T[capacity];

    for (int i = 0; i < len; i++) {
        arr[i] = da_arr.arr[i];
    }

    return *this;
}

//  Реализация алгоритма экспоненциального поиска   
int BinarySearch(int* A, int left, int right, int search_elem) {
    int mid = 0;
    while (true) {
        mid = (left + right) / 2;
    
        if (search_elem < A[mid]) {
            right = mid - 1;
        }
        else if (search_elem > A[mid]) {
            left = mid + 1;
        }
        else return mid;

        if (left > right) return -1;
    }
}

int ExponentialSearch(int * A, int left, int right, int search_elem) {
    if (left >= right) return -1;
    
    if (A[left] == search_elem) {
        return left;
    }

    int bound = 1;
    while (left + bound < right && A[left + bound] < search_elem) {
        bound *= 2;
    }

    return BinarySearch(A, left + bound / 2, std::min(left + bound, right - 1), search_elem);
}

//  Реализация алгоритма поиска пересечения двух массивов
DynamicArray<int> IntersectionArrays(int * A, int n, int * B, int m) {
    DynamicArray<int> res;
    int left = 0;
    int index_elem = 0;

    for (int i = 0; i < m; i++) {
        index_elem = ExponentialSearch(A, left, n, B[i]);

        if (index_elem != -1) {
            res.Append(B[i]);
            left = index_elem + 1;
        }

        if (left >= n) break;
    }
    
    return res;
}

int main()
{
    int n = 0;
    int m = 0;

    std::cin >> n >> m;

    int * A = new int[n];
    int * B = new int[m];

    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> B[i];
    }

    DynamicArray<int> res;
    res = IntersectionArrays(A, n, B, m);

    delete[] A;
    delete[] B;

    for (int i = 0; i < res.GetLen(); i++) {
        std::cout << res[i] << " ";
    }

    return 0;
}