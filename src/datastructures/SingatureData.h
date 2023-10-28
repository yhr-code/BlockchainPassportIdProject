#ifndef SINGATUREDATA_H
#define SINGATUREDATA_H
#include <zlib.h>
#include <iostream>
#include <cstring>

#include <string>
#include <vector>

struct signatureData {
    int termNumber; //样品号
    char signatureBeginTime[8];
    char signatureEndTime[8];
    char signatureShootingAgency[30];
    int width;      // 分辨率宽度
    int length;     // 分辨率高度
    int pixelNumber; // 像素数量
    char imageFormat[3]; // 仅支持黑白，可以用BW表示
    char storeArea[300 * 1000]; // 用于存储二进制数据，300x1000的分辨率，每个像素一个字节
    uint32_t checksum; // 用于存储CRC32校验值

    void WriteData(const char* data, int dataSize) {
        // 检查剩余空间是否足够
        if (dataSize > sizeof(storeArea)) {
            std::cout << "签名数据太大，无法存储。请选择较小的签名图像。" << std::endl;
            return;
        }

        // 复制数据到存储空间
        std::memcpy(storeArea, data, dataSize);

        // 更新pixelNumber和checksum
        pixelNumber = width * length;
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


#endif //SINGATUREDATA_H