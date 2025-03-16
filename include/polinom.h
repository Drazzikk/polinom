#pragma once
#include "list.h"
#include <iostream>

using namespace std;
const size_t MAX_DEGREE = 9;

class Monom
{
protected:
    size_t degree;
    double k;

public:
    Monom(size_t deg = 0, double kf = 0) : degree(deg), k(kf)
    {
        if (!is_deg_correct())
            throw std::domain_error("domain_error");
    }

    size_t get_x_degree() const noexcept { return degree / 100; }

    size_t get_y_degree() const noexcept { return (degree / 10) % 10; }

    size_t get_z_degree() const noexcept { return degree % 10; }

    size_t get_degree() const
    {
        if (this == nullptr)
            throw std::domain_error("domain_error");
        return degree;
    }

    double getK() const noexcept { return k; }

    void setK(const double _k) noexcept { k = _k; }

    bool is_deg_correct() const noexcept { return (get_x_degree() <= MAX_DEGREE && get_y_degree() <= MAX_DEGREE && get_z_degree() <= MAX_DEGREE); }

    Monom operator+(const Monom& monom) const {
        if (degree == monom.degree) {
            double result_k = k + monom.k;
            if (result_k == 0) {
                return Monom(0, 0);
            }
            else {
                return Monom(degree, result_k);
            }
        }
        throw std::domain_error("domain_error");
    }

    Monom operator-(const Monom& monom) const {
        if (degree == monom.degree) {
            double result_k = k - monom.k;
            if (result_k == 0) {
                return Monom(0, 0);
            }
            else {
                return Monom(degree, result_k);
            }
        }
        throw std::domain_error("domain_error");
    }

    Monom operator*(const double scalar)
    {
        Monom res(degree, k*scalar);
        if (res.getK() == 0)
            return Monom(0, 0);
        return res;
    }

    Monom operator*(const Monom& monom)
    {
        size_t new_x = get_x_degree() + monom.get_x_degree();
        size_t new_y = get_y_degree() + monom.get_y_degree();
        size_t new_z = get_z_degree() + monom.get_z_degree();
        if (new_x > MAX_DEGREE || new_y > MAX_DEGREE || new_z > MAX_DEGREE)
            throw std::domain_error("domain_error");
        size_t newDegree = new_x * 100 + new_y * 10 + new_z;
        double newK = k * monom.k;
        return Monom(newDegree, newK);
    }
};

class Polinom : public List<Monom>
{
public:
    Polinom() {}
    ~Polinom() {}

    Polinom(const Polinom& polinom) : List<Monom>(polinom) {}

    Polinom& operator=(const Polinom& polinom)
    {
        if (this != &polinom)
            List<Monom>::operator=(polinom);
        return *this;
    }

    void addMonom(const Monom& monom)
    {
        if (monom.getK() == 0) return;

        Node<Monom>* prevNode = nullptr;
        Node<Monom>* currNode = first; 

        while (currNode != nullptr && currNode->value.get_degree() > monom.get_degree())
        {
            prevNode = currNode;
            currNode = currNode->next;
        }

        if (currNode != nullptr && currNode->value.get_degree() == monom.get_degree()) {
            double newK = currNode->value.getK() + monom.getK();
            if (newK == 0) {
                // Erase the node
                if (prevNode == nullptr) {
                    pop_front();  
                }
                else {
                    prevNode->next = currNode->next;
                    if (currNode == last) {
                        last = prevNode;
                    }
                    delete currNode;
                    size--;
                }
            }
            else {
                currNode->value.setK(newK);  
            }
        }
        else {
            Node<Monom>* newNode = new Node<Monom>(monom);

            if (prevNode == nullptr)
            {
                newNode->next = first;
                first = newNode;
                if (last == nullptr)
                    last = newNode;
            }
            else
            {
                newNode->next = currNode;
                prevNode->next = newNode;
                if (currNode == nullptr) {
                    last = newNode; 
                }

            }
            size++;

        }
    }

    Polinom operator+(const Polinom& polinom) const
    {
        Polinom res(*this);
        for (Iterator it = polinom.begin(); it != polinom.end(); ++it)
            res.addMonom(*it);
        return res;
    }

    Polinom operator*(double scalar) const
    {
        Polinom res;
        Iterator it;
        for (it = begin(); it != end(); ++it)
        {
            Monom product = *it * scalar;
            if (product.getK() != 0)
                res.addMonom(product);
        }
        return res;
    }

    Polinom operator*(const Monom& monom) const
    {
        Polinom res;
        Iterator it;
        for (it = begin(); it != end(); ++it)
        {
            Monom product = (*it) * monom;
            if (product.getK() != 0)
                res.addMonom(product);
        }
        return res;
    }

    Polinom operator*(const Polinom& polinom) const
    {
        Polinom res;
        for (Iterator it1 = begin(); it1 != end(); ++it1)
        {
            for (Iterator it2 = polinom.begin(); it2 != polinom.end(); ++it2)
            {
                Monom product = (*it1) * (*it2);
                if (product.getK() != 0)
                    res.addMonom(product); 
            }
        }
        return res;
    }
};