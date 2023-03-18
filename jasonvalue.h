#ifndef _JASON_VALUE_H_
#define _JASON_VALUE_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>

enum TYPE
{
    TYPE_STRING = 0,
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_BOOL,
    TYPE_ARRAY,
    TYPE_OBJECT,
};

class JasonValue
{
public:
    virtual ~JasonValue() {}
    virtual bool Parse(char*& start, char* end, std::string key, char terminator) = 0;
    void Print(std::string &content, int intend)
    {
        PrintHead(content, intend);
        PrintContent(content, intend);
        PrintEnd(content, intend);
    }

    void Print(std::ostream &content, int intend)
    {
        PrintHead(content, intend);
        PrintContent(content, intend);
        PrintEnd(content, intend);
    }

    bool IsObject() { return type == TYPE_OBJECT; }
    bool IsArray() { return type == TYPE_ARRAY; }
    bool IsBool() { return type == TYPE_BOOL; }
    bool IsInt() { return type == TYPE_INT; }
    bool IsDouble() { return type == TYPE_DOUBLE; }
    bool IsString() { return type == TYPE_STRING; }

private:
    virtual void PrintHead(std::string &content, int intend) = 0;
    virtual void PrintContent(std::string &content, int intend) = 0;
    virtual void PrintEnd(std::string &content, int intend) = 0;


    virtual void PrintHead(std::ostream &content, int intend) = 0;
    virtual void PrintContent(std::ostream &content, int intend) = 0;
    virtual void PrintEnd(std::ostream &content, int intend) = 0;

protected:
    JasonValue(TYPE t) : type(t) {}
    TYPE type;
};

class JasonStringValue : public JasonValue
{
public:
    bool Parse(char*& start, char* end, std::string key, char terminator);
    virtual void PrintHead(std::string &content, int intend);
    virtual void PrintContent(std::string &content, int intend);
    virtual void PrintEnd(std::string &content, int intend);

    virtual void PrintHead(std::ostream &content, int intend);
    virtual void PrintContent(std::ostream &content, int intend);
    virtual void PrintEnd(std::ostream &content, int intend);

protected:
    friend class JasonObject;
    friend class JasonListValue;

    JasonStringValue() : JasonValue(TYPE_STRING) {}
    std::string value;
};

class JasonListValue : public JasonValue
{
public:
    ~JasonListValue();
    bool Parse(char*& start, char* end, std::string key, char terminator);
    virtual void PrintHead(std::string &content, int intend);
    virtual void PrintContent(std::string &content, int intend);
    virtual void PrintEnd(std::string &content, int intend);

    virtual void PrintHead(std::ostream &content, int intend);
    virtual void PrintContent(std::ostream &content, int intend);
    virtual void PrintEnd(std::ostream &content, int intend);

protected:
    friend class JasonObject;
    JasonListValue() : JasonValue(TYPE_ARRAY) {}
    std::vector<JasonValue*> values;
    bool bNeedReturn = false;
};

class JasonIntValue : public JasonValue
{
public:
    bool Parse(char*& start, char* end, std::string key, char terminator);
    virtual void PrintHead(std::string &content, int intend);
    virtual void PrintContent(std::string &content, int intend);
    virtual void PrintEnd(std::string &content, int intend);

    virtual void PrintHead(std::ostream &content, int intend);
    virtual void PrintContent(std::ostream &content, int intend);
    virtual void PrintEnd(std::ostream &content, int intend);

protected:
    friend class JasonObject;
    friend class JasonListValue;

    JasonIntValue() : JasonValue(TYPE_INT) {}
    int value;
};

class JasonDoubleValue : public JasonValue
{
public:
    bool Parse(char*& start, char* end, std::string key, char terminator);
    virtual void PrintHead(std::string &content, int intend);
    virtual void PrintContent(std::string &content, int intend);
    virtual void PrintEnd(std::string &content, int intend);

    virtual void PrintHead(std::ostream &content, int intend);
    virtual void PrintContent(std::ostream &content, int intend);
    virtual void PrintEnd(std::ostream &content, int intend);

protected:
    friend class JasonObject;
    friend class JasonListValue;

    JasonDoubleValue() : JasonValue(TYPE_DOUBLE) {}
    double value;
};

class JasonBoolValue : public JasonValue
{
public:
    bool Parse(char*& start, char* end, std::string key, char terminator);
    virtual void PrintHead(std::string &content, int intend);
    virtual void PrintContent(std::string &content, int intend);
    virtual void PrintEnd(std::string &content, int intend);

    virtual void PrintHead(std::ostream &content, int intend);
    virtual void PrintContent(std::ostream &content, int intend);
    virtual void PrintEnd(std::ostream &content, int intend);

protected:
    friend class JasonObject;
    friend class JasonListValue;

    JasonBoolValue() : JasonValue(TYPE_BOOL) {}
    bool value;
};

#endif