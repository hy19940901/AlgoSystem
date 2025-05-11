// File: src/design_patterns.cpp
#include "../include/design_patterns.hpp"

using namespace std;

// ==================== Inheritance and Polymorphism ==================== //
Animal::Animal(const string& animalName) : name_(animalName) {
    cout << "Animal Constructor: " << name_ << " created." << endl;
}

void Animal::Speak() const {
    cout << "Animal " << name_ << " makes a sound." << endl;
}

Animal::~Animal() {
    cout << "Animal Destructor: " << name_ << " destroyed." << endl;
}

Dog::Dog(const string& dogName) : Animal(dogName) {
    cout << "Dog Constructor: " << name_ << " created." << endl;
}

void Dog::Speak() const {
    cout << "Dog " << name_ << " barks: Woof!" << endl;
}

Dog::~Dog() {
    cout << "Dog Destructor: " << name_ << " destroyed." << endl;
}

Cat::Cat(const string& catName) : Animal(catName) {
    cout << "Cat Constructor: " << name_ << " created." << endl;
}

void Cat::Speak() const {
    cout << "Cat " << name_ << " meows: Meow!" << endl;
}

Cat::~Cat() {
    cout << "Cat Destructor: " << name_ << " destroyed." << endl;
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

void Circle::Draw() const {
    cout << "Drawing a Circle." << endl;
}

Circle::~Circle() {
    cout << "Circle Destructor: Circle destroyed." << endl;
}

Rectangle::Rectangle() {
    cout << "Rectangle Constructor: Rectangle created." << endl;
}

void Rectangle::Draw() const {
    cout << "Drawing a Rectangle." << endl;
}

Rectangle::~Rectangle() {
    cout << "Rectangle Destructor: Rectangle destroyed." << endl;
}

// ======================= Singleton Pattern =========================== //
Singleton* Singleton::instance_ = nullptr;

Singleton::Singleton() {
    cout << "Singleton Constructor: Instance created." << endl;
}

Singleton* Singleton::GetInstance() {
    if (!instance_) {
        instance_ = new Singleton();
    }
    return instance_;
}

void Singleton::ShowMessage() {
    cout << "Singleton Instance Accessed." << endl;
}

Singleton::~Singleton() {
    cout << "Singleton Destructor: Instance destroyed." << endl;
}

FullSingleton* FullSingleton::instance_ = nullptr;
mutex FullSingleton::instance_mutex_;

FullSingleton::FullSingleton() {
    cout << "Full Singleton Constructor: Instance created." << endl;
}

FullSingleton* FullSingleton::GetInstance() {
    lock_guard<mutex> lock(instance_mutex_);
    if (!instance_) {
        instance_ = new FullSingleton();
    }
    return instance_;
}

void FullSingleton::DestroyInstance() {
    lock_guard<mutex> lock(instance_mutex_);
    delete instance_;
    instance_ = nullptr;
    cout << "Full Singleton Destructor: Instance destroyed." << endl;
}

void FullSingleton::ShowMessage() {
    cout << "Full Singleton Instance Accessed." << endl;
}

FullSingleton::~FullSingleton() {}

// ===================== Factory Method Pattern ======================== //
Product::Product(const string& productName) : name_(productName) {
    cout << "Product Constructor: " << name_ << " created." << endl;
}

Product::~Product() {
    cout << "Product Destructor: " << name_ << " destroyed." << endl;
}

ConcreteProductA::ConcreteProductA() : Product("Product A") {}

void ConcreteProductA::Use() const {
    cout << "Using " << name_ << "." << endl;
}

ConcreteProductB::ConcreteProductB() : Product("Product B") {}

void ConcreteProductB::Use() const {
    cout << "Using " << name_ << "." << endl;
}

ProductFactory::ProductFactory() {
    cout << "ProductFactory Constructor called." << endl;
}

ProductFactory::~ProductFactory() {
    cout << "ProductFactory Destructor called." << endl;
}

Product* FactoryA::CreateProduct() const {
    return new ConcreteProductA();
}

Product* FactoryB::CreateProduct() const {
    return new ConcreteProductB();
}

// ======================== Observer Pattern =========================== //
void Subject::Attach(Observer* observer) {
    observers_.push_back(observer);
}

void Subject::Notify(const string& message) {
    for (auto observer : observers_) {
        observer->Update(message);
    }
}

ConcreteObserver::ConcreteObserver(const string& observerName) : name_(observerName) {}

void ConcreteObserver::Update(const string& message) {
    cout << "Observer " << name_ << " received: " << message << endl;
}

// ======================== Strategy Pattern =========================== //
Context::Context(Strategy* strategy) : strategy_(strategy) {}

void Context::SetStrategy(Strategy* new_strategy) {
    strategy_ = new_strategy;
}

void Context::PerformAction() const {
    strategy_->Execute();
}

void StrategyA::Execute() const {
    cout << "Executing Strategy A." << endl;
}

void StrategyB::Execute() const {
    cout << "Executing Strategy B." << endl;
}
