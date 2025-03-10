#pragma once

#include <iostream>
using namespace std;

template<typename T>
class Node
{
public:
    T value;
    Node* next;

    Node(T val = T(), Node* nxt = nullptr) : value(val), next(nxt) {}
};

template<typename T>
class List
{
protected:
    Node<T>* first;
    Node<T>* last;
    size_t size;

public:
    class Iterator
    {
        Node<T>* current;

    public:
        Iterator() : current(nullptr) {}

        Iterator(Node<T>* node) : current(node) {}

        Iterator(const Iterator& it) : current(it.current) {}

        Node<T>* get_current() const noexcept { return current; }

        Iterator& operator++()
        {
            if (current)
                current = current->next;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        T& operator*() const
        {
            if (!current)
                throw std::domain_error("domain_error");
            return current->value;
        }

        bool operator==(const Iterator& it) const { return this->current == it.current; }
        bool operator!=(const Iterator& it) const { return !(*this == it); }

    };

    List() : first(nullptr), last(nullptr), size(0) {}

    List(const List<T>& other) : List()
    {
        for (Iterator it = other.begin(); it != other.end(); ++it)
            push_back(*it);
    }

    List<T>& operator=(const List<T>& other)
    {
        if (this != &other)
        {
            clear();
            for (Iterator it = other.begin(); it != other.end(); ++it)
                push_back(*it);
        }

        return *this;
    }

    ~List() { clear(); }

    Node<T>* get_first() const noexcept { return first; }

    size_t get_size() const noexcept { return size; }

    Iterator begin() noexcept { return Iterator(first); }

    Iterator begin() const noexcept { return Iterator(first); }

    Iterator end() noexcept { return Iterator(); }

    Iterator end() const noexcept { return Iterator(); }

    void clear()
    {
        while (first)
        {
            Node<T>* temp = first;
            first = first->next;
            delete temp;
        }
        last = nullptr;
        size = 0;
    }

    void insert(T elem, Node<T>* node)
    {
        if (!node)
            push_front(elem);
        else
        {
            Node<T>* newNode = new Node<T>(elem, node->next);
            node->next = newNode;
            if (!newNode->next)
                last = newNode;
            size++;
        }
    }

    void push_front(T elem)
    {
        Node<T>* newNode = new Node<T>(elem, first);
        first = newNode;
        if (!last)
            last = first;
        size++;
    }

    void pop_front()
    {
        if (!first)
            throw std::logic_error("List is empty");
        Node<T>* temp = first;
        first = first->next;
        delete temp;
        if (!first)
            last = nullptr;
        size--;
    }

    void push_back(T elem)
    {
        if (!last)
            push_front(elem);
        else
        {
            Node<T>* newNode = new Node<T>(elem);
            last->next = newNode;
            last = newNode;
            size++;
        }
    }

    void erase(Node<T>* node)
    {
        if (!node)
            pop_front();
        else
        {
            bool nodeFound = false;
            Node<T>* current = first;
            Node<T>* prev = nullptr;
            while (current)
            {
                if (current == node)
                {
                    nodeFound = true;
                    break;
                }
                prev = current;
                current = current->next;
            }
            if (!nodeFound)
                throw std::logic_error("Node not in list");
            if (prev)
            {
                prev->next = node->next;
                if (!prev->next)
                    last = prev;
            }
            else
            {
                first = node->next;
                if (!first)
                    last = nullptr;
            }
            delete node;
            size--;
        }
    }
};