#ifndef TOGGLER_H
#define TOGGLER_H

namespace utl
{

class Toggler
{
public:
    Toggler(bool initValue = false);
    ~Toggler();

    bool toggle();
    bool getState();
private:
    bool value;
};

}

#endif // TOGGLER_H
