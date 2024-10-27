#include "../include/Octagon.h"
#include <cmath>

Octagon::Octagon(const std::vector<std::pair<double, double>>& vertices) : vertices_(vertices) {
    if (vertices_.size() != 8) {
        throw std::invalid_argument("Octagon должен иметь ровно 8 вершин.");
    }
}


Octagon::Octagon() : vertices_(8) {}


Octagon& Octagon::operator=(const Figure& other) {
    if (this != &other) {
        const Octagon* other_octagon = dynamic_cast<const Octagon*>(&other);
        if (!other_octagon) {
            throw std::invalid_argument("Присваивание объекта другого типа невозможно.");
        }
        this->vertices_ = other_octagon->vertices_;
    }
    return *this;
}


Octagon& Octagon::operator=(Figure&& other) noexcept {
    if (this != &other) {
        Octagon* other_octagon = dynamic_cast<Octagon*>(&other);
        if (other_octagon) {
            this->vertices_ = std::move(other_octagon->vertices_);
        }
    }
    return *this;
}


bool Octagon::operator==(const Figure& other) const {
    const Octagon* other_octagon = dynamic_cast<const Octagon*>(&other);
    return other_octagon && this->vertices_ == other_octagon->vertices_;
}



double Octagon::area() const {
    double area = 0;
    for (size_t i = 0; i < vertices_.size(); ++i) {
        const auto& [x1, y1] = vertices_[i];
        const auto& [x2, y2] = vertices_[(i + 1) % vertices_.size()];
        area += x1 * y2 - x2 * y1;
    }
    return std::abs(area) / 2;
}

std::pair<double, double> Octagon::center() const {
    double x_sum = 0, y_sum = 0;
    for (const auto& [x, y] : vertices_) {
        x_sum += x;
        y_sum += y;
    }
    return {x_sum / vertices_.size(), y_sum / vertices_.size()};
}

void Octagon::read(std::istream& in) {
    for (auto& vertex : vertices_) {
        in >> vertex.first >> vertex.second;
    }
}

void Octagon::print(std::ostream& out) const {
    for (const auto& vertex : vertices_) {
        out << "(" << vertex.first << ", " << vertex.second << ") ";
    }
}
