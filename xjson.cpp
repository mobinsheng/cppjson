/***************************
 * json解析器/生成器
 * 参考了cJSON和jsoncpp的代码
 * 作者：NB_vol_1
 * 可以自由使用和修改
 * **************************/

#include "xjson.h"
#include <string.h>
#include <assert.h>

#define NAME_SIZE (512)

/// 忽略大小写比较字符串
/// \brief strcasecmp
/// \param str1
/// \param str2
/// \return
///
int strcasecmp(const char *str1,const char *str2)
{
    const char* s1 = str1;
    const char* s2 = str2;

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (!s1)
        return (s1==s2)?0:1;

    if (!s2)
        return 1;

    size_t len = len1 > len2?len2:len1;

    for(size_t i = 0; i < len ;++i)
    {
        if(tolower(s1[i]) != tolower(s2[i]))
            return 1;
    }

    return 0;
}

///
/// \brief xJSONValue::xJSONValue
/// \param pBelongto
/// json值对象的构造函数
xJSONValue::xJSONValue(xJSONNode* pBelongto):m_pBelongto(pBelongto)
{
    m_nValue = 0;

    m_fValue = 0;

    m_bValue = false;

}

///
/// \brief xJSONValue::~xJSONValue
///
/// json值对象的析钩函数
xJSONValue::~xJSONValue()
{
	// 什么都没做
    switch (m_pBelongto->m_nType) {
    case xJSON::invalid_type:
        break;
    case xJSON::null_type:
        break;
    case xJSON::string_type:
        break;
    case xJSON::int_type:
        break;
    case xJSON::double_type:
        break;
    case xJSON::bool_type:
        break;
    case xJSON::object_type:

        break;
    case xJSON::array_type:

        break;
    default:
        break;
    }
}

///
/// \brief xJSONValue::toString
/// \return
///
string&                 xJSONValue::toString()
{
    return m_strValue;
}

///
/// \brief xJSONValue::toInt
/// \return
///
int&                        xJSONValue::toInt()
{
    return m_nValue;
}

///
/// \brief xJSONValue::toFloat
/// \return
///
double&                xJSONValue:: toFloat()
{
    return m_fValue;
}

///
/// \brief xJSONValue::toBool
/// \return
///
bool&                       xJSONValue::toBool()
{
    return m_bValue;
}

///
/// \brief xJSONValue::operator =
/// \param v
/// \return
///
xJSONValue& xJSONValue::operator=(const string& v)
{
    m_strValue = v;

    return *this;
}

///
/// \brief xJSONValue::operator =
/// \param v
/// \return
///
xJSONValue& xJSONValue::operator=(const int v)
{
    m_nValue = v;

    return *this;
}

///
/// \brief xJSONValue::operator =
/// \param v
/// \return
///
xJSONValue& xJSONValue::operator=(const double v)
{
    m_fValue = v;

    return *this;
}

///
/// \brief xJSONValue::operator =
/// \param v
/// \return
///
xJSONValue& xJSONValue::operator=(const bool& v)
{
    m_bValue = v;

    return *this;
}

///
/// \brief xJSON::xJSON
///
xJSON::xJSON()
{
    m_pRoot = 0;
}

///
/// \brief xJSON::~xJSON
///
xJSON::~xJSON()
{

    if(m_pRoot == 0)
        return;

    while(m_NodeList.empty() == false)
    {
        ReleaseJSONNode(*m_NodeList.begin());
    }

    m_NodeList.clear();;

    m_pRoot = 0;
}

///
/// \brief xJSONNode::xJSONNode
/// \param pBelongto
///
xJSONNode::xJSONNode(xJSON* pBelongto):m_Value(this),m_pBelongto(pBelongto)
{
    m_nType = xJSON::object_type;
}

///
/// \brief xJSONNode::~xJSONNode
///
xJSONNode::~xJSONNode()
{
    m_ChildList.clear();
}

///
/// \brief xJSONNode::GetChild
/// \return
///
vector<xJSONNode*>& xJSONNode::GetChild()
{
    return m_ChildList;
}

///
/// \brief xJSONNode::GetType
/// \return
///
int xJSONNode::GetType()
{
    return m_nType;
}

///
/// \brief xJSONNode::GetName
/// \return
///
string xJSONNode::GetName()
{
    return m_strName;
}

///
/// \brief xJSONNode::SetName
/// \param name
///
void  xJSONNode::SetName(const string& name)
{
    m_strName = name;
}

///
/// \brief xJSONNode::SetValue
/// \param v
///
void  xJSONNode::SetValue(int v)
{
    m_Value = (int)v;

    m_nType = xJSON::int_type;
}

///
/// \brief xJSONNode::SetValue
/// \param v
///
void  xJSONNode::SetValue(double v)
{
    m_Value = (double)v;

    m_nType = xJSON::double_type;
}

///
/// \brief xJSONNode::SetValueTrue
///
void xJSONNode::SetValueTrue()
{
    m_Value = true;

    m_nType = xJSON::bool_type;
}

///
/// \brief xJSONNode::SetValueFalse
///
void xJSONNode::SetValueFalse()
{
    m_Value = false;

    m_nType = xJSON::bool_type;
}

///
/// \brief xJSONNode::SetValue
/// \param v
///
void  xJSONNode::SetValue(xJSONNode* v)
{
    //m_Value = v;
    m_ChildList.push_back(v);

    m_nType = xJSON::object_type;
}

///
/// \brief xJSONNode::SetValue
/// \param v
///
void  xJSONNode::SetValue(const vector<xJSONNode*>& v)
{

    for(size_t i = 0; i < v.size(); ++i)
    {
        m_ChildList.push_back(v[i]);
    }

    m_nType = xJSON::array_type;
}

///
/// \brief xJSONNode::SetValue
/// \param v
///
void xJSONNode::SetValue(const string &v)
{
    m_Value = v;

    m_nType = xJSON::string_type;
}

///
/// \brief xJSONNode::SetValue
/// \param v
///
void xJSONNode::SetValue(const char* v)
{
    m_Value = string(v);

    m_nType = xJSON::string_type;
}

///
/// \brief xJSONNode::SetValue
///
void xJSONNode::SetValue()
{
    m_nType = xJSON::null_type;
}

///
/// \brief xJSONNode::SetValue
/// \param name
/// \param v
///
void  xJSONNode::SetValue(const string& name,int v)
{
    SetName(name);

    SetValue(v);
}

///
/// \brief xJSONNode::SetValue
/// \param name
/// \param v
///
void  xJSONNode::SetValue(const string& name,double v)
{
    SetName(name);

    SetValue(v);
}

///
/// \brief xJSONNode::SetValueTrue
/// \param name
///
void  xJSONNode::SetValueTrue(const string& name)
{
    SetName(name);

    SetValueTrue();
}

///
/// \brief xJSONNode::SetValueFalse
/// \param name
///
void  xJSONNode::SetValueFalse(const string& name)
{
    SetName(name);

    SetValueFalse();
}

///
/// \brief xJSONNode::SetValue
/// \param name
/// \param v
///
void  xJSONNode::SetValue(const string& name,xJSONNode* v)
{
    SetName(name);

    SetValue(v);
}

///
/// \brief xJSONNode::SetValue
/// \param name
/// \param v
///
void  xJSONNode::SetValue(const string& name,const vector<xJSONNode*>& v)
{
    SetName(name);

    SetValue(v);
}

///
/// \brief xJSONNode::GetValue
/// \return
///
xJSONValue& xJSONNode::GetValue()
{
    return m_Value;
}

///
/// \brief xJSONNode::operator []
/// \param key
/// \return
///
xJSONNode& xJSONNode::operator[](const string& key)
{
    for(size_t i = 0 ; i < m_ChildList.size(); ++i)
    {
        xJSONNode* node = m_ChildList[i];

        if(node == 0)
            continue;

        if(node->GetName() == key)
        {
            return *node;
        }
    }

    xJSONNode* node = m_pBelongto->CreateJSONNode();

    node->m_nType = xJSON::object_type;

    node->SetName(key);

    m_ChildList.push_back(node);

    return *node;
}

///
/// \brief xJSONNode::operator =
/// \param v
/// \return
///
xJSONNode& xJSONNode::operator=(const string& v)
{
    m_Value = v;

    m_nType = xJSON::string_type;

    return *this;
}

///
/// \brief xJSONNode::operator =
/// \param v
/// \return
///
xJSONNode& xJSONNode::operator=(const char* v)
{
    m_Value = string(v);

    m_nType = xJSON::string_type;

    return *this;
}

///
/// \brief xJSONNode::operator =
/// \param v
/// \return
///
xJSONNode& xJSONNode::operator=(double v)
{
    m_Value = v;

    m_nType = xJSON::bool_type;

    return *this;
}

///
/// \brief xJSONNode::operator =
/// \param v
/// \return
///
xJSONNode& xJSONNode::operator=(int v)
{
    m_Value = v;

    m_nType = xJSON::int_type;

    return *this;
}

///
/// \brief xJSONNode::operator =
/// \param v
/// \return
///
xJSONNode& xJSONNode::operator=(xJSONNode* v)
{
    if(v == 0)
        return *this;

    m_ChildList.insert(m_ChildList.end(),v->m_ChildList.begin(),v->m_ChildList.end());

    m_nType = xJSON::object_type;

    return *this;
}

///
/// \brief xJSONNode::operator =
/// \param v
/// \return
///
xJSONNode& xJSONNode::operator=(const bool& v)
{
    m_Value = v;

    m_nType = xJSON::bool_type;

    return *this;
}

///
/// \brief xJSONNode::operator =
/// \param v
/// \return
///
xJSONNode& xJSONNode::operator=(const vector<xJSONNode*>& v)
{
    for(size_t i = 0; i < v.size(); ++i)
    {
        m_ChildList.push_back(v[i]);
    }

    m_nType = xJSON::array_type;

    return *this;
}

///
/// \brief xJSONNode::toString
/// \return
///
string&                                 xJSONNode::toString()
{
    return m_Value.toString();
}

///
/// \brief xJSONNode::toInt
/// \return
///
int&                                      xJSONNode::toInt()
{
    return m_Value.toInt();
}

///
/// \brief xJSONNode::toFloat
/// \return
///
double&                              xJSONNode::toFloat()
{
    return m_Value.toFloat();
}

///
/// \brief xJSONNode::toBool
/// \return
///
bool&                                  xJSONNode::toBool()
{
    return m_Value.toBool();
}

///
/// \brief xJSONNode::toObject
/// \return
///
xJSONNode*                      xJSONNode::toObject()
{
    return this;
}

///
/// \brief xJSONNode::toArray
/// \return
///
vector<xJSONNode*>&     xJSONNode::toArray()
{
    return m_ChildList;
}

///
/// \brief xJSONNode::AddChild
/// \param name
/// \param value
///
void xJSONNode::AddChild(const string &name, int value)
{
    xJSONNode* node = m_pBelongto->CreateJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::int_type;
    node->m_Value = value;

    m_ChildList.push_back(node);
}

///
/// \brief xJSONNode::AddChild
/// \param name
/// \param value
///
void xJSONNode::AddChild(const string& name,double value)
{
    xJSONNode* node = m_pBelongto->CreateJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::double_type;
    node->m_Value = value;

    m_ChildList.push_back(node);
}

///
/// \brief xJSONNode::AddChild
/// \param name
/// \param value
///
void xJSONNode::AddChild(const string& name,bool value)
{
    xJSONNode* node = m_pBelongto->CreateJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::bool_type;
    node->m_Value = value;

    m_ChildList.push_back(node);
}

///
/// \brief xJSONNode::AddChild
/// \param name
/// \param value
///
void xJSONNode::AddChild(const string& name,const string& value)
{

    xJSONNode* node = m_pBelongto->CreateJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::string_type;
    node->m_Value = value;

    m_ChildList.push_back(node);

}

///
/// \brief xJSONNode::AddChild
/// \param name
/// \param value
///
void xJSONNode::AddChild(const string& name,const char* value)
{

    xJSONNode* node = m_pBelongto->CreateJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::string_type;
    node->m_Value = string(value);

    m_ChildList.push_back(node);

}

///
/// \brief xJSONNode::AddChild
/// \param name
/// \param value
///
void xJSONNode::AddChild(const string &name,  xJSONNode *value)
{


    xJSONNode* node = (xJSONNode*)value;
    node->SetName(name);
    node->m_nType = xJSON::object_type;
    m_ChildList.push_back(node);
}

///
/// \brief xJSONNode::AddChild
/// \param value
///
void xJSONNode::AddChild(xJSONNode *value)
{


    xJSONNode* node = (xJSONNode*)value;
    node->SetName(value->GetName());
    node->m_nType = xJSON::object_type;
    m_ChildList.push_back(node);
}

///
/// \brief xJSONNode::AddChild
/// \param name
/// \param value
///
void xJSONNode::AddChild(const string& name,const vector<xJSONNode*> value)
{

    xJSONNode* node = m_pBelongto->CreateJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::array_type;
    node->SetValue(value);

    m_ChildList.push_back(node);
}

///
/// \brief xJSONNode::AddChild
/// \param name
///
void xJSONNode::AddChild(const string &name)
{
    xJSONNode* node = m_pBelongto->CreateJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::null_type;

    m_ChildList.push_back(node);
}

///
/// \brief xJSON::Open
/// \param fileName
/// \return
///
bool xJSON::Open(const char* fileName)
{
    if(fileName == 0)
        return false;

    FILE* input = fopen(fileName,"r");
    if(input == 0)
        return false;

    fseek(input,0,SEEK_END);//SEEK_SET
    size_t len = ftell(input);
    fseek(input,0,SEEK_SET);

    char* buffer = new char[len + 1];
    buffer[len] = 0;

    fread(buffer,1,len,input);

    fclose(input);

    return Read(buffer);

}

///
/// \brief skip
/// \param in
/// \return
///
static const char *skip(const char *in)
{
    while (in && *in && (unsigned char)*in<=32)
        in++;

    return in;
}

///
/// \brief xJSON::Read
/// \param buffer
/// \return
///
bool xJSON::Read(const char* buffer)
{
    buffer = skip(buffer);
    if(buffer == 0)
    {
        return false;
    }

    m_pRoot = CreateJSONNode();

    Parse(m_pRoot,buffer);

    return m_pRoot;
}

///
/// \brief xJSON::ParseName
/// \param name
/// \param len
/// \param buffer
/// \return
///
const char* xJSON::ParseName(char *name, size_t len,const char *buffer)
{
    const char* p = buffer;

    memset(name,0,len);

    p = skip(p);

    if(p == 0 || *p != '\"')
        return buffer;


    int name_len = 0;

    ++p;

    const char* begin = p;


    while(p != 0 && *p != '\"')
    {
        ++name_len;
        ++p;
    }

    if(p == 0 || *p != '\"')
        return buffer;

    strncpy(name,begin,name_len);
    ++p;

    return p;
}

///
/// \brief xJSON::Parse
/// \param pNode
/// \param buffer
/// \return
///
const char* xJSON::Parse(xJSONNode* pNode,const char* buffer)
{
    buffer = skip(buffer);

    if(0 == buffer)
        return 0;

    int x= strcasecmp("null",buffer);
    if(*buffer == '\"')
    {
        pNode->m_nType = string_type;
        buffer = ParseStr(pNode,buffer);
    }
    else if(*buffer == '{')
    {
        pNode->m_nType = object_type;
        buffer = ParseObj(pNode,buffer);
    }
    else if(*buffer == '[')
    {
        pNode->m_nType = array_type;
        buffer = ParseArray(pNode,buffer);
    }
    else if(*buffer == '-' || (*buffer>='0' && *buffer <= '9'))
    {
        pNode->m_nType = int_type;
        buffer = ParseNum(pNode,buffer);
    }
    else if(strlen(buffer) >= 4 && strcasecmp("null",buffer) == 0)
    {
        pNode->m_nType = null_type;
        buffer = ParseNull(pNode,buffer);
    }
    else  if(strlen(buffer) >= 4 && strcasecmp("true",buffer) == 0)
    {
        pNode->m_nType = bool_type;
        buffer = ParseBool(pNode,buffer);
    }
    else  if(strlen(buffer) >= 5 && strcasecmp("false",buffer) == 0)
    {
        pNode->m_nType = bool_type;
        buffer = ParseBool(pNode,buffer);
    }
    else
    {
        return 0;
    }


}

///
/// \brief xJSON::ParseStr
/// \param pNode
/// \param buffer
/// \return
///
const char* xJSON::ParseStr(xJSONNode* pNode,const char* buffer)
{
    if(buffer == 0)
        return 0;

    buffer = skip(buffer);

    if(buffer == 0)
        return 0;

    if(*buffer != '\"')
        return 0;

    char value[NAME_SIZE] = {0};

    buffer = ParseName(value,NAME_SIZE,buffer);

    if(buffer == 0)
        return 0;

    buffer = skip(buffer);

    pNode->SetValue(value);

    return buffer;
}

///
/// \brief xJSON::ParseObj
/// \param pNode
/// \param buffer
/// \return
///
const char* xJSON::ParseObj(xJSONNode* pNode,const char* buffer)
{
    if(buffer == 0)
        return 0;

    if(*buffer != '{')
        return 0;

    buffer++;

    buffer = skip(buffer);

    if(buffer == 0)
    {
        return 0;
    }



    char name[NAME_SIZE] = {0};

    const char*p = ParseName(name,NAME_SIZE,buffer);

    if(p != buffer)
    {
        buffer =p;
        buffer = skip(buffer);

        if(buffer == 0)
            return 0;

        if(*buffer != ':')
            return 0;

        ++buffer;

        xJSONNode* node = CreateJSONNode();

        node->SetName(name);

        buffer = Parse(node,buffer);

        if(buffer == 0)
        {
            ReleaseJSONNode(node);
            return 0;
        }

        pNode->m_ChildList.push_back(node);

        buffer = skip(buffer);

        if(*buffer == '}')
        {
            ++buffer;
            return buffer;
        }
    }
    else
    {
        buffer = p;

        buffer = skip(buffer);

        buffer = skip(buffer);

        if(*buffer == '}')
        {
            xJSONNode* node = CreateJSONNode();
            pNode->SetValue(node);
            ++buffer;
            return buffer;
        }
        else
        {
            return 0;
        }
    }

    while(*buffer == ',')
    {
        buffer++;
        buffer = ParseName(name,NAME_SIZE,buffer);
        if(buffer == 0)
            return 0;

        buffer = skip(buffer);

        if(buffer == 0 || *buffer != ':')
            return 0;

        buffer++;

        buffer = skip(buffer);

        xJSONNode* child = CreateJSONNode();
        child->SetName(name);
        buffer = Parse(child,buffer);

        if(buffer == 0)
        {
            ReleaseJSONNode(child);
            return 0;
        }

        buffer = skip(buffer);

        if(buffer == 0)
        {
            ReleaseJSONNode(child);
            return 0;
        }

        pNode->m_ChildList.push_back(child);
    }

    buffer = skip(buffer);

    if(buffer == 0 || *buffer != '}')
        return 0;

    buffer++;
    buffer = skip(buffer);
    return buffer;
}

///
/// \brief xJSON::ParseArray
/// \param pNode
/// \param buffer
/// \return
///
const char* xJSON::ParseArray(xJSONNode* pNode,const char* buffer)
{
    if(buffer == 0)
        return 0;

    buffer = skip(buffer);

    if(buffer == 0)
        return 0;

    if(*buffer != '[')
        return 0;

    ++buffer;

    buffer = skip(buffer);

    xJSONNode* node = CreateJSONNode();

    buffer = Parse(node,buffer);

    if(buffer == 0)
    {
        ReleaseJSONNode(node);
        return 0;
    }

    buffer = skip(buffer);

    if(buffer == 0)
    {
        ReleaseJSONNode(node);
        return 0;
    }

    if(*buffer == ']')
    {
        pNode->m_ChildList.push_back(node);
        ++buffer;
        return buffer;
    }

    buffer = skip(buffer);

    if(buffer == 0 || *buffer != ',')
    {
        ReleaseJSONNode(node);
        return 0;
    }

    pNode->m_ChildList.push_back(node);

    while(buffer != 0 && *buffer == ',')
    {
        buffer++;
        buffer = skip(buffer);
        if(buffer == 0)
            return 0;
        node = CreateJSONNode();
        buffer = Parse(node,buffer);
        if(0 == buffer)
            return 0;
        pNode->m_ChildList.push_back(node);
        buffer = skip(buffer);
    }

    if(buffer == 0)
    {
        return 0;
    }

    if(*buffer != ']')
        return 0;

    buffer++;
    return buffer;
}

///
/// \brief xJSON::ParseNull
/// \param pNode
/// \param buffer
/// \return
///
const char* xJSON::ParseNull(xJSONNode* pNode,const char* buffer)
{
    buffer = skip(buffer);
    if(buffer == 0)
        return 0;

    if(strlen(buffer) < 4)
        return 0;

    if(strcasecmp("null",buffer) == 0)
    {
        pNode->m_nType = null_type;
    }
    else
    {
        return 0;

    }

    buffer += 4;
    return buffer;
}

///
/// \brief xJSON::ParseBool
/// \param pNode
/// \param buffer
/// \return
///
const char* xJSON::ParseBool(xJSONNode* pNode,const char* buffer)
{
    buffer = skip(buffer);
    if(buffer == 0)
        return 0;

    if(strlen(buffer) < 4)
        return 0;

    if(strcasecmp("true",buffer) == 0)
    {
        pNode->SetValueTrue();
        buffer += 4;
    }
    else
    {
        if(strlen(buffer) < 5)
        {
            return 0;
        }

        if(strcasecmp("false",buffer) == 0)
        {
            pNode->SetValueFalse();
            buffer += 5;
        }
        else
        {
            return 0;
        }
    }

    return buffer;
}

///
/// \brief xJSON::ParseNum
/// \param pNode
/// \param buffer
/// \return
///
const char* xJSON::ParseNum(xJSONNode* pNode,const char* buffer)
{
    buffer = skip(buffer);
    if(buffer == 0)
        return 0;

    bool negative = false;

    if(*buffer == '-')
    {
        negative =true;
        buffer++;
    }

    while(buffer != 0 && *buffer == '0')
    {
        ++buffer;
    }

    if(buffer == 0)
        return 0;

    const char* begin = buffer;
    char num[512];
    memset(num,0,512);

    size_t len = 0;
    while ((*buffer >= '0') && (*buffer <= '9'))
    {
        num[len] = *buffer;
        ++buffer;
        ++len;
    }

    if(*buffer>32 && *buffer != '.' && *buffer != ',' && *buffer != ']' && *buffer != '}')
        return 0;

    if(*buffer == '.')
    {
        num[len] = *buffer;
        ++buffer;
        ++len;
        while ((*buffer >= '0') && (*buffer <= '9'))
        {
            num[len] = *buffer;
            ++buffer;
            ++len;
        }

        pNode->SetValue(atof(num));
    }
    else
    {
        pNode->SetValue(atoi(num));
    }

    return buffer;
}

///
/// \brief xJSON::Write
/// \param strData
/// \param format
///
void  xJSON::Write(string& strData,bool format)
{
    if(m_pRoot == 0)
        m_pRoot = CreateJSONNode();

    return Build(m_pRoot,strData,format,0);
}

///
/// \brief xJSON::Build
/// \param pNode
/// \param strData
/// \param format
/// \param depth
///
void xJSON::Build(xJSONNode *pNode, string &strData, bool format, int depth)
{
    if(pNode == NULL)
    {
        return ;
    }


    switch (pNode->m_nType) {
    case invalid_type:
        break;
    case null_type:
        BuildNull(pNode,strData,format,depth);
        break;
    case string_type:
        BuildStr(pNode,strData,format,depth);
        break;
    case int_type:
        BuildInt(pNode,strData,format,depth);
        break;
    case double_type:
        BuildFloat(pNode,strData,format,depth);
        break;
    case bool_type:
        BuildBool(pNode,strData,format,depth);
        break;
    case object_type:
        BuildObj(pNode,strData,format,depth);

        break;
    case array_type:
        BuildArray(pNode,strData,format,depth);
        break;
    default:
        break;
    }

}

///
/// \brief xJSON::BuildStr
/// \param pNode
/// \param strData
/// \param format
/// \param depth
///
void xJSON::BuildStr(xJSONNode* pNode,string& strData,bool format ,int depth)
{
    strData += "\"";
    strData += pNode->GetValue().toString();
    strData += "\"";

}

///
/// \brief xJSON::BuildInt
/// \param pNode
/// \param strData
/// \param format
/// \param depth
///
void xJSON::BuildInt(xJSONNode* pNode,string& strData,bool format ,int depth)
{

    char buff[64] = {0};
    sprintf(buff,"%d",pNode->GetValue().toInt());
    strData += (char*)buff;



}

///
/// \brief xJSON::BuildFloat
/// \param pNode
/// \param strData
/// \param format
/// \param depth
///
void xJSON::BuildFloat(xJSONNode* pNode,string& strData,bool format ,int depth)
{
    char buff[64] = {0};
    sprintf(buff,"%f",pNode->GetValue().toFloat());
    strData += (char*)buff;

}

///
/// \brief xJSON::BuildBool
/// \param pNode
/// \param strData
/// \param format
/// \param depth
///
void xJSON::BuildBool(xJSONNode* pNode,string& strData,bool format ,int depth)
{
    string str = "true";
    if(pNode->GetValue().toBool() == false)
        str = "false";

    strData += str;

}

///
/// \brief xJSON::BuildNull
/// \param pNode
/// \param strData
/// \param format
/// \param depth
///
void xJSON::BuildNull(xJSONNode* pNode,string& strData,bool format ,int depth)
{
    strData += "null";

}

///
/// \brief xJSON::BuildObj
/// \param pNode
/// \param strData
/// \param format
/// \param depth
///
void xJSON::BuildObj(xJSONNode* pNode,string& strData,bool format ,int depth)
{

    if(pNode == 0)
        return ;

    if(format)
    {
        if(depth != 0)
            strData += "\n";

        for(int i = 0 ; i < depth ; ++ i)
        {
            strData += "\t";
        }
        strData += "{";

    }


    if(format)
    {
        strData += "\n";
    }


    for(int j = 0; j < pNode->GetChild().size(); ++j)
    {
        if(pNode->GetChild()[j] == 0)
            continue;

        xJSONNode* pChildNode = pNode->GetChild()[j];

        if(format)
        {
            for(int i =0 ;i < depth + 1; ++i)
            {
                strData += "\t";
            }
        }

        strData += "\"";
        strData += pChildNode->GetName();
        strData += "\"";
        strData += ":";

        Build(pChildNode,strData,format,depth+1);

        if(j != pNode->GetChild().size() - 1)
        {
            strData += ",";
        }

        if(format)
        {
            strData += "\n";
        }
    }

    if(format)
    {
        for(int i =0 ;i < depth ; ++i)
        {
            strData += "\t";
        }
    }
    strData += "}";
}

///
/// \brief xJSON::BuildArray
/// \param pNode
/// \param strData
/// \param format
/// \param depth
///
void xJSON::BuildArray(xJSONNode* pNode,string& strData,bool format ,int depth)
{

    if(format)
    {
        if(depth != 0)
            strData += "\n";

        for(int i = 0 ; i < depth ; ++ i)
        {
            strData += "\t";
        }
        strData += "[";

    }

    //strData += "[";
    if(format)
    {
        strData += "\n";
    }
    for(int j = 0; j < pNode->m_ChildList.size(); ++j)
    {
        if(pNode->m_ChildList[j] == 0)
            continue;

        xJSONNode* pChildNode = pNode->m_ChildList[j];

        if(format)
        {
            for(int i = 0; i < depth + 1; ++i)
            {
                strData += "\t";
            }
        }

        Build(pChildNode,strData,format,depth+1);


        if(j != pNode->m_ChildList.size() - 1)
        {
            strData += ",";
        }

        if(format)
        {
            strData += "\n";
        }


    }

    if(format)
    {
        for(int i =0 ;i < depth ; ++i)
        {
            strData += "\t";
        }
    }

    strData += "]";
}

///
/// \brief xJSON::WiteFile
/// \param fileName
/// \param format
///
void xJSON::WiteFile(const string& fileName,bool format)
{
    FILE* out = fopen(fileName.c_str(),"w");

    if(out == 0)
    {
        return ;
    }

    string strData;

    Write(strData);

    fwrite(strData.c_str(),1,strData.size(),out);

    fflush(out);

    fclose(out);

}

///
/// \brief xJSON::CreateJSONNode
/// \return
///
xJSONNode* xJSON::CreateJSONNode()
{
    xJSONNode* node = new xJSONNode(this);

    m_NodeList.insert(node);

    return node;
}

///
/// \brief xJSON::ReleaseJSONNode
/// \param node
///
void xJSON::ReleaseJSONNode(xJSONNode *node)
{
    set<xJSONNode*>::iterator it;

    it = m_NodeList.find(node);

    if(it == m_NodeList.end())
        return;

    m_NodeList.erase(it);

    delete node;

}

///
/// \brief xJSON::PrintJSON
/// \param node
///
void xJSON::PrintJSON(xJSONNode *node)
{
    string strData;

    Build(node,strData,true,0);

    cout << strData << endl;
}

///
/// \brief xJSON::PrintJSON
///
void xJSON::PrintJSON()
{
    string strData;

    Build(GetRoot(),strData,true,0);

    cout << strData << endl;
}

///
/// \brief xJSON::operator []
/// \param key
/// \return
///
xJSONNode& xJSON::operator[](const string& key)
{
    if(m_pRoot == 0)
        m_pRoot = CreateJSONNode();

    return (*m_pRoot)[key];
}

///
/// \brief xJSON::GetRoot
/// \return
///
xJSONNode* xJSON::GetRoot()
{
    return m_pRoot;
}

