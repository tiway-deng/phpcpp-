<?php
// class ExampleClass {

// const MYCONST='MYC';
// }

// class OtherClass{

// }

// function some_function($param)
//     {
//         echo("userspace function called with $param\n");
//     }

    // example input
    $input = array(
        'x' =>  10,
        'y' =>  20,
        'z' =>  30
    );

//     example_function($input, function($param1, $param2) {
//         echo("lambda function called with param $param1 $param2\n");
//     });


example_function($input);

// correct call, parameters are numeric and two objects of the right type
// example(12, ExampleClass::MYCONST);

// also valid, first parameter is not numeric but an array, but the
// Zend engine does not check this even though it was specified
//example(array(1,2,3), new ExampleClass(), new OtherClass());

// // invalid, wrong number of parameters
// example(12, new ExampleClass());

// // invalid, wrong objects
// example(12, new DateTime(), new DateTime());

// // invalid, "y" and "z" are no objects
// example("x", "y", "z");


?>