#ifndef BGRSENCODERDECODER__
#define BGRSENCODERDECODER__

#include <string>

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
    operationType operationType (const std::string& inString)

public:
    std::string encode(std::string msg);
    std::string decodeNextByte(char c);
};

#endif
