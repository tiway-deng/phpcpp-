#include <phpcpp.h>
#include <iostream>

void example(Php::Parameters &params)
{
    for (auto &key : params) 
    {
        // output key
        Php::out << "key: " << key << std::endl;
    }
}  

void example_function(Php::Parameters &params)
{
    // first parameter is an array
    Php::Value array = params[0];

    // call the PHP array_keys() function to get the parameter keys
    std::vector<std::string> keys = Php::array_keys(array);

    // loop through the keys
    for (auto &key : keys) 
    {
        // output key
        Php::out << "key: " << key << std::endl;
    }

    // call a function from user space
    Php::Value data = Php::call("some_function", "some_parameter");

    // create an object (this will also call __construct())
    Php::Object time("DateTime", "now");

    // call a method on the datetime object
    Php::out << time.call("format", "Y-m-d H:i:s") << std::endl;

    // second parameter is a callback function
    Php::Value callback = params[1];

    // call the callback function
    callback("some","parameter");

    // in PHP it is possible to create an array with two parameters, the first
    // parameter being an object, and the second parameter should be the name
    // of the method, we can do that in PHP-CPP too
    Php::Array time_format({time, "format"});

    // call the method that is stored in the array
    Php::out << time_format("Y-m-d H:i:s") << std::endl;
}

Php::Value my_return_value_function(Php::Parameters &params)
{
    // first parameter is an array
    Php::Value array = params[0];

     for (auto &iter : array)
    {
        // output key and value
        Php::out << iter.first << ": " << iter.second << std::endl;
    }

    return 0;
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
        extension.add<example>("example",{
            Php::ByVal("a", Php::Type::Numeric),
            Php::ByVal("d", Php::Type::Constant),
        });

        extension.add<example_function>("example_function");

        extension.add<my_return_value_function>("my_return_value_function");
        
        // return the extension
        return extension;
    }
}
