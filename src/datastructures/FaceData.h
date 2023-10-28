#ifndef FACEDATA_H
#define FACEDATA_H
#include <zlib.h>
#include <iostream>
#include <cstring>

#include <string>
#include <vector>

struct faceData
{
   int termNumber;//样品号
   char faceDataBeginTime[8];
   char faceDataEndTime[8];
   char facialBiometricCollectionAgency[30];
   char facialBiometricFormat[10];
   char storeArea[10000];
   uint32_t checksum;  // 用于存储CRC32校验值

   void WriteData(const char* data, int dataSize) {
        // 检查剩余空间是否足够
        if (dataSize > sizeof(storeArea)) {
            std::cout << "面部特征空间太大，无法存储。请选择较小特征数据。" << std::endl;
            return;
        }

        // 复制数据到存储空间
        std::memcpy(storeArea, data, dataSize);

        // 更新checksum
    
        CalculateChecksum();
    }

    void CalculateChecksum() {
        checksum = 0;
        for (int i = 0; i < sizeof(storeArea); ++i) {
            checksum += static_cast<uint32_t>(storeArea[i]);
        }
    }

    bool VerifyChecksum() {
        uint32_t storedChecksum = checksum;
        CalculateChecksum(); // 重新计算以防数据修改
        return storedChecksum == checksum;
    } 

   
};
#endif //FACEDATA_H