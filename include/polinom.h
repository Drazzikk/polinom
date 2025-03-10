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

    size_t get_degree() const noexcept
    {
        if (this == nullptr)
            throw std::domain_error("domain_error");
        return degree;
    }

    double getK() const noexcept { return k; }

    void setK(const double _k) noexcept { k = _k; }

    bool is_deg_correct() const noexcept { return (get_x_degree() <= MAX_DEGREE && get_y_degree() <= MAX_DEGREE && get_z_degree() <= MAX_DEGREE); }

    Monom operator+(const Monom& monom)
    {
        if (degree == monom.degree)
            return Monom(degree, k + monom.k);
        throw std::domain_error("domain_error");
    }

    Monom operator-(const Monom& monom)
    {
        if (degree == monom.degree)
            return Monom(degree, k - monom.k);
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

        Iterator prev = end();
        Iterator curr = begin();

        while (curr != end() && (*curr).get_degree() > monom.get_degree())
        {
            prev = curr;
            ++curr;
        }

        if (curr != end() && (*curr).get_degree() == monom.get_degree())
        {
            (*curr).setK((*curr).getK() + monom.getK());
            if ((*curr).getK() == 0)
                erase(curr.get_current());
        }
        else
            insert(monom, prev.get_current());
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
        Iterator it1;
        for (it1 = begin() ; it1 != end(); it1++)
        {
            for (Iterator it2 = polinom.begin(); it2 != polinom.end(); it2++)
            {
                Monom product = (*it1) * (*it2);
                if (product.getK() != 0)
                    res.addMonom(product);
            }
        }
        return res;
    }
};