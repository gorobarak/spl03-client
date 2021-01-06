#ifndef BGRSENCODERDECODER__
#define BGRSENCODERDECODER__

#include <string>
#include <vector>

enum operationType {
    ADMINREG,
    STUDENTREG,
    LOGIN,
    LOGOUT,
    COURSEREG,
    KDAMCHECK,
    COURSESTAT,
    STUDENTSTAT,
    ISREGISTERED,
    UNREGISTER,
    MYCOURSES,
    ACK,
    ERR
};

class BGRSencoderDecoder {
private:
    int idx = 0;
    int opcode;
    int subjectOpcode;
    std::vector<char> buffer;





    operationType operationType (const std::string& inString);
    void pushByte(char c);
    std::string popString();
    void shortToBytes(short num, char* byteArr);
    short bytesToShort(char* bytesArr);

public:
    std::string encode(std::string msg);
    std::string decodeNextByte(char c);
};

#endif
