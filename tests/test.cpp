#include <gtest/gtest.h>

#include "Pharmacy.h"
#include "Product.h"
#include "Medicine.h"
#include "ReleaseForm.h"
#include "Manufacturer.h"
#include "SaleRecord.h"

#include <string>
#include <algorithm>

TEST(ProductTest, Getters)
{
    Product p("Гематоген", 50.5);

    EXPECT_GT(p.getId(), 0);
    EXPECT_EQ(p.getName(), "Гематоген");
    EXPECT_DOUBLE_EQ(p.getPrice(), 50.5);
}

TEST(ProductTest, GetInfo)
{
    Product p("Витамин С", 100.0);
    std::string info = p.getInfo();

    EXPECT_NE(info.find("Витамин С"), std::string::npos);
    EXPECT_NE(info.find("100"), std::string::npos);
    EXPECT_NE(info.find("ID:"), std::string::npos);
}

TEST(ReleaseFormTest, GetFormName)
{
    ReleaseForm form("Ампулы");
    EXPECT_EQ(form.getFormName(), "Ампулы");
}

TEST(ManufacturerTest, GetName)
{
    Manufacturer m("ФармаПлюс");
    EXPECT_EQ(m.getName(), "ФармаПлюс");
}

TEST(SaleRecordTest, GettersAndToString)
{
    SaleRecord sale("Иванов И.И.", "15.10.2023", 2);

    EXPECT_EQ(sale.getBuyerName(), "Иванов И.И.");
    EXPECT_EQ(sale.getDate(), "15.10.2023");
    EXPECT_EQ(sale.getQuantity(), 2);

    std::string s = sale.toString();
    EXPECT_NE(s.find("Иванов И.И."), std::string::npos);
    EXPECT_NE(s.find("15.10.2023"), std::string::npos);
    EXPECT_NE(s.find("2"), std::string::npos);
}

TEST(MedicineTest, Getters)
{
    Medicine m("Аспирин", 120.0, ReleaseForm("Таблетки"), Manufacturer("Bayer"), "10.2025", "От боли");

    EXPECT_GT(m.getId(), 0);
    EXPECT_EQ(m.getName(), "Аспирин");
    EXPECT_DOUBLE_EQ(m.getPrice(), 120.0);
    EXPECT_EQ(m.getReleaseForm().getFormName(), "Таблетки");
    EXPECT_EQ(m.getManufacturer().getName(), "Bayer");
    EXPECT_EQ(m.getExpirationDate(), "10.2025");
    EXPECT_EQ(m.getAnnotation(), "От боли");
}

TEST(MedicineTest, DiseasesAndSales)
{
    Medicine m("Парацетамол", 150.0, ReleaseForm("Таблетки"), Manufacturer("ФармаПлюс"), "12.2025", "От жара");

    EXPECT_FALSE(m.treatsDisease("Кашель"));
    m.addTargetDisease("Жар");
    m.addTargetDisease("Головная боль");

    EXPECT_TRUE(m.treatsDisease("Жар"));
    EXPECT_TRUE(m.treatsDisease("Головная боль"));
    EXPECT_EQ(m.getTargetDiseases().size(), 2u);

    m.addSale(SaleRecord("Петров", "20.10.2023", 1));
    EXPECT_EQ(m.getSales().size(), 1u);
    EXPECT_EQ(m.getSales()[0].getBuyerName(), "Петров");
}

TEST(PharmacyTest, AddAndGetProducts)
{
    Pharmacy pharmacy;
    EXPECT_TRUE(pharmacy.getProducts().empty());
    EXPECT_TRUE(pharmacy.getMedicines().empty());

    Product p("Бинт", 30.0);
    pharmacy.addProduct(p);
    pharmacy.addProduct(p);

    EXPECT_EQ(pharmacy.getProducts().size(), 1u);
    EXPECT_EQ(pharmacy.getProducts()[0].getName(), "Бинт");

    Medicine m("Нурофен", 250.0, ReleaseForm("Капсулы"), Manufacturer("Reckitt Benckiser"), "11.2026", "Болеутоляющее");
    pharmacy.addMedicine(m);
    pharmacy.addMedicine(m);
    pharmacy.addProduct(m);

    EXPECT_EQ(pharmacy.getMedicines().size(), 1u);
    EXPECT_EQ(pharmacy.getMedicines()[0].getName(), "Нурофен");
}

TEST(PharmacyTest, Polymorphism)
{
    Product p("Пластырь", 15.0);
    Medicine m("Смекта", 180.0, ReleaseForm("Порошок"), Manufacturer("Ipsen"), "08.2027", "От живота");

    const Product &pRef = p;
    const Product &mRef = m;

    EXPECT_EQ(dynamic_cast<const Medicine *>(&pRef), nullptr);
    EXPECT_NE(dynamic_cast<const Medicine *>(&mRef), nullptr);

    EXPECT_EQ(pRef.getInfo().find("Порошок"), std::string::npos);
    EXPECT_NE(mRef.getInfo().find("Порошок"), std::string::npos);
}

TEST(PharmacyTest, ManufacturerAndFormDeduplication)
{
    Pharmacy pharmacy;

    pharmacy.addManufacturer(Manufacturer("Bayer"));
    pharmacy.addManufacturer(Manufacturer("Bayer"));
    EXPECT_EQ(pharmacy.getManufacturers().size(), 1u);

    pharmacy.addReleaseForm(ReleaseForm("Сироп"));
    pharmacy.addReleaseForm(ReleaseForm("Сироп"));
    EXPECT_EQ(pharmacy.getReleaseForms().size(), 1u);
}
