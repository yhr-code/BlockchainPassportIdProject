#ifndef FINGERPRINTSDATA_H
#define FINGERPRINTSDATA_H
#include <zlib.h>
#include <iostream>
#include <cstring>

#include <string>
#include <vector>
struct fingerprintsData
{
    fingerData leftHandFingerData;
    fingerData rightHandFingerData;
};

struct fingerData
{
   int termNumber;//样品号
   char fingerDataBeginTime[8];
   char fingerDataEndTime[8];
   char fingerBiometricCollectionAgency[30];
   char fingerBiometricFormat[10];
   char FingerprintUsage[2];//  r and l 表示左右手 1-5表示从大拇指到小拇指 一共2位 如果缺失 用xx代替
   char storeArea[10000];
   uint32_t checksum;  // 用于存储CRC32校验值

   void WriteData(const char* data, int dataSize) {
        // 检查剩余空间是否足够
        if (dataSize > sizeof(storeArea)) {
            std::cout << "指纹特征空间太大，无法存储。请选择较小特征数据。" << std::endl;
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

#endif //FINGERPRINTSDATA_H
