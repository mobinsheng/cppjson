#ifndef CPPJSON_H
#define CPPJSON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

using namespace std;

//namespace lazy

#ifndef null
#define null NULL
#endif

class xJSON;
class xJSONNode;

// json节点的值
// 值的类型有多种可能
class xJSONValue
{
    friend class xJSONNode;
    friend class xJSON;
public:
    xJSONValue(xJSONNode* pBelongto);
    ~xJSONValue();
    string&                                 toString();
    int&                                      toInt();
    double&                              toFloat();
    bool&                                  toBool();
    vector<xJSONNode*>&     toArray();
    xJSONNode*                      toObject();

    xJSONValue& operator=(const string& v);
    xJSONValue& operator=(const int v);
    xJSONValue& operator=(const double v);
    xJSONValue& operator=(const bool& v);
    xJSONValue& operator=(const vector<xJSONNode*>& v);
    xJSONValue& operator=(xJSONNode* v);

private:

    string                                   m_strValue;
    int                                         m_nValue;
    double                                  m_fValue;
    bool                                      m_bValue;
    vector<xJSONNode*>         m_ArrayValue;
    xJSONNode*                        m_pObjValue;

    xJSONNode*                      m_pBelongto;
};

class xJSONNode
{
public:

    xJSONNode();
    ~xJSONNode();

    friend class xJSONValue;
    friend class xJSON;

    void SetName(const string& name);

    void SetValue(int v);
    void SetValue(double v);
    void SetValue(xJSONNode* v);
    void SetValue(const vector<xJSONNode*>& v);
    void SetValue(const string& v);
    void SetValue(const char* v);
    void SetValue();
    void SetValueTrue();
    void SetValueFalse();

    void SetValue(const string& name,int v);
    void SetValue(const string& name,double v);
    void SetValueTrue(const string& name);
    void SetValueFalse(const string& name);
    void SetValue(const string& name,xJSONNode* v);
    void SetValue(const string& name,const vector<xJSONNode*>& v);
    void SetValue(const string& name,const string& v);

    xJSONNode& operator[](const string& key);

    xJSONNode& operator=(const string& v);
    xJSONNode& operator=(const char* v);
    xJSONNode& operator=(double v);
    xJSONNode& operator=(int v);
    xJSONNode& operator=(xJSONNode* v);
    xJSONNode& operator=(const bool& v);
    xJSONNode& operator=(const vector<xJSONNode*>& v);


    string&                                 toString();
    int&                                      toInt();
    double&                              toFloat();
    bool&                                  toBool();
    vector<xJSONNode*>&     toArray();
    xJSONNode*                      toObject();


    xJSONValue&         GetValue();


    vector<xJSONNode*>&    GetChild();
    int                              GetType();
    string                         GetName();


    void AddChild(const string& name,int value);
    void AddChild(const string& name,double value);
    void AddChild(const string& name,bool value);
    void AddChild(const string& name,const string& value);
    void AddChild(const string& name, xJSONNode* value);
    void AddChild(xJSONNode* value);
    void AddChild(const string& name,const vector<xJSONNode*> value);
    void AddChild(const string& name);


private:

    xJSONNode(const xJSONNode & rect);
    //赋值操作符
    xJSONNode& operator=(const xJSONNode &rect);
    int                         m_nType;

    string                   m_strName;

    xJSONValue          m_Value;

    vector<xJSONNode*> m_ChildList;
};

class xJSON
{
public:
    friend class xJSON;

    bool Open(const char* fileName);

    bool Failed();

    bool Read(const char* buffer);

    void  BuildJsonData(string& strData,bool format = true);

    void WiteFile(const string& fileName,bool format = true);

    xJSONNode* CreateJSON();

    void PrintJSON(xJSONNode* node);

    enum NodeType
    {
        invalid_type,
        null_type,
        string_type,
        int_type,
        double_type,
        bool_type,
        object_type,
        array_type,
    };


    ~xJSON();

    xJSONNode& operator[](const string& key);

    xJSONNode* GetRoot();




    xJSON();
private:

    xJSON(const xJSON & rect);
    //赋值操作符
    xJSON& operator=(const xJSON &rect);


    static void Build(xJSONNode* pNode,string& strData,bool format ,int depth);

    static void BuildStr(xJSONNode* pNode,string& strData,bool format ,int depth);
    static void BuildInt(xJSONNode* pNode,string& strData,bool format ,int depth);
    static void BuildFloat(xJSONNode* pNode,string& strData,bool format ,int depth);
    static void BuildBool(xJSONNode* pNode,string& strData,bool format ,int depth);
    static void BuildNull(xJSONNode* pNode,string& strData,bool format ,int depth);
    static void BuildObj(xJSONNode* pNode,string& strData,bool format ,int depth);
    static void BuildArray(xJSONNode* pNode,string& strData,bool format ,int depth);


    static const char* Parse(xJSONNode* pNode,const char* buffer);
    static const char* ParseStr(xJSONNode* pNode,const char* buffer);
    static const char* ParseObj(xJSONNode* pNode,const char* buffer);
    static const char* ParseArray(xJSONNode* pNode,const char* buffer);
    static const char* ParseNull(xJSONNode* pNode,const char* buffer);
    static const char* ParseBool(xJSONNode* pNode,const char* buffer);
    static const char* ParseNum(xJSONNode* pNode,const char* buffer);

    static const char* ParseName(char* name,size_t len,const char* buffer);


    xJSONNode*     m_pRoot;
    bool m_bFailed;
};




//}


#endif // CPPJSON_H
