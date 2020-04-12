/* Богомолова Мария, АПО-13
    Задача 3_3
    Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
    Требования: Очередь должна быть реализована в виде класса. Стек тоже должен быть реализован в виде класса.
    Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
    Формат входных данных.
    В первой строке количество команд n. n ≤ 1000000.
    Каждая команда задаётся как 2 целых числа: a b.
    a = 2 - pop front
    a = 3 - push back
    Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
    Для очереди используются команды 2 и 3.
    Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
    Формат выходных данных.
    Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
*/

#include <iostream>

#define INITIAL_SIZE 10
#define INCREASE_INDEX 2

template <typename T>
class Stack {

public:
    Stack();

    ~Stack();

    void push(const T &element);

    T pop();

    bool isEmpty();

private:
    T *buffer; //буфер для хранения данных

    size_t capacity; //вместимость буфера

    size_t size; //реальный размер буфера (количество хранимых элементов)

    int head; //значение "головы"

    void resize();
};



template <typename T>
class Queue {
public:
    Queue();

    ~Queue();

    void enqueue(const T &element);

    T dequeue();

private:
    Stack<T> leftStack, rightStack; //правый и левый стек для реализации очереди на 2х стеках
};


int main() {
    Queue<int> queue;

    int n = 0;
    int cmd = 0; //считываемая команда пользователя
    int element = 0;
    int ret_pop = 0;

    bool flag = true;

    std::cin >> n;
    if (!n)
        return 0;

    for (size_t i = 0; i < n; i++) {
        std::cin >> cmd >> element;

        //в зависимости от команды пользователя, вызываем тот или иной метод
        switch (cmd) {
            case 3:
                queue.enqueue(element);
                break;
            case 2:
                ret_pop = queue.dequeue();
                if (element != ret_pop)
                    flag = false; //извлеченное значение не соответствует введенному
                break;
            default:
                break;
        }
    }

    if (flag)
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}

//----------------------------------------------------
// реализация очереди

template <typename T>
Queue<T>::Queue() = default;

template <typename T>
Queue<T>::~Queue() = default;

//добавление нового элемента в очередь
template <typename T>
void Queue<T>::enqueue(const T &element) {
    //добавляем элемент в левый стек
    leftStack.push(element);
}

//извлечение элемента из очереди
template <typename T>
T Queue<T>::dequeue() {
    //если в правом стеке что-либо хранится,
    //то последний элемент в очереди = последнему элементу в правом стеке
    if (!rightStack.isEmpty())
        return rightStack.pop();
    else {
        //если правый стек пуст, то "переливаем" элементы из левого стека в правый,
        //после чего достает элемент
        while (!leftStack.isEmpty())
            rightStack.push(leftStack.pop());
        return rightStack.pop();
    }
}

//------------------------------------------------------------------
//реализация стека

//конструктор стека
template <typename T>
Stack<T>::Stack() {
    size = 0;
    head = 0;
    capacity = INITIAL_SIZE; //вместимость буфера для хранения стека
    buffer = new T[INITIAL_SIZE]; //реальный размер буфера (количество хранимых в нем элементов)
}

//деструктор стека
template <typename T>
Stack<T>::~Stack() {
    delete [] buffer;
}

//добавление элемента в стен
template <typename T>
void Stack<T>::push(const T &element) {
    //в случае, если место в буфере заканчивается, изменяем размер буфера путем выделения памяти
    if (head == capacity - 1)
        resize();

    //добавление нового элемента
    head++;
    buffer[head] = element;
    size++;
}

//извлечение элемента из стека
template <typename T>
T Stack<T>::pop() {
    //из пустого стека вернется значение -1
    if (isEmpty())
        return -1;

    //иначе извлекаем значение и уменьшаем количество хранимых элементов
    T ret_val = buffer[head];
    head--;
    size--;
    return ret_val;
}

//проверка стека на пустоту
template <typename T>
bool Stack<T>::isEmpty() {
    return !size;
}

//изменение размера стека в случае недостатка в памяти
template <typename T>
void Stack<T>::resize() {
    size_t newCapacity = capacity * INCREASE_INDEX;
    T *tmp = new T[newCapacity]; //перевыделяем память

    std::copy(buffer, buffer + head + 1, tmp); //копируем содержимое

    //присваиваем новые значения полям объекта
    capacity = newCapacity;
    delete [] buffer;
    buffer = tmp;
}