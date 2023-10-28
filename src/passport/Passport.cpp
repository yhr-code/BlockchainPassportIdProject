#include "PassportStructs.h"

// 实现 PassportForeignKey 的构造函数
PassportForeignKey::PassportForeignKey(IdCardData* idCard, int passportNumber) {
    idCardPtr = idCard;
    passportPtr = nullptr;
    this->passportNumber = passportNumber;
    isLatestPassport = false;
}

// 实现 PassportForeignKey 的构造函数
PassportForeignKey::PassportForeignKey(PassportData* passport, int passportNumber, bool isLatest) {
    idCardPtr = nullptr;
    passportPtr = passport;
    this->passportNumber = passportNumber;
    isLatestPassport = isLatest;
}

// 设置护照指针
void PassportForeignKey::setPassportPointer(PassportData* passport) {
    passportPtr = passport;
}

// 设置身份证指针
void PassportForeignKey::setIdCardPointer(IdCardData* idCard) {
    idCardPtr = idCard;
}

// PassportData 的构造函数
PassportData::PassportData() {
    // 在这里初始化 PassportData 的成员变量
}

// PassportSign 的构造函数
PassportSign::PassportSign(const PassportData& passportData) {
    std::strcpy(passportIDget, passportData.passportID);
    // 其他成员变量的初始化
}

// 如果有其他成员函数的实现，也可以在这里添加

// 如果有其他 Passport 类相关的函数实现，也可以在这里添加
