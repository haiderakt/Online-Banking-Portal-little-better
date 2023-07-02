# SemProject-OnlineBankingPortal
A semester project that replicates the working of an online banking portal. Developed in C++ using fundamental programming concepts.

**Code Components:**
Number of lines: 400+

**Functions and their purpose:**
int main() : main function of the program
void landing_page() : displaying first page information
void register_page() : taking input from user and registering them
void login_page() : validates the username and password to login the user
void account_page(string) : displaying account information and accessing banking features

**Libraries used:**
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <sys/stat.h>

**Programming Fundamental Concepts Used:**
Conditional statements
Loops
Strings
Generating random values
Function calls
Pass by value
File handling

**Features of the Program:**
•	Main Menu:
  o	Registeration Page:
    Taking Bio-data of the User
    Making the user set a username for their account
    Making the user set a password for their account
    Making the user select an account type
    Giving instant credit to the user based on account type
    Generating an account number for the user

  o	Login Page:
    Logging in through username and password

  o	Account Page:
    Displaying all information of the user
      -Full name			
      -Account Number
      -Age
      -Contact
      -Cnic
      -Account Type
      -Username
      -Password
      -Account Balance
      -Due Repayment
    Offering transaction options to the user:
      -Send money
      -Repayment of credit
    Changing password
    Logging out and return to main menu

