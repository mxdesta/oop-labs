#ifndef HEXAGON_H
#define HEXAGON_H

#include "Figure.h"
#include <vector>

class Hexagon : public Figure {
public:
    // Новый конструктор, принимающий вектор вершин
    Hexagon(const std::vector<std::pair<double, double>>& vertices);

    // Конструктор по умолчанию
    Hexagon();
    
    Hexagon& operator=(const Figure& other) override;           // Оператор присваивания копированием
    Hexagon& operator=(Figure&& other) noexcept override;       // Оператор присваивания перемещением
    bool operator==(const Figure& other) const override; 

    double area() const override;
    std::pair<double, double> center() const override;

protected:
    void read(std::istream& in) override;
    void print(std::ostream& out) const override;

private:
    std::vector<std::pair<double, double>> vertices_;
};

#endif // HEXAGON_H
