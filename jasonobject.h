#ifndef _JASON_OBJECT_H_
#define _JASON_OBJECT_H_

#include <string>
#include <map>

#include "jasonvalue.h"

class JasonObject : public JasonValue
{
public:
    JasonObject() : JasonValue(TYPE_OBJECT) {}
    ~JasonObject();
    
    bool Parse(char*& start, char* end, std::string key, char terminator);
    void PrintHead(std::string &content, int intend);
    void PrintContent(std::string &content, int intend);
    void PrintEnd(std::string &content, int intend);

    void PrintHead(std::ostream &content, int intend);
    void PrintContent(std::ostream &content, int intend);
    void PrintEnd(std::ostream &content, int intend);
  
    std::string tostring(std::string &out);
    void tostring(std::ostream &out);

private:
    std::string ParseKey(char*& start, char* end, char terminator);
    bool ParseValue(char*& start, char* end, std::string key, char terminator);

    std::map<std::string, JasonValue*> values;
};

#endif