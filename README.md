# CBR Currency Checker
A 9th labwork of C/C++ course (2nd semester, 3-4 stream).

The program is used to print the currency dates of different currencies to the Russian rouble (RUB)

This project was compiled with the use of CMake in Visual Studio Code. For build, do these steps:
1. Clone a repository
2. Click Build all projects in menu when clicking a RMB on CMakeLists.txt (in VS Code)
3. Run `cd build` and then `make`. The executable will appear in build directory
4. Run an executable

## How to use the program
Compile the program using the instruction above and run it with needed arguments.
Examples are `main.exe --Vname=USD --Vnom=10 --Date=01.01.2024` and `main.exe --Vname=EUR --Vnom=2 --DateDate=01.01.2024-25.03.2024 --FileName=output.txt`

List of all arguments:
- --Vname - Currency code (obligatory)
- --Vnom - Value of the currency (not obligatory, if not defined, default value is used instead)
- --Date - Date of the currency rate (not obligatory, not compatible with --DateDate, if not defined, current date is used instead)
- --DateDate - All the dates between starting and ending dates (not obligatory, not compatible with --Date)
- --FileName - Name of the file where the result should be written (not obligatory, if not defined, the result is printed instead)
