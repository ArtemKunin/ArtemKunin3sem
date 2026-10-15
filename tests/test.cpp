#include <gtest/gtest.h>

#include "Pharmacy.h"
#include "Product.h"
#include "Medicine.h"
#include "ReleaseForm.h"
#include "Manufacturer.h"
#include "SaleRecord.h"

#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>

TEST(ReleaseFormTest, DefaultConstructor) {
    ReleaseForm form;
    EXPECT_EQ(form.getFormName(), "");
}

TEST(ReleaseFormTest, ParameterizedConstructorAndGetFormName) {
    ReleaseForm form("Таблетки");
    EXPECT_EQ(form.getFormName(), "Таблетки");
}

TEST(ManufacturerTest, DefaultConstructor) {
    Manufacturer m;
    EXPECT_EQ(m.getName(), "");
}

TEST(ManufacturerTest, ParameterizedConstructorAndGetName) {
    Manufacturer m("ООО ФармаПлюс");
    EXPECT_EQ(m.getName(), "ООО ФармаПлюс");
}

TEST(SaleRecordTest, DefaultConstructor) {
    SaleRecord sale;
    EXPECT_EQ(sale.getBuyerName(), "");
    EXPECT_EQ(sale.getDate(), "");
    EXPECT_EQ(sale.getQuantity(), 0);
}

TEST(SaleRecordTest, GettersAndToString) {
    SaleRecord sale("Иванов И.И.", "15.10.2023", 2);

    EXPECT_EQ(sale.getBuyerName(), "Иванов И.И.");
    EXPECT_EQ(sale.getDate(), "15.10.2023");
    EXPECT_EQ(sale.getQuantity(), 2);

    std::string s = sale.toString();
    EXPECT_NE(s.find("Иванов И.И."), std::string::npos);
    EXPECT_NE(s.find("15.10.2023"), std::string::npos);
    EXPECT_NE(s.find("2"), std::string::npos);
}

TEST(ProductTest, DefaultConstructorHasValidId) {
    Product p;
    EXPECT_GT(p.getId(), 0);
    EXPECT_EQ(p.getName(), "");
    EXPECT_DOUBLE_EQ(p.getPrice(), 0.0);
}

TEST(ProductTest, GettersAutoId) {
    Product p("Гематоген", 50.5);

    EXPECT_GT(p.getId(), 0);
    EXPECT_EQ(p.getName(), "Гематоген");
    EXPECT_DOUBLE_EQ(p.getPrice(), 50.5);
}

TEST(ProductTest, ConstructorWithExplicitId) {
    Product p("Бинт стерильный", 35.0, 42);
    EXPECT_EQ(p.getId(), 42);
    EXPECT_EQ(p.getName(), "Бинт стерильный");
    EXPECT_DOUBLE_EQ(p.getPrice(), 35.0);
}

TEST(ProductTest, GetInfo) {
    Product p("Витамин С", 100.0, 10);
    std::string info = p.getInfo();

    EXPECT_NE(info.find("ID: 10"), std::string::npos);
    EXPECT_NE(info.find("Витамин С"), std::string::npos);
    EXPECT_NE(info.find("100"), std::string::npos);
}

TEST(MedicineTest, DefaultConstructorHasValidId) {
    Medicine m;
    EXPECT_GT(m.getId(), 0);
    EXPECT_EQ(m.getName(), "");
    EXPECT_DOUBLE_EQ(m.getPrice(), 0.0);
    EXPECT_EQ(m.getReleaseForm().getFormName(), "");
    EXPECT_EQ(m.getManufacturer().getName(), "");
    EXPECT_EQ(m.getExpirationDate(), "");
    EXPECT_EQ(m.getAnnotation(), "");
    EXPECT_TRUE(m.getSales().empty());
    EXPECT_TRUE(m.getTargetDiseases().empty());
}

TEST(MedicineTest, GettersAutoId) {
    Medicine m("Аспирин", 120.0, ReleaseForm("Таблетки"), Manufacturer("Bayer"), "10.2025", "Принимать после еды");

    EXPECT_GT(m.getId(), 0);
    EXPECT_EQ(m.getName(), "Аспирин");
    EXPECT_DOUBLE_EQ(m.getPrice(), 120.0);
    EXPECT_EQ(m.getReleaseForm().getFormName(), "Таблетки");
    EXPECT_EQ(m.getManufacturer().getName(), "Bayer");
    EXPECT_EQ(m.getExpirationDate(), "10.2025");
    EXPECT_EQ(m.getAnnotation(), "Принимать после еды");
}

TEST(MedicineTest, ConstructorWithExplicitId) {
    Medicine m("Нурофен", 250.0, ReleaseForm("Капсулы"), Manufacturer("Reckitt"), "12.2026", "От боли", 99);

    EXPECT_EQ(m.getId(), 99);
    EXPECT_EQ(m.getName(), "Нурофен");
    EXPECT_DOUBLE_EQ(m.getPrice(), 250.0);
    EXPECT_EQ(m.getReleaseForm().getFormName(), "Капсулы");
    EXPECT_EQ(m.getManufacturer().getName(), "Reckitt");
    EXPECT_EQ(m.getExpirationDate(), "12.2026");
    EXPECT_EQ(m.getAnnotation(), "От боли");
}

TEST(MedicineTest, AddAndGetSales) {
    Medicine m("Парацетамол", 150.0, ReleaseForm("Таблетки"), Manufacturer("ФармаПлюс"), "12.2025", "От жара");

    EXPECT_TRUE(m.getSales().empty());

    m.addSale(SaleRecord("Иванов И.И.", "15.10.2023", 2));
    m.addSale(SaleRecord("Петров П.П.", "20.10.2023", 1));

    ASSERT_EQ(m.getSales().size(), 2u);
    EXPECT_EQ(m.getSales()[0].getBuyerName(), "Иванов И.И.");
    EXPECT_EQ(m.getSales()[0].getQuantity(), 2);
    EXPECT_EQ(m.getSales()[1].getBuyerName(), "Петров П.П.");
    EXPECT_EQ(m.getSales()[1].getDate(), "20.10.2023");
}

TEST(MedicineTest, TargetDiseasesAndTreatsDisease) {
    Medicine m("Доктор Мом", 320.0, ReleaseForm("Сироп"), Manufacturer("Здоровье"), "01.2026", "От кашля");

    EXPECT_TRUE(m.getTargetDiseases().empty());
    EXPECT_FALSE(m.treatsDisease("Кашель"));

    m.addTargetDisease("Кашель");
    m.addTargetDisease("Боль в горле");

    ASSERT_EQ(m.getTargetDiseases().size(), 2u);
    EXPECT_EQ(m.getTargetDiseases()[0], "Кашель");
    EXPECT_EQ(m.getTargetDiseases()[1], "Боль в горле");

    EXPECT_TRUE(m.treatsDisease("Кашель"));
    EXPECT_TRUE(m.treatsDisease("Боль в горле"));
    EXPECT_FALSE(m.treatsDisease("Мигрень"));
}

TEST(MedicineTest, GetInfoContainsAllFields) {
    Medicine m("Парацетамол", 150.0, ReleaseForm("Таблетки"), Manufacturer("ФармаПлюс"), "12.2025", "При температуре", 77);
    std::string info = m.getInfo();

    EXPECT_NE(info.find("ID: 77"), std::string::npos);
    EXPECT_NE(info.find("Парацетамол"), std::string::npos);
    EXPECT_NE(info.find("150"), std::string::npos);
    EXPECT_NE(info.find("Таблетки"), std::string::npos);
    EXPECT_NE(info.find("ФармаПлюс"), std::string::npos);
    EXPECT_NE(info.find("12.2025"), std::string::npos);
    EXPECT_NE(info.find("При температуре"), std::string::npos);
}

static bool pharmacyHasName(const Pharmacy& ph, const std::string& name) {
    bool inProducts = std::any_of(ph.getProducts().begin(), ph.getProducts().end(), [&name](const Product& p) {
        return p.getName() == name;
    });
    if (inProducts) return true;

    return std::any_of(ph.getMedicines().begin(), ph.getMedicines().end(), [&name](const Medicine& m) {
        return m.getName() == name;
    });
}

TEST(PharmacyTest, DefaultConstructorEmptyCollections) {
    Pharmacy ph;
    EXPECT_TRUE(ph.getProducts().empty());
    EXPECT_TRUE(ph.getMedicines().empty());
    EXPECT_TRUE(ph.getManufacturers().empty());
    EXPECT_TRUE(ph.getReleaseForms().empty());
}

TEST(PharmacyTest, AddAndGetProductsAndMedicines) {
    Pharmacy ph;

    Product p("Гематоген", 50.0);
    ph.addProduct(p);
    ph.addProduct(p); 

    EXPECT_EQ(ph.getProducts().size(), 1u);
    EXPECT_TRUE(pharmacyHasName(ph, "Гематоген"));

    Medicine m1("Аспирин", 120.0, ReleaseForm("Таблетки"), Manufacturer("Bayer"), "10.2025", "От боли");
    ph.addMedicine(m1);
    ph.addMedicine(m1); 
    ph.addProduct(m1); 

    EXPECT_EQ(ph.getMedicines().size(), 1u);
    EXPECT_TRUE(pharmacyHasName(ph, "Аспирин"));

    Medicine m2("Цитрамон", 80.0, ReleaseForm("Таблетки"), Manufacturer("Фарма"), "11.2026", "От головы");
    ph.addProduct(m2);
    EXPECT_EQ(ph.getMedicines().size(), 2u);
    EXPECT_TRUE(pharmacyHasName(ph, "Цитрамон"));
}

TEST(PharmacyTest, DuplicateIdRejectedAcrossLists) {
    Pharmacy ph;

    Product p1("Бинт", 30.0, 100);
    Product p2("Вата", 40.0, 100);
    Medicine mSameIdAsProduct("Зеленка", 60.0, ReleaseForm("Раствор"), Manufacturer("Фарм"), "01.2027", "Антисептик", 100);

    ph.addProduct(p1);
    ph.addProduct(p2); 
    ph.addMedicine(mSameIdAsProduct);

    EXPECT_EQ(ph.getProducts().size(), 1u);
    EXPECT_EQ(ph.getMedicines().size(), 0u);
    EXPECT_TRUE(pharmacyHasName(ph, "Бинт"));
    EXPECT_FALSE(pharmacyHasName(ph, "Вата"));
    EXPECT_FALSE(pharmacyHasName(ph, "Зеленка"));

    Medicine m1("Анальгин", 90.0, ReleaseForm("Таблетки"), Manufacturer("Фарм"), "01.2026", "Аннотация", 200);
    Medicine m2("Но-шпа", 190.0, ReleaseForm("Таблетки"), Manufacturer("Фарм"), "01.2026", "Аннотация", 200);
    Product pSameIdAsMedicine("Жгут", 110.0, 200);

    ph.addMedicine(m1);
    ph.addMedicine(m2); 
    ph.addProduct(pSameIdAsMedicine); 

    EXPECT_EQ(ph.getMedicines().size(), 1u);
    EXPECT_EQ(ph.getProducts().size(), 1u);
    EXPECT_TRUE(pharmacyHasName(ph, "Анальгин"));
    EXPECT_FALSE(pharmacyHasName(ph, "Но-шпа"));
    EXPECT_FALSE(pharmacyHasName(ph, "Жгут"));
}

TEST(PharmacyTest, AddAndGetManufacturersAndReleaseFormsDeduplication) {
    Pharmacy ph;

    ph.addManufacturer(Manufacturer("Bayer"));
    ph.addManufacturer(Manufacturer("Bayer"));
    ph.addManufacturer(Manufacturer("ФармаПлюс"));

    ASSERT_EQ(ph.getManufacturers().size(), 2u);
    EXPECT_EQ(ph.getManufacturers()[0].getName(), "Bayer");
    EXPECT_EQ(ph.getManufacturers()[1].getName(), "ФармаПлюс");

    ph.addReleaseForm(ReleaseForm("Таблетки"));
    ph.addReleaseForm(ReleaseForm("Таблетки"));
    ph.addReleaseForm(ReleaseForm("Сироп"));

    ASSERT_EQ(ph.getReleaseForms().size(), 2u);
    EXPECT_EQ(ph.getReleaseForms()[0].getFormName(), "Таблетки");
    EXPECT_EQ(ph.getReleaseForms()[1].getFormName(), "Сироп");
}

TEST(PharmacyTest, PolymorphismAndVirtualDestructor) {
    Product* pPtr = new Product("Аскорбинка", 25.0);
    Product* mPtr = new Medicine("Смекта", 180.0, ReleaseForm("Порошок"), Manufacturer("Ipsen"), "08.2027", "Для ЖКТ");

    EXPECT_EQ(dynamic_cast<const Medicine*>(pPtr), nullptr);
    EXPECT_NE(dynamic_cast<const Medicine*>(mPtr), nullptr);

    EXPECT_EQ(pPtr->getInfo().find("Порошок"), std::string::npos);
    EXPECT_NE(mPtr->getInfo().find("Порошок"), std::string::npos);

    delete pPtr;
    delete mPtr;
}

TEST(PharmacyTest, PrintAllOutput) {
    Pharmacy ph;
    ph.addProduct(Product("Гематоген", 50.0, 1));
    ph.addMedicine(Medicine("Аспирин", 120.0, ReleaseForm("Таблетки"), Manufacturer("Bayer"), "10.2025", "От боли", 2));

    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    ph.printAll();

    std::cout.rdbuf(oldCout);
    std::string output = buffer.str();

    EXPECT_NE(output.find("Гематоген"), std::string::npos);
    EXPECT_NE(output.find("Аспирин"), std::string::npos);
    EXPECT_NE(output.find("Bayer"), std::string::npos);
}

TEST(PharmacyTest, PrintSalesForMedicineByPeriodOutput) {
    Pharmacy ph;
    Medicine m("Парацетамол", 150.0, ReleaseForm("Таблетки"), Manufacturer("ФармаПлюс"), "12.2025", "От жара");
    m.addSale(SaleRecord("Иванов И.И.", "15.10.2023", 2));
    m.addSale(SaleRecord("Сидоров С.С.", "05.11.2023", 3));
    ph.addMedicine(m);

    std::stringstream buffer1;
    std::streambuf* oldCout1 = std::cout.rdbuf(buffer1.rdbuf());
    ph.printSalesForMedicineByPeriod("Парацетамол", ".10.2023");
    std::cout.rdbuf(oldCout1);

    std::string out1 = buffer1.str();
    EXPECT_NE(out1.find("Иванов И.И."), std::string::npos);
    EXPECT_EQ(out1.find("Сидоров С.С."), std::string::npos);

    std::stringstream buffer2;
    std::streambuf* oldCout2 = std::cout.rdbuf(buffer2.rdbuf());
    ph.printSalesForMedicineByPeriod("Парацетамол", ".12.2023");
    std::cout.rdbuf(oldCout2);

    std::string out2 = buffer2.str();
    EXPECT_NE(out2.find("Продаж за этот период не найдено"), std::string::npos);

    std::stringstream buffer3;
    std::streambuf* oldCout3 = std::cout.rdbuf(buffer3.rdbuf());
    ph.printSalesForMedicineByPeriod("Несуществующее", ".10.2023");
    std::cout.rdbuf(oldCout3);

    std::string out3 = buffer3.str();
    EXPECT_NE(out3.find("Продаж за этот период не найдено"), std::string::npos);
}

TEST(PharmacyTest, PrintMedicinesForDiseaseOutput) {
    Pharmacy ph;
    Medicine m1("Парацетамол", 150.0, ReleaseForm("Таблетки"), Manufacturer("ФармаПлюс"), "12.2025", "От жара");
    m1.addTargetDisease("Головная боль");

    Medicine m2("Доктор Мом", 320.0, ReleaseForm("Сироп"), Manufacturer("Здоровье"), "01.2026", "От кашля");
    m2.addTargetDisease("Кашель");

    ph.addMedicine(m1);
    ph.addMedicine(m2);

    std::stringstream buffer1;
    std::streambuf* oldCout1 = std::cout.rdbuf(buffer1.rdbuf());
    ph.printMedicinesForDisease("Головная боль");
    std::cout.rdbuf(oldCout1);

    std::string out1 = buffer1.str();
    EXPECT_NE(out1.find("Парацетамол"), std::string::npos);
    EXPECT_EQ(out1.find("Доктор Мом"), std::string::npos);

    std::stringstream buffer2;
    std::streambuf* oldCout2 = std::cout.rdbuf(buffer2.rdbuf());
    ph.printMedicinesForDisease("Бессонница");
    std::cout.rdbuf(oldCout2);

    std::string out2 = buffer2.str();
    EXPECT_NE(out2.find("Подходящих лекарств не найдено"), std::string::npos);
}
