#ifndef OCTAGON_H
#define OCTAGON_H

#include "Figure.h"
#include <vector>

class Octagon : public Figure {
public:
    // Новый конструктор, принимающий вектор вершин
    Octagon(const std::vector<std::pair<double, double>>& vertices);

    // Конструктор по умолчанию
    Octagon();
    
    Octagon& operator=(const Figure& other) override;
    Octagon& operator=(Figure&& other) noexcept override;

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

#endif // OCTAGON_H
