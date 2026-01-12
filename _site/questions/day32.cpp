#include <iostream>

class BaseClass {
public:
  void compute() { std::cout << "base "; }
};

class ChildClass : public BaseClass {
public:
  void compute() { std::cout << "child "; }
};

int main() {
   BaseClass b;
   b.compute();
   ChildClass c;
   c.compute();
   BaseClass *p;
   p = &b;
   p->compute();
   p = &c;
   p->compute();
}
