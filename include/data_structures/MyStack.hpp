#ifndef MYSTACK_HPP
#define MYSTACK_HPP

#include <stdexcept>

template <typename T>
class MyStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* topNode;
    size_t stackSize;
    
public:
    // Конструктор
    MyStack() : topNode(nullptr), stackSize(0) {}
    
    // Деструктор
    ~MyStack() {
        clear();
    }
    
    // Копирующий конструктор
    MyStack(const MyStack& other) : topNode(nullptr), stackSize(0) {
        if (!other.isEmpty()) {
            // Создаем обратную копию, а потом переворачиваем
            MyStack<T> temp;
            Node* current = other.topNode;
            while (current) {
                temp.push(current->data);
                current = current->next;
            }
            
            // Теперь переворачиваем
            while (!temp.isEmpty()) {
                push(temp.pop());
            }
        }
    }
    
    // Оператор присваивания
    MyStack& operator=(const MyStack& other) {
        if (this != &other) {
            clear();
            if (!other.isEmpty()) {
                MyStack<T> temp;
                Node* current = other.topNode;
                while (current) {
                    temp.push(current->data);
                    current = current->next;
                }
                
                while (!temp.isEmpty()) {
                    push(temp.pop());
                }
            }
        }
        return *this;
    }
    
    // Добавление элемента
    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        ++stackSize;
    }
    
    // Удаление и возврат верхнего элемента
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        
        Node* nodeToDelete = topNode;
        T value = nodeToDelete->data;
        topNode = topNode->next;
        delete nodeToDelete;
        --stackSize;
        
        return value;
    }
    
    // Просмотр верхнего элемента без удаления
    T& peek() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return topNode->data;
    }
    
    const T& peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return topNode->data;
    }
    
    // Проверка на пустоту
    bool isEmpty() const {
        return topNode == nullptr;
    }
    
    // Получение размера
    size_t size() const {
        return stackSize;
    }
    
    // Очистка стека
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
    
    // Для совместимости с STL алгоритмами
    class Iterator {
    private:
        Node* current;
        
    public:
        Iterator(Node* node) : current(node) {}
        
        T& operator*() { return current->data; }
        Iterator& operator++() { 
            if (current) current = current->next;
            return *this;
        }
        bool operator!=(const Iterator& other) const { 
            return current != other.current; 
        }
    };
    
    Iterator begin() { return Iterator(topNode); }
    Iterator end() { return Iterator(nullptr); }
};

#endif // MYSTACK_HPP