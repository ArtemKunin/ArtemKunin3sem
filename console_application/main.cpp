#include <iostream>
#include "Pharmacy.h"

/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена корректно
 */
int main()
{

    system("chcp 65001 > nul");

    Pharmacy pharmacy;
    pharmacy.addReleaseForm(ReleaseForm("Таблетки"));
    pharmacy.addReleaseForm(ReleaseForm("Сироп"));
    pharmacy.addManufacturer(Manufacturer("ООО ФармаПлюс"));
    pharmacy.addManufacturer(Manufacturer("Здоровье Инкорпорейтед"));
    Medicine med1("Парацетамол", 150.50, ReleaseForm("Таблетки"), Manufacturer("ООО ФармаПлюс"), "12.2025", "Принимать при высокой температуре");
    med1.addTargetDisease("Жар");
    med1.addTargetDisease("Головная боль");
    med1.addSale(SaleRecord("Иванов Иван Иванович", "15.10.2023", 2));
    med1.addSale(SaleRecord("Петров Пётр Петрович", "20.10.2023", 1));
    med1.addSale(SaleRecord("Сидоров Сидор", "05.11.2023", 3));

    Medicine med2("Доктор Мом", 320.00, ReleaseForm("Сироп"), Manufacturer("Здоровье Инкорпорейтед"), "01.2026", "Пить по одной ложке 3 раза в день");
    med2.addTargetDisease("Кашель");
    med2.addTargetDisease("Боль в горле");
    med2.addSale(SaleRecord("Смирнова Анна", "18.10.2023", 1));

    pharmacy.addMedicine(med1);
    pharmacy.addMedicine(med2);

    Product prod1("Гематоген", 50.0);
    pharmacy.addProduct(prod1);

    pharmacy.printAll();

    for (const Medicine &m : pharmacy.getMedicines())
    {
        std::cout << m.getInfo() << "\n"
                  << std::endl;
    }

    pharmacy.printSalesForMedicineByPeriod("Парацетамол", ".10.2023"); 
    pharmacy.printSalesForMedicineByPeriod("Парацетамол", ".11.2023"); 

    pharmacy.printMedicinesForDisease("Головная боль");
    pharmacy.printMedicinesForDisease("Кашель");

    std::vector<Product *> baseCollection;
    baseCollection.push_back(new Product("Аскорбинка", 25.0));
    baseCollection.push_back(new Medicine("Аспирин", 120.0, ReleaseForm("Таблетки"), Manufacturer("Bayer"), "10.2027", "Обезболивающее"));

    for (const Product *item : baseCollection)
    {
        std::cout << item->getInfo() << "\n"
                  << std::endl;
    }
    for (Product *item : baseCollection)
    {
        delete item;
    }

    return 0;
}
