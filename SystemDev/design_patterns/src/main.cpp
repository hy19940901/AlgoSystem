// File: main.cpp
#include "../include/design_patterns.hpp"
#include <memory> // for unique_ptr

int main() {
    // ==================== Inheritance and Polymorphism ====================
    Animal* dog = new Dog("Buddy");
    Animal* cat = new Cat("Kitty");
    dog->Speak();  // Dog-specific behavior
    cat->Speak();  // Cat-specific behavior
    delete dog;
    delete cat;

    // ===================== Abstract Class: Shape ==========================
    Shape* circle = new Circle();
    Shape* rectangle = new Rectangle();
    circle->Draw();    // Circle-specific draw
    rectangle->Draw(); // Rectangle-specific draw
    delete circle;
    delete rectangle;

    // ===================== Singleton Usage ================================
    Singleton* s1 = Singleton::GetInstance();
    s1->ShowMessage();

    FullSingleton* fs1 = FullSingleton::GetInstance();
    fs1->ShowMessage();
    FullSingleton::DestroyInstance(); // clean-up

    // ===================== Factory Method Pattern =========================
    std::unique_ptr<ProductFactory> factory_a(new FactoryA());
    std::unique_ptr<Product> product_a(factory_a->CreateProduct());
    product_a->Use();

    std::unique_ptr<ProductFactory> factory_b(new FactoryB());
    std::unique_ptr<Product> product_b(factory_b->CreateProduct());
    product_b->Use();

    // ===================== Observer Pattern ===============================
    Subject subject;
    ConcreteObserver observer1("Observer1");
    ConcreteObserver observer2("Observer2");
    subject.Attach(&observer1);
    subject.Attach(&observer2);
    subject.Notify("Event triggered!");

    // ===================== Strategy Pattern ===============================
    StrategyA strategy_a;
    StrategyB strategy_b;
    Context context(&strategy_a);
    context.PerformAction(); // Executes Strategy A
    context.SetStrategy(&strategy_b);
    context.PerformAction(); // Executes Strategy B

    return 0;
}
