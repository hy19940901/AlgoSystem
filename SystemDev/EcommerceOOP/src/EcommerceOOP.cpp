#include "../include/EcommerceOOP.h"
#include <iostream>
using namespace std;

namespace ecommerce {

void User::setUsername(const string& u) { username = u; }
void User::setPassword(const string& p) { password = p; }
void User::print() const { cout << "User: " << username << endl; }

Product::Product(string n, double p) : name(n), price(p) {}
void Product::print() const { cout << "Product: " << name << ", $" << price << endl; }
Book::Book(string n, double p, string a) : Product(n, p), author(a) {}
void Book::print() const { cout << "Book: " << name << " by " << author << ", $" << price << endl; }
InternalProduct::InternalProduct(string n, double p) : Product(n, p) {}
void InternalProduct::print() const { cout << "InternalProduct: " << name << ", $" << price << endl; }
PrivateProduct::PrivateProduct(string n, double p) : Product(n, p) {}
void PrivateProduct::print() const { cout << "PrivateProduct: [hidden details]" << endl; }

double HolidayDiscount::apply(double price) const { return price * 0.8; }

Order::Order(int i) : id(i) { cout << "Order created: " << id << endl; }
Order::~Order() { cout << "Order destroyed: " << id << endl; }
Cart::Cart(int val) { data = new int(val); }
Cart::Cart(const Cart& other) { data = new int(*other.data); }
Cart::~Cart() { delete data; }
void Cart::print() const { cout << "Cart value: " << *data << endl; }
int Platform::totalUsers = 0;
const double TAX = 0.08;

void userFlow() {
    User u;
    u.setUsername("alice");
    u.setPassword("1234");
    u.print();
}

void productShowcase() {
    Book b("C++ Primer", 59.9, "Lippman"); b.print();
    InternalProduct ip("InternalWidget", 10.0); ip.print();
    PrivateProduct pp("PrivateWidget", 5.0); pp.print();
}

void discountSystem() {
    HolidayDiscount h;
    DiscountPolicy* d = &h;
    cout << "Original: $100, Discounted: $" << d->apply(100) << endl;
    cout << "Max(3, 7): " << getMax(3, 7) << endl;
}

void orderLifecycle() {
    Order* o = new Order(1);
    delete o;
    unique_ptr<Order> smart = make_unique<Order>(2);
}

void cartCopyTest() {
    Cart c1(10);
    Cart c2 = c1;
    *c1.data = 20;
    c1.print();
    c2.print();
}

void platformStats() {
    Platform::totalUsers++;
    cout << "Total users: " << Platform::totalUsers << ", Tax: " << TAX << endl;
}

void referenceExamples() {
    int a = 5;
    int& ref = a;
    int&& r = 6 + 1;
    cout << "Ref: " << ref << ", RVal: " << r << ", Square: " << square(ref) << endl;
}

void inventoryOverview() {
    vector<string> items = {"apple", "banana"};
    unordered_map<string, double> prices = {{"apple", 1.0}, {"banana", 0.8}};
    for (const auto& item : items) cout << item << " ";
    cout << endl;
    for (const auto& [k, v] : prices) cout << k << ": $" << v << endl;
}

} // namespace ecommerce
