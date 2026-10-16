#pragma once
#include "Product.h"
#include "Medicine.h"
#include "Manufacturer.h"
#include "ReleaseForm.h"
#include <vector>

/**
 * @brief Класс Pharmacy
 */
class Pharmacy
{
private:
    /**
     * @brief Массив базовых товаров
     */
    std::vector<Product> products;

    /**
     * @brief Массив лекарств
     */
    std::vector<Medicine> medicines;

    /**
     * @brief Массив изготовителей
     */
    std::vector<Manufacturer> manufacturers;

    /**
     * @brief Массив форм выпуска
     */
    std::vector<ReleaseForm> releaseForms;

    /**
     * @brief Проверить наличие товара с данным ID в аптеке
     * @param id - ID товара
     * @return true, если товар с таким ID уже есть
     */
    bool containsId(const int id) const;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Pharmacy() = default;

    /**
     * @brief Деструктор
     */
    ~Pharmacy() = default;

    /**
     * @brief Добавить товар
     * @param product - товар
     */
    void addProduct(const Product &product);

    /**
     * @brief Добавить товар-лекарство через базовый интерфейс
     * @param medicine - лекарство
     */
    void addProduct(const Medicine &medicine);

    /**
     * @brief Добавить лекарство
     * @param medicine - лекарство
     */
    void addMedicine(const Medicine &medicine);

    /**
     * @brief Добавить изготовителя
     * @param manufacturer - изготовитель
     */
    void addManufacturer(const Manufacturer &manufacturer);

    /**
     * @brief Добавить форму выпуска
     * @param form - форма выпуска
     */
    void addReleaseForm(const ReleaseForm &form);

    /**
     * @brief Получить список товаров
     * @return ссылку на массив товаров
     */
    const std::vector<Product> &getProducts() const noexcept;

    /**
     * @brief Получить список лекарств
     * @return ссылку на массив лекарств
     */
    const std::vector<Medicine> &getMedicines() const noexcept;

    /**
     * @brief Получить список изготовителей
     * @return ссылку на массив изготовителей
     */
    const std::vector<Manufacturer> &getManufacturers() const noexcept;

    /**
     * @brief Получить список форм выпуска
     * @return ссылку на массив форм выпуска
     */
    const std::vector<ReleaseForm> &getReleaseForms() const noexcept;

    /**
     * @brief Выдавать данные о всех лекарствах
     */
    void printAll() const;

    /**
     * @brief Выдавать информацию о продажах данного лекарства за период (неделя, месяц, год)
     * @param medicineName - название лекарства
     * @param period - период в виде строки
     */
    void printSalesForMedicineByPeriod(const std::string &medicineName, const std::string &period) const;

    /**
     * @brief Выдавать список лекарств, применяемых для выбранной болезни
     * @param disease - название болезни
     */
    void printMedicinesForDisease(const std::string &disease) const;
};
