#include "jasonobject.h"
#include "jasonvalue.h"
#include <iostream>
#include <string>

JasonObject::~JasonObject()
{
    for(auto item : values)
    {
        delete item.second;
        item.second = nullptr;
    }

    values.clear();
}

bool JasonObject::Parse(char*& start, char* end, std::string key, char terminator)
{
    while(start != end)
    {
        if (*start == '}')
            break;

        if (*start == '"')
        {
            std::string key = ParseKey(start, end, '"');
            if (key.empty())
                return false;
            else
            {
                values[key] = nullptr;
            }            

            if (!ParseValue(start, end, key, terminator))
                return false;
        }

        start++;
    }

    return true;
}

std::string JasonObject::ParseKey(char*& start, char* end, char terminator)
{
    bool bRightQuote = false;
    bool bLeftQuote = false;
    char* temp;

    while(start != end)
    {
        if (start == end)
            if (!bRightQuote)
                return "";

        if(*start == '"')
        {
            if (!bLeftQuote)
            {
                bLeftQuote = true;
                temp = start + 1;
            }
            else
            {
                if (!bRightQuote)
                    bRightQuote = true;

                if (bLeftQuote && bRightQuote) {
                    std::string key;
                    key.assign(temp, start);
                    if(key.empty())
                        return "";

                    start ++;
                    return key;
                }
            }
        } 

        start++;
    }

    return "";
}

bool JasonObject::ParseValue(char*& start, char* end, std::string key, char terminator)
{
    JasonValue *value = nullptr;
    while(start != end)
    {
        if (*start ==' ' || *start == ':')
        {
            start++;
            continue;
        }
        else if (*start == '[')
        {
            start++;
            value = new JasonListValue();
            values[key] = value;
        }
        else if (*start == '{')
        {
            start++;
            value = new JasonObject();
            values[key] = value;
        }
        else if (*start == '"')
        {
            start++;
            value = new JasonStringValue();
            values[key] = value;
        }   
        else if (*start == 'f' || *start == 't')
        {
            value = new JasonBoolValue();
            values[key] = value;
        }
        else if (*start >= '0' && *start <= '9')
        {
            value = new JasonIntValue();
            values[key] = value;
        }

        if (value) {
            if(value->Parse(start, end, key, '}'))
                return true;
            else
            {
                delete value;
                value = nullptr;
                return false;
            }             
        }

        start++;
    }
    return true;
}

std::string JasonObject::tostring(std::string &out)
{
    if (values.size() > 0)
    {
        int intend = 0;
        Print(out, intend);        
    }

    return out;
}

void JasonObject::tostring(std::ostream &out)
{
    if (values.size() > 0)
    {
        int intend = 0;
        Print(out, intend);        
    }
}

void JasonObject::PrintHead(std::string &content, int intend)
{
    std::string temp((intend)*4, ' ');
    content += temp;
    content += "{\n\r";
}

void JasonObject::PrintContent(std::string &content, int intend)
{
    int i=0;
    int size = (int)values.size();

    intend++;

    for(auto& item : values)
    {
        std::string temp(intend*4, ' ');
        content += temp;
        content += "\"";
        content += item.first;
        content += "\":";

        item.second->Print(content, intend);

        if (++i < size)
            content += ",";

        content += "\n\r";
    }

    intend--;
}

void JasonObject::PrintEnd(std::string &content, int intend)
{
    std::string temp((intend)*4, ' ');
    content += temp;
    content += "}";
}

void JasonObject::PrintHead(std::ostream &content, int intend)
{
    std::string temp((intend)*4, ' ');
    content << temp;
    content << "{\n\r";
}

void JasonObject::PrintContent(std::ostream &content, int intend)
{
    int i=0;
    int size = (int)values.size();

    intend++;

    for(auto& item : values)
    {
        std::string temp(intend*4, ' ');
        content << temp;
        content << "\"";
        content << item.first;
        content << "\":";

        item.second->Print(content, intend);

        if (++i < size)
            content << ",";

        content << "\n\r"; 
    }

    intend--;
}

void JasonObject::PrintEnd(std::ostream &content, int intend)
{
    std::string temp((intend)*4, ' ');
    content << temp;
    content << "}";
}