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
    char opcode[2];
    std::size_t pos = msg.find(' ');
    std::string operation(msg.substr(0,pos));
    std::string body(msg.substr(pos + 1,msg.length()));
    switch (operationType(operation)) {
        case ADMINREG:{
            shortToBytes(1, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);

            std::size_t split = body.find(' ');
            std::string username(msg.substr(0,split));
            std::string pass(msg.substr(split + 1,body.length()));

            for (int i = 0; i < username.size(); i++) {
                buffer.push_back(username[i]);
            }
            buffer.push_back('\0');
            for (int i = 0; i < pass.size(); i++) {
                buffer.push_back(pass[i]);
            }
            buffer.push_back('\0');
            break;
        }
        case STUDENTREG:{
            shortToBytes(2, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);

            std::size_t split = body.find(' ');
            std::string username(msg.substr(0,split));
            std::string pass(msg.substr(split + 1,body.length()));

            for (int i = 0; i < username.size(); i++) {
                buffer.push_back(username[i]);
            }
            buffer.push_back('\0');
            for (int i = 0; i < pass.size(); i++) {
                buffer.push_back(pass[i]);
            }
            buffer.push_back('\0');
            break;
        }
        case LOGIN:{
            shortToBytes(3, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);

            std::size_t split = body.find(' ');
            std::string username(msg.substr(0,split));
            std::string pass(msg.substr(split + 1,body.length()));

            for (int i = 0; i < username.size(); i++) {
                buffer.push_back(username[i]);
            }
            buffer.push_back('\0');
            for (int i = 0; i < pass.size(); i++) {
                buffer.push_back(pass[i]);
            }
            buffer.push_back('\0');
            break;
        }
        case LOGOUT: {
            shortToBytes(4, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            break;
        }
        case COURSEREG:{
            shortToBytes(5, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            for (int i = 0; i < body.size(); i++) {
                buffer.push_back(body[i]);
            }
            break;
        }
        case KDAMCHECK:{
            shortToBytes(6, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            for (int i = 0; i < body.size(); i++) {
                buffer.push_back(body[i]);
            }
            break;
        }
        case COURSESTAT:{
            shortToBytes(7, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            for (int i = 0; i < body.size(); i++) {
                buffer.push_back(body[i]);
            }
            break;
        }
        case STUDENTSTAT: {
            shortToBytes(8, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            for (int i = 0; i < body.size(); i++) {
                buffer.push_back(body[i]);
            }
            buffer.push_back('\0');
            break;
        }
        case ISREGISTERED:{
            shortToBytes(9, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            for (int i = 0; i < body.size(); i++) {
                buffer.push_back(body[i]);
            }
            break;
        }
        case UNREGISTER:{
            shortToBytes(10, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            for (int i = 0; i < body.size(); i++) {
                buffer.push_back(body[i]);
            }
            break;
        }
        case MYCOURSES: {
            shortToBytes(11, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            break;
        }
//        case ACK:
//        case ERR:
        default:{
            break;
        }
    }
    return std::string(buffer.begin(), buffer.end());
}

void shortToBytes(short num, char* bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

short bytesToShort(char* bytesArr) {
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}

std::string BGRSencoderDecoder::decodeNextByte(char c) {


}


