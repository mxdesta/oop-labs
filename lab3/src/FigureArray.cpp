#include "../include/FigureArray.h"

void FigureArray::AddFigure(Figure* figure) {
    figures_.emplace_back(figure);
}

void FigureArray::RemoveFigure(size_t index) {
    if (index < figures_.size()) {
        figures_.erase(figures_.begin() + index);
    } else {
        std::cerr << "Индекс за пределами массива." << std::endl;
    }
}

void FigureArray::PrintAll() const {
    for (const auto& figure : figures_) {
        std::cout << *figure << " Площадь: " << double(*figure) << std::endl;
    }
}

double FigureArray::TotalArea() const {
    double total_area = 0;
    for (const auto& figure : figures_) {
        total_area += figure->area();
    }
    return total_area;
}
