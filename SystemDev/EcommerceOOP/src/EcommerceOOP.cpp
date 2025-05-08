#include "../include/EcommerceOOP.h"
#include <cstring>
#include <vector>
#include <cstdlib>

#define DISCOUNT_RATE 0.2

namespace ecommerce {

// --- User Implementation ---
User::User(std::string i, std::string u, std::string e)
    : id(std::move(i)), username(std::move(u)), email(std::move(e)) {}

std::string User::getId() const { return id; }
std::string User::getName() const { return username; }

// --- Customer Implementation ---
Customer::Customer(std::string id, std::string u, std::string e, std::string p)
    : User(std::move(id), std::move(u), std::move(e)), password(std::move(p)) {}

bool Customer::login(const std::string& input) const {
    return input == password;
}

void Customer::print() const {
    std::cout << "Customer: " << username << " <" << email << ">" << std::endl;
}

// --- Product Implementation ---
Product::Product(std::string i, std::string n, double p, std::string c, int s)
    : id(std::move(i)), name(std::move(n)), price(p), category(std::move(c)), stock(s) {}

std::string Product::getId() const { return id; }
std::string Product::getName() const { return name; }

void Product::print() const {
    std::cout << "Product: " << name << " [$" << price << ", Stock: " << stock << "]" << std::endl;
}

bool Product::isAvailable() const {
    return stock > 0;
}

double Product::getPrice() const {
    return price;
}

// --- DiscountPolicy Implementation ---
double HolidayDiscount::apply(double price) const {
    return price * (1.0 - DISCOUNT_RATE);
}

// --- Cart Implementation ---
void Cart::addItem(std::shared_ptr<Product> p, int quantity) {
    items[p] += quantity;
}

double Cart::computeTotal(const DiscountPolicy* policy) const {
    double total = 0.0;
    for (const auto& [product, qty] : items) {
        double unit = product->getPrice();
        if (policy) unit = policy->apply(unit);
        total += unit * qty;
    }
    return total;
}

void Cart::print() const {
    for (const auto& [product, qty] : items) {
        product->print();
        std::cout << "Qty: " << qty << std::endl;
    }
}

// --- Order Implementation ---
Order::Order(std::string i, std::shared_ptr<Customer> c, Cart crt)
    : id(std::move(i)), customer(std::move(c)), cart(std::move(crt)), status(OrderStatus::Pending) {}

std::string Order::getId() const {
    return id;
}

std::string Order::getName() const {
    return "Order for " + customer->getName();
}

void Order::print() const {
    std::cout << "[Order] ID: " << id << ", Status: " << toString(status) << std::endl;
    customer->print();
    cart.print();
}

OrderStatus Order::getStatus() const {
    return status;
}

void Order::updateStatus(OrderStatus newStatus) {
    status = newStatus;
}

// --- Educational Demo Function ---
void memoryDemo() {
    std::cout << "\n--- Memory Management Demo ---" << std::endl;

    // Manual new/delete
    Product* legacyProduct = new Product("P003", "Legacy Mouse", 19.99, "Peripherals", 50);
    legacyProduct->print();
    delete legacyProduct;

    // malloc/free
    char* buffer = (char*)malloc(100);
    std::strcpy(buffer, "C-style memory allocation");
    std::cout << buffer << std::endl;
    free(buffer);

    // smart pointer
    std::shared_ptr<Product> modernProduct = std::make_shared<Product>(
        "P004", "Modern Headphones", 89.99, "Audio", 20);
    modernProduct->print();

    // vector
    std::vector<std::shared_ptr<Product>> catalog;
    catalog.push_back(modernProduct);
    catalog.push_back(std::make_shared<Product>("P005", "Monitor", 199.99, "Display", 12));

    std::cout << "\nCatalog Items:" << std::endl;
    for (const auto& p : catalog) {
        p->print();
    }
}

} // namespace ecommerce
