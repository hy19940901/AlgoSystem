// File: src/design_patterns.cpp
#include "../include/design_patterns.hpp"

using namespace std;

// ==================== Inheritance and Polymorphism ==================== //
Animal::Animal(const string& animalName) : name(animalName) {
    cout << "Animal Constructor: " << name << " created." << endl;
}

void Animal::speak() const {
    cout << "Animal " << name << " makes a sound." << endl;
}

Animal::~Animal() {
    cout << "Animal Destructor: " << name << " destroyed." << endl;
}

Dog::Dog(const string& dogName) : Animal(dogName) {
    cout << "Dog Constructor: " << name << " created." << endl;
}

void Dog::speak() const {
    cout << "Dog " << name << " barks: Woof!" << endl;
}

Dog::~Dog() {
    cout << "Dog Destructor: " << name << " destroyed." << endl;
}

Cat::Cat(const string& catName) : Animal(catName) {
    cout << "Cat Constructor: " << name << " created." << endl;
}

void Cat::speak() const {
    cout << "Cat " << name << " meows: Meow!" << endl;
}

Cat::~Cat() {
    cout << "Cat Destructor: " << name << " destroyed." << endl;
}

// ================= Abstract Classes and Interfaces =================== //
Shape::Shape() {
    cout << "Shape Constructor called." << endl;
}

Shape::~Shape() {
    cout << "Shape Destructor called." << endl;
}

Circle::Circle() {
    cout << "Circle Constructor: Circle created." << endl;
}

void Circle::draw() const {
    cout << "Drawing a Circle." << endl;
}

Circle::~Circle() {
    cout << "Circle Destructor: Circle destroyed." << endl;
}

Rectangle::Rectangle() {
    cout << "Rectangle Constructor: Rectangle created." << endl;
}

void Rectangle::draw() const {
    cout << "Drawing a Rectangle." << endl;
}

Rectangle::~Rectangle() {
    cout << "Rectangle Destructor: Rectangle destroyed." << endl;
}

// ======================= Singleton Pattern =========================== //
Singleton* Singleton::instance = nullptr;

Singleton::Singleton() {
    cout << "Singleton Constructor: Instance created." << endl;
}

Singleton* Singleton::getInstance() {
    if (!instance) {
        instance = new Singleton();
    }
    return instance;
}

void Singleton::showMessage() {
    cout << "Singleton Instance Accessed." << endl;
}

Singleton::~Singleton() {
    cout << "Singleton Destructor: Instance destroyed." << endl;
}

FullSingleton* FullSingleton::instance = nullptr;
mutex FullSingleton::instanceMutex;

FullSingleton::FullSingleton() {
    cout << "Full Singleton Constructor: Instance created." << endl;
}

FullSingleton* FullSingleton::getInstance() {
    lock_guard<mutex> lock(instanceMutex);
    if (!instance) {
        instance = new FullSingleton();
    }
    return instance;
}

void FullSingleton::destroyInstance() {
    lock_guard<mutex> lock(instanceMutex);
    delete instance;
    instance = nullptr;
    cout << "Full Singleton Destructor: Instance destroyed." << endl;
}

void FullSingleton::showMessage() {
    cout << "Full Singleton Instance Accessed." << endl;
}

FullSingleton::~FullSingleton() {}

// ===================== Factory Method Pattern ======================== //
Product::Product(const string& productName) : name(productName) {
    cout << "Product Constructor: " << name << " created." << endl;
}

Product::~Product() {
    cout << "Product Destructor: " << name << " destroyed." << endl;
}

ConcreteProductA::ConcreteProductA() : Product("Product A") {}

void ConcreteProductA::use() const {
    cout << "Using " << name << "." << endl;
}

ConcreteProductB::ConcreteProductB() : Product("Product B") {}

void ConcreteProductB::use() const {
    cout << "Using " << name << "." << endl;
}

ProductFactory::ProductFactory() {
    cout << "ProductFactory Constructor called." << endl;
}

ProductFactory::~ProductFactory() {
    cout << "ProductFactory Destructor called." << endl;
}

Product* FactoryA::createProduct() const {
    return new ConcreteProductA();
}

Product* FactoryB::createProduct() const {
    return new ConcreteProductB();
}

// ======================== Observer Pattern =========================== //
void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::notify(const string& message) {
    for (auto observer : observers) {
        observer->update(message);
    }
}

ConcreteObserver::ConcreteObserver(const string& observerName) : name(observerName) {}

void ConcreteObserver::update(const string& message) {
    cout << "Observer " << name << " received: " << message << endl;
}

// ======================== Strategy Pattern =========================== //
Context::Context(Strategy* strategy) : strategy(strategy) {}

void Context::setStrategy(Strategy* newStrategy) {
    strategy = newStrategy;
}

void Context::performAction() const {
    strategy->execute();
}

void StrategyA::execute() const {
    cout << "Executing Strategy A." << endl;
}

void StrategyB::execute() const {
    cout << "Executing Strategy B." << endl;
}
