#include "Manufacturer.h"

Manufacturer::Manufacturer(const std::string &name) : name(name) {}

const std::string &Manufacturer::getName() const noexcept
{
    return name;
}
