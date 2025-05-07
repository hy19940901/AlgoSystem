#ifndef ECOMMERCE_OOP_H
#define ECOMMERCE_OOP_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace ecommerce {

/** Interface for printable objects */
class IPrintable {
public:
    virtual void print() const = 0;
    virtual ~IPrintable() = default;
};

/** Represents a user */
class User : public IPrintable {
private:
    std::string username;
    std::string password;
public:
    void setUsername(const std::string& u);
    void setPassword(const std::string& p);
    void print() const override;
};

/** Base product class */
class Product : public IPrintable {
public:
    std::string name;
    double price;
    Product(std::string n, double p);
    virtual void print() const override;
    virtual ~Product() = default;
};

/** Book derived from Product */
class Book : public Product {
private:
    std::string author;
public:
    Book(std::string n, double p, std::string a);
    void print() const override;
};

class InternalProduct : protected Product {
public:
    using Product::name;
    using Product::price;
    InternalProduct(std::string n, double p);
    void print() const;
};

class PrivateProduct : private Product {
public:
    PrivateProduct(std::string n, double p);
    void print() const;
};

class DiscountPolicy {
public:
    virtual double apply(double price) const = 0;
    virtual ~DiscountPolicy() = default;
};

class HolidayDiscount : public DiscountPolicy {
public:
    double apply(double price) const override;
};

class Order {
public:
    int id;
    Order(int i);
    ~Order();
};

class Cart {
public:
    int* data;
    Cart(int val);
    Cart(const Cart& other);
    ~Cart();
    void print() const;
};

class Platform {
public:
    static int totalUsers;
};

extern const double TAX;
inline int square(int x) { return x * x; }

/**
 * @brief Returns the maximum of two values.
 * @tparam T A comparable type.
 * @param a First value
 * @param b Second value
 * @return The greater of a and b
 */
template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

void userFlow();
void productShowcase();
void discountSystem();
void orderLifecycle();
void cartCopyTest();
void platformStats();
void referenceExamples();
void inventoryOverview();
} // namespace ecommerce

#endif
