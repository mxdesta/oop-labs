#include "../include/Pentagon.h"
#include <cmath>

Pentagon::Pentagon(const std::vector<std::pair<double, double>>& vertices) : vertices_(vertices) {
    if (vertices_.size() != 5) {
        throw std::invalid_argument("Pentagon должен иметь ровно 5 вершин.");
    }
}

// Пустой конструктор по умолчанию
Pentagon::Pentagon() : vertices_(5) {}

// Оператор присваивания копированием
Pentagon& Pentagon::operator=(const Figure& other) {
    if (this != &other) {
        const Pentagon* other_pentagon = dynamic_cast<const Pentagon*>(&other);
        if (!other_pentagon) {
            throw std::invalid_argument("Присваивание объекта другого типа невозможно.");
        }
        this->vertices_ = other_pentagon->vertices_;
    }
    return *this;
}

// Оператор присваивания перемещением
Pentagon& Pentagon::operator=(Figure&& other) noexcept {
    if (this != &other) {
        Pentagon* other_pentagon = dynamic_cast<Pentagon*>(&other);
        if (other_pentagon) {
            this->vertices_ = std::move(other_pentagon->vertices_);
        }
    }
    return *this;
}

// Оператор равенства
bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* other_pentagon = dynamic_cast<const Pentagon*>(&other);
    return other_pentagon && this->vertices_ == other_pentagon->vertices_;
}

double Pentagon::area() const {
    double area = 0;
    for (size_t i = 0; i < vertices_.size(); ++i) {
        const auto& [x1, y1] = vertices_[i];
        const auto& [x2, y2] = vertices_[(i + 1) % vertices_.size()];
        area += x1 * y2 - x2 * y1;
    }
    return std::abs(area) / 2;
}

std::pair<double, double> Pentagon::center() const {
    double x_sum = 0, y_sum = 0;
    for (const auto& [x, y] : vertices_) {
        x_sum += x;
        y_sum += y;
    }
    return {x_sum / vertices_.size(), y_sum / vertices_.size()};
}

void Pentagon::read(std::istream& in) {
    for (auto& vertex : vertices_) {
        in >> vertex.first >> vertex.second;
    }
}

void Pentagon::print(std::ostream& out) const {
    for (const auto& vertex : vertices_) {
        out << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}
