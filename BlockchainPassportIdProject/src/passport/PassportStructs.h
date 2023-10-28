#ifndef PASSPORTSTRUCTS_H
#define PASSPORTSTRUCTS_H
#include <zlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "PhotoData.h"
#include "FaceData.h"
#include "FingerprintsData.h"
#include "SingatureData.h"
#include "IdcardStructs.h"

struct IdentityDocuments
{
    struct IdentityDocumentsData;
    struct IdentityDocumentsId;
    struct IdentityDocumentsForeignKey;
};

struct Passport//
{
    struct PassportSign;
    struct PassportData;
    struct PassportForeignKey;
};

// struct IdCard {
//     struct IdCardData {
//         // ...成员变量和方法...
//     };

//     struct IdCardSign {
//         // ...成员变量和方法...
//     };

//     class IdCardForeignKey {
//         // ...成员变量和方法...
//     };

//     IdCardData data;
//     IdCardSign sign;
//     IdCardForeignKey foreignKey; // 这里实例化了 IdCaForeignKey 类
// };//待补充


struct PassportSign {
    char citizenID[30];  // 公民唯一ID
    char passportIDget[9];  // 获取护照号码
    int term;  // 表明这是该公民第几本护照
    bool newest;  // 表示是否为最新护照

    // 构造函数的声明
    PassportSign(const PassportData& passportData)
    {
    std::strcpy(passportIDget, passportData.passportID);
    // 初始化其他成员变量
    };
};




struct PassportData 
{
    char* data;                // 用于存储大容量数据
    char name[30];             // 姓名，30字节
    char passportID[9];        // 护照号码，9字节 like E12345678//代表这本护照的唯一显式标识
    char countryOfIssue[3];    // 发行国家，3字节 like CHN
    char nationality[3];       // 国籍，3字节 like CHN
    char dateOfBirth[8];       // 出生日期，8字节 like 20020822(YYYY-MM-DD)
    char gender;               // 性别，1字节 like F/M/N
    char issuingAgency[40];    // 发行机构，40字节
    char startDate[4];         // 护照有效期开始日期，4字节
    char expirationDate[4];    // 护照有效期结束日期，4字节
    photoData photo;          // 照片数据
    faceData faceData;
    fingerprintsData fingeData;
    signatureData signature;
    
};

struct PassportForeignKey
{
    IdCardForeignKey* idCardPtr; // 指向身份证数据的指针
    PassportData* passportPtr; // 指向护照数据的指针
    int passportNumber; // 护照发放顺序 从最开始第一本护照为1 依次累加
    bool isLatestPassport; // 是否为最新护照的标志

    // 构造函数，接受指向身份证数据的指针和护照编号
    PassportForeignKey(IdCardData* idCard, int passportNumber);

    // 构造函数，接受指向护照数据的指针、护照编号和是否为最新护照的标志
    PassportForeignKey(PassportData* passport, int passportNumber, bool isLatest);

    // 设置护照指针
    void setPassportPointer(PassportData* passport);

    // 设置身份证指针
    void setIdCardPointer(IdCardData* idCard);
};//需要修改



#endif // PASSPORTSTRUCTS_H
