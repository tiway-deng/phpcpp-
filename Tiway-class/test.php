<?php

$object = new MyClass(12) ;


// $object->myMethod(22);

// var_dump($object->property1); //string(5) "prop1"

// var_dump($object->property2);  // Cannot access protected property MyClass::$property2 

// var_dump($object::MY_CONSTANT_1);
// MyClass::MyClass
// 0x55791942d3e0
// 3
// php constructor
// float(3.1415)
// MyClass::__destruct
// MyClass::~MyClass

// var_dump(MyClass::MY_CONSTANT_1); //float(3.1415)


// $object1 = $object->objectMethod(13);


// $object = clone $object1;   Call to private MyClass::__clone() from context ''

// echo(get_class($object)."\n");

echo "-----------";
echo $object->value();
echo "-----------";
$object->increment();
echo "-----------";
echo $object->value();

// echo(get_class($object1)."\n");


