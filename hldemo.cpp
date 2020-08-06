#include "hldemo.h"

#include <iostream>
#include <fstream>
#include <iostream>

namespace HLDemo {
DemoInfoReturnCode getDemoInfo(const std::string path, DemoInfo & demoInfo)
{
    // See https://developer.valvesoftware.com/wiki/Demo
    // for information about the file format
    std::ifstream file;
    file.open(path, std::ios::binary | std::ios::in);

    char buf[261];
    if (!file.is_open()) {
        return FILE_NOT_FOUND;
    }
    // Check if the file has the correct header
    file.read(buf, 8);
    if (strcmp("HL2DEMO\0", buf)) {
        return INVALID_FILE;
    }
    // skip over two integer parameters we don't care about
    file.seekg(8, file.cur);

    file.read(buf, 260);
    demoInfo.serverName = buf;
    file.read(buf, 260);
    demoInfo.clientName = buf;
    file.read(buf, 260);
    demoInfo.mapName = buf;
    file.seekg(260);
    file.read((char *)(& demoInfo.playbackTime), sizeof (float));
    file.read((char *)(& demoInfo.numTicks), sizeof (int));
    demoInfo.fileName = path;
    file.close();
    return SUCCESS;
}
}
