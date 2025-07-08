/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include "class.h"

void sandbox() {
  MyClass obj;
  obj.setMyAttribute(42);
  int value = obj.getMyAttribute();
  obj.myMethod();
}