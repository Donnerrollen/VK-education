//  Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды
//  push* и pop* .
//  Формат входных данных.
//  В первой строке количество команд n.n ≤ 1000000.
//  Каждая команда задаётся как 2 целых числа : a b.
//  a = 1 - push front
//  a = 2 - pop front
//  a = 3 - push back
//  a = 4 - pop back
//  Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
//  Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
//  Если дана команда pop*, то число b - ожидаемое значение.Если команда pop вызвана для пустой
//  структуры данных, то ожидается “ - 1”.
//  Формат выходных данных.
//  Требуется напечатать YES - если все ожидаемые значения совпали.Иначе, если хотя бы одно
//  ожидание не оправдалось, то напечатать NO.
//
//  3_2.Реализовать дек с динамическим зацикленным буфером(на основе динамического массива).
//  Требования: Дек должен быть реализован в виде класса.
//
//  in:
//  3
//  1 44
//  3 50
//  2 44
//  output:
//  YES
//
//  in:
//  2
//  2 - 1
//  1 10
//  output:
//  YES
//
//  in:
//  2
//  3 44
//  4 66
//  output:
//  NO

#include <iostream>

//класс Дека
template <typename T>
class Deq {
public:
    Deq();
    Deq(const Deq& dq_new);
    ~Deq();

    bool IsEmpty();
    void PushFront(T el);
    T PopFront();
    void PushBack(T el);
    T PopBack();
    Deq& operator=(const Deq& dq_new);

private:
    int start;
    int end;
    int capacity;
    int len;
    T * arr;
};

template <typename T>
Deq<T>::Deq() {
    start = 1;
    end = 0;
    capacity = 2;
    len = 0;

    arr = new T[capacity];
}

template <typename T>
Deq<T>::Deq(const Deq& dq_new) {
    delete[] arr;

    start = len - 1;
    end = 0;
    len = dq_new.len;
    capacity = dq_new.capacity;
    arr = new T[capacity];

    for (int i = 0; i < len; i++) {
        arr[i] = dq_new.arr[(dq_new.end + 1 + i) % capacity];
    }
}

template <typename T>
Deq<T>::~Deq() {
    delete[] arr;
}

template <typename T>
bool Deq<T>::IsEmpty() {
    return (len == 0 ? 1 : 0);
}

template <typename T>
void Deq<T>::PushFront(T el) {
    if (len < capacity) {
        arr[start] = el;
        start = (start + 1) % capacity;
        len++;
    }
    else {
        T * new_arr = new T[2 * capacity];

        for (int i = 0; i < len; i++) {
            new_arr[i] = arr[(end + 1 + i) % capacity];
        }

        capacity *= 2;
        end = capacity - 1;
        start = len;

        delete[] arr;
        arr = new_arr;

        arr[start++] = el;
        len++;
    }
}

template <typename T>
T Deq<T>::PopFront() {
    if (len == 0) {
        return -1;
    }
    else {
        start--;
        if (start < 0) start += capacity;
        len--;
        return arr[start];
    }
}

template <typename T>
void Deq<T>::PushBack(T el) {
    if (len < capacity) {
        arr[end] = el;
        end--;
        if (end < 0) end += capacity;
        len++;
    }
    else {
        T * new_arr = new T[2 * capacity];

        for (int i = 0; i < len; i++) {
            new_arr[i] = arr[(end + 1 + i) % capacity];
        }

        capacity *= 2;
        end = capacity - 1;
        start = len;

        delete[] arr;
        arr = new_arr;

        arr[end--] = el;
        len++;
    }
}

template <typename T>
T Deq<T>::PopBack() {
    if (len == 0) {
        return -1;
    }
    else {
        end = (end + 1) % capacity;
        len--;
        return arr[end];
    }
}

template <typename T>
Deq<T>& Deq<T>::operator= (const Deq& dq_new) {
    delete[] arr;

    start = len - 1;
    end = 0;
    len = dq_new.len;
    capacity = dq_new.capacity;
    arr = new T[capacity];

    for (int i = 0; i < len; i++) {
        arr[i] = dq_new.arr[(dq_new.end + 1 + i) % capacity];
    }
}

int main()
{
    Deq<int> q1;
    int n = 0;
    int buf = 0;
    int elem = 0;

    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> buf;

        switch (buf) {
            case 1: 
                std::cin >> buf;
                q1.PushFront(buf);
                break;
            case 2:
                std::cin >> buf;
                elem = q1.PopFront();
                if (buf != elem) {
                    std::cout << "NO";
                    return 0;
                }
                break;
            case 3:
                std::cin >> buf;
                q1.PushBack(buf);
                break;
            case 4:
                std::cin >> buf;
                elem = q1.PopBack();
                if (buf != elem) {
                    std::cout << "NO";
                    return 0;
                }
                break;
        }
    }
    std::cout << "YES";
    return 0;
}