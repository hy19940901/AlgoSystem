// Folder: include/design_patterns
// File: design_patterns.hpp
#ifndef DESIGN_PATTERNS_HPP
#define DESIGN_PATTERNS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <mutex>

using std::string;

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
public:
    explicit Animal(const string& animal_name);
    virtual ~Animal();

    /**
     * @brief Simulates the animal speaking.
     */
    virtual void speak() const;

protected:
    string name_;  ///< Name of the animal
};

/**
 * @brief Represents a dog. Inherits from Animal.
 */
class Dog : public Animal {
public:
    explicit Dog(const string& dog_name);
    ~Dog();
    void speak() const override;
};

/**
 * @brief Represents a cat. Inherits from Animal.
 */
class Cat : public Animal {
public:
    explicit Cat(const string& cat_name);
    ~Cat();
    void speak() const override;
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

/**
 * @brief Abstract interface for drawable shapes.
 */
class Shape {
public:
    Shape();
    virtual ~Shape();

    /**
     * @brief Draws the shape.
     */
    virtual void draw() const = 0;
};

/**
 * @brief Represents a concrete Circle shape.
 */
class Circle : public Shape {
public:
    Circle();
    ~Circle();
    void draw() const override;
};

/**
 * @brief Represents a concrete Rectangle shape.
 */
class Rectangle : public Shape {
public:
    Rectangle();
    ~Rectangle();
    void draw() const override;
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
public:
    /**
     * @brief Returns the single instance of Singleton.
     */
    static Singleton* get_instance();

    /**
     * @brief Prints a message from the singleton.
     */
    void show_message();

    ~Singleton();

private:
    Singleton();                         ///< Private constructor
    static Singleton* instance_;         ///< Static instance
};

/**
 * @brief Thread-safe Singleton using mutex.
 */
class FullSingleton {
public:
    static FullSingleton* get_instance();
    static void destroy_instance();
    void show_message();
    ~FullSingleton();

private:
    FullSingleton();
    static FullSingleton* instance_;
    static std::mutex instance_mutex_;
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

/**
 * @brief Abstract base class for products.
 */
class Product {
public:
    explicit Product(const string& product_name);
    virtual ~Product();

    /**
     * @brief Uses the product.
     */
    virtual void use() const = 0;

protected:
    string name_; ///< Product name
};

/**
 * @brief Concrete implementation of Product A.
 */
class ConcreteProductA : public Product {
public:
    ConcreteProductA();
    void use() const override;
};

/**
 * @brief Concrete implementation of Product B.
 */
class ConcreteProductB : public Product {
public:
    ConcreteProductB();
    void use() const override;
};

/**
 * @brief Abstract factory interface.
 */
class ProductFactory {
public:
    ProductFactory();
    virtual ~ProductFactory();

    /**
     * @brief Creates a new product.
     * @return Pointer to dynamically allocated product
     */
    virtual Product* create_product() const = 0;
};

/**
 * @brief Concrete factory for Product A.
 */
class FactoryA : public ProductFactory {
public:
    Product* create_product() const override;
};

/**
 * @brief Concrete factory for Product B.
 */
class FactoryB : public ProductFactory {
public:
    Product* create_product() const override;
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

/**
 * @brief Abstract Observer interface.
 */
class Observer {
public:
    /**
     * @brief Callback function for when Subject changes.
     * @param message Notification message
     */
    virtual void update(const string& message) = 0;
    virtual ~Observer() = default;
};

/**
 * @brief Subject class that manages observers.
 */
class Subject {
public:
    /**
     * @brief Registers an observer to the subject.
     */
    void attach(Observer* observer);

    /**
     * @brief Notifies all observers of an event.
     * @param message The notification message.
     */
    void notify(const string& message);

private:
    std::vector<Observer*> observers_;  ///< List of registered observers
};

/**
 * @brief Concrete implementation of an Observer.
 */
class ConcreteObserver : public Observer {
public:
    explicit ConcreteObserver(const string& observer_name);
    void update(const string& message) override;

private:
    string name_; ///< Observer's name for display
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

/**
 * @brief Strategy interface for interchangeable behavior.
 */
class Strategy {
public:
    virtual void execute() const = 0;
    virtual ~Strategy() = default;
};

/**
 * @brief Concrete Strategy A.
 */
class StrategyA : public Strategy {
public:
    void execute() const override;
};

/**
 * @brief Concrete Strategy B.
 */
class StrategyB : public Strategy {
public:
    void execute() const override;
};

/**
 * @brief Context that uses a Strategy object.
 */
class Context {
public:
    explicit Context(Strategy* strategy);

    /**
     * @brief Sets a new strategy.
     */
    void set_strategy(Strategy* new_strategy);

    /**
     * @brief Performs an action using the current strategy.
     */
    void perform_action() const;

private:
    Strategy* strategy_;
};

#endif  // DESIGN_PATTERNS_HPP