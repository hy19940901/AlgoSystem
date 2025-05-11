#include "../include/ecommerce_oop.h"
#include <cstring>
#include <vector>
#include <cstdlib>

#define DISCOUNT_RATE 0.2

namespace ecommerce {

// --- User ---
User::User(std::string id, std::string username, std::string email)
    : id_(std::move(id)), username_(std::move(username)), email_(std::move(email)) {}

std::string User::get_id() const { return id_; }
std::string User::get_name() const { return username_; }

// --- Customer ---
Customer::Customer(std::string id, std::string username, std::string email, std::string password)
    : User(std::move(id), std::move(username), std::move(email)), password_(std::move(password)) {}

bool Customer::login(const std::string& input) const {
    return input == password_;
}

void Customer::print() const {
    std::cout << "Customer: " << username_ << " <" << email_ << ">" << std::endl;
}

// --- Product ---
Product::Product(std::string id, std::string name, double price, std::string category, int stock)
    : id_(std::move(id)), name_(std::move(name)), price_(price),
      category_(std::move(category)), stock_(stock) {}

std::string Product::get_id() const { return id_; }
std::string Product::get_name() const { return name_; }

void Product::print() const {
    std::cout << "Product: " << name_ << " [$" << price_ << ", Stock: " << stock_ << "]" << std::endl;
}

bool Product::is_available() const {
    return stock_ > 0;
}

double Product::get_price() const {
    return price_;
}

// --- HolidayDiscount ---
double HolidayDiscount::apply(double price) const {
    return price * (1.0 - DISCOUNT_RATE);
}

// --- Cart ---
void Cart::add_item(std::shared_ptr<Product> product, int quantity) {
    items_[product] += quantity;
}

double Cart::compute_total(const DiscountPolicy* policy) const {
    double total = 0.0;
    for (const auto& [product, qty] : items_) {
        double unit_price = product->get_price();
        if (policy) unit_price = policy->apply(unit_price);
        total += unit_price * qty;
    }
    return total;
}

void Cart::print() const {
    for (const auto& [product, qty] : items_) {
        product->print();
        std::cout << "Qty: " << qty << std::endl;
    }
}

// --- Order ---
Order::Order(std::string id, std::shared_ptr<Customer> customer, Cart cart)
    : id_(std::move(id)), customer_(std::move(customer)), cart_(std::move(cart)),
      status_(OrderStatus::Pending) {}

std::string Order::get_id() const {
    return id_;
}

std::string Order::get_name() const {
    return "Order for " + customer_->get_name();
}

void Order::print() const {
    std::cout << "[Order] ID: " << id_ << ", Status: " << to_string(status_) << std::endl;
    customer_->print();
    cart_.print();
}

OrderStatus Order::get_status() const {
    return status_;
}

void Order::update_status(OrderStatus new_status) {
    status_ = new_status;
}

// --- memory_demo ---
void memory_demo() {
    std::cout << "\n--- Memory Management Demo ---" << std::endl;

    Product* legacy_product = new Product("P003", "Legacy Mouse", 19.99, "Peripherals", 50);
    legacy_product->print();
    delete legacy_product;

    char* buffer = (char*)malloc(100);
    std::strcpy(buffer, "C-style memory allocation");
    std::cout << buffer << std::endl;
    free(buffer);

    std::shared_ptr<Product> modern_product = std::make_shared<Product>(
        "P004", "Modern Headphones", 89.99, "Audio", 20);
    modern_product->print();

    std::vector<std::shared_ptr<Product>> catalog;
    catalog.push_back(modern_product);
    catalog.push_back(std::make_shared<Product>("P005", "Monitor", 199.99, "Display", 12));

    std::cout << "\nCatalog Items:" << std::endl;
    for (const auto& p : catalog) {
        p->print();
    }
}

}  // namespace ecommerce
