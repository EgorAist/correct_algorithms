#include <iostream>
#include <assert.h>

using namespace std;

/*
	Богомолова Мария
 	Группа АПО-13
                                    Задача 2_4

 Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k],
 ближайшего по значению к B[i].
 n ≤ 110000, m ≤ 1000.
 Время работы поиска для каждого элемента B[i]: O(log(k)).
*/

int findTwinInRange(const int *array, int twink, int size_array);

int binarySearch(const int *array, int start, int end, int twink);

int main()
{

    int size_arr_A = 0; // размер массива А

    // вводим размер массива А
    cin >> size_arr_A;

    //проверка условий по размеру массива А
    assert(size_arr_A > 0 && size_arr_A <= 110000);

    // выделение памяти под массив А
    int *arr_A = new int[size_arr_A];

    // заполнение элементов массива А
    for (int i = 0; i < size_arr_A; i++)
        cin >> arr_A[i];


    int size_arr_B = 0; // размер массива В

    // вводим размер массива В
    cin >> size_arr_B;

    // проверка условий по размеру массива B
    assert(size_arr_B > 0 && size_arr_B <= 1000);

    // выделение памяти под массив В
    int *arr_B = new int[size_arr_B];

    // заполнение элементов массива В,
    // поиск ближайшего минимального индекса
    // в массиве А для элемента B[i]
    for (int i = 0; i < size_arr_B; i++)
    {
        cin >> arr_B[i];
        cout << findTwinInRange(arr_A, arr_B[i], size_arr_A) << " ";
    }

    // очистка памяти
    delete []arr_A;
    delete []arr_B;

    return 0;
}

int findTwinInRange(const int *array, int twink, int size_array)
{
    int start = 0;
    int end = 0;

    // если элемент B[i] меньше, чем
    // А[0], то ближайший минимальный индекс 0
    if (twink < array[0])
        return 0;

    // если элемент B[i] больше, чем
    // А[size_array - 1], то ближайший
    // минимальный индекс size_array - 1
    if (twink > array[size_array - 1])
        return size_array - 1;

    //Находим промезжуток, где находится ближайший элемент
    while (array[end] < twink)
    {
        start = end + 1;
        if (end * 2 < size_array)
            if(!end)
                end = 1;
            else
                end = end * 2;
        else
            end = size_array - 1;
    }

    //Ищем индекс ближайшего элемента с помощью бинарного поиска
    int nearest_index = binarySearch(array, start, end, twink);

    //Определяем близжайший индекс
    if (abs(array[nearest_index] - twink) < abs(array[nearest_index - 1] - twink))
        return nearest_index;
    else
        return nearest_index - 1;
}

int binarySearch(const int *array, int start, int end, int twink)
{
    int middle = 0;

    while (start != end)
    {
        //середина массива
        middle = (end + start) / 2;
        //в какой части, относительно середины находится элемент
        if (twink <= array[middle])
            end = middle;
        else
            start = middle + 1;
    }

    return start;
}