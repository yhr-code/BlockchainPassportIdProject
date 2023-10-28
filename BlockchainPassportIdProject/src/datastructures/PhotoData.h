#ifndef PHOTODATA_H
#define PHOTODATA_H
#include <zlib.h>
#include <iostream>
#include <cstring>

#include <string>
#include <vector>

struct photoData 
{
    int termNumber;//样品号
    char photoBeginTime[8];
    char photoEndTime[8];
    char photoShootingAgency[30];
    int width;
    int length;
    int pixelNumber;
    char imageFormat[3];//RGB BGR
    char storeArea[500000];//使用2进制
    uint32_t checksum;  // 用于存储CRC32校验值
    
    void WriteData(const char* data, int dataSize) {
        // 检查剩余空间是否足够
        if (dataSize > sizeof(storeArea)) {
            std::cout << "照片太大，无法存储。请选择较小的照片。" << std::endl;
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



    // Function to convert RGB image data to binary format
    std::vector<char> ConvertRGBToBinary(const std::string& rgbData, int width, int height)
    {
        // Perform conversion logic for RGB to binary
        // Example: Convert RGB data to binary format

    // Dummy conversion: In this example, simply copy the RGB data to binary
    std::vector<char> binaryData(rgbData.begin(), rgbData.end());
        return binaryData;
    }

    // Function to convert BGR image data to binary format
    std::vector<char> ConvertBGRToBinary(const std::string& bgrData, int width, int height) {
        // Perform conversion logic for BGR to binary
        // Example: Convert BGR data to binary format

        // Dummy conversion: In this example, simply copy the BGR data to binary
        
    std::vector<char> binaryData(bgrData.begin(), bgrData.end());
        return binaryData;
    }

    // Function to store binary image data in the data structure
    void StoreImageData(photoData& data, const std::string& imageFormat, const std::string& imageData, int width, int height) {
        std::vector<char> binaryData;

        // Convert image format to binary format
        if (imageFormat == "RGB") {
            binaryData = ConvertRGBToBinary(imageData, width, height);
        } 
    
    else if (imageFormat == "BGR") {
            binaryData = ConvertBGRToBinary(imageData, width, height);
        } else {
            std::cout << "Unsupported image format. Please provide RGB or BGR format." << std::endl;
            return;
        }

        // Check if the binary image data size is within the limit
        if (binaryData.size() > sizeof(data.storeArea)) {
            std::cout << 
        
    "Image size exceeds the storage limit. Please choose a smaller image." << std::endl;
            return;
        }

        // Copy binary image data to storeArea
        std::copy(binaryData.begin(), binaryData.end(), data.storeArea);

        // Pad the remaining space in storeArea with zeros (if necessary)
        std::fill(data.storeArea + binaryData.size(), data.storeArea + sizeof(data.storeArea), 0);

        // Update other members and calculate checksum
        data.width = width;
        data.length = height;
        data.pixelNumber = width * height;
    // Calculate the checksum
        data.CalculateChecksum();
    }
};



#endif //PHOTODATA_H