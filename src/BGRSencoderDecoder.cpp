#include <BGRSencoderDecoder.h>
#include <vector>
#include <iostream>

operationType BGRSencoderDecoder::operationType (const std::string& inString) {
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
            std::string username(body.substr(0,split));
            std::string pass(body.substr(split + 1,body.length()));

            for (unsigned int i = 0; i < username.size(); i++) {
                buffer.push_back(username[i]);
            }
            buffer.push_back('\0');
            for (unsigned int i = 0; i < pass.size(); i++) {
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
            std::string username(body.substr(0,split));
            std::string pass(body.substr(split + 1,body.length()));

            for (unsigned int i = 0; i < username.size(); i++) {
                buffer.push_back(username[i]);
            }
            buffer.push_back('\0');
            for (unsigned int i = 0; i < pass.size(); i++) {
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
            std::string username(body.substr(0,split));
            std::string pass(body.substr(split + 1,body.length()));

            for (unsigned int i = 0; i < username.size(); i++) {
                buffer.push_back(username[i]);
            }
            buffer.push_back('\0');
            for (unsigned int i = 0; i < pass.size(); i++) {
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
            short b = std::stoi(body);
            char courseNum[2];
            shortToBytes(b, courseNum);
            buffer.push_back(courseNum[0]);
            buffer.push_back(courseNum[1]);
            break;
        }
        case KDAMCHECK:{
            shortToBytes(6, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            short b = std::stoi(body);
            char courseNum[2];
            shortToBytes(b, courseNum);
            buffer.push_back(courseNum[0]);
            buffer.push_back(courseNum[1]);
            break;
        }
        case COURSESTAT:{
            shortToBytes(7, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            short b = std::stoi(body);
            char courseNum[2];
            shortToBytes(b, courseNum);
            buffer.push_back(courseNum[0]);
            buffer.push_back(courseNum[1]);
            break;
        }
        case STUDENTSTAT: {
            shortToBytes(8, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            for (unsigned int i = 0; i < body.size(); i++) {
                buffer.push_back(body[i]);
            }
            buffer.push_back('\0');
            break;
        }
        case ISREGISTERED:{
            shortToBytes(9, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            short b = std::stoi(body);
            char courseNum[2];
            shortToBytes(b, courseNum);
            buffer.push_back(courseNum[0]);
            buffer.push_back(courseNum[1]);
            break;
        }
        case UNREGISTER:{
            shortToBytes(10, opcode);
            buffer.push_back(opcode[0]);
            buffer.push_back(opcode[1]);
            short b = std::stoi(body);
            char courseNum[2];
            shortToBytes(b, courseNum);
            buffer.push_back(courseNum[0]);
            buffer.push_back(courseNum[1]);
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

void BGRSencoderDecoder::shortToBytes(short num, char* bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

short BGRSencoderDecoder::bytesToShort(char* bytesArr) {
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}

std::string BGRSencoderDecoder::decodeNextByte(char c) {
    idx++;
    pushByte(c);
    if (idx == 2) {
        char arr[2];
        arr[0] = buffer[0];
        arr[1] = buffer[1];

        opcode = bytesToShort(arr);
    }
    if (idx == 4) {
        char arr[2];
        arr[0] = buffer[2];
        arr[1] = buffer[3];

        subjectOpcode = bytesToShort(arr);
    }

    if(idx <= 4) {
        return "-1";
    }

    switch (opcode) {
        case 12: {
            if (c == '\0') {
                return ("ACK " + std::to_string(subjectOpcode)  + popString());
            }
            break;
        }

        case 13: {//error
            if (c == '\0') {
                idx = 0;
                buffer.clear();
                return ("ERROR " + std::to_string(subjectOpcode));
            }
            break;
        }
    }
    return "-1";
}

std::string BGRSencoderDecoder::popString() {
    std::string out;
    for (unsigned int i = 4; i < buffer.size() - 1; i++) {//not including ending \0
        out += buffer[i];
    }
    idx = 0;
    buffer.clear();
    return (out.length() == 0) ? out : "\n" + out;
}

void BGRSencoderDecoder::pushByte(char c) {
    buffer.push_back(c);
}

BGRSencoderDecoder::BGRSencoderDecoder() : idx(0), opcode(0), subjectOpcode(0), buffer() {}


