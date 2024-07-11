#include <iostream>
#include <exception>
#include <string>
#include <cpr/cpr.h>
#include <parser.hpp>

int main (int argc, char* argv[]) {
    std::string Vname;
    std::string Date, Date1, Date2;
    std::string FileName;
    std::string link;
    int Vnom = -1;
    int LongDate = 0;
    int PrintInFile = 0;
    try {
        parseArguments(argc, argv, Vname, Vnom, Date, LongDate, FileName, PrintInFile, Date1, Date2, link);
        cpr::Response response = cpr::Get(cpr::Url{link});
        if (response.status_code == 200) {
            parseString(response.text, Vname, Vnom, Date, LongDate, FileName, PrintInFile, Date1, Date2);
        } else {
            throw std::logic_error("Could not get data from link " + link);
        }
    } catch (std::logic_error error) {
        std::cout << error.what() << "\n";
    }
}