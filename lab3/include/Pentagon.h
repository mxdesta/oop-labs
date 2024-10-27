#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"
#include <vector>

class Pentagon : public Figure {
public:
    // Новый конструктор, принимающий вектор вершин
    Pentagon(const std::vector<std::pair<double, double>>& vertices);

    // Конструктор по умолчанию
    Pentagon();

     // Операторы присваивания
    Pentagon& operator=(const Figure& other) override;
    Pentagon& operator=(Figure&& other) noexcept override;

    // Оператор сравнения на равенство
    bool operator==(const Figure& other) const override;

    double area() const override;
    std::pair<double, double> center() const override;

protected:
    void read(std::istream& in) override;
    void print(std::ostream& out) const override;

private:
    std::vector<std::pair<double, double>> vertices_;
};

#endif // PENTAGON_H
