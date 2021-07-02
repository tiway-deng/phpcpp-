#include <phpcpp.h>
#include <iostream>
#include<cstdio>
#include<time.h>
#include<stdlib.h>
#include <string>

Php::Value gen_by_charp(Php::Parameters &params)
{
    //长度参数
    int len = params[0];
    //返回值声明
    Php::Value result;
    //声明返回值长度，并返回指针给str
    char* str = new char[len+1];
    //srand函数是随机数发生器rand的初始化函数,我们常常使用系统时间来初始化;
    //使用time函数来获取系统时间，得到的值是一个时间戳
    srand(time(NULL)+1);

    for (int i = 0; i < len; ++i)
    {
        switch ((rand() % 3))
        {
        case 1:
            str[i] = 'A' + rand() % 26;
            break;
        case 2:
            str[i] = 'a' + rand() % 26;
            break;
        default:
            str[i] = '0' + rand() % 10;
            break;
        }
    }
    str[len+1] = '\0';

    return str;
} 

Php::Value gen_by_char(Php::Parameters &params)
{
    int len = params[0];
    srand(time(NULL)+2);

    char str[len+1];
    int i;
    
    for (i = 0; i < len; ++i)
    {
        switch ((rand() % 3))
        {
        case 1:
            str[i] = 'A' + rand() % 26;
            break;
        case 2:
            str[i] = 'a' + rand() % 26;
            break;
        default:
            str[i] = '0' + rand() % 10;
            break;
        }
    }
    str[len+1] = '\0';

    return str;
}  

Php::Value gen_by_string(Php::Parameters &params)
{
    int len = params[0];
    srand(time(NULL)+3);
    std::string str = "";
    
    for (int i = 0; i < len; ++i)
    {
        switch ((rand() % 3))
        {
        case 1:
            str += 'A' + rand() % 26;
            break;
        case 2:
            str += 'a' + rand() % 26;
            break;
        default:
            str += '0' + rand() % 10;
            break;
        }
    }
    
    return str;
}

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {
    
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("tiway", "1.0");
        
        // @todo    add your own functions, classes, namespaces to the extension
        extension.add<gen_by_char>("gen_by_char", {
            Php::ByRef("strLength", Php::Type::Numeric)
        });
        extension.add<gen_by_charp>("gen_by_charp", {
            Php::ByRef("strLength", Php::Type::Numeric)
        });
        extension.add<gen_by_string>("gen_by_string", {
            Php::ByRef("strLength", Php::Type::Numeric)
        });
        
        // return the extension
        return extension;
    }
}
