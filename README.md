## Term-Project
CSC 455 term project
# Customer Reward System
A customer reward system is a software that tracks the customer’s shopping behavior and reward points
to the customer.

<hr/>

## Usage

This program provides a terminal based menu system that provides the following features:
* Customer registration.
* Customer Removal.
* Product addition.
* Product removal.
* Shopping.
* View customer using customer ID.
* Redeem rewards.
* Configure rewards

To preserve the state of the program, all data is stored in various .txt files

<strong> If these files are edited outside the program, your data might become corrupted </strong>

<hr/>

## Compilation

The Program can be compiled using different utilities, Make or CMake. Make is the preferred and tested option.
### Make

When compiling with make, there are the following commands that can be used:
>make
>
or
>
>make build
>
>
Will compile all the code into an executable

<br>

>make run
>
Will run the executable created by make build and start the program

>make clean
>
Deletes the executable file so that the program can be recompiled

<br/>

### CMake

CMake is not available on Missouri State Servers, but it is included in the package for its developing and testing capability when used on a local machine

First, ensure that CMake is installed locally by running the following command:
>cmake --version
>
When compiling with cmake, there does have to be some changes made to the program for proper compilation.

Before running any commands, you must go into src/main/menu.cpp and comment out the #include statements under //MAKE
and then uncomment the CMake includes. The result should look as follows

>// MAKE
> 
>// #include "Clientele.h"
> 
>// #include "Inventory.h"
> 
>// #include "Utilities.h"
> 
>// #include "Transaction.h"


>
>// CMAKE
> 
>#include "include/Clientele.h"
> 
>#include "include/Inventory.h"
> 
>#include "include/Utilities.h"
> 
>#include "include/Transaction.h"

After these changes you are free to open the project in your preferred IDE and configure CMake from there
or you can execute 
>cmake CMakeLists.txt
> 
> make

to build the project that way
<hr/>
