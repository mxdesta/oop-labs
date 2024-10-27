#include "../include/Hexagon.h"
#include <cmath>

Hexagon::Hexagon(const std::vector<std::pair<double, double>>& vertices) : vertices_(vertices) {
    if (vertices_.size() != 6) {
        throw std::invalid_argument("Hexagon должен иметь ровно 6 вершин.");
    }
}


Hexagon::Hexagon() : vertices_(6) {}

Hexagon& Hexagon::operator=(const Figure& other) {
    if (this != &other) {
        const Hexagon* other_hexagon = dynamic_cast<const Hexagon*>(&other);
        if (!other_hexagon) {
            throw std::invalid_argument("Присваивание объекта другого типа невозможно.");
        }
        this->vertices_ = other_hexagon->vertices_;
    }
    return *this;
}


Hexagon& Hexagon::operator=(Figure&& other) noexcept {
    if (this != &other) {
        Hexagon* other_hexagon = dynamic_cast<Hexagon*>(&other);
        if (other_hexagon) {
            this->vertices_ = std::move(other_hexagon->vertices_);
        }
    }
    return *this;
}


bool Hexagon::operator==(const Figure& other) const {
    const Hexagon* other_hexagon = dynamic_cast<const Hexagon*>(&other);
    return other_hexagon && this->vertices_ == other_hexagon->vertices_;
}

double Hexagon::area() const {
    double area = 0;
    for (size_t i = 0; i < vertices_.size(); ++i) {
        const auto& [x1, y1] = vertices_[i];
        const auto& [x2, y2] = vertices_[(i + 1) % vertices_.size()];
        area += x1 * y2 - x2 * y1;
    }
    return std::abs(area) / 2;
}

std::pair<double, double> Hexagon::center() const {
    double x_sum = 0, y_sum = 0;
    for (const auto& [x, y] : vertices_) {
        x_sum += x;
        y_sum += y;
    }
    return {x_sum / vertices_.size(), y_sum / vertices_.size()};
}

void Hexagon::read(std::istream& in) {
    for (auto& vertex : vertices_) {
        in >> vertex.first >> vertex.second;
    }
}

void Hexagon::print(std::ostream& out) const {
    for (const auto& vertex : vertices_) {
        out << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}
