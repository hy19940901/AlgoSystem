#include "../include/EcommerceOOP.h"
#include <iostream>
#include <memory>
#include <iomanip> // for setprecision

using namespace ecommerce;

int main() {
    // Create a customer
    std::shared_ptr<Customer> customer = std::make_shared<Customer>(
        "C001", "Alice", "alice@example.com", "password123");

    // Create products
    std::shared_ptr<Product> p1 = std::make_shared<Product>(
        "P001", "C++ Primer", 59.99, "Books", 10);
    std::shared_ptr<Product> p2 = std::make_shared<Product>(
        "P002", "Mechanical Keyboard", 129.50, "Electronics", 5);

    // Add products to cart
    Cart cart;
    cart.addItem(p1, 2);  // 2 books
    cart.addItem(p2, 1);  // 1 keyboard

    // Display cart contents
    std::cout << "\n--- CART CONTENTS ---" << std::endl;
    cart.print();

    // Apply discount
    HolidayDiscount discount;
    double discountedTotal = cart.computeTotal(&discount);

    // Create order
    Order order("O1001", customer, cart);

    // Print order
    std::cout << "\n--- ORDER DETAILS ---" << std::endl;
    order.print();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total after discount: $" << discountedTotal << std::endl;

    // Update order status
    order.updateStatus(OrderStatus::Paid);
    std::cout << "Updated status: " << toString(order.getStatus()) << std::endl;

    // Run memory demo
    memoryDemo();

    return 0;
}
