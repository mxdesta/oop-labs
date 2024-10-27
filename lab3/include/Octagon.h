#ifndef OCTAGON_H
#define OCTAGON_H

#include "Figure.h"
#include <vector>

class Octagon : public Figure {
public:

    Octagon(const std::vector<std::pair<double, double>>& vertices);


    Octagon();

    Octagon& operator=(const Figure& other) override;
    Octagon& operator=(Figure&& other) noexcept override;

    bool operator==(const Figure& other) const override;

    double area() const override;
    std::pair<double, double> center() const override;

protected:
    void read(std::istream& in) override;
    void print(std::ostream& out) const override;

private:
    std::vector<std::pair<double, double>> vertices_;
};

#endif 
