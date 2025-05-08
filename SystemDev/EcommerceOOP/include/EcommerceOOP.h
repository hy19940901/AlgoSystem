#ifndef ECOMMERCE_OOP_H
#define ECOMMERCE_OOP_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>

namespace ecommerce {

/**
 * @brief Enumeration representing possible states of an order.
 *        Used to track the lifecycle of an order.
 */
enum class OrderStatus {
    Pending,    ///< Order has been created but not paid yet
    Paid,       ///< Order has been paid by the customer
    Shipped,    ///< Order has been shipped by the seller
    Delivered   ///< Order has been delivered to the customer
};

/**
 * @brief Converts an OrderStatus enum value to its string representation.
 *
 * @param status The enum value of the order status.
 * @return A human-readable string representing the order status.
 */
inline std::string toString(OrderStatus status) {
    switch (status) {
        case OrderStatus::Pending: return "Pending";
        case OrderStatus::Paid: return "Paid";
        case OrderStatus::Shipped: return "Shipped";
        case OrderStatus::Delivered: return "Delivered";
        default: return "Unknown";
    }
}

/**
 * @brief Abstract base class for all core objects in the e-commerce domain.
 *        Provides a uniform interface for ID, name, and printing.
 */
class Entity {
public:
    virtual std::string getId() const = 0;    ///< Returns the unique identifier of the entity
    virtual std::string getName() const = 0;  ///< Returns the name/label of the entity
    virtual void print() const = 0;           ///< Prints summary information of the entity
    virtual ~Entity() = default;              ///< Virtual destructor for safe polymorphic deletion
};

/**
 * @brief Abstract base class representing a system user.
 *        Extends Entity with login credentials.
 */
class User : public Entity {
protected:
    std::string id;        ///< User ID
    std::string username;  ///< Username displayed in UI
    std::string email;     ///< Email for communication
public:
    User(std::string i, std::string u, std::string e);
    std::string getId() const override;
    std::string getName() const override;

    /**
     * @brief Authenticates the user with a password.
     * @param password The input password to check.
     * @return True if the password is correct.
     */
    virtual bool login(const std::string& password) const = 0;
};

/**
 * @brief A concrete class representing a registered customer.
 *        Stores a password and overrides print and login.
 */
class Customer : public User {
    std::string password; ///< Stored user password
public:
    Customer(std::string id, std::string u, std::string e, std::string p);
    bool login(const std::string& input) const override;
    void print() const override;
};

/**
 * @brief Represents a product available for purchase.
 *        Includes pricing, categorization, and inventory.
 */
class Product : public Entity {
protected:
    std::string id;        ///< Product ID
    std::string name;      ///< Product name
    double price;          ///< Price per unit
    std::string category;  ///< Product category (e.g., Books, Electronics)
    int stock;             ///< Inventory count
public:
    Product(std::string i, std::string n, double p, std::string c, int s);
    std::string getId() const override;
    std::string getName() const override;
    void print() const override;

    /**
     * @brief Checks if the product is available.
     * @return True if stock is greater than zero.
     */
    bool isAvailable() const;

    /**
     * @brief Returns the price of the product.
     * @return Price per unit.
     */
    double getPrice() const;
};

/**
 * @brief Abstract interface for discount policies.
 *        Allows pricing logic to be injected dynamically.
 */
class DiscountPolicy {
public:
    /**
     * @brief Applies the discount to a given price.
     * @param price Original price.
     * @return Discounted price.
     */
    virtual double apply(double price) const = 0;
    virtual ~DiscountPolicy() = default;
};

/**
 * @brief A fixed 20% discount for holidays.
 */
class HolidayDiscount : public DiscountPolicy {
public:
    double apply(double price) const override;
};

/**
 * @brief Represents a user's shopping cart.
 *        Tracks selected products and quantities.
 */
class Cart {
    std::unordered_map<std::shared_ptr<Product>, int> items; ///< Product to quantity map
public:
    /**
     * @brief Adds a product to the cart.
     * @param p Product to add.
     * @param quantity Number of units to add.
     */
    void addItem(std::shared_ptr<Product> p, int quantity);

    /**
     * @brief Computes the total cost of the cart.
     * @param policy Optional discount policy to apply.
     * @return Total price after discount (if any).
     */
    double computeTotal(const DiscountPolicy* policy = nullptr) const;

    /**
     * @brief Prints all cart contents (products and their quantities).
     */
    void print() const;
};

/**
 * @brief Represents a placed order.
 *        Captures the cart snapshot and user at time of checkout.
 */
class Order : public Entity {
    std::string id;                              ///< Order ID
    std::shared_ptr<Customer> customer;          ///< Customer who placed the order
    Cart cart;                                   ///< Cart contents
    OrderStatus status;                          ///< Current status of the order
public:
    Order(std::string i, std::shared_ptr<Customer> c, Cart crt);
    std::string getId() const override;
    std::string getName() const override;
    void print() const override;

    /**
     * @brief Retrieves the current status of the order.
     * @return Enum value of order status.
     */
    OrderStatus getStatus() const;

    /**
     * @brief Updates the status of the order.
     * @param newStatus New status to assign.
     */
    void updateStatus(OrderStatus newStatus);
};

/**
 * @brief Demonstrates different memory management techniques:
 *        new/delete, malloc/free, smart pointers, STL containers.
 */
void memoryDemo();

} // namespace ecommerce

#endif
