//Требование для всех вариантов Задачи 4
//Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса.
//Решение должно поддерживать передачу функции сравнения снаружи.
//Куча должна быть динамической.
//
//4.1 Слияние массивов.
//Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
//Требования: время работы O(N* logK).Ограничение на размер кучи O(K)..
//Формат входных данных : Сначала вводится количество массивов K.Затем по очереди размер каждого массива
//  и элементы массива.Каждый массив упорядочен по возрастанию.
//Формат выходных данных : Итоговый отсортированный массив.
//
//in:
//3
//1
//6
//2
//50 90
//3
//1 10 70
//
//out:
//1 6 10 50 70 90

#include <iostream>

bool Compare(int left, int right) {
    if (left > right) return true;
    return false;
}

template <typename T>
class DynamicArray {
public: 
    DynamicArray();
    ~DynamicArray();

    int GetLen() const { return len; };
    int GetCapacity() const { return capacity; }

    T & operator[](int index);
    T & operator= (const DynamicArray<T>& darr);

    void PushBack(T elem);
    void DeleteLast() { len--; };
private:
    T* arr;
    int len;
    int capacity;

    void Grow();
};

template <typename T>
class Heap {
public:
    Heap() { ptComparator = Compare; };
    Heap(bool (*ptc)(T left, T right));
    Heap(bool (*ptc)(T left, T right), const DynamicArray<T>& darr) { ptComparator = ptc; arr = darr; };
    Heap(const DynamicArray<T>& darr);
    ~Heap() = default;

    void Insert(T elem);

    T ExtractRoot();

    T PeekRoot() const;

private:
    DynamicArray<T> arr;
    bool (*ptComparator)(T left, T right);

    void BuildHeap();
    void SiftDown(int i);
    void SiftUp(int i);
};


template <typename T>
DynamicArray<T>::DynamicArray() {
    arr = new T[2];
    len = 0;
    capacity = 2;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] arr;
}

template <typename T>
void DynamicArray<T>::Grow() {
    T* arr_new = new T[capacity * 2];

    for (int i = 0; i < len; i++){
        arr_new[i] = arr[i];
    }

    capacity *= 2;

    delete[] arr;
    arr = arr_new;

    return;
}

template <typename T>
void DynamicArray<T>::PushBack(T elem) {
    if (len < capacity) {
        arr[len++] = elem;
    }
    else {
        Grow();
        arr[len++] = elem;
    }
    return;
}

template <typename T>
T & DynamicArray<T>::operator[] (int index) {
    return arr[index];
}

template <typename T>
T & DynamicArray<T>::operator= (const DynamicArray<T> & darr) {
    T* new_arr = new T[darr.GetCapacity()];

    for (int i = 0; i < darr.GetLen(); i++) {
        new_arr[i] = darr[i];
    }

    len = darr.GetLen();
    capacity = darr.GetCapacity();

    delete[] arr;

    arr = new_arr;
    return;
}

template <typename T>
Heap<T>::Heap(bool (*ptc)(T left, T right)) {
    ptComparator = ptc;
}

template <typename T>
Heap<T>::Heap(const DynamicArray<T>& darr) {
    arr = darr;
    ptComparator = Compare;
}

template <typename T>
T Heap<T>::PeekRoot() const {
    if (arr.GetLen != 0) return arr[0];
    return NULL;
}

template <typename T>
void Heap<T>::SiftUp(int index)
{
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (ptComparator(arr[index], arr[parent]))
            return;
        std::swap(arr[index], arr[parent]);
        index = parent;
    }
}

template <typename T>
void Heap<T>::SiftDown(int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // Ищем большего сына, если такой есть.
    int largest = i;
    if (left < arr.GetLen() && !ptComparator(arr[left], arr[largest])) {
        largest = left;
    }
    if (right < arr.GetLen() && !ptComparator(arr[right], arr[largest])) {
        largest = right;
    }
    // Если больший сын есть, то проталкиваем корень в него.
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        SiftDown(largest);
    }
}

template <typename T>
void Heap<T>::Insert(T elem) {
    arr.PushBack(elem);
    SiftUp(arr.GetLen() - 1);
}

template <typename T>
T Heap<T>::ExtractRoot()
{
    if (arr.GetLen() != 0) {
        T result = arr[0];

        arr[0] = arr[arr.GetLen() - 1];
        arr.DeleteLast();

        if (arr.GetLen() != 0) {
            SiftDown(0);
        }

        return result;
    }

    return NULL;
}

template <typename T>
void Heap<T>::BuildHeap()
{   
    for (int i = arr.Size() / 2 - 1; i >= 0; --i) {
        SiftDown(i);
    }
}

int main()
{   
    int n = 0;
    std::cin >> n;
    int count = 0;

    Heap<int> h(Compare);

    for (int i = 0; i < n; i++) {
        int k = 0;
        std::cin >> k;

        for (int j = 0; j < k; j++) {
            int b = 0;
            std::cin >> b;
            h.Insert(b);
            count++;
        }
    }

    for (int i = 0; i < count; i++) {
        std::cout << h.ExtractRoot() << " ";
    }
}