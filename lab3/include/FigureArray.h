#ifndef FIGURE_ARRAY_H
#define FIGURE_ARRAY_H

#include "Figure.h"
#include <vector>
#include <memory>
#include <iostream>

class FigureArray {
public:
    void AddFigure(Figure* figure);
    void RemoveFigure(size_t index);
    void PrintAll() const;
    double TotalArea() const;

private:
    std::vector<std::unique_ptr<Figure>> figures_;
};

#endif // FIGURE_ARRAY_H
