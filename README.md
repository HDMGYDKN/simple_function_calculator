# Simple Function Calculator
This is a calculator that allows you to calculate function within expressions. You can define a function and calculate it easily. The calculator will automatically store the function's return values which will make your calculation faster.
## HERE ARE THE BASIC INSTRUCTIONS
This is the function calculater(Powered by Tony hu). You can input help() to learn more in the calculator.
Thank you for using the function calculater.(Input help(version) to check out the version of the calculator.) This is basically a calculater,but what's more is that you can calculate functions. Allow me to demonstrate:
### THE BASICS
You can input simple expressions like ``1+1``, ``2^2``, etc. Here are the rules:   
``note: in here, 0 stands for false, 1 stands for true, just like c++.``   
**\+** stands for plus, means you add two things together. ``1+1=2``     
**\-** stands for minus, means you let a number minus another. ``2-1=1``       
**\*** stands for times, means you let a number times another. ``2*2=4``   
**\/** stands for division(I'll skip on the detail explanation). ``6/2=3``   
**\%** means mod. ``11%3=2``   
**\^** means power. ``3^3=27``   
**\|** means or. ``1|1=1`` ``0|1=1`` ``0|0=0``    
**\&** means and. ``1&1=1`` ``0&1=0`` ``0&0=0``    
**\>** means bigger than. ``2>1=1`` ``1>1=1`` ``0>1=0``   
**\<** means smaller than. ``2<1=0`` ``1<1=0`` ``0<1=1``   
**\=** means equal. ``(1=1)=1`` ``(2=1)=0``   
**(),[],{}** are brackets.  
### FUNCTION DEFINATION
That's all the operators. Now, I'll show you how to **define a function**:
There are **two modes**, **calculation mode** and **function mode**.
I was teaching you how to use the function mode just then, you can enter expressions and calculate them.
But, if you want to add in functions, you can:
#### FIRST WAY OF ADDING A FUNCTION
Use command ``add``, like ``add:math.h``.
#### SECOND WAY OF ADDING A FUNCTION
If you just want to write one function, you can just define it. You can input ``break`` if you want to exit.
#### THIRD WAY OF ADDING A FUNCTION
You can use command ``file``, like file:(here you can define functions just like in a file). Input end to end the entering and start calculating with the new defined functions, or input break to exit function mode and leave the defined functions.
In the function mode, you can define functions, here's the rules:
```
function[do_save or do_not_save or don't write anything]=function_name(function_parameters){   
   if(function_condition) function_expression;   
}
```   
If you enter **do_save**,that means the calculater will save the result, and when you call the function with the same values again, it will return the answer.(It is do_save if you don't write anything.)  
The answer of the function is the first function_expression that the function_condition paired with it is true.   
Example:
```
function[]=f(x){
   if(x>2) f(x-1)+f(x-2);
   if((x<2)|(x=2)) 1;
}
```
You can write a expression in function mode, and it could be calculated **when you add the function in**.   
You can also add files in function mode with ``add``, but in another way:    
like ``add[\user\blablabla\main.hdm,test.hdm,math.h]``, the first one means add in ``\user\blablabla\main.hdm``,the second one means add in test.hdm which is in the same directory,the third one means add in a STL,which will be explained later.  
You can write notes with ``//`` or ``/**/`` in function mode.
```
//this makes the hole line after it a note.
/*this makes anything between it a note.*/
```
Note doesn't count as column in errors. ~~gotta fix that later~~   
STL is a lot of functions that are defined by the calculater, you can add them like a normal file,and use ``help(file_name)`` (like ``help(math.h)``) to check out what can the file do, and use ``help(file_name,function_name)`` (like ``help(math.h,floor)``) to check out what a function can do.   
## STLS
Here are the STL files:    
``math.h``, ``system.h``, ``print.h``, ``variable.h``, ``random.h``,``file.h``.
### MATH.H   
This is a file that contains mathematic calculation functions. With ``sum(start_from,go_to,expression)``, ``prod(start_from,go_to,expression)``, ``floor(input_value)``, ``ceil(input_value)`` four functions.  
#### SUM
This is a mathematic calculation function. It's like sigma, which is a summation operation. ``sum(i=a,b,f(i))`` means ``f(a)+f(a+1)...+f(b-1)+f(b)``. For example, ``sum(k=0,5,k^2) = 0^2+ 1^2+2^2+3^2+4^2+5^2``.
#### PROD
This is a mathematic calculation function. It's like Π, which is a quadrature operation. prod(i=a,b,f(i)) means ``f(a)*f(a+1)*f(a+2)...*f(b-1)*f(b)``. For example, ``prod(k=0,3,2*i+1)=1*3*5*7. ``
#### FLOOR
This is a mathematic calculation function. ``floor(a)`` means the first integer that is smaller than or equal to a. For example, ``floor(1.2)=1``, ``floor(-12/13)=-1``.
#### CEIL
This is a mathematic calculation function. ``ceil(a)`` means the first integer that is bigger than or equal to a. For example, ``floor(1.2)=2``, ``floor(-12/13)=0``.
### SYSTEM.H
This is a file that contains system setting functions. With  ``do_reduction(change_value)``, ``output_style(change_value)``, ``save_decimal_point(change_value)``, ``expression_output(change_value)``, ``system(do_string)``, ``do_output(change_value)`` .
#### DO_REDUCTION
This is a system function. ``do_reduction(change_value)``. If change_value equals 0, it means do not do reduction, which means if you input 12/8 it will give you 12/8. If change_value equals 1,it means do reduction, which means if you input 12/3 it will give you 3/2(assuming you are in fraction mode, more on that in output_style). Function returns 0. 
#### OUTPUT_STYLE
This is a system function. ``output_style(change_value)``. If change_value is fraction, the answer of a calculation will be a fraction, which means if you input 12/8 it will give you 3/2. If change_value is decimal, the answer of a calculation will be a decimal,which means if you input 12/8 it will give you 1.50000(you can use save_decimal_point to change how many points will be saved, assuming it's five). Function returns 0. 
#### SAVE_DECIMAL_POINT
This is a system function. ``save_decimal_point(change_value)``. change_value is the decimal points that will be saved with the answer(which will still be calculated by fraction) , and it will be the decimal point that will be saved with the ^ operator. For example, when you're in the decimal mode (more on that in output_style) ,if the change_value is 1, the answer of 12/5 is 2.4, if the change_value is 5, the answer of 12/5 is 2.40000 . If the change_value is 0, the answer of 15^(1/2) is 3. If the change_value is five, the answer of 15^(1/2) is 193649/50000 (assuming you're in fraction mode). Function returns 0.
#### SYSTEM
This is a system function that allows you to use terminal in the function calculator. Use it like the **print functions**. Function returns 0.
#### DO_OUTPUT
This is a system function that allows you to set if the print function print on the terminal.(0 for false, 1 for true) Function returns 0.  
### PRINT.H
This is a file that allows you to output stuff. It contains ``printn(output_value)``, ``prints(output_value)``, ``printw()``, ``printl()``, ``printv(answer)``, ``getchar()``, ``putchar(input_value)``, ``to_int(char_value)``. Note: to output line feed `` `` and ``,``, you need to write ``\n`` ``\w`` and ``\,``.
#### PRINTN
This is a function that allows you to output number. ``printn(output_value)`` means output output_value. For example, ``printn(1+1)`` outputs 2. Function returns output_value.
#### PRINTS
This is a function that allows you to output strings. ``prints(output_value)`` means output output_value, and return 0. For example, ``prints(1+1)`` outputs 1+1 and returns 0. 
#### PRINTW
This is a function that allows you to output white space. ''printw()'' means output a white space, and return 0.
#### PRINTL
This is a function that allows you to output line feed. printl() means output a line feed, and return 0.
#### PRINTV
This is a function that allows you to output strings and numbers at the same time. ``printv({arg1,arg2,...})`` (note: the double bracket can let you input multiple parameters). The function will think ``arg1`` is a string, ``arg2`` is a number, ``arg3`` is a string... Function returns the sum of the numbers. For example, ``printv({expression:,1+1,+,2+2,=,1+1+2+2})`` outputs ``expression:2+4=6``, returns 12. 
#### GETCHAR
This is a function that allows you to input one char. The function returns the ASCII code of the char that was inputted.
#### PUTCHAR
This is a function that allows you to output one char. ``putchar(input_value)`` will output the char that has the ASCII code input_value. The function returns the ASCII code of the char that was outputted.
#### TO_INT
This is a function that allows you to turn one char into a number. ``to_int(char_value)`` will return the ACSII code of char_value.
### VARIABLE.h
This is a file that allows you to create variables. It contains ``equal(variable,equal_expression)``, ``make_array(array_name,array_info)``, ``equal(array_name,array_info,value)``, ``at(array_name,pos)``.
#### EQUAL
There are two functions that are both called equal: ``equal(variable,equal_expression)`` and ``equal(array_name,array_info,value)``. The first equal can assign variable with equal_expression, if variable don't exist, the function will define it first and assign it with equal_expression (note: if you use the variable in equal_expression but the variable don't exist, the program will assume variable is 0).the function will return equal_expression. The second equal can assign a number in a array. Assign array_name\[array_info\] with value. (note: if array_info have more than one layer, you need to enclose it in parentheses.) For example, ``equal(a,10,1+1)`` means ``a[10]=1+1``, ``equal(b,{1,2},2+3)`` means ``b[1][2]=2+3``. (note:subscript starts with 0.) The function will return value.
#### MAKE_ARRAY
This function allows you to define an array. ``make_array(array_name,array_info)`` means define a array called array_name with array_info. If the array have more than one layer, you'll have to enclose it in parentheses. For example: ``make_array(a,3)`` means define ``a[3]``, but you can only visit ``a[0~2]``; ``make_array(b,(3,5))`` means define ``b[3][5]``, but you can only visit ``b[0~2][0~4]``.
#### AT
This function allows you to visit a number in an array. ``at(array_name,pos)`` means visit array_name at pos. If the array have more than one layer, you'll have to enclose pos in parentheses. For example, ``at(a,12)`` means visit ``a[12]``, ``at(b,(3,2,1))`` means visit ``b[3][2][1]``.
### RANDOM.H
This is a file that allows you to get random numbers. It contains ``random(left_value,right_value)``.
#### RANDOM 
This is a function that allows you to get random numbers. ``random(left_value,right_value)`` means get a random number between left_value and right_value (could be left_value or right_value).
### FILE.H
This is a file that contains the file function that allows you to read from file and write things in a file. It contains ``read(file_name)`` and ``write(file_name)``.
#### READ
This is a function that allows you to set where the calculator will get inputs. ``read(file_name)`` means get the inputs from the file file_name, and ``read()`` means get the inputs from the terminal.
#### WRITE
This is a function that allows you to set where the calculator will output. ``write(file_name)`` means output to the file file_name, and ``write()`` means output to the terminal.

# THANKS
****Huge thanks with all the users of this calculator.****
