#pragma once

#include <string>

/**
 * @brief Класс Product
 */
class Product
{
protected:
    /**
     * @brief Статический счетчик ID
     */
    static int nextId;

    /**
     * @brief id товара из списка
     */
    int id;

    /**
     * @brief Название товара
     */
    std::string name;

    /**
     * @brief Цена товара
     */
    double price;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Product();

    /**
     * @brief Конструктор
     * @param name - название товара
     * @param price - цена товара
     * @param id - id товара (0 для автогенерации)
     */
    Product(const std::string &name, const double price, const int id = 0);

    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Product() = default;

    /**
     * @brief Получить id товара
     * @return id товара
     */
    int getId() const noexcept;

    /**
     * @brief получить название товара
     * @return название товара
     */
    const std::string &getName() const noexcept;

    /**
     * @brief получить цену товара
     * @return Цена товара
     */
    double getPrice() const noexcept;

    /**
     * @brief виртуальный метод получения информации
     */
    virtual std::string getInfo() const;
};
