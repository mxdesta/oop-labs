#include "include/Hexagon.h"
#include "include/Octagon.h"
#include "include/Pentagon.h"
#include "include/FigureArray.h"
#include <iostream>

int main() {
    FigureArray array;

    Hexagon* hexagon = new Hexagon();
    std::cout << "Введите координаты 6 вершин шестиугольника по часовой стрелке:" << std::endl;
    std::cin >> *hexagon;
    array.AddFigure(hexagon);
    std::cout << "Добавлена фигура:" << std::endl << *hexagon << std::endl << "Площадь: " << double(*hexagon) << std::endl;

    Octagon* octagon = new Octagon();
    std::cout << "Введите координаты 8 вершин восьмиугольника по часовой стрелке:" << std::endl;
    std::cin >> *octagon;
    array.AddFigure(octagon);
    std::cout << "Добавлена фигура:" << std::endl << *octagon << std::endl << "Площадь: " << double(*octagon) << std::endl;

    Pentagon* pentagon = new Pentagon();
    std::cout << "Введите координаты 5 вершин пятиугольника по часовой стрелке:" << std::endl;
    std::cin >> *pentagon;
    array.AddFigure(pentagon);
    std::cout << "Добавлена фигура:" << std::endl << *pentagon << std::endl << "Площадь: " << double(*pentagon) << std::endl;

    std::cout << "Все фигуры:" << std::endl;
    array.PrintAll();

    std::cout << "Общая площадь всех фигур: " << array.TotalArea() << std::endl;

    size_t index;
    std::cout << "Введите индекс объекта для удаления:" << std::endl;
    std::cin >> index;
    array.RemoveFigure(index);

    std::cout << "Оставшиеся фигуры:" << std::endl;
    array.PrintAll();

    return 0;
}
