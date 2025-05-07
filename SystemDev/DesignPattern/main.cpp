#include <iostream>
#include <memory>
#include <vector>
#include <mutex>
using namespace std;

// ----------------------------------------
// 1. Regular Class with Constructors, Inheritance, and Virtual Functions
// Demonstrates basic inheritance, virtual functions, pure virtual functions, and constructors.
// ----------------------------------------
class Animal {
protected:
    string name; // Protected to allow derived classes to initialize it

public:
    Animal(const string& animalName) : name(animalName) {
        cout << "Animal Constructor: " << name << " created." << endl;
    }

    virtual void speak() const { // Virtual function with default implementation
        cout << "Animal " << name << " makes a sound." << endl;
    }

    virtual ~Animal() {
        cout << "Animal Destructor: " << name << " destroyed." << endl;
    }
};

class Dog : public Animal {
public:
    Dog(const string& dogName) : Animal(dogName) {
        cout << "Dog Constructor: " << name << " created." << endl;
    }

    void speak() const override { // Overridden method
        cout << "Dog " << name << " barks: Woof!" << endl;
    }

    ~Dog() {
        cout << "Dog Destructor: " << name << " destroyed." << endl;
    }
};

class Cat : public Animal {
public:
    Cat(const string& catName) : Animal(catName) {
        cout << "Cat Constructor: " << name << " created." << endl;
    }

    void speak() const override { // Overridden method
        cout << "Cat " << name << " meows: Meow!" << endl;
    }

    ~Cat() {
        cout << "Cat Destructor: " << name << " destroyed." << endl;
    }
};

// Abstract class with a pure virtual function
class Shape {
public:
    virtual void draw() const = 0; // Pure virtual function

    Shape() {
        cout << "Shape Constructor called." << endl;
    }

    virtual ~Shape() {
        cout << "Shape Destructor called." << endl;
    }
};

class Circle : public Shape {
public:
    Circle() {
        cout << "Circle Constructor: Circle created." << endl;
    }

    void draw() const override {
        cout << "Drawing a Circle." << endl;
    }

    ~Circle() {
        cout << "Circle Destructor: Circle destroyed." << endl;
    }
};

class Rectangle : public Shape {
public:
    Rectangle() {
        cout << "Rectangle Constructor: Rectangle created." << endl;
    }

    void draw() const override {
        cout << "Drawing a Rectangle." << endl;
    }

    ~Rectangle() {
        cout << "Rectangle Destructor: Rectangle destroyed." << endl;
    }
};

// ----------------------------------------
// 2. Singleton Pattern with Constructor
// Ensures a class has only one instance and provides a global access point.
// Used for objects that are globally shared, such as configuration managers.
// ----------------------------------------
class Singleton {
private:
    static Singleton* instance; // Static instance
    Singleton() {
        cout << "Singleton Constructor: Instance created." << endl;
    } // Private constructor

public:
    static Singleton* getInstance() {
        if (!instance) {
            instance = new Singleton();
        }
        return instance;
    }

    void showMessage() {
        cout << "Singleton Instance Accessed." << endl;
    }

    ~Singleton() {
        cout << "Singleton Destructor: Instance destroyed." << endl;
    }

    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

// Static instance initialization
Singleton* Singleton::instance = nullptr;

// ----------------------------------------
// 3. Full Singleton Pattern with Constructor
// Similar to Singleton but allows explicit destruction.
// Extends the Singleton pattern to allow explicit destruction of the instance.
// Useful when resources need to be freed during runtime.
// ----------------------------------------
class FullSingleton {
private:
    static FullSingleton* instance; // Static pointer
    static mutex instanceMutex;     // Mutex for thread safety
    FullSingleton() {
        cout << "Full Singleton Constructor: Instance created." << endl;
    } // Private constructor

public:
    static FullSingleton* getInstance() {
        lock_guard<mutex> lock(instanceMutex);
        if (!instance) {
            instance = new FullSingleton();
        }
        return instance;
    }

    static void destroyInstance() {
        lock_guard<mutex> lock(instanceMutex);
        delete instance;
        instance = nullptr;
        cout << "Full Singleton Destructor: Instance destroyed." << endl;
    }

    void showMessage() {
        cout << "Full Singleton Instance Accessed." << endl;
    }

    ~FullSingleton() {}

    // Delete copy constructor and assignment operator
    FullSingleton(const FullSingleton&) = delete;
    FullSingleton& operator=(const FullSingleton&) = delete;
};

// Static members initialization
FullSingleton* FullSingleton::instance = nullptr;
mutex FullSingleton::instanceMutex;

// ----------------------------------------
// 4. Factory Method Pattern with Constructors
// Defines an interface for creating objects, allowing subclasses to decide which class to instantiate.
// Useful for situations where the exact type of object isn't known at compile time.
// ----------------------------------------
class Product {
protected:
    string name;

public:
    Product(const string& productName) : name(productName) {
        cout << "Product Constructor: " << name << " created." << endl;
    }

    virtual void use() const = 0; // Pure virtual function

    virtual ~Product() {
        cout << "Product Destructor: " << name << " destroyed." << endl;
    }
};

class ConcreteProductA : public Product {
public:
    ConcreteProductA() : Product("Product A") {}

    void use() const override {
        cout << "Using " << name << "." << endl;
    }
};

class ConcreteProductB : public Product {
public:
    ConcreteProductB() : Product("Product B") {}

    void use() const override {
        cout << "Using " << name << "." << endl;
    }
};

// Factory interface
class ProductFactory {
public:
    virtual Product* createProduct() const = 0; // Factory method

    ProductFactory() {
        cout << "ProductFactory Constructor called." << endl;
    }

    virtual ~ProductFactory() {
        cout << "ProductFactory Destructor called." << endl;
    }
};

class FactoryA : public ProductFactory {
public:
    Product* createProduct() const override {
        return new ConcreteProductA();
    }
};

class FactoryB : public ProductFactory {
public:
    Product* createProduct() const override {
        return new ConcreteProductB();
    }
};

// ----------------------------------------
// 5. Observer Pattern
// Defines a one-to-many dependency between objects so that when one changes state, all dependents are notified.
// Useful in event-driven systems like GUI frameworks or data synchronization.
// ----------------------------------------
class Observer {
public:
    virtual void update(const string& message) = 0;
    virtual ~Observer() {}
};

class Subject {
private:
    vector<Observer*> observers;

public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void notify(const string& message) {
        for (auto observer : observers) {
            observer->update(message);
        }
    }
};

class ConcreteObserver : public Observer {
private:
    string name;

public:
    ConcreteObserver(const string& observerName) : name(observerName) {}

    void update(const string& message) override {
        cout << "Observer " << name << " received: " << message << endl;
    }
};

// ----------------------------------------
// 6. Strategy Pattern
// Defines a family of algorithms, encapsulates each one, and makes them interchangeable.
// Useful for situations where an object must dynamically change its behavior.
// ----------------------------------------
class Strategy {
public:
    virtual void execute() const = 0;
    virtual ~Strategy() {}
};

class StrategyA : public Strategy {
public:
    void execute() const override {
        cout << "Executing Strategy A." << endl;
    }
};

class StrategyB : public Strategy {
public:
    void execute() const override {
        cout << "Executing Strategy B." << endl;
    }
};

class Context {
private:
    Strategy* strategy;

public:
    Context(Strategy* strategy) : strategy(strategy) {}

    void setStrategy(Strategy* newStrategy) {
        strategy = newStrategy;
    }

    void performAction() const {
        strategy->execute();
    }
};

// ----------------------------------------
// Main Function to Demonstrate Patterns
// ----------------------------------------
int main() {
    // 1. Regular Class
    Animal* dog = new Dog("Buddy");
    Animal* cat = new Cat("Kitty");
    dog->speak();
    cat->speak();
    delete dog;
    delete cat;

    Shape* circle = new Circle();
    Shape* rectangle = new Rectangle();
    circle->draw();
    rectangle->draw();
    delete circle;
    delete rectangle;

    // 2. Singleton Pattern
    Singleton* s1 = Singleton::getInstance();
    s1->showMessage();

    // 3. Full Singleton Pattern
    FullSingleton* fs1 = FullSingleton::getInstance();
    fs1->showMessage();
    FullSingleton::destroyInstance();

    // 4. Factory Method Pattern
    unique_ptr<ProductFactory> factoryA(new FactoryA());
    unique_ptr<Product> productA(factoryA->createProduct());
    productA->use();

    unique_ptr<ProductFactory> factoryB(new FactoryB());
    unique_ptr<Product> productB(factoryB->createProduct());
    productB->use();

    // 5. Observer Pattern
    Subject subject;
    ConcreteObserver observer1("Observer1");
    ConcreteObserver observer2("Observer2");
    subject.attach(&observer1);
    subject.attach(&observer2);
    subject.notify("Important Update!");

    // 6. Strategy Pattern
    StrategyA strategyA;
    StrategyB strategyB;
    Context context(&strategyA);
    context.performAction(); // Output: Executing Strategy A.
    context.setStrategy(&strategyB);
    context.performAction(); // Output: Executing Strategy B.

    return 0;
}
