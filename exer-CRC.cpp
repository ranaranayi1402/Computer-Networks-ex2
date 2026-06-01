#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

uint32_t crc32(const string& data) {
    uint32_t crc = 0xFFFFFFFF;

    for (unsigned char c : data) {
        crc ^= c;

        for (int i = 0; i < 8; i++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }

    return ~crc;
}

//test
int main() {

    string frame =
        "DestinationMAC"
        "SourceMAC"
        "EtherType"
        "PayloadData";

    uint32_t fcs = crc32(frame);

    cout << "CRC/FCS = "
         << hex << uppercase
         << fcs << endl;


    uint32_t receivedFCS = crc32(frame);

    if (receivedFCS == fcs)
        cout << "Frame is VALID" << endl;
    else
        cout << "Frame is CORRUPTED" << endl;

    return 0;
}