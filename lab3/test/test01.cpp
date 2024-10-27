#include <gtest/gtest.h>
#include "../include/Hexagon.h"  // Ваши заголовки должны быть правильно прописаны
#include "../include/Octagon.h"
#include "../include/FigureArray.h"
#include "../include/Pentagon.h"

// Тесты для класса Hexagon
TEST(HexagonTest, AreaCalculation) {
    Hexagon hexagon(std::vector<std::pair<double, double>>{{0, 0}, {1, 0}, {1.5, 0.866}, {1, 1.732}, {0, 1.732}, {-0.5, 0.866}});
    EXPECT_NEAR(hexagon.area(), 2.598, 1e-3); // Площадь правильного шестиугольника
}

TEST(HexagonTest, CenterCalculation) {
    Hexagon hexagon(std::vector<std::pair<double, double>>{{0, 0}, {1, 0}, {1.5, 0.866}, {1, 1.732}, {0, 1.732}, {-0.5, 0.866}});

    auto center = hexagon.center();
    EXPECT_NEAR(center.first, 0.5, 1e-1);
    EXPECT_NEAR(center.second, 0.866, 1e-1);
}

TEST(HexagonTest, AssignAndCompare) {
    Figure* h1 = new Hexagon({{0, 0}, {1, 0}, {1.5, 0.866}, {1, 1.732}, {0, 1.732}, {-0.5, 0.866}});
    Figure* h2 = new Hexagon();
    *h2 = *h1;
    EXPECT_TRUE(*h1 == *h2);
}

// Тесты для класса Pentagon
TEST(PentagonTest, AreaCalculation) {
    Pentagon pentagon(std::vector<std::pair<double, double>>{
        {0, 0}, {1, 0}, {1.5, 1.0}, {0.5, 1.5}, {-0.5, 1.0}
    });
    EXPECT_NEAR(pentagon.area(), 2, 1e-3);  // Ожидаемая площадь для правильного пятиугольника
}

TEST(PentagonTest, CenterCalculation) {
    Pentagon pentagon(std::vector<std::pair<double, double>>{
        {0, 0}, {1, 0}, {1.5, 1.0}, {0.5, 1.5}, {-0.5, 1.0}
    });
    auto center = pentagon.center();
    EXPECT_NEAR(center.first, 0.5, 1e-1);  // Ожидаемое значение для центра X
    EXPECT_NEAR(center.second, 0.7, 1e-1); // Ожидаемое значение для центра Y
}

TEST(PentagonTest, AssignAndCompare) {
    Figure* p1 = new Pentagon({{0, 0}, {1, 0}, {1.5, 1.0}, {0.5, 1.5}, {-0.5, 1.0}});
    Figure* p2 = new Pentagon();
    *p2 = *p1;
    EXPECT_TRUE(*p1 == *p2);
}

// Тесты для класса Octagon
TEST(OctagonTest, AreaCalculation) {
    Octagon octagon(std::vector<std::pair<double, double>>{
        {0, 0}, {1, 0}, {1.414, 0.414}, {1.414, 1.414},
        {1, 1.414}, {0, 1.414}, {-0.414, 1.414}, {-0.414, 0.414}
    });
    EXPECT_NEAR(octagon.area(), 2.414, 1e-3);  // Исправленная площадь восьмиугольника
}

TEST(OctagonTest, CenterCalculation) {
    Octagon octagon(std::vector<std::pair<double, double>>{
        {0, 0}, {1, 0}, {1.414, 0.414}, {1.414, 1.414},
        {1, 1.414}, {0, 1.414}, {-0.414, 1.414}, {-0.414, 0.414}
    });
    auto center = octagon.center();
    EXPECT_NEAR(center.first, 0.5, 1e-1);  // Предполагаемый центр X
    EXPECT_NEAR(center.second, 0.8, 1e-1); // Предполагаемый центр Y
}


TEST(FigureArrayTest, AddFiguresAndCalculateTotalArea) {
    FigureArray array;

    // Добавляем фигуры
    Figure* hexagon = new Hexagon({{0, 0}, {1, 0}, {1.5, 0.866}, {1, 1.732}, {0, 1.732}, {-0.5, 0.866}});
    Figure* octagon = new Octagon({{0, 0}, {1, 0}, {1.414, 0.414}, {1.414, 1.414}, {1, 1.414}, {0, 1.414}, {-0.414, 1.414}, {-0.414, 0.414}});
    
    array.AddFigure(std::move(hexagon));
    array.AddFigure(std::move(octagon));
    
    // Исправленное значение общей площади
    EXPECT_NEAR(array.TotalArea(), 5.012, 1e-3); 
}

TEST(FigureArrayTest, RemoveFigureAndCheckRemainingArea) {
    FigureArray array;
    
    // Добавляем фигуры
    Figure* hexagon = new Hexagon({{0, 0}, {1, 0}, {1.5, 0.866}, {1, 1.732}, {0, 1.732}, {-0.5, 0.866}});
    Figure* octagon = new Octagon({{0, 0}, {1, 0}, {1.414, 0.414}, {1.414, 1.414}, {1, 1.414}, {0, 1.414}, {-0.414, 1.414}, {-0.414, 0.414}});
    
    array.AddFigure(std::move(hexagon));
    array.AddFigure(std::move(octagon));
    
    // Удаляем одну фигуру (шестиугольник)
    array.RemoveFigure(0);
    
    // Исправленное значение оставшейся площади
    EXPECT_NEAR(array.TotalArea(), 2.414, 1e-3); 
}




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
