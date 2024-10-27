#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <utility>

class Figure {
public:
    virtual ~Figure() noexcept = default;

    virtual std::pair<double, double> center() const = 0;  // Переименовано для единообразия
    virtual double area() const = 0;  // Метод для вычисления площади

    // Оператор приведения типа к double
    virtual operator double() const { return area(); }

    friend std::ostream& operator<<(std::ostream& os, const Figure& fig) {
        fig.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure& fig) {
        fig.read(is);
        return is;
    }

    virtual Figure& operator=(const Figure& other) = 0;
    virtual Figure& operator=(Figure&& other) noexcept = 0;

    virtual bool operator==(const Figure& other) const = 0;

protected:
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0; 
};

#endif
