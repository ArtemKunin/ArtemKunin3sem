#include "Medicine.h"

Medicine::Medicine() : Product() {}

Medicine::Medicine(const std::string &name, const double price, const ReleaseForm &releaseForm, const Manufacturer &manufacturer, const std::string &expirationDate, const std::string &annotation, const int id)
    : Product(name, price, id), releaseForm(releaseForm), manufacturer(manufacturer), expirationDate(expirationDate), annotation(annotation) {}

const ReleaseForm &Medicine::getReleaseForm() const noexcept
{
    return releaseForm;
}

const Manufacturer &Medicine::getManufacturer() const noexcept
{
    return manufacturer;
}

const std::string &Medicine::getExpirationDate() const noexcept
{
    return expirationDate;
}

const std::string &Medicine::getAnnotation() const noexcept
{
    return annotation;
}

const std::vector<SaleRecord> &Medicine::getSales() const noexcept
{
    return sales;
}

const std::vector<std::string> &Medicine::getTargetDiseases() const noexcept
{
    return targetDiseases;
}

void Medicine::addSale(const SaleRecord &sale)
{
    sales.push_back(sale);
}

void Medicine::addTargetDisease(const std::string &disease)
{
    targetDiseases.push_back(disease);
}

bool Medicine::treatsDisease(const std::string &disease) const noexcept
{
    for (const std::string &d : targetDiseases)
    {
        if (d == disease)
            return true;
    }
    return false;
}

std::string Medicine::getInfo() const
{
    std::string result = Product::getInfo();
    result += "\n   Форма выпуска: " + releaseForm.getFormName();
    result += "\n   Изготовитель: " + manufacturer.getName();
    result += "\n   Годен до: " + expirationDate;
    result += "\n   Аннотация: " + annotation;
    return result;
}
