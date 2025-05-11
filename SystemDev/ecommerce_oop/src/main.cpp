#include "../include/ecommerce_oop.h"
#include <iostream>
#include <memory>
#include <iomanip>

using namespace ecommerce;

int main() {
    // Create a customer
    std::shared_ptr<Customer> customer = std::make_shared<Customer>(
        "C001", "Alice", "alice@example.com", "password123");

    // Create products
    std::shared_ptr<Product> product1 = std::make_shared<Product>(
        "P001", "C++ Primer", 59.99, "Books", 10);
    std::shared_ptr<Product> product2 = std::make_shared<Product>(
        "P002", "Mechanical Keyboard", 129.50, "Electronics", 5);

    // Add products to cart
    Cart cart;
    cart.add_item(product1, 2);  // 2 books
    cart.add_item(product2, 1);  // 1 keyboard

    // Display cart contents
    std::cout << "\n--- CART CONTENTS ---" << std::endl;
    cart.print();

    // Apply discount
    HolidayDiscount discount;
    double discounted_total = cart.compute_total(&discount);

    // Create order
    Order order("O1001", customer, cart);

    // Print order
    std::cout << "\n--- ORDER DETAILS ---" << std::endl;
    order.print();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total after discount: $" << discounted_total << std::endl;

    // Update order status
    order.update_status(OrderStatus::Paid);
    std::cout << "Updated status: " << to_string(order.get_status()) << std::endl;

    // Run memory demo
    memory_demo();

    return 0;
}
