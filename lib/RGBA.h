#ifndef RGBA_H
#define RGBA_H

#include <iostream>

// A structure for a color.  Each channel is 8 bits [0-255].
struct RGBA {
    RGBA() : r(0), g(0), b(0), a(255) {}
    RGBA(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}

    // C++ TIP:
    // A union struct. Essentially, this makes b <==> channels[0],
    // g <==> channels[1], etc. In other words: b, g, r, and a are
    // stored at the same memory location as channels[4]. Note that
    // sizeof(b)+sizeof(g)+sizeof(r)+sizeof(a) = sizeof(channels)
    // so the memory overlaps **exactly**.
    //
    // You might want to take advantage of union structs in later
    // assignments, although we don't require or expect you to do so.
    //

    union {
        struct { unsigned char r, g, b, a; };
        unsigned char channels[4];
    };

    RGBA operator+(const RGBA &c1) const;
    RGBA operator-(const RGBA &c1) const;
    RGBA operator*(const RGBA &c1) const;
    RGBA operator/(const RGBA &c1) const;

    friend bool operator==(const RGBA &c1, const RGBA &c2);
    friend bool operator!=(const RGBA &c1, const RGBA &c2);

    void print();
};

// A structure for a color.  Each channel is a float (uncapped).
struct RGBAFloat {
    RGBAFloat() : r(0.f), g(0.f), b(0.f), a(255.f) {}
    RGBAFloat(float red, float green, float blue, float alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}

    // C++ TIP:
    // A union struct. Essentially, this makes b <==> channels[0],
    // g <==> channels[1], etc. In other words: b, g, r, and a are
    // stored at the same memory location as channels[4]. Note that
    // sizeof(b)+sizeof(g)+sizeof(r)+sizeof(a) = sizeof(channels)
    // so the memory overlaps **exactly**.
    //
    // You might want to take advantage of union structs in later
    // assignments, although we don't require or expect you to do so.
    //

    union {
        struct { float r, g, b, a; };
        float channels[4];
    };

    RGBAFloat operator+(const RGBAFloat &c1) const;
    RGBAFloat operator-(const RGBAFloat &c1) const;
    RGBAFloat operator*(const RGBAFloat &c1) const;
    RGBAFloat operator/(const RGBAFloat &c1) const;

    void operator*=(const float &num);

    friend bool operator==(const RGBAFloat &c1, const RGBAFloat &c2);
    friend bool operator!=(const RGBAFloat &c1, const RGBAFloat &c2);

    void print();

    void normalize();
    void unNormalize();
    void clamp(const bool &normalized);
};

namespace RGBAUtils{
    RGBA toRGBA(RGBAFloat const &that);
    RGBAFloat toRGBAFloat(RGBA const &that);
    RGBAFloat distance(const RGBAFloat &c1, const RGBAFloat &c2);
}



#endif // RGBA_H
