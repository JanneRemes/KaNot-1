#include "Keyboard.h"

Keyboard::Keyboard() 
{
}

Keyboard::Keyboard(const std::vector<bool>& keyStates)
        : _keyStates(keyStates) { }

Keyboard::Keyboard(const Keyboard& keyboard)
        : _keyStates(keyboard._keyStates) { }

Keyboard::~Keyboard() { }



bool Keyboard::isKeyDown(const Key key)
{
        return _keyStates[key];
}

bool Keyboard::isKeyUp(const Key key)
{
        return !isKeyDown(key);
}

// Operators

Keyboard& Keyboard::operator =(const Keyboard& keyboard)
{
        if(this != &keyboard)
                _keyStates = keyboard._keyStates;

        return *this;
}