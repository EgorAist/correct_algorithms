#include <iostream>
#include <assert.h>
using namespace std;

/*
                Задача 7_3

 Дан массив неотрицательных целых 64-разрядных чисел.
 Количество чисел не больше 1000000. Отсортировать массив
 методом MSD по битам (бинарный QuickSort).
*/

#define bitIsOneS 63

inline int bitIsOne (long long number, int i);
void binaryQuickSort(long long *, int, int, int );

int main()
{
    int elements_count; // количество элементов в массиве
    // вводим количество элементов
    cin >> elements_count;
    // проверка условий на размер массива
    assert(elements_count < 1000000 || elements_count > 0);

    // выделяем память под массив
    long long *array = new long long[elements_count];

    // заполняем массив элементами
    for (int i = 0; i < elements_count; ++i)
    {
        cin >> array[i];
        // проверка условия неотрицательности элементов массива
        assert(i >= 0);
    }

    // сортируем массив при помощи бинарной быстрой сортировки
    binaryQuickSort(array, 0, elements_count - 1, bitIsOneS);

    // выводим отсортированный массив через пробел
    for (int i = 0; i < elements_count; ++i)
        cout << array[i] << " ";

    // чистим память
    delete []array;

    return 0;
}

//Проверка наличия единицы в раряде под номером i
inline int bitIsOne (long long number, int i)
{
    return (number >> i) & 1;
}

// бинарная быстрая сортировка
void binaryQuickSort(long long *array, int left, int right, int d)
{
    /* Работает пока left <= right, т.е. все элементы справа от array[i]
       имеют 1 в d-й позиции, а все элементы слева имеют 0 в d-й позиции,
       или пока не прошли по всем битам
    */
    if (right <= left || d < 0)
        return;

    int i = left,
            j = right;

    // Ищем 0 бит и меняем это число с тем, которое имеет 1 в позиции d
    while (i != j)
    {
        while (bitIsOne(array[i], d) == 0 && (i < j))
            i++;

        while (bitIsOne(array[j], d) == 1 && (j > i))
            j--;

        // меняем элементы местами
        swap(array[i], array[j]);
    }

    // если у среднего элемента в d-й позиции 0, то сдаигаем правую границу на 1
    if (bitIsOne(array[right], d) == 0)
        j++;

    // бинарная быстрая сортировка вызывается рекурсивно для разных частей
    binaryQuickSort(array, left, j - 1, d - 1 );
    binaryQuickSort(array, j, right, d - 1 );
}