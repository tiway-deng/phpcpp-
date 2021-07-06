#include <phpcpp.h>
#include <iostream>
#include <string>

//声明MyClass类为可以被外部php 调用
class MyClass : public Php::Base
{
//属性声明：用原生的c++ 属性类型
private:
    int _value;
    
public:
    //构造函数
    MyClass()
    {
        _value = 3;
        std::cout << "MyClass::MyClass" << std::endl;
        std::cout << this << std::endl;
        std::cout << _value << std::endl;
    }
    MyClass(int value) : _value(value)
    {
        std::cout << "MyClass::MyClass(" << value << ")" << std::endl;
    }
    //拷贝构造
    MyClass(const MyClass &that)
    {
        std::cout << "MyClass::MyClass copy constructor" << std::endl;
    }
    //析构函数
    virtual ~MyClass()
    {
        std::cout << "MyClass::~MyClass" << std::endl;
    }
    //php 构造函数，区别于c++ 构造函数，只是在实例化完成后第一个默认执行的函数（对于c++就是普通函数）
    void __construct(Php::Parameters &params)
    {
        // 属性初始化
        if (!params.empty()) _value = params[0];
        std::cout << "php constructor" << std::endl;
    }
    //php 析构函数
    //virtual 虚函数 虚函数是指一个类中你希望重载的成员函数 ，当你用一个  基类指针或引用   指向一个继承类对象的时候，调用一个虚函数时, 实际调用的是继承类的版本
    virtual void __destruct()
    {
        std::cout << "MyClass::__destruct" << std::endl;
    }
    //静态方法
    static void staticMethod(Php::Parameters &params)
    {
        std::cout << "staticMethod GETS CALLED!!!!" << std::endl;
    }
    //返回类对象
    Php::Value objectMethod(Php::Parameters &params)
    {
        int initValue = params[0];
        return Php::Object("MyClass", new MyClass(initValue));
    }

    Php::Value myMethod(Php::Parameters &params)
    {
        return params[0];
    }
    


    Php::Value increment() { return ++_value; }
    Php::Value decrement() { return --_value; }
    Php::Value value() const { return _value; }
};

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

        //声明一个接口类
         Php::Interface myInterface("MyInterface");
        //声明接口方法
        myInterface.method("myMethod", { 
            Php::ByVal("value", Php::Type::String, true) 
        });

        Php::Class<MyClass> myClass("MyClass");
        // myClass.implements(myInterface);
        myClass.method<&MyClass::myMethod>("myMethod", {
            Php::ByVal("value", Php::Type::String, true) 
        });
        //声明类属性
        myClass.property("property1", "prop1");
        myClass.property("property2", "prop2", Php::Protected);
        //类常量
        myClass.constant("MY_CONSTANT_1", 3.1415);
        myClass.add(Php::Constant("MY_CONSTANT_2", "constant string"));
        myClass.method<&MyClass::__construct>("__construct", {
            Php::ByVal("a", Php::Type::Numeric)
        });
        //
        myClass.method<&MyClass::__destruct>("__destruct");
        //静态方法
        myClass.method<&MyClass::staticMethod>("staticMethod");
        myClass.method<&MyClass::objectMethod>("objectMethod", { 
            Php::ByVal("n", Php::Type::Numeric, true) 
        });
        //标记为 public、private 或 protected 来限定访问修饰符
        //标志参数可以与 Php::Abstract 或 Php::Final 进行按位或运算
        myClass.method<&MyClass::value>("value", Php::Public | Php::Final);
        myClass.method<&MyClass::increment>("increment");
        myClass.method<&MyClass::decrement>("decrement");
        //声明类对象禁止克隆
        myClass.method("__clone", Php::Private);

        // add the class to the extension
        extension.add(std::move(myInterface));
        extension.add(std::move(myClass));

        

        
        
        // return the extension
        return extension;
    }
}
