#include "Product.h"

int Product::nextId = 1;

Product::Product() : id(nextId++), price(0.0) {}

Product::Product(const std::string &name, const double price, const int id)
    : id(id > 0 ? id : nextId++), name(name), price(price)
{
    if (this->id >= nextId)
    {
        nextId = this->id + 1;
    }
}

int Product::getId() const noexcept
{
    return id;
}

const std::string &Product::getName() const noexcept
{
    return name;
}

double Product::getPrice() const noexcept
{
    return price;
}

std::string Product::getInfo() const
{
    return "ID: " + std::to_string(id) +
           "Товар: " + name +
           "Цена: " + std::to_string(price) + " руб.";
}
