// File: main.cpp
#include "../include/design_patterns.hpp"
#include <memory> // for unique_ptr

int main() {
    // ==================== Inheritance and Polymorphism ====================
    Animal* dog = new Dog("Buddy");
    Animal* cat = new Cat("Kitty");
    dog->speak();  // Dog-specific behavior
    cat->speak();  // Cat-specific behavior
    delete dog;
    delete cat;

    // ===================== Abstract Class: Shape ==========================
    Shape* circle = new Circle();
    Shape* rectangle = new Rectangle();
    circle->draw();    // Circle-specific draw
    rectangle->draw(); // Rectangle-specific draw
    delete circle;
    delete rectangle;

    // ===================== Singleton Usage ================================
    Singleton* s1 = Singleton::getInstance();
    s1->showMessage();

    FullSingleton* fs1 = FullSingleton::getInstance();
    fs1->showMessage();
    FullSingleton::destroyInstance(); // clean-up

    // ===================== Factory Method Pattern =========================
    std::unique_ptr<ProductFactory> factoryA(new FactoryA());
    std::unique_ptr<Product> productA(factoryA->createProduct());
    productA->use();

    std::unique_ptr<ProductFactory> factoryB(new FactoryB());
    std::unique_ptr<Product> productB(factoryB->createProduct());
    productB->use();

    // ===================== Observer Pattern ===============================
    Subject subject;
    ConcreteObserver observer1("Observer1");
    ConcreteObserver observer2("Observer2");
    subject.attach(&observer1);
    subject.attach(&observer2);
    subject.notify("Event triggered!");

    // ===================== Strategy Pattern ===============================
    StrategyA strategyA;
    StrategyB strategyB;
    Context context(&strategyA);
    context.performAction(); // Executes Strategy A
    context.setStrategy(&strategyB);
    context.performAction(); // Executes Strategy B

    return 0;
}
