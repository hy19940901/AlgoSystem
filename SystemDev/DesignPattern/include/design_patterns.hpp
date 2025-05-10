// Folder: include/design_patterns
// File: design_patterns.hpp
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <mutex>

// =======================================================================
// Inheritance and Polymorphism
// =======================================================================
/**
 * @section Inheritance
 * @brief Demonstrates classical OOP inheritance and polymorphism.
 *
 * Concept:
 * - A base class defines a general interface.
 * - Derived classes provide specialized behavior.
 *
 * Pros:
 * - Encourages code reuse.
 * - Enables polymorphism through base class pointers.
 *
 * Cons:
 * - Tight coupling between base and derived classes.
 * - Fragile base class problem (modifying base class impacts all children).
 */

class Animal {
protected:
    std::string name;

public:
    Animal(const std::string& animalName);
    virtual void speak() const; ///< Can be overridden by derived classes
    virtual ~Animal();
};

class Dog : public Animal {
public:
    Dog(const std::string& dogName);
    void speak() const override;
    ~Dog();
};

class Cat : public Animal {
public:
    Cat(const std::string& catName);
    void speak() const override;
    ~Cat();
};

// =======================================================================
// Abstract Classes and Interfaces
// =======================================================================
/**
 * @section Abstract Classes
 * @brief Define interfaces with pure virtual functions for polymorphic behavior.
 *
 * Purpose:
 * - Enforce contract for subclasses.
 * - Support runtime polymorphism.
 *
 * Pros:
 * - Guarantees method implementation in derived classes.
 * - Decouples interface from implementation.
 *
 * Cons:
 * - Cannot instantiate abstract classes.
 */

class Shape {
public:
    Shape();
    virtual void draw() const = 0;
    virtual ~Shape();
};

class Circle : public Shape {
public:
    Circle();
    void draw() const override;
    ~Circle();
};

class Rectangle : public Shape {
public:
    Rectangle();
    void draw() const override;
    ~Rectangle();
};

// =======================================================================
// Singleton Pattern
// =======================================================================
/**
 * @section Singleton
 * @brief Restricts a class to a single instance and provides a global access point.
 *
 * Purpose:
 * - Ensure only one object of a class exists (e.g., config manager, logger).
 *
 * Pros:
 * - Controlled access to the sole instance.
 * - Reduces memory footprint.
 *
 * Cons:
 * - Global state can lead to testing and concurrency issues.
 * - Hidden dependencies.
 */

class Singleton {
private:
    static Singleton* instance; ///< Static pointer ensures only one instance
    Singleton(); ///< Private constructor prevents external instantiation

public:
    static Singleton* getInstance(); ///< Access point for the singleton instance
    void showMessage(); ///< Sample function to show singleton behavior
    ~Singleton();

    Singleton(const Singleton&) = delete; ///< Prevent copying
    Singleton& operator=(const Singleton&) = delete; ///< Prevent assignment
};

class FullSingleton {
private:
    static FullSingleton* instance;
    static std::mutex instanceMutex; ///< Protects instance creation for thread safety
    FullSingleton(); ///< Hidden constructor

public:
    static FullSingleton* getInstance(); ///< Thread-safe accessor
    static void destroyInstance(); ///< Allows explicit destruction (advanced use case)
    void showMessage();
    ~FullSingleton();

    FullSingleton(const FullSingleton&) = delete;
    FullSingleton& operator=(const FullSingleton&) = delete;
};

// =======================================================================
// Factory Method Pattern
// =======================================================================
/**
 * @section Factory Method
 * @brief Delegates object creation to subclasses.
 *
 * Purpose:
 * - Decouple object creation from usage.
 * - Promote object-oriented design by reducing direct dependencies.
 *
 * Pros:
 * - Follows Open/Closed Principle.
 * - Simplifies client code.
 *
 * Cons:
 * - Increases number of classes.
 * - Can be overkill for simple instantiations.
 */

class Product {
protected:
    std::string name;

public:
    Product(const std::string& productName);
    virtual void use() const = 0;
    virtual ~Product();
};

class ConcreteProductA : public Product {
public:
    ConcreteProductA();
    void use() const override;
};

class ConcreteProductB : public Product {
public:
    ConcreteProductB();
    void use() const override;
};

class ProductFactory {
public:
    ProductFactory();
    virtual Product* createProduct() const = 0;
    virtual ~ProductFactory();
};

class FactoryA : public ProductFactory {
public:
    Product* createProduct() const override;
};

class FactoryB : public ProductFactory {
public:
    Product* createProduct() const override;
};

// =======================================================================
// Observer Pattern
// =======================================================================
/**
 * @section Observer Pattern
 * @brief Establishes a one-to-many dependency between objects.
 *
 * Purpose:
 * - Notify all dependents automatically when the subject changes.
 * - Used in event-driven systems, GUIs, etc.
 *
 * Pros:
 * - Low coupling between subject and observers.
 * - Supports broadcast communication.
 *
 * Cons:
 * - Can be inefficient if observer list is large.
 * - Difficult to debug notification chains.
 */

class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() {}
};

class Subject {
private:
    std::vector<Observer*> observers; ///< Stores registered observers

public:
    void attach(Observer* observer); ///< Adds a new observer
    void notify(const std::string& message); ///< Broadcasts message to all observers
};

class ConcreteObserver : public Observer {
private:
    std::string name;

public:
    ConcreteObserver(const std::string& observerName);
    void update(const std::string& message) override;
};

// =======================================================================
// Strategy Pattern
// =======================================================================
/**
 * @section Strategy Pattern
 * @brief Enables selecting an algorithm’s behavior at runtime.
 *
 * Purpose:
 * - Encapsulate different algorithms and make them interchangeable.
 * - Avoid hardcoding logic via if-else/switch.
 *
 * Pros:
 * - Promotes open/closed principle.
 * - Reduces code duplication for algorithms.
 *
 * Cons:
 * - Client must be aware of strategy differences.
 * - Increased number of classes.
 */

class Strategy {
public:
    virtual void execute() const = 0;
    virtual ~Strategy() {}
};

class StrategyA : public Strategy {
public:
    void execute() const override;
};

class StrategyB : public Strategy {
public:
    void execute() const override;
};

class Context {
private:
    Strategy* strategy; ///< Points to the current strategy implementation

public:
    Context(Strategy* strategy); ///< Accepts strategy at runtime
    void setStrategy(Strategy* newStrategy); ///< Switch strategy dynamically
    void performAction() const; ///< Delegates to current strategy
};
