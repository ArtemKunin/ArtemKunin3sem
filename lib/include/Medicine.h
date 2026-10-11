#pragma once
#include "Product.h"
#include "ReleaseForm.h"
#include "Manufacturer.h"
#include "SaleRecord.h"
#include <vector>

/**
 * @brief Класс Medicine - наследник класса Product
 */
class Medicine : public Product
{
private:
    /**
     * @brief Форма выпуска
     */
    ReleaseForm releaseForm;

    /**
     * @brief Изготовитель
     */
    Manufacturer manufacturer;

    /**
     * @brief Срок годности
     */
    std::string expirationDate;

    /**
     * @brief Аннотация
     */
    std::string annotation;

    /**
     * @brief Записи о продажах
     */
    std::vector<SaleRecord> sales;

    /**
     * @brief Список болезней, от которых применяется лекарство
     */
    std::vector<std::string> targetDiseases;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Medicine();

    /**
     * @brief Конструктор
     * @param name - название лекарства
     * @param price - цена
     * @param releaseForm - форма выпуска
     * @param manufacturer - изготовитель
     * @param expirationDate - срок годности
     * @param annotation - аннотация
     * @param id - ID лекарства (0 для автогенерации)
     */
    Medicine(const std::string &name, const double price, const ReleaseForm &releaseForm, const Manufacturer &manufacturer, const std::string &expirationDate, const std::string &annotation, const int id = 0);

    /**
     * @brief Получить форму выпуска
     * @return ссылку на форму выпуска
     */
    const ReleaseForm &getReleaseForm() const noexcept;

    /**
     * @brief Получить изготовителя
     * @return ссылку на изготовителя
     */
    const Manufacturer &getManufacturer() const noexcept;

    /**
     * @brief Получить срок годности
     * @return срок годности
     */
    const std::string &getExpirationDate() const noexcept;

    /**
     * @brief Получить аннотацию
     * @return аннотацию
     */
    const std::string &getAnnotation() const noexcept;

    /**
     * @brief Получить записи о продажах
     * @return Массив продаж
     */
    const std::vector<SaleRecord> &getSales() const noexcept;

    /**
     * @brief Получить список болезней
     * @return Массив болезней
     */
    const std::vector<std::string> &getTargetDiseases() const noexcept;

    /**
     * @brief Функция добавления записи о продаже
     * @param sale - ссылка на запись о продаже
     */
    void addSale(const SaleRecord &sale);

    /**
     * @brief Функция добавления болезни в список показаний
     * @param disease - название болезни
     */
    void addTargetDisease(const std::string &disease);

    /**
     * @brief Функция проверки, применяется ли лекарство от болезни
     * @param disease - название болезни
     * @return true - если применяется, иначе false
     */
    bool treatsDisease(const std::string &disease) const noexcept;

    /**
     * @brief Получение информации о лекарстве
     * @return Информацию о лекарстве
     */
    std::string getInfo() const override;
};
