#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 虚函数指针定义
typedef struct Animal Animal;
typedef struct AnimalVTable {
    void (*speak)(Animal* self);
    void (*destroy)(Animal* self);
} AnimalVTable;

// 基类 Animal
struct Animal {
    const AnimalVTable* vtable;
    char name[32];
};

// Animal 方法
void animal_speak(Animal* self) {
    printf("%s makes a sound.\n", self->name);
}

void animal_destroy(Animal* self) {
    printf("Destroying Animal: %s\n", self->name);
    free(self);
}

// 虚表实例
AnimalVTable animal_vtable = {
    .speak = animal_speak,
    .destroy = animal_destroy
};

// 子类 Dog
typedef struct Dog {
    Animal base; // "继承" Animal
    int bark_volume;
} Dog;

// Dog 方法
void dog_speak(Animal* self) {
    Dog* dog = (Dog*)self;
    printf("%s barks loudly! Volume: %d\n", dog->base.name, dog->bark_volume);
}

void dog_destroy(Animal* self) {
    Dog* dog = (Dog*)self;
    printf("Destroying Dog: %s\n", dog->base.name);
    free(dog);
}

AnimalVTable dog_vtable = {
    .speak = dog_speak,
    .destroy = dog_destroy
};

// 构造函数
Animal* dog_new(const char* name, int volume) {
    Dog* dog = (Dog*)malloc(sizeof(Dog));
    if (!dog) return NULL;
    dog->base.vtable = &dog_vtable;
    strncpy(dog->base.name, name, sizeof(dog->base.name) - 1);
    dog->bark_volume = volume;
    return (Animal*)dog;
}

// 子类 Cat
typedef struct Cat {
    Animal base;
    int meow_pitch;
} Cat;

void cat_speak(Animal* self) {
    Cat* cat = (Cat*)self;
    printf("%s meows sweetly. Pitch: %d\n", cat->base.name, cat->meow_pitch);
}

void cat_destroy(Animal* self) {
    Cat* cat = (Cat*)self;
    printf("Destroying Cat: %s\n", cat->base.name);
    free(cat);
}

AnimalVTable cat_vtable = {
    .speak = cat_speak,
    .destroy = cat_destroy
};

Animal* cat_new(const char* name, int pitch) {
    Cat* cat = (Cat*)malloc(sizeof(Cat));
    if (!cat) return NULL;
    cat->base.vtable = &cat_vtable;
    strncpy(cat->base.name, name, sizeof(cat->base.name) - 1);
    cat->meow_pitch = pitch;
    return (Animal*)cat;
}

// 主程序
int main() {
    Animal* pets[2];
    pets[0] = dog_new("Buddy", 10);
    pets[1] = cat_new("Kitty", 5);

    for (int i = 0; i < 2; ++i) {
        pets[i]->vtable->speak(pets[i]);   // 多态调用
    }

    for (int i = 0; i < 2; ++i) {
        pets[i]->vtable->destroy(pets[i]); // 多态析构
    }

    return 0;
}
