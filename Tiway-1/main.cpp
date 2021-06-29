#include <phpcpp.h>
#include <iostream>

void example()
{
    // the C++ equivalent of the echo() function
    Php::out << "example output" << std::endl;

    // generate output without a newline, and ensure that it is flushed
    Php::out << "example output" << std::flush;

    // or call the flush() method
    Php::out << "example output";
    Php::out.flush();
    
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
        extension.add<example>("example");
        
        // return the extension
        return extension;
    }
}
