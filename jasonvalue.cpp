#include "jasonvalue.h"
#include "jasonobject.h"
#include <string>

JasonListValue::~JasonListValue()
{
    for(auto item : values)
    {
        delete item;
        item = nullptr;
    }

    values.clear();
}

bool JasonStringValue::Parse(char*& start, char* end, std::string key, char terminator)
{
    char* temp = start;
    while(start != end)
    {
        if(*start == '"')
        {
            value.assign(temp, start);
            start++;
            return true;
        } 

        start++;
    }
    return true;
}

bool JasonListValue::Parse(char*& start, char* end, std::string key, char terminator)
{
    JasonValue *v = nullptr;
    while(start != end)
    {
        if (*start == ']')
            return true;

        if (*start == '{')
        {
            while(*start != '}')
            {
                v = new JasonObject();
                if (v->Parse(start, end, "",'}'))
                {
                    values.emplace_back(v);
                    v = nullptr;
                }
                else
                    return false;
            }
        }

        if (*start == '"')
        {
            start++;
            v = new JasonStringValue();
            if (v->Parse(start, end, "",'}'))
            {
                values.emplace_back(v);
                v = nullptr;
                continue;
            }
            else
                return false;
        }

        if (*start == 'f' || *start == 't')
        {
            v = new JasonBoolValue();
            if (v->Parse(start, end, "", '}'))
            {
                values.emplace_back(v);
                v = nullptr;
                continue;
            }
            else
                return false;
        }

        if (*start >= '0' && *start <= '9')
        {
            v = new JasonIntValue();
            if (v->Parse(start, end, "", '}'))
            {
                values.emplace_back(v);
                v = nullptr;
                continue;
            }
            else
                return false;
        }

        start++;
    }

    return true;
}

bool JasonIntValue::Parse(char*& start, char* end, std::string key, char terminator)
{
    char* temp = start;
    while(start != end)
    {
        if (*start == ',' || *start == '\n' || *start == ']')
        {
            std::string str(temp, start);
            value = std::stoi(str);
            return true;
        }

        start++;
    }
    return true;
}

bool JasonDoubleValue::Parse(char*& start, char* end, std::string key, char terminator)
{
    char* temp = start;
    while(start != end)
    {
        if (*start == ',' || *start == '\n' || *start == ']')
        {
            std::string str(temp, start);
            value = std::stod(str);
            return true;
        }

        start++;
    }
    return true;
}

bool JasonBoolValue::Parse(char*& start, char* end, std::string key, char terminator)
{
    char* temp = start;
    while(start != end)
    {
        if (*start == ',' || *start == ']' || *start == '\n')
            return true;

        if (*start == 'f')
        {
            value = false;
        }

        if (*start == 't')
        {
            value = true;
        }

        start++;
    }
    return true;
}


void JasonStringValue::PrintHead(std::string &content, int intend)
{
    content += "\"";
}

void JasonStringValue::PrintContent(std::string &content, int intend)
{
    content += value;
}

void JasonStringValue::PrintEnd(std::string &content, int intend)
{
    content += "\"";
}

void JasonIntValue::PrintHead(std::string &content, int intend)
{

}

void JasonIntValue::PrintContent(std::string &content, int intend)
{
    std::string temp = std::to_string(value);
    content += temp;
}

void JasonIntValue::PrintEnd(std::string &content, int intend)
{

}

void JasonBoolValue::PrintHead(std::string &content, int intend)
{

}

void JasonBoolValue::PrintContent(std::string &content, int intend)
{
    std::string temp;
    if (value)
    {
        temp = "true";
        content += temp;
    }
    else
    {
        temp = "false";
        content += temp;
    }
}

void JasonBoolValue::PrintEnd(std::string &content, int intend)
{
}

void JasonDoubleValue::PrintHead(std::string &content, int intend)
{

}

void JasonDoubleValue::PrintContent(std::string &content, int intend)
{
    std::string temp = std::to_string(value);
    content += temp;
}

void JasonDoubleValue::PrintEnd(std::string &content, int intend)
{

}

void JasonListValue::PrintHead(std::string &content, int intend)
{
    std::string temp = "[";
    content += "[";

    if (values.size() > 0)
    {
        JasonValue *v = values[0];
        if (v->IsObject())
        {
            bNeedReturn = true;
            content += "\n\r";
        }        
    }
}

void JasonListValue::PrintContent(std::string &content, int intend)
{
    int i=0;
    int size = (int)values.size();

    for(auto &item : values)
    {
        if (i>0 && item->IsObject())
        {
            content += "\n\r";
        }
        
        item->Print(content, intend);

        if (++i < size)
        {
            content += ",";
        }
    }
}

void JasonListValue::PrintEnd(std::string &content, int intend)
{
    content += "]";
}


//
void JasonStringValue::PrintHead(std::ostream &content, int intend)
{
    std::string temp = "\"";
    content << temp;
}

void JasonStringValue::PrintContent(std::ostream &content, int intend)
{
    content << value;
}

void JasonStringValue::PrintEnd(std::ostream &content, int intend)
{
    std::string temp = "\"";
    content << temp;
}

void JasonIntValue::PrintHead(std::ostream &content, int intend)
{

}

void JasonIntValue::PrintContent(std::ostream &content, int intend)
{
    std::string temp = std::to_string(value);
    content << temp;
}

void JasonIntValue::PrintEnd(std::ostream &content, int intend)
{

}

void JasonBoolValue::PrintHead(std::ostream &content, int intend)
{

}

void JasonBoolValue::PrintContent(std::ostream &content, int intend)
{
    std::string temp;
    if (value)
    {
        temp = "true";
        content << temp;
    }
    else
    {
        temp = "false";
        content << temp;
    }
}

void JasonBoolValue::PrintEnd(std::ostream &content, int intend)
{
}

void JasonDoubleValue::PrintHead(std::ostream &content, int intend)
{

}

void JasonDoubleValue::PrintContent(std::ostream &content, int intend)
{
    std::string temp = std::to_string(value);
    content << temp;
}

void JasonDoubleValue::PrintEnd(std::ostream &content, int intend)
{

}

void JasonListValue::PrintHead(std::ostream &content, int intend)
{
    std::string temp = "[";
    content << temp;

    if (values.size() > 0)
    {
        JasonValue *v = values[0];
        if (v->IsObject())
        {
            bNeedReturn = true;
            temp = "\n\r";
            content << temp;
        }        
    }
}

void JasonListValue::PrintContent(std::ostream &content, int intend)
{
    int i=0;
    int size = (int)values.size();

    for(auto &item : values)
    {
        if (i>0 && item->IsObject())
        {
            content << "\n\r";
        }

        item->Print(content, intend);
        
        if (++i < size)
        {
            content << ",";
        }
    }
}

void JasonListValue::PrintEnd(std::ostream &content, int intend)
{
    std::string temp = "]";
    content << temp;
}