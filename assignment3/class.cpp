#include "class.h"

MyClass::MyClass() : myAttribute(0) {
}

MyClass::MyClass(int initialValue) : myAttribute(initialValue) {
}

MyClass::~MyClass() {
}

void MyClass::myMethod() {
}

int MyClass::getMyAttribute() const {
    return myAttribute;
}

void MyClass::setMyAttribute(int value) {
    myAttribute = value;
}

void MyClass::helperMethod() {
}
