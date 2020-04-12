/*
                         Задача 3_2

 Реализовать дек с динамическим зацикленным буфером.

 Формат входных данных.
 В первой строке количество команд n. n ≤ 1000000.
 Каждая команда задаётся как 2 целых числа: a b.
     a = 1 - push front
     a = 2 - pop front
     a = 3 - push back
     a = 4 - pop back
 Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
 Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
 Если дана команда pop*, то число b - ожидаемое значение.
 Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
 Формат выходных данных.
 Требуется напечатать YES - если все ожидаемые значения совпали.
 Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

 Требования: Дек должен быть реализован в виде класса.
*/

#include <iostream>
#include <cassert>

using namespace std;

#define MIN_SIZE 10
#define MULTIPLY_BY_TWO 2

template <typename T>
// дек - это двусторонняя очередь
// элементы в дек можно класть и доставать
// как с начала, так и с конца
class Deque
{
public:
    Deque();  // конструктор
    ~Deque(); // деструктор

    void pushFront(const T &element); // положить спереди
    void pushBack(const T &element);  // положить сзади

    T popFront(); // достать элемент спереди
    T popBack();  // достать элемент сзади

    bool isEmpty(); // проверка на то, что дек пустой

private:
    // направление элементов в деке слева направо
    int tail_element; // хвостовой элемент (количество элементов - 1)
    int head_element; // головной элемент (0)

    T *buf;          // буфер для хранения элементов
    size_t buf_size; // вместимость буфера
    size_t size;     // количество элементов в деке
    // (количество занятых элементов в буфере)

    void resize(); // изменить размер буфера
};

template <typename T>
Deque<T>::Deque(): head_element{0}, tail_element{0}
{
    // выделение памяти под буфер
    buf = new T[MIN_SIZE];
    // вместимость - количество элементов в буфере
    buf_size = MIN_SIZE;
    // количество элементов в деке - 0
    size = 0;
}

template <typename T>
Deque<T>::~Deque()
{
    // очистка памяти
    delete []buf;
}

template <typename T>
bool Deque<T>::isEmpty()
{
    // если size = 0, то вернуть 1
    return !size;
}


template <typename T>
void Deque<T>::pushBack(const T &element)
{
    // проверка на то, что в буфере еще осталось место
    if (size + 1 > buf_size)
        resize();

    // положить элемент в конец
    buf[tail_element] = element;
    // увеличить количество реально занятого пространства в буфере
    size++;
    // так как дек зациклен, нужно искать остаток от деления
    tail_element = (tail_element + 1) % buf_size;
}


template <typename T>
void Deque<T>::pushFront(const T &element)
{
    // проверка на то, что в буфере еще осталось место
    if (size + 1 > buf_size)
        resize();

    // изменения положения головного элемента
    head_element = (head_element - 1 + buf_size) % buf_size;
    // кладем новый элемент в начало
    buf[head_element] = element;
    // увеличить количество реально занятого пространства в буфере
    size++;
}


template <typename T>
T Deque<T>::popFront()
{
    // проверка дека на отсутствие элементов
    if (isEmpty())
        return -1;

    // возвращение головного элемента
    T return_element = buf[head_element];
    // изменение положения головного элемента
    head_element = (head_element + 1) % buf_size;
    // изменения размера дека
    size--;
    // возвращение нужного элемента
    return return_element;
}


template <typename T>
T Deque<T>::popBack()
{
    // проверка дека на отсутствие элементов
    if (isEmpty())
        return -1;

    // параресчет хвостового элемента
    tail_element = (tail_element - 1 + buf_size) % buf_size;
    // изменение размера дека
    size--;
    // возвращение нужного элемента
    return buf[tail_element];
}


template <typename T>
void Deque<T>::resize()
{
    // новое количество элементов в буфере -
    // это старое количество * 2
    size_t new_buf_size = buf_size * MULTIPLY_BY_TWO;

    // выделяем память под новый буфер
    T *tmp = new T[new_buf_size];

    // если головной элемент меньше, чем хвостовой
    if (head_element < tail_element)
        copy(buf + head_element, buf + tail_element, tmp + head_element);
    else {
        /* Поскольку буфер зацикленный, tail_element может распологаться в начале массива,
         * соответственно он может быть меньше head_element. В этом случае расширяем зацикленный
         * буфер и поэтому копируем его частями */
        copy(buf + head_element, buf + buf_size, tmp + head_element);
        copy(buf, buf + tail_element, tmp + buf_size);
        tail_element = buf_size + tail_element;
    }

    // изменяем количество элементов
    buf_size = new_buf_size;
    // очищаем буфер
    delete []buf;
    // теперь буфер реалицированный
    buf = tmp;
}

int main()
{
    // создаем объект класса дек
    Deque<int> deque;

    // количество элементов
    int n = 0;
    cin >> n;
    // проверка условий
    assert(n >= 0);

    bool is_correct = true;   // флаг для проверка корректности
    int command = 0;          // код команды
    int element = 0;          // элемент, с которым нужно выполнять действия
    int return_element = 0;   // возвращаемый элемент

    for (size_t i = 0; i < n; i++)
    {
        cin >> command >> element;

        switch (command)
        {
            // положить в начало
            case 1:
                deque.pushFront(element);
                break;

                // вернуть первый элемент
            case 2:
                return_element = deque.popFront();
                // проверка на ошибку
                if (element != return_element)
                    is_correct = false;
                break;

                // положить последний элемент
            case 3:
                deque.pushBack(element);
                break;

                // вернуть последний элемент
            case 4:
                return_element = deque.popBack();
                // проверка на ошибку
                if (element != return_element)
                    is_correct = false;
                break;

            default:
                break;
        }
    }

    if (is_correct)
        cout << "YES";
    else
        cout << "NO";

    return 0;
}
