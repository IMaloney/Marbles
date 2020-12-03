#include "RGBA.h"
#include "math.h"

RGBA RGBA::operator+(const RGBA &that) const {
    return RGBA(this->r + that.r, this->g + that.g, this->b + that.b, this->a + that.a);
}

RGBA RGBA::operator-(const RGBA &that) const {
    return RGBA(this->r - that.r, this->g - that.g, this->b - that.b, this->a - that.a);
}

RGBA RGBA::operator*(const RGBA &that) const {
    return RGBA(this->r * that.r, this->g * that.g, this->b * that.b, this->a * that.a);
}

RGBA RGBA::operator/(const RGBA &that) const {
    return RGBA(this->r / that.r, this->g / that.g, this->b / that.b, this->a / that.a);
}

bool operator==(const RGBA &c1, const RGBA &c2) {
    return (c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b) && (c1.a == c2.a);
}

bool operator!=(const RGBA &c1, const RGBA &c2) {
    return !operator==(c1, c2);
}

// testing
void RGBA::print(){
    std::cout << "red: " << static_cast<float>(this->r) << " green: " << static_cast<float>(this->g) << " blue: " << static_cast<float>(this->b) << std::endl;
}


RGBAFloat RGBAFloat::operator+(const RGBAFloat &that) const {
    return RGBAFloat(this->r + that.r, this->g + that.g, this->b + that.b, this->a + that.a);
}

RGBAFloat RGBAFloat::operator-(const RGBAFloat &that) const {
    return RGBAFloat(this->r - that.r, this->g - that.g, this->b - that.b, this->a - that.a);
}

RGBAFloat RGBAFloat::operator*(const RGBAFloat &that) const {
    return RGBAFloat(this->r * that.r, this->g * that.g, this->b * that.b, this->a * that.a);
}

RGBAFloat RGBAFloat::operator/(const RGBAFloat &that) const {
    return RGBAFloat(this->r / that.r, this->g / that.g, this->b / that.b, this->a / that.a);
}

void RGBAFloat::operator*=(const float &num) {
    this->r *= num;
    this->g *= num;
    this->b *= num;
}

bool operator==(const RGBAFloat &c1, const RGBAFloat &c2) {
    return (c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b) && (c1.a == c2.a);
}

bool operator!=(const RGBAFloat &c1, const RGBAFloat &c2) {
    return !operator==(c1, c2);
}


// testing
void RGBAFloat::print(){
    std::cout << "red: " << this->r << " green: " << this->g << " blue: " << this->b << std::endl;
}

// see if we can just modify the original
void RGBAFloat::normalize() {
    this->r /= 255.f;
    this->b /= 255.f;
    this->g /= 255.f;
}

void RGBAFloat::unNormalize() {
    this->r *= 255.f;
    this->b *= 255.f;
    this->g *= 255.f;
}

void RGBAFloat::clamp(const bool &normalized) {
    float val = (normalized) ? 1.f : 255.f;
    this->r = (this->r < 0) ? 0 : (this->r > val) ? val : this->r;
    this->g = (this->g < 0) ? 0 : (this->g > val) ? val : this->g;
    this->b = (this->b < 0) ? 0 : (this->b > val) ? val : this->b;

}

RGBAFloat RGBAUtils::toRGBAFloat(RGBA const &that) {
    return RGBAFloat(static_cast<float>(that.r), static_cast<float>(that.g), static_cast<float>(that.b), static_cast<float>(that.a));
}


RGBA RGBAUtils::toRGBA(RGBAFloat const &that) {
    return RGBA(static_cast<unsigned char>(that.r), static_cast<unsigned char>(that.g), static_cast<unsigned char>(that.b), static_cast<unsigned char>(that.a));
}

RGBAFloat RGBAUtils::distance(const RGBAFloat &c1, const RGBAFloat &c2) {
    float r, g, b;
    // need to check this
    r = std::sqrt(std::pow(c1.r, 2.0) + std::pow((c2.r), 2.0));
    g = std::sqrt(std::pow((c1.g), 2.0) + std::pow((c2.g), 2.0));
    b = std::sqrt(std::pow((c1.b), 2.0) + std::pow((c2.b), 2.0));
    return RGBAFloat((r), (g), (b), c1.a);
}
