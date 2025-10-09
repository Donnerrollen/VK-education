//1.2 Вернуть значение бита в числе N по его номеру K.
//Формат входных данных.Число N, номер бита K
//in       out
//25 3 ->  1
//25 2 ->  0

#include <iostream>

bool CheckBitInPossition(int num, int k) {
    int buf = 1;

    for (int i = 0; i < k; i++) {
        buf = buf << 1;
    }

    return ( (num & buf) == 0 ? false : true);
}

int main()
{
    int N = 0;
    int K = 0;
   
    std::cin >> N >> K;

    int res = CheckBitInPossition(N, K);

    std::cout << res;
}