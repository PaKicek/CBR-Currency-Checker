#pragma once
#include <cstring>
#include <ctime>
#include <fstream>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <currencycodes.hpp>

void parseArguments (int argc, char** argv, std::string& Vname, int& Vnom, std::string& Date, int& LongDate, std::string& FileName, int& PrintInFile, std::string& Date1, std::string& Date2, std::string& link) {
    if (argc > 1) {
        char* VnameArg = argv[1];
        if (strncmp(VnameArg, "--Vname=", 8) == 0) {
            if (currencycodes.find(VnameArg += 8) == currencycodes.end()) {
                throw std::invalid_argument("Vname argument is not correct");
            }
            Vname = VnameArg;
            if (argc > 2) {
                char* secondArg = argv[2];
                if (strncmp(secondArg, "--Vnom=", 7) == 0) {
                    if (std::atoi(secondArg += 7) <= 0) {
                        throw std::invalid_argument("Vnom argument is not correct");
                    }
                    Vnom = std::atoi(secondArg);
                    if (argc > 3) {
                        char* thirdArg = argv[3];
                        if (strncmp(thirdArg, "--Date=", 7) == 0) {
                            if (strlen(thirdArg += 7) != 10) {
                                throw std::invalid_argument("Date argument is not correct");
                            }
                            LongDate = 1;
                            thirdArg[2] = '/';
                            thirdArg[5] = '/';
                            Date = thirdArg;
                            if (argc > 4) {
                                char* fourthArg = argv[4];
                                if (strncmp(fourthArg, "--FileName=", 11) == 0) {
                                    FileName = fourthArg += 11;
                                    PrintInFile = 1;
                                }
                            }
                        } else if (strncmp(thirdArg, "--DateDate=", 11) == 0) {
                            if (strlen(thirdArg += 11) != 21) {
                                throw std::invalid_argument("DateDate argument is not correct");
                            }
                            LongDate = 2;
                            thirdArg[2] = '/';
                            thirdArg[5] = '/';
                            thirdArg[13] = '/';
                            thirdArg[16] = '/';
                            Date = thirdArg;
                            if (argc > 4) {
                                char* fourthArg = argv[4];
                                if (strncmp(fourthArg, "--FileName=", 11) == 0) {
                                    FileName = fourthArg += 11;
                                    PrintInFile = 1;
                                }
                            }
                        } else if (strncmp(thirdArg, "--FileName=", 11) == 0) {
                            FileName = thirdArg += 11;
                            PrintInFile = 1;
                        }
                    }
                } else if (strncmp(secondArg, "--Date=", 7) == 0) {
                    if (strlen(secondArg += 7) != 10) {
                        throw std::invalid_argument("Date argument is not correct");
                    }
                    LongDate = 1;
                    secondArg[2] = '/';
                    secondArg[5] = '/';
                    Date = secondArg;
                    if (argc > 3) {
                        char* thirdArg = argv[3];
                        if (strncmp(thirdArg, "--FileName=", 11) == 0) {
                            FileName = thirdArg += 11;
                            PrintInFile = 1;
                        }
                    }
                } else if (strncmp(secondArg, "--DateDate=", 11) == 0) {
                    if (strlen(secondArg += 11) != 21) {
                        throw std::invalid_argument("DateDate argument is not correct");
                    }
                    LongDate = 2;
                    secondArg[2] = '/';
                    secondArg[5] = '/';
                    secondArg[13] = '/';
                    secondArg[16] = '/';
                    Date = secondArg;
                    if (argc > 3) {
                        char* thirdArg = argv[3];
                        if (strncmp(thirdArg, "--FileName=", 11) == 0) {
                            FileName = thirdArg += 11;
                            PrintInFile = 1;
                        }
                    }
                } else if (strncmp(secondArg, "--FileName=", 11) == 0) {
                    FileName = secondArg += 11;
                    PrintInFile = 1;
                }
            }
            if (LongDate == 0) {
                LongDate = 1;
                char string[1000] = "";
                time_t time = std::time(NULL);
                struct tm* currenttime = std::localtime(&time);
                if (currenttime->tm_mday < 10) {
                    std::strcat(string, "0");
                }
                std::strcat(string, std::to_string(currenttime->tm_mday).c_str());
                std::strcat(string, "/");
                if (currenttime->tm_mon + 1) {
                    std::strcat(string, "0");
                }
                std::strcat(string, std::to_string(currenttime->tm_mon + 1).c_str());
                std::strcat(string, "/");
                std::strcat(string, std::to_string(currenttime->tm_year + 1900).c_str());
                Date = string;
            } else if (LongDate == 2) {
                char* Date1ptr = (char*)Date.c_str();
                char* Date2ptr = ((char*)Date.c_str()) + 11;
                std::strtok(Date1ptr, "-");
                Date1 = Date1ptr;
                Date2 = Date2ptr;
            }
            if (LongDate == 2) {
                char linkptr[1000] = "http://www.cbr.ru/scripts/XML_dynamic.asp?date_req1=";
                std::strcat(linkptr, Date1.c_str());
                std::strcat(linkptr, "&date_req2=");
                std::strcat(linkptr, Date2.c_str());
                std::strcat(linkptr, "&VAL_NM_RQ=");
                std::strcat(linkptr, currencycodes[Vname].c_str());
                link = linkptr;
            } else {
                char linkptr[1000] = "http://www.cbr.ru/scripts/XML_daily.asp?date_req=";
                std::strcat(linkptr, Date.c_str());
                link = linkptr;
            }
        } else {
            throw std::invalid_argument("The first argument must be Vname");
        }
    } else {
        throw std::logic_error("Example: main.exe --Vname=USD --Vnom=10 --Date=01.01.2024");
    }
}

void parseString (std::string& string, std::string& Vname, int& Vnom, std::string& Date, int& LongDate, std::string& FileName, int& PrintInFile, std::string& Date1, std::string& Date2) {
    char* str = const_cast<char*>(string.c_str());
    char buffer[100];
    long double Value = -1;
    char CurrentDate[100];
    std::string CurrentDateString;
    std::ofstream file;
    if (LongDate == 0 || LongDate == 1) {
        if (PrintInFile == 1) {
            file.open(FileName);
        }
        for (char* i = str; *i != '\0'; i++) {
            if (strncmp(i, const_cast<char*>(Vname.c_str()), 3) == 0) {
                if (Vnom != -1) {
                    for (; strncmp(i, "<VunitRate>", 11) != 0; i++) {}
                    i += 11;
                    char* start = i;
                    int counter = 0;
                    for (; *i != ','; i++, counter++) {}
                    *i = '.';
                    for (; *i != '<'; i++, counter++) {}
                    Value = std::atof(strncpy(buffer, start, counter)) * Vnom;
                    Date[2] = '.';
                    Date[5] = '.';
                    if (PrintInFile == 1) {
                        if (file) {
                            file << Vname << " " << Vnom << " " << Date << " " << Value << "\n";   
                        } else {
                            throw std::logic_error("Could not open the file " + FileName);
                        }
                    } else {
                        std::cout << Vname << " " << Vnom << " " << Date << " " << Value << "\n";
                    }
                } else {
                    for (; strncmp(i, "<Nominal>", 9) != 0; i++) {}
                    i += 9;
                    char* start = i;
                    int counter = 0;
                    for (; *i != '<'; i++, counter++) {}
                    Vnom = std::atoi(strncpy(buffer, start, counter));
                    for (; strncmp(i, "<Value>", 7) != 0; i++) {}
                    i += 7;
                    start = i;
                    counter = 0;
                    for (; *i != ','; i++, counter++) {}
                    *i = '.';
                    for (; *i != '<'; i++, counter++) {}
                    Value = std::atof(strncpy(buffer, start, counter));
                    Date[2] = '.';
                    Date[5] = '.';
                    if (PrintInFile == 1) {
                        if (file) {
                            file << Vname << " " << Vnom << " " << Date << " " << Value << "\n";   
                        } else {
                            throw std::logic_error("Could not open the file " + FileName);
                        }
                    } else {
                        std::cout << Vname << " " << Vnom << " " << Date << " " << Value << "\n";
                    }
                }
                break;
            }
        }
        if (PrintInFile == 1) {
            file.close();
            std::cout << "Successfully written the result in file " + FileName + " \n";
        }
    } else if (LongDate == 2) {
        if (PrintInFile == 1) {
            file.open(FileName);
        }
        for (char* i = str; *i != '\0'; i++) {
            if (strncmp(i, "Date=", 5) == 0) {
                i += 6;
                strncpy(CurrentDate, i, 11);
                if (Vnom != -1) {
                    for (; strncmp(i, "<VunitRate>", 11) != 0; i++) {}
                    i += 11;
                    char* start = i;
                    int counter = 0;
                    for (; *i != ','; i++, counter++) {}
                    *i = '.';
                    for (; *i != '<'; i++, counter++) {}
                    Value = std::atof(strncpy(buffer, start, counter)) * Vnom;
                    Date[2] = '.';
                    Date[5] = '.';
                    CurrentDateString.assign(CurrentDate, CurrentDate + 10);
                    if (PrintInFile == 1) {
                        if (file) {
                            file << Vname << " " << Vnom << " " << CurrentDateString << " " << Value << "\n";
                        } else {
                            throw std::logic_error("Could not open the file " + FileName);
                        }
                    } else {
                        std::cout << Vname << " " << Vnom << " " << CurrentDateString << " " << Value << "\n";
                    }
                } else {
                    for (; strncmp(i, "<Nominal>", 9) != 0; i++) {}
                    i += 9;
                    char* start = i;
                    int counter = 0;
                    for (; *i != '<'; i++, counter++) {}
                    Vnom = std::atoi(strncpy(buffer, start, counter));
                    for (; strncmp(i, "<Value>", 7) != 0; i++) {}
                    i += 7;
                    start = i;
                    counter = 0;
                    for (; *i != ','; i++, counter++) {}
                    *i = '.';
                    for (; *i != '<'; i++, counter++) {}
                    Value = std::atof(strncpy(buffer, start, counter));
                    Date[2] = '.';
                    Date[5] = '.';
                    CurrentDateString.assign(CurrentDate, CurrentDate + 10);
                    if (PrintInFile == 1) {
                        if (file) {
                            file << Vname << " " << Vnom << " " << CurrentDateString << " " << Value << "\n";   
                        } else {
                            throw std::logic_error("Could not open the file " + FileName);
                        }
                    } else {
                        std::cout << Vname << " " << Vnom << " " << CurrentDateString << " " << Value << "\n";
                    }
                }
            }
        }
        if (PrintInFile == 1) {
            file.close();
            std::cout << "Successfully written the result in file " + FileName + " \n";
        }
    }
}