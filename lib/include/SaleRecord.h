#pragma once

#include <string>

/**
 * @brief класс SaleRecord
 */
class SaleRecord
{
private:
    /**
     * @brief Имя покупателя
     */
    std::string buyerName;

    /**
     * @brief Дата продажи
     */
    std::string date;

    /**
     * @brief Количество проданного товара
     */
    int quantity;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    SaleRecord() = default;

    /**
     * @brief Конструктор
     * @param buyerName - имя покупателя
     * @param date - дата продажи
     * @param quantity - количество
     */
    SaleRecord(const std::string &buyerName, const std::string &date, const int quantity);

    /**
     * @brief Получить имя покупателя
     * @return имя покупателя
     */
    const std::string &getBuyerName() const noexcept;

    /**
     * @brief Получить дату продажи
     * @return дата продажи
     */
    const std::string &getDate() const noexcept;

    /**
     * @brief получить количество
     * @return количество
     */
    int getQuantity() const noexcept;

    /**
     * @brief получить строку с информацией о продаже
     * @return строка с информацией о продаже
     */
    std::string toString() const;
};
