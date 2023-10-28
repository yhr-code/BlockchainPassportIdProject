
#ifndef IDCARDSTRUCT_H
#define IDCARDSTRUCT_H
#include <zlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
struct IdCard {
    struct IdCardData {
        // ...成员变量和方法...
    };

    struct IdCardSign {
        // ...成员变量和方法...
    };

    struct IdCardForeignKey {
        // ...成员变量和方法...
    };

    IdCardData data;
    IdCardSign sign;
    IdCardForeignKey foreignKey; // 这里实例化了 IdCaForeignKey 类
};//待补充
#endif //IDCARDSTRUCT_H