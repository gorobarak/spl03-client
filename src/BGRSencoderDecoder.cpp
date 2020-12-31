#include <BGRSencoderDecoder.h>
#include <vector>

operationType operationType (const std::string& inString) {
    if (inString == "ADMINREG") return ADMINREG;
    if (inString == "LOGIN") return LOGIN;
    if (inString == "LOGOUT") return LOGOUT;
    if (inString == "STUDENTREG") return STUDENTREG;
    if (inString == "COURSEREG") return COURSEREG;
    if (inString == "KDAMCHECK") return KDAMCHECK;
    if (inString == "COURSESTAT") return COURSESTAT;
    if (inString == "STUDENTSTAT") return STUDENTSTAT;
    if (inString == "ISREGISTERED") return ISREGISTERED;
    if (inString == "UNREGISTER") return UNREGISTER;
    if (inString == "MYCOURSES") return MYCOURSES;
    if (inString == "ACK") return ACK;
    return ERR;
}

std::string BGRSencoderDecoder::encode(std::string msg) {
    std::vector<char> buffer;
    std::size_t pos = msg.find(' ');
    std::string operation(msg.substr(0,pos));
    std::string body(msg.substr(pos,msg.length()));
    switch (operationType(operation)) {
        case ADMINREG:
            break;
        case STUDENTREG:
            break;
        case LOGIN:
            break;
        case LOGOUT: {

            break;
        }
        case COURSEREG:
            break;
        case KDAMCHECK:
            break;
        case COURSESTAT:
            break;
        case STUDENTSTAT:
            break;
        case ISREGISTERED:
            break;
        case UNREGISTER:
            break;
        case MYCOURSES:
            break;
        case ACK:
            break;
        case ERR:
            break;
        default:{
            break;
        }
    }
}


