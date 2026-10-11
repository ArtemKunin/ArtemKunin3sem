#pragma once

#include <string>

/**
 * @brief Класс Форма выпуска
 */
class ReleaseForm
{
private:
    /**
     * @brief название формы выпуска
     */
    std::string formName;

public:
    /**
     * @brief конструктор по умолчанию
     */
    ReleaseForm() = default;

    /**
     * @brief Конструктор
     * @param formName - название формы выпуска
     */
    explicit ReleaseForm(const std::string &formName);

    /**
     * @brief получить название формы выпуска
     * @return название формы выпуска
     */
    const std::string &getFormName() const noexcept;
};
