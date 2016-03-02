/***************************
 * json解析器/生成器
 * 参考了cJSON和jsoncpp的代码
 * 基本的功能都有了
 * 我不想把它写的太复杂
 * 作者：NB_vol_1
 * 可以自由使用和修改
 * **************************/

#ifndef CPPJSON_H
#define CPPJSON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <set>

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

using namespace std;

//

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


    xJSONValue& operator=(const string& v);
    xJSONValue& operator=(const int v);
    xJSONValue& operator=(const double v);
    xJSONValue& operator=(const bool& v);


private:

    // 各种值
    string                                   m_strValue;
    int                                         m_nValue;
    double                                  m_fValue;
    bool                                      m_bValue;

    // 所属的json节点
    xJSONNode*                      m_pBelongto;
};

// json中的每一个键值对或者，数组中的每一个元素都是节点
// 节点可以有名字（键值对），也可以没有名字（例如数组中的元素）
class xJSONNode
{
public:

    xJSONNode(xJSON* pBelongto);
    ~xJSONNode();

    friend class xJSONValue;
    friend class xJSON;

    void SetName(const string& name);

    // 赋值
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

    // 下标操作符号（对对象、数组有效）
    xJSONNode& operator[](const string& key);

    // 赋值重载,下面的五个函数实际改变的是节点本身的值
    xJSONNode& operator=(const string& v);
    xJSONNode& operator=(const char* v);
    xJSONNode& operator=(double v);
    xJSONNode& operator=(int v);
    xJSONNode& operator=(const bool& v);

    // 复制重载，下面两个函数实际改变的（修改的）是节点的子节点
    xJSONNode& operator=(xJSONNode* v);
    xJSONNode& operator=(const vector<xJSONNode*>& v);

    // 取值
    string&                                 toString();
    int&                                      toInt();
    double&                              toFloat();
    bool&                                  toBool();
    xJSONNode*                      toObject();
    vector<xJSONNode*>&     toArray();


    xJSONValue&                     GetValue();


    vector<xJSONNode*>&    GetChild();

    int                                       GetType();

    string                                  GetName();


    // 添加孩子
    void AddChild(const string& name,int value);
    void AddChild(const string& name,double value);
    void AddChild(const string& name,bool value);
    void AddChild(const string& name,const string& value);
    void AddChild(const string& name,const char* value);
    void AddChild(const string& name, xJSONNode* value);
    void AddChild(xJSONNode* value);
    void AddChild(const string& name,const vector<xJSONNode*> value);
    void AddChild(const string& name);
private:

    xJSONNode(const xJSONNode & rect);

    //赋值操作符
    xJSONNode& operator=(const xJSONNode &rect);

    // 节点的类型
    int                         m_nType;

    // 节点的名字（可以为空）
    string                   m_strName;

    // 节点的值
    xJSONValue          m_Value;

    // 节点的孩子（对于对象、数组有效）
    vector<xJSONNode*> m_ChildList;

    // 所属的json对象
    xJSON*              m_pBelongto;
};

// json对象
class xJSON
{
public:
    friend class xJSON;

    // 打开一个json文件，解析为json数据
    bool Open(const char* fileName);

    // 读取一个字符串，解析为json数据
    bool Read(const char* buffer);

    // 把json对象的数据写入字符串中
    void  Write(string& strData,bool format = true);

    // 把json对象的数据写入文件中
    void WiteFile(const string& fileName,bool format = true);

    // 创建一个json节点
    // 分配json节点都需要调用这个函数，目的是为了方便管理内存，用户只需要调用这个函数
    // 无需自己释放内存，内存的释放统一由xJSON来进行
    xJSONNode* CreateJSONNode();

    // 输出到屏幕上
    void PrintJSON(xJSONNode* node);

    void PrintJSON();

    // json节点的类型
    enum NodeType
    {
        // 无效类型
        invalid_type,
        // 空类型
        null_type,
        // 字符串类型
        string_type,
        // 整形
        int_type,
        // 浮点型
        double_type,
        // 布尔类型
        bool_type,
        // 对象类型
        object_type,
        // 数组类型
        array_type,
    };

    ~xJSON();

    // 下标操作符号，可以使用字符串作为下标来访问数据
    xJSONNode& operator[](const string& key);

    // 获取根节点
    xJSONNode* GetRoot();

    xJSON();

private:

    // 释放一个节点的内存
    void ReleaseJSONNode(xJSONNode* node);

    xJSON(const xJSON & rect);

    // 赋值操作符
    xJSON& operator=(const xJSON &rect);

    // 把json对象的所有节点格式化为字符串
    void Build(xJSONNode* pNode,string& strData,bool format ,int depth);
    void BuildStr(xJSONNode* pNode,string& strData,bool format ,int depth);
    void BuildInt(xJSONNode* pNode,string& strData,bool format ,int depth);
    void BuildFloat(xJSONNode* pNode,string& strData,bool format ,int depth);
    void BuildBool(xJSONNode* pNode,string& strData,bool format ,int depth);
    void BuildNull(xJSONNode* pNode,string& strData,bool format ,int depth);
    void BuildObj(xJSONNode* pNode,string& strData,bool format ,int depth);
    void BuildArray(xJSONNode* pNode,string& strData,bool format ,int depth);

    // 把字符串解析为json节点
    const char* Parse(xJSONNode* pNode,const char* buffer);
    const char* ParseStr(xJSONNode* pNode,const char* buffer);
    const char* ParseObj(xJSONNode* pNode,const char* buffer);
    const char* ParseArray(xJSONNode* pNode,const char* buffer);
    const char* ParseNull(xJSONNode* pNode,const char* buffer);
    const char* ParseBool(xJSONNode* pNode,const char* buffer);
    const char* ParseNum(xJSONNode* pNode,const char* buffer);
    const char* ParseName(char* name,size_t len,const char* buffer);

    // 根节点
    xJSONNode*     m_pRoot;

    // 节点列表
    set<xJSONNode*> m_NodeList;
};





#endif // CPPJSON_H
