#include "SaleRecord.h"

SaleRecord::SaleRecord(const std::string &buyerName, const std::string &date, const int quantity)
    : buyerName(buyerName), date(date), quantity(quantity) {}

const std::string &SaleRecord::getBuyerName() const noexcept
{
    return buyerName;
}

const std::string &SaleRecord::getDate() const noexcept
{
    return date;
}

int SaleRecord::getQuantity() const noexcept
{
    return quantity;
}

std::string SaleRecord::toString() const
{
    return "Покупатель: " + buyerName + "/ Дата: " + date + "/ Кол-во: " + std::to_string(quantity);
}
