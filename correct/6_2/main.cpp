#include <iostream>

using namespace std;

/*
	Богомолова Мария
 	Группа АПО-13
                                    Задача 6_2
 Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..10^9] размера n.
 Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции
 с индексом k ∈[0..n-1] в отсортированном массиве.
 Напишите нерекурсивный алгоритм.
 Требования к дополнительной памяти: O(n).
 Требуемое среднее время работы: O(n).
 Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 Описание для случая прохода от начала массива к концу:
 Выбирается опорный элемент.
 Опорный элемент меняется с последним элементом массива.
 Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
 Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат
 нерассмотренные элементы. Последним элементом лежит опорный.
 Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
 Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
 Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного,
 то сдвигаем j. Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
 В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
 Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 Функцию Partition реализуйте методом прохода двумя итераторами
 от конца массива к началу.
*/

void medianOfThree(int *array, int left, int right);     // Установка медианы в нужное место
int partition(int *array, int left, int right);          // Нахождение места элемента
int kStatistics(int *array, int left, int right, int k); // K-я статистика

int main ()
{
    int count_elements = 0;
    cin >> count_elements;

    int k = 0;
    cin >> k;

    int *array = new int[count_elements];

    for (int i = 0; i < count_elements; ++i)
        cin >> array[i];

    cout << kStatistics(array, 0, count_elements - 1, k);

    delete []array;
    return 0;
}

void medianOfThree(int *array, int left, int right)
{
    // Установка элементов с индексами left, right, ( left + right ) / 2
    // В порядке [средний, минимальный, максимальный] на позиции
    // [left, ( left + right ) / 2, right]
    // т.е. на месте a[left] становится средний из 3х элементов

    if (array[(left + right) / 2] > array[right])
        swap (array[(left + right) / 2], array[right]);

    if (array[left] < array[(left + right) / 2])
        swap ( array[left], array[(left + right) / 2]);

    if (array[left] > array[right])
        swap (array[left], array[right]);
}

int partition(int *array, int left, int right)
{
    // Метод прохода двумя итераторами от конца массива к началу.
    medianOfThree(array, left, right);
    int i = right;
    int j = right;
    bool step = false;

    while (j > left)
    {
        // Ускорение для повторяющихся элементов
        while (array[left] == array[j] && j > left)
        {
            if (step)
                swap(array[i--], array[j--]);
            else
                --j;

            step =! step;
        }

        while (array[j] < array[left] && j > left)
            --j;

        while (array[j] > array[left] && j > left)
            swap(array[j--], array[i--]);
    }
    swap(array[left], array[i]);

    return i;
}

int kStatistics(int *array, int left, int right, int k)
{
    // Модификация quick_sort для поиска к-й статистики
    int l = left;
    int r = right;
    int p = -1;
    while (p != k)
    {
        p = partition(array, l, r);
        if (p < k)
            l = p + 1;
        else
            r = p - 1;
    }

    return array[k];
}