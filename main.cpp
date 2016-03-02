#include <iostream>
#include <xjson.h>
using namespace std;

void w()
{

    xJSON json;
  xJSONNode* jsonnode= json.CreateJSONNode();

    jsonnode->AddChild("name","mbs");
    jsonnode->AddChild("addr","ZH");
    jsonnode->AddChild("other","none");

    xJSONNode* obj = json.CreateJSONNode(),
            *subobj = json.CreateJSONNode(),
            *subobj2= json.CreateJSONNode();

    obj->SetName("obj");
    obj->AddChild("test","test");

    obj->AddChild(subobj);

    subobj->AddChild(subobj2);
    subobj->SetName("subobj");

    subobj2->SetName("hhhhhhhh");

    subobj2->SetValue("fff");
    subobj2->SetName("subobj2");

    vector<xJSONNode*> vec;

    for(int i = 0; i < 8 ; i++)
    {
        xJSONNode* node = json.CreateJSONNode();
        char buf[4] = {0};
        sprintf(buf,"%d",i);
        node->SetName((buf));
        node->SetValue(buf);
        vec.push_back(node);
    }

    jsonnode->AddChild(obj);
    jsonnode->AddChild("Array",vec);


    jsonnode->AddChild("int",100024);
    jsonnode->AddChild("bool",true);
    jsonnode->AddChild("double",1.23456);
    jsonnode->AddChild("NULL");
    string str;

    json["d"] = "json";
    json["1"] = 3;
    json["s"]["1"] =1;
    json["s"]["2"] =2;
    json["s"]["null"] = false;
    json["root"] = jsonnode;
    json.GetRoot()->AddChild("root2",jsonnode);

     json.Write(str);

     {
     //xJSONNode test = *json;
     //xJSONNode test2 = *json;
     }

    //cout << str <<endl;

}

void r()
{
    xJSON json;
    char text[] = "{\"name\":\"jack\",\"age\":\"18\"}";
     json.Open("test1.json");///home/mbs/work/cpp/cjosn/tests/test4


    vector<xJSONNode*> node =  json["root2"]["Array"].toArray();
    json.PrintJSON();



    int i = 0;
     cin >> i;
}

string g_str = "test";
string& getstr()
{
    return g_str;
}

int main()
{


    w();

    r();

    return 0;
}

