#include "xjson.h"
#include <string.h>
#include <assert.h>

#define NAME_SIZE (512)
/*
 int strcasecmp(const char *str1,const char *str2)
{
     const char* s1 = str1;
     const char* s2 = str2;
    if (!s1)
        return (s1==s2)?0:1;

    if (!s2)
        return 1;

    for(; tolower(*s1) == tolower(*s2) && s1 != 0 && s2 != 0; ++s1, ++s2)
        if(*s1 == 0 || *s2 == 0)
            return 0;

    if(s1 == 0 || s2 == 0)
        return 0;

    return 1;

    return tolower(*(const unsigned char *)s1) - tolower(*(const unsigned char *)s2);
}
*/
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

 xJSONValue::xJSONValue(xJSONNode* pBelongto):m_pBelongto(pBelongto)
 {


     m_nValue = 0;
     m_fValue = 0;
     m_bValue = false;

 }

 xJSONValue::~xJSONValue(){
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

 string&                 xJSONValue::toString()
 {
     return m_strValue;
 }

 int&                        xJSONValue::toInt()
 {
     return m_nValue;
 }

 double&                xJSONValue:: toFloat()
 {
     return m_fValue;
 }

 bool&                       xJSONValue::toBool()
 {
     return m_bValue;
 }



 xJSONValue& xJSONValue::operator=(const string& v)
 {
     m_strValue = v;
     return *this;
 }

 xJSONValue& xJSONValue::operator=(const int v)
 {
     m_nValue = v;
     return *this;
 }

 xJSONValue& xJSONValue::operator=(const double v)
 {
     m_fValue = v;
     return *this;
 }

 xJSONValue& xJSONValue::operator=(const bool& v)
 {
     m_bValue = v;
     return *this;
 }



xJSON::xJSON()
{
    m_pRoot = 0;
    m_bFailed= true;
}


xJSON::~xJSON()
{
    if(m_pRoot == 0)
        return;

    delete m_pRoot;
    m_pRoot = 0;
}

xJSONNode::xJSONNode():m_Value(this)
{
    m_nType = xJSON::object_type;
}

xJSONNode::~xJSONNode()
{
    /**/

    // 删除孩子们的数据

    for(int i = 0; i < m_ChildList.size(); ++i)
    {
        if(m_ChildList[i] != 0)
        {
            delete m_ChildList[i];
        }
    }

    m_ChildList.clear();
}

vector<xJSONNode*>& xJSONNode::GetChild()
{
    return m_ChildList;
}

int xJSONNode::GetType()
{
    return m_nType;
}

string xJSONNode::GetName()
{
    return m_strName;
}

void  xJSONNode::SetName(const string& name)
{
    m_strName = name;
}

void  xJSONNode::SetValue(int v)
{
    m_Value = (int)v;
    m_nType = xJSON::int_type;
}

void  xJSONNode::SetValue(double v)
{
    m_Value = (double)v;
    m_nType = xJSON::double_type;
}



void xJSONNode::SetValueTrue()
{
    m_Value = true;
    m_nType = xJSON::bool_type;
}

void xJSONNode::SetValueFalse()
{
    m_Value = false;
    m_nType = xJSON::bool_type;
}

void  xJSONNode::SetValue(xJSONNode* v)
{
    //m_Value = v;
    m_ChildList.push_back(v);
    m_nType = xJSON::object_type;
}

void  xJSONNode::SetValue(const vector<xJSONNode*>& v)
{

    for(size_t i = 0; i < v.size(); ++i)
    {
        m_ChildList.push_back(v[i]);
    }
    m_nType = xJSON::array_type;
}

void xJSONNode::SetValue(const string &v)
{
    m_Value = v;
    m_nType = xJSON::string_type;
}

void xJSONNode::SetValue(const char* v)
{
    m_Value = string(v);
    m_nType = xJSON::string_type;
}

void xJSONNode::SetValue()
{
    m_nType = xJSON::null_type;
}

void  xJSONNode::SetValue(const string& name,int v)
{
    SetName(name);
    SetValue(v);
}

void  xJSONNode::SetValue(const string& name,double v)
{
    SetName(name);
    SetValue(v);
}


void  xJSONNode::SetValueTrue(const string& name)
{
    SetName(name);
    SetValueTrue();
}

void  xJSONNode::SetValueFalse(const string& name)
{
    SetName(name);
    SetValueFalse();
}

void  xJSONNode::SetValue(const string& name,xJSONNode* v)
{
    SetName(name);
    SetValue(v);
}

void  xJSONNode::SetValue(const string& name,const vector<xJSONNode*>& v)
{
    SetName(name);
    SetValue(v);
}



xJSONValue& xJSONNode::GetValue()
{
    return m_Value;
}

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
    xJSONNode* node = new xJSONNode;
    node->m_nType = xJSON::object_type;
    node->SetName(key);
    m_ChildList.push_back(node);
    return *node;
}

xJSONNode& xJSONNode::operator=(const string& v)
{
    m_Value = v;
    m_nType = xJSON::string_type;
    return *this;
}

xJSONNode& xJSONNode::operator=(const char* v)
{
    m_Value = string(v);
    m_nType = xJSON::string_type;
    return *this;
}

xJSONNode& xJSONNode::operator=(double v)
{
    m_Value = v;
    m_nType = xJSON::bool_type;
    return *this;
}

xJSONNode& xJSONNode::operator=(int v)
{
    m_Value = v;
    m_nType = xJSON::int_type;
    return *this;
}

xJSONNode& xJSONNode::operator=(xJSONNode* v)
{
    if(v == 0)
        return *this;

    m_ChildList.insert(m_ChildList.end(),v->m_ChildList.begin(),v->m_ChildList.end());

    m_nType = xJSON::object_type;
    return *this;
}

xJSONNode& xJSONNode::operator=(const bool& v)
{
    m_Value = v;
    m_nType = xJSON::bool_type;
    return *this;
}

xJSONNode& xJSONNode::operator=(const vector<xJSONNode*>& v)
{
    for(size_t i = 0; i < v.size(); ++i)
    {
        m_ChildList.push_back(v[i]);
    }
    m_nType = xJSON::array_type;
    return *this;
}

string&                                 xJSONNode::toString()
{
    return m_Value.toString();
}

int&                                      xJSONNode::toInt()
{
    return m_Value.toInt();
}

double&                              xJSONNode::toFloat()
{
    return m_Value.toFloat();
}

bool&                                  xJSONNode::toBool()
{
    return m_Value.toBool();
}
/*
vector<xJSONNode*>&    xJSONNode:: toArray()
{
    return m_Value.toArray();
}

xJSONNode*                      xJSONNode::toObject()
{
    return m_Value.toObject();
}*/

void xJSONNode::AddChild(const string &name, int value)
{
    xJSONNode* node = new xJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::int_type;
    node->m_Value = value;

    m_ChildList.push_back(node);
}

void xJSONNode::AddChild(const string& name,double value)
{
    xJSONNode* node = new xJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::double_type;
    node->m_Value = value;

    m_ChildList.push_back(node);
}

void xJSONNode::AddChild(const string& name,bool value)
{
    xJSONNode* node = new xJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::bool_type;
    node->m_Value = value;

    m_ChildList.push_back(node);
}

void xJSONNode::AddChild(const string& name,const string& value)
{

    xJSONNode* node = new xJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::string_type;
    node->m_Value = value;

    m_ChildList.push_back(node);

}

void xJSONNode::AddChild(const string& name,const char* value)
{

    xJSONNode* node = new xJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::string_type;
    node->m_Value = string(value);

    m_ChildList.push_back(node);

}



void xJSONNode::AddChild(const string &name,  xJSONNode *value)
{


    xJSONNode* node = (xJSONNode*)value;
    node->SetName(name);
    node->m_nType = xJSON::object_type;
    m_ChildList.push_back(node);
}

void xJSONNode::AddChild(xJSONNode *value)
{


    xJSONNode* node = (xJSONNode*)value;
    node->SetName(value->GetName());
    node->m_nType = xJSON::object_type;
    m_ChildList.push_back(node);
}

void xJSONNode::AddChild(const string& name,const vector<xJSONNode*> value)
{

    xJSONNode* node = new xJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::array_type;
    node->SetValue(value);

    m_ChildList.push_back(node);
}

void xJSONNode::AddChild(const string &name)
{
    xJSONNode* node = new xJSONNode();
    node->m_strName = name;
    node->m_nType = xJSON::null_type;

    m_ChildList.push_back(node);
}

///////////////////////////////////////////
/// \brief xJSON::Open
/// \param fileName
/// \return
///
#include <stdio.h>
#include <stdlib.h>
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

    return Read(buffer);

}

bool xJSON::Failed()
{
    return m_bFailed;
}

static const char *skip(const char *in)
{
    while (in && *in && (unsigned char)*in<=32)
        in++;

    return in;
}

bool xJSON::Read(const char* buffer)
{
    buffer = skip(buffer);
    if(buffer == 0)
    {
        return false;
    }

    m_pRoot = new xJSONNode;

    Parse(m_pRoot,buffer);

    return m_pRoot;
}


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

        xJSONNode* node = new xJSONNode;

        node->SetName(name);

        buffer = Parse(node,buffer);

        if(buffer == 0)
        {
            delete node;
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
            xJSONNode* node = new xJSONNode;
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

        xJSONNode* child = new xJSONNode;
        child->SetName(name);
        buffer = Parse(child,buffer);

        if(buffer == 0)
        {
            delete child;
            return 0;
        }

        buffer = skip(buffer);

        if(buffer == 0)
        {
            delete child;
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

    xJSONNode* node = new xJSONNode;

    buffer = Parse(node,buffer);

    if(buffer == 0)
    {
        delete node;
        return 0;
    }

    buffer = skip(buffer);

    if(buffer == 0)
    {
        delete node;
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
        delete node;
        return 0;
    }

    pNode->m_ChildList.push_back(node);

    while(buffer != 0 && *buffer == ',')
    {
        buffer++;
        buffer = skip(buffer);
        if(buffer == 0)
            return 0;
        node = new xJSONNode;
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


void  xJSON::BuildJsonData(string& strData,bool format)
{
    if(m_pRoot == 0)
        m_pRoot = new xJSONNode;

    Build(m_pRoot,strData,format,0);
}

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

void xJSON::BuildStr(xJSONNode* pNode,string& strData,bool format ,int depth)
{
    strData += "\"";
    strData += pNode->GetValue().toString();
    strData += "\"";
}

void xJSON::BuildInt(xJSONNode* pNode,string& strData,bool format ,int depth)
{

    char buff[64] = {0};
    sprintf(buff,"%d",pNode->GetValue().toInt());
    strData += (char*)buff;

}
void xJSON::BuildFloat(xJSONNode* pNode,string& strData,bool format ,int depth)
{
    char buff[64] = {0};
    sprintf(buff,"%f",pNode->GetValue().toFloat());
    strData += (char*)buff;
}
void xJSON::BuildBool(xJSONNode* pNode,string& strData,bool format ,int depth)
{
    string str = "true";
    if(pNode->GetValue().toBool() == false)
        str = "false";

    strData += str;
}
void xJSON::BuildNull(xJSONNode* pNode,string& strData,bool format ,int depth)
{
    strData += "null";
}
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

void xJSON::WiteFile(const string& fileName,bool format)
{
}

xJSONNode* xJSON::CreateJSON()
{
    xJSONNode* node = new xJSONNode;
    return node;
}


void xJSON::PrintJSON(xJSONNode *node)
{
    string strData;
    Build(node,strData,true,0);

    cout << strData << endl;
}

xJSONNode& xJSON::operator[](const string& key)
{
    if(m_pRoot == 0)
        m_pRoot = new xJSONNode;

    return (*m_pRoot)[key];
}

xJSONNode* xJSON::GetRoot()
{
    return m_pRoot;
}
