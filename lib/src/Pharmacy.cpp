#include "Pharmacy.h"
#include <iostream>
#include <algorithm>

bool Pharmacy::containsId(const int id) const
{
    bool inMedicines = std::any_of(medicines.begin(), medicines.end(), [id](const Medicine &m)
                                   { return m.getId() == id; });
    if (inMedicines)
        return true;

    return std::any_of(products.begin(), products.end(), [id](const Product &p)
                       { return p.getId() == id; });
}

void Pharmacy::addProduct(const Product &product)
{
    if (containsId(product.getId()))
        return;
    products.push_back(product);
}

void Pharmacy::addProduct(const Medicine &medicine)
{
    addMedicine(medicine);
}

void Pharmacy::addMedicine(const Medicine &medicine)
{
    if (containsId(medicine.getId()))
        return;
    medicines.push_back(medicine);
}

void Pharmacy::addManufacturer(const Manufacturer &manufacturer)
{
    auto it = std::find_if(manufacturers.begin(), manufacturers.end(), [&manufacturer](const Manufacturer &m)
                           { return m.getName() == manufacturer.getName(); });
    if (it != manufacturers.end())
        return;
    manufacturers.push_back(manufacturer);
}

void Pharmacy::addReleaseForm(const ReleaseForm &form)
{
    auto it = std::find_if(releaseForms.begin(), releaseForms.end(), [&form](const ReleaseForm &f)
                           { return f.getFormName() == form.getFormName(); });
    if (it != releaseForms.end())
        return;
    releaseForms.push_back(form);
}

const std::vector<Product> &Pharmacy::getProducts() const noexcept { return products; }
const std::vector<Medicine> &Pharmacy::getMedicines() const noexcept { return medicines; }
const std::vector<Manufacturer> &Pharmacy::getManufacturers() const noexcept { return manufacturers; }
const std::vector<ReleaseForm> &Pharmacy::getReleaseForms() const noexcept { return releaseForms; }

void Pharmacy::printAll() const
{
    for (const Product &p : products)
    {
        std::cout << p.getInfo() << std::endl;
    }
    for (const Medicine &m : medicines)
    {
        std::cout << m.getInfo() << "\n"
                  << std::endl;
    }
}

void Pharmacy::printSalesForMedicineByPeriod(const std::string &medicineName, const std::string &period) const
{
    std::cout << "Продажи препарата '" << medicineName << "' за период [" << period << "]" << std::endl;
    bool found = false;
    for (const Medicine &m : medicines)
    {
        if (m.getName() == medicineName)
        {
            for (const SaleRecord &sale : m.getSales())
            {
                if (sale.getDate().find(period) != std::string::npos)
                {
                    std::cout << sale.toString() << std::endl;
                    found = true;
                }
            }
        }
    }
    if (!found)
    {
        std::cout << "Продаж за этот период не найдено." << std::endl;
    }
    std::cout << std::endl;
}

void Pharmacy::printMedicinesForDisease(const std::string &disease) const
{
    std::cout << "Лекарства от болезни: " << disease << "" << std::endl;
    bool found = false;
    for (const Medicine &m : medicines)
    {
        if (m.treatsDisease(disease))
        {
            std::cout << "- " << m.getName() << " (" << m.getPrice() << " руб.)" << std::endl;
            found = true;
        }
    }
    if (!found)
    {
        std::cout << "Подходящих лекарств не найдено." << std::endl;
    }
    std::cout << std::endl;
}
