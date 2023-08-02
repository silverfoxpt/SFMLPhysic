#ifndef H_MANAGERTEMPLATECLASS
#define MANAGERTEMPLATECLASS

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

template <typename Child>
class Manager {
    protected:
        std::vector<Child> controlledObjects;

    public:
        virtual Child* AddNewControlledObject(Child args)   = 0;
        virtual Child* GetControlledObject(int idx) = 0;
};

#endif