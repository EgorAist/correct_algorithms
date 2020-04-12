#include <iostream>
#include <assert.h>
using namespace std;

/*
                            Задача 4_3

 На вокзале есть некоторое количество тупиков, куда прибывают электрички.
 Этот вокзал является их конечной станцией. Дано расписание движения электричек,
 в котором для каждой электрички указано время ее прибытия, а также время
 отправления в следующий рейс. Электрички в расписании упорядочены по времени прибытия.
 Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером.
 При этом если электричка из какого-то тупика отправилась в момент времени X, то электричку,
 которая прибывает в момент времени X, в этот тупик ставить нельзя, а электричку,
 прибывающую в момент X+1 — можно. В данный момент на вокзале достаточное количество тупиков
 для работы по расписанию. Напишите программу, которая по данному расписанию определяет,
 какое минимальное количество тупиков требуется для работы вокзала.

*/

// Heap - куча
class Heap
{
private:

    // функции для поддержания кучи
    void moveDown(int index);
    void moveUp(int index);

    // выделение доп. памяти
    void reallocate();

    int *buffer;    // массив для кучи
    int size;       // количество элементов в кучи
    int capacity;   // количество выделенной памяти

public:

    Heap(int cap);      // конструктор
    ~Heap();            // деструктор

    int extractMin();                                       // достать минимальный элемент из кучи
    void insert(int element);                               // добавление нового элемента
    int peekAtNext() { return isEmpty() ? 0 : buffer[0]; }  // посмотреть на первый элемент

    bool isEmpty() { return size == 0; }    // проверка на отсутствие элементов
    int getSize() { return size; }          // вернуть кол-во элементов в куче

};

// Подсчет минимально необходимого количества тупиков
int countDeadends(const int count);

int main()
{
    int n = 0; // количество поездов
    // вводим количество поездов
    cin >> n;
    // проверка условий 
    assert(n >= 0);

    // подсчет количества тупиков
    int min_count_deadends = countDeadends(n);
    // вывод количества тупиков
    cout << min_count_deadends;

    return 0;
}

// конструктор
Heap::Heap(int cap)
{
    capacity = cap; // изначально выделено памяти
    size = 0;       // изначально элементов в куче - 0
    buffer = new int[capacity]; // выделение памяти в массиве под кучу
}

// деструктор
Heap::~Heap()
{
    delete []buffer; // очистка памяти
}

// для организации кучи
void Heap::moveDown(int index)
{
    int left_son = 2 * index + 1;
    int right_son = 2 * index + 2;

    int smallest_son = index;

    if (left_son < size && buffer[left_son] < buffer[index])
        smallest_son = left_son;

    if (right_son < size && buffer[right_son] < buffer[smallest_son])
        smallest_son = right_son;

    if (smallest_son != index)
    {
        swap(buffer[index], buffer[smallest_son]);
        moveDown(smallest_son);
    }
}

// для организации кучи
void Heap::moveUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (buffer[index] >= buffer[parent])
            return;

        swap(buffer[index], buffer[parent]);

        index = parent;
    }
}

// реалокация памяти
void Heap::reallocate()
{
    int new_capacity = capacity * 2; // новое кол-во выделенной памяти
    int *new_buffer = new int[new_capacity]; // выделение памяти в новом буффере

    // копирование элементов из старого буфера в новый
    for (int i = 0; i < capacity; ++i)
        new_buffer[i] = buffer[i];

    // удаление старого буфера
    delete []buffer;

    // в куче буфер = новый буфер
    buffer = new_buffer;
    // в куче кол-во выделенной памяти = новое кол-во выделенной памяти
    capacity = new_capacity;
}

// вставка нового элемента
void Heap::insert(int element)
{
    buffer[size] = element;
    moveUp(size++);

    // если кол-во элементов в куче равно кол-ву
    // выделенной памяти, то сделать реалокацию
    if (size == capacity)
        reallocate();
}

// достать минимальный элемент из кучи
int Heap::extractMin()
{
    // проверка на отсутсвие элементов
    if (isEmpty())
        return 0;

    // минимальный элемент
    int result = buffer[0];

    // для организации кучи
    if (size > 0)
        buffer[0] = buffer[--size];
        // обработка ошибки
    else
        buffer[0] = 0;

    // для организации кучи
    moveDown(0);

    return result;
}

// Подсчет минимально необходимого количества тупиков
int countDeadends(const int n)
{
    int minimum_deadends = 0,   // минимальное кол-во тупиков
    arrival = 0,            // время прибытия
    departure = 0;          // время отбытия

    // создаем объект класса Heap
    Heap Heap(n * 2 );

    // для всех поездов
    for (int i = 0; i < n; ++i)
    {
        // Ввод времени прибытия и отбытия
        cin >> arrival >> departure;

        if (!Heap.isEmpty())
        {
            // Если некоторые электрички к моменту прибытия уехали - извлекаем
            while (arrival > Heap.peekAtNext() && (Heap.peekAtNext() != 0))
                Heap.extractMin();
        }

        // Добавляем время отправления прибывшей
        Heap.insert(departure);

        // Смотрим, сколько путей занято
        if (Heap.getSize() > minimum_deadends)
            minimum_deadends = Heap.getSize();
    }

    return minimum_deadends;
}