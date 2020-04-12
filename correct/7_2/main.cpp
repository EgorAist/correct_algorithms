#include <iostream>
using namespace std;

/*
 	Богомолова Мария
 	Группа АПО-13
                            Задача 7_2

 Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 106.
 Отсортировать массив методом поразрядной сортировки LSD по байтам.

 */


// получаем значение байта по номеру
int get_byte(long long number, size_t byte_number)
{
    int result = number >> (8 * byte_number) & 255;
    return result;
}

// сортировка подсчетом массива чисел по n-ому байту
void counting_sort(long long *data, size_t array_size, const size_t byte_number)
{
    size_t counters[256] = {0};

    // считаем количество чисел с разными значениями байта (от 0 до 255)
    for(size_t i = 0; i < array_size; i++)
        counters[get_byte(data[i], byte_number)]++;

    // расчитываем первые индексы для вставки чисел
    for(size_t i = 1; i < 256; i++)
        counters[i] += counters[i - 1];

    //создаем массив для результатов
    long long *tmp = new long long[array_size];

    // создаем отсортированный массив результатов
    for(size_t i = array_size - 1; ; i--)
    {
        tmp[--counters[get_byte(data[i], byte_number)]] = data[i];
        if(i == 0)
            break;
    }

    // переписываем отсортированный массив в исходный
    for(size_t i = 0; i < array_size; i++)
        data[i] = tmp[i];

    delete[] tmp;
}

// сортировка LSD
void LSD_sort(long long *data, size_t array_size)
{
    size_t bytes_count = sizeof(long long);

    for(size_t byte = 0; byte < bytes_count; byte++)
        counting_sort(data, array_size, byte);
}

int main()
{
    size_t array_size = 0;
    cin >> array_size;

    long long *data = new long long[array_size];
    for(size_t i = 0; i < array_size; i++)
        cin >> data[i];

    LSD_sort(data, array_size);

    for(size_t i = 0; i < array_size; i++)
        cout << data[i] << " ";

    delete []data;

    return 0;
}