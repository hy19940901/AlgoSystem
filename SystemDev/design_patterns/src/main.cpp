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
    Singleton* s1 = Singleton::get_instance();
    s1->show_message();

    FullSingleton* fs1 = FullSingleton::get_instance();
    fs1->show_message();
    FullSingleton::destroy_instance(); // clean-up

    // ===================== Factory Method Pattern =========================
    std::unique_ptr<ProductFactory> factory_a(new FactoryA());
    std::unique_ptr<Product> product_a(factory_a->create_product());
    product_a->use();

    std::unique_ptr<ProductFactory> factory_b(new FactoryB());
    std::unique_ptr<Product> product_b(factory_b->create_product());
    product_b->use();

    // ===================== Observer Pattern ===============================
    Subject subject;
    ConcreteObserver observer1("Observer1");
    ConcreteObserver observer2("Observer2");
    subject.attach(&observer1);
    subject.attach(&observer2);
    subject.notify("Event triggered!");

    // ===================== Strategy Pattern ===============================
    StrategyA strategy_a;
    StrategyB strategy_b;
    Context context(&strategy_a);
    context.perform_action(); // Executes Strategy A
    context.set_strategy(&strategy_b);
    context.perform_action(); // Executes Strategy B

    return 0;
}
