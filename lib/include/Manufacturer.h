#pragma once
#include <string>

/**
 * @brief Класс изготовитель
 */
class Manufacturer
{
private:
    /**
     * @brief Название изготовителя
     */
    std::string name;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Manufacturer() = default;

    /**
     * @brief Конструктор
     * @param name - название изготовителя
     */
    explicit Manufacturer(const std::string &name);

    /**
     * @brief Получить название изготовителя
     * @return Название изготовителя
     */
    const std::string &getName() const noexcept;
};
