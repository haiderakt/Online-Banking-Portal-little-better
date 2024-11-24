#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <sys/stat.h>
#include <cstdlib>

using namespace std;

// ---Password encryption
string xorEncryptDecrypt(const string& data, char key) {
    string result = data;
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] ^= key; // --- XOR operation
    }
    return result;
}

// --- Function Prototypes:
void landing_page();
void register_page();
void login_page();
void account_page(string);

// --- Function Definitions:
int main() {	// <--- Usage: Main function.
	
	int choice;
	
	landing_page();
	
	cout << "\n\n\t\t\tEnter Choice: ";	
	cin >> choice;
	cin.ignore();

	switch (choice)
	{
		case 1:
			register_page();
			main();
			break;
		
		case 2:
			login_page();
			main();
			break;

		case 3:
			system("cls");		
			cout << "Exiting...\n";	
			break;

		default:
			main();	// <--- This will recall the main function if user enters anything invalid.
			break;
	}

	return 0;
}

void landing_page() {	// <--- Usage: Displaying first page info.
	
	system("cls");
	cout << "\t\t ___________________________________________________________\n";
	cout << "\t\t|                                                           |\n";
	cout << "\t\t|                                                           |\n";	
	cout << "\t\t|              Welcome to Online Banking Portal             |\n";
	cout << "\t\t|                                                           |\n";	
	cout << "\t\t|___________________________________________________________|\n";
	cout << "\t\t                                                             \n";
	cout << "\t\t                 Enter 1 to Register with us                 \n";
	cout << "\t\t             Enter 2 to Login as registered user             \n";
	cout << "\t\t                 Enter 3 to Exit the program                 \n";
	cout << "\t\t_____________________________________________________________\n";
}

void register_page() {	// <--- Usage: Takes input from the user to register them.
	
	system("cls");
	
	srand(time(0));
	string username, password, account_type, contact, cnic, full_name;
	int account_number, balance, repayment, age, choice;
	fstream f;

	cout << "\t\t_____________________________________________________________\n";
	cout << "\t\t                                                             \n";
	cout << "\t\t                      Registration Page                      \n";
	cout << "\t\t        Please enter VALID data for your registration.       \n";
	cout << "\t\t_____________________________________________________________\n";	

	cout << "\n\n\tEnter your Full Name: ";
	getline(cin, full_name);
	cout << "\n\tEnter your Age: ";
	cin >> age;
	cin.ignore();
	cout << "\n\tEnter your Contact number: ";
	getline(cin, contact);
	cout << "\n\tEnter your CNIC number (without dashes): ";
	getline(cin, cnic);
	cout << "\n\tEnter a Username for Banking Portal (no spaces allowed): ";
	getline(cin, username);
	cout << "\n\tEnter a Password for Banking Portal (no spaces allowed): ";
	getline(cin, password);
	
	system("cls");
	cout << "\n\n\t\tCongratulations! Your account has been created.";
	cout << "\n\t\tPlease tell us which account type do you need? (1/2/3)";
	cout << "\n\n\n\t1. Business account (instant credit of 50000)";
	cout << "\n\n\t2. Casual account (instant credit of 30000)";
	cout << "\n\n\t3. Student account (instant credit of 15000)";
	cout << "\n\n\n\n\t\tEnter Choice: ";
	cin >> choice;
	cin.ignore();

	if (choice == 1) {
		account_type = "Business";
		balance = repayment = 50000;
	}
	else if (choice == 2) {
		account_type = "Casual";
		balance = repayment = 30000;
	}
	else if (choice == 3) {
		account_type = "Student";
		balance = repayment = 15000;
	}

	account_number = rand() % (99999999 - 10000000 + 1) + 10000000;	// <--- Generates a random account number for the user.

	mkdir("Records");	// <--- Makes a folder "Records" in parent directory of the .cpp file
	f.open("Records\\" + username + ".txt", ios::app);	// <--- makes a "username".txt file

     string encryptedPassword = xorEncryptDecrypt(password, 'K'); //---Encrypting the password before saving it

	// Storing data in the file:
	f << username << endl << encryptedPassword << endl << account_number << endl << account_type << endl << balance << endl << repayment << endl;
	f << age << endl << contact << endl << cnic << endl << full_name << endl;
	f.close();

	cout << "\n\n\t\tYour information has been saved! Press ENTER to continue... \n";
	getchar();
}

void login_page() {	// <--- Usage: Validates username and password to login a user.

	system("cls");

	int choice, i = 0;
	string username, password, inFile_username, inFile_password;
	fstream f;

	cout << "\t\t_____________________________________________________________\n";
	cout << "\t\t                                                             \n";
	cout << "\t\t                          Login Page                         \n";
	cout << "\t\t          Please enter VALID username and password.          \n";
	cout << "\t\t_____________________________________________________________\n";

	cout << "\n\nEnter your username: ";
	getline(cin, username);
	cout << "\nEnter your password: ";
	getline(cin, password);

	f.open("Records\\" + username + ".txt");

	if (f) // <--- Executes if the file of the entered username exists.
	{
		while (!f.eof())	// <--- Traversing till the end of file.
		{
            string decryptedPassword = xorEncryptDecrypt(inFile_password, 'K');//--Decrypting the password before using

			f >> inFile_username >> inFile_password;	// <--- Storing first 2 lines of the file (username and password).

			if (username == inFile_username && password == inFile_password)	// <--- Executes if the entered username and password match.
			{
				f.close();
				account_page(username);	// <--- Takes the user to their account page.
				break;
			}
			
			else	// <--- Executes if the entered username and password do not match.
			{
				f.close();
				cout << "\n\n\t\t\tInvalid username or password! choose an option:\n\n";
				cout << "\n\t\t1. RETRY Login";
				cout << "\n\t\t2. REGISTER as a new user";
				cout << "\n\n\n\t\t\tEnter Choice: ";
				cin >> choice;
				cin.ignore();

				if (choice == 1)
				{
					login_page();
					break;
				}
				else if (choice == 2)
				{
					register_page();
					break;
				}
				else
				{
					cout << "\n\n\n\t\t\tInvalid Input! Press ENTER to go back to main menu...\n";
					getchar();
					break;
				}
			}
		}
	}
	
	else // <--- Executes if the file does not exist.
	{
		f.close();
		cout << "\n\n\t\t\tInvalid username or password! choose an option:\n\n";
		cout << "\n\t\t1. RETRY Login";
		cout << "\n\t\t2. REGISTER as a new user";
		cout << "\n\n\n\t\t\tEnter Choice: ";
		cin >> choice;
		cin.ignore();

		if (choice == 1)
		{
			login_page();
		}
		else if (choice == 2)
		{
			register_page();
		}
		else
		{
			cout << "\n\n\n\t\t\tInvalid Input! Press ENTER to go back to main menu...\n";
			getchar();
		}
	}
}

void account_page(string username) {	// <--- Usage: Displays account information and integrates Banking features.
	
	system("cls");
	
	string password, account_type, contact, cnic, full_name;
	int account_number, balance, repayment, age, i, ch1, ch2; 
	fstream f;
	f.open("Records\\" + username + ".txt");

	// Storing data from file:
	f >> username >> password >> account_number >> account_type >> balance >> repayment;
	f >> age >> contact >> cnic;
	
	while (i < 2)
	{
		getline(f, full_name); // <--- Stores full name from the file.
		i++;
	}

	f.close();

	cout << "\t\t ___________________________________________________________\n";
	cout << "\t\t|                                                           |\n";
	cout << "\t\t|                                                           |\n";	
	cout << "\t\t|                       Account Page                        |\n";
	cout << "\t\t|                                                           |\n";	
	cout << "\t\t|___________________________________________________________|\n";
	cout << "\t\t                                                             \n";
	cout << "\t\t                 Welcome! " << full_name << endl;
	cout << "\t\t                Account Number: " << account_number << endl;
	cout << "\t\t_____________________________________________________________\n";
	cout << "\t\t                                                             \n";
	cout << "\t\t                                                             \n";
	cout << "\t\tContact: " << contact << "\t\tUsername: " << username << endl;
	cout << "\n\t\tCNIC: " << cnic << "\t\tPassword: " << password << endl;
	cout << "\n\t\tAccount Type: " << account_type << "\t\tAge: " << age << endl;
	cout << "\n\n\n\t\tAccount Balance: " << balance << "\t\tRemaining Repayment: " << repayment << endl;
	cout << "\t\t                                                             \n";
	cout << "\t\t_____________________________________________________________\n";
	cout << "\t\t                                                             \n";
	cout << "\t\t                Enter 1 to Make a Transaction                \n";
	cout << "\t\t                 Enter 2 to Change Password                  \n";
	cout << "\t\t          Enter 3 to Logout and Return to Main Menu          \n";
	cout << "\t\t_____________________________________________________________\n";

	cout << "\n\n\t\t\tEnter Choice: ";
	cin >> ch1;

	if (ch1 == 1)	// <--- Executes if user wants to make a Transaction.
	{
		cout << "\t\t_____________________________________________________________\n";
		cout << "\t\t                                                             \n";
		cout << "\t\t                Select the type of Transaction               \n";
		cout << "\t\t_____________________________________________________________\n";
		cout << "\t\t                                                             \n";
		cout << "\t\t                    Enter 1 to Send money                    \n";
		cout << "\t\t                   Enter 2 to Repay credit                   \n";
		cout << "\t\t              Enter 3 to Return to Account page              \n";
		cout << "\t\t_____________________________________________________________\n";

		cout << "\n\n\t\t\tEnter Choice: ";
		cin >> ch2;

		if (ch2 == 1)	// <--- Executes if the user wants to send money.
		{
			system("cls");
			string temp;
			int amount;
			
			cout << "\n\nEnter Reciever's account number: ";
			cin >> temp;
			cout << "\n\nEnter the amount to send: ";
			cin >> amount;
			cout << "\n\nConfirm your transaction with your password: ";
			cin >> temp;

			if (temp == password)
			{
				balance = balance - amount; // <--- Updated balance after transaction.

				string file_name = "Records\\" + username + ".txt";
				string del_file_cmd = "del /s /q " + file_name;	// <--- DOS cmd to delete the current file, in order to store updated data in new file.			
				system(del_file_cmd.c_str()); // <--- Executing the cmd.
				system("cls");

				f.open("Records\\" + username + ".txt", ios::app);	// <--- Makes a "username".txt file again to store updated data.
				
				// Storing data in the file:
				f << username << endl << password << endl << account_number << endl;
				f << account_type << endl << balance << endl << repayment << endl;
				f << age << endl << contact << endl << cnic << endl << full_name << endl;
				f.close();

				cout << "\n\n\t\t\tTransaction Successful!";
			}
			else
				cout << "\n\n\t\t\tTransaction Failed!";

			cout << "\n\t\t\tPress Enter to return to Account Page...";
			cin.ignore();
			getchar();
			account_page(username);
		}

		else if (ch2 == 2)	// <--- Executes if the user wants to Repay credit.
		{
			system("cls");
			int amount;

			cout << "\n\nEnter the amount of credit to repay using existing balance: ";
			cin >> amount;
			
			// Updating data:
			repayment = repayment - amount;
			balance = balance - amount;

			string file_name = "Records\\" + username + ".txt";
			string del_file_cmd = "del /s /q " + file_name;	// <--- DOS cmd to delete the current file, to store updated data in new file.		
			system(del_file_cmd.c_str()); // <--- Executing the cmd.
			system("cls");

			f.open("Records\\" + username + ".txt", ios::app);	// <--- Makes a "username".txt file again to store updated data.
			
			// Storing data in the file:
			f << username << endl << password << endl << account_number << endl << account_type << endl << balance << endl << repayment << endl;
			f << age << endl << contact << endl << cnic << endl << full_name << endl;
			f.close();

			cout << "\n\n\t\t\tRepayment Successful!";
			cout << "\n\t\t\tPress Enter to return to Account Page...";
			cin.ignore();
			getchar();
			account_page(username);
		}

		else	// <--- Executes in case of 3, or invalid entry.
			account_page(username);
	}
	
	else if (ch1 == 2)	// <--- Executes if the user wants to change password.
	{
		system("cls");
		string new_pass, confirm_pass;
		cout << "\t\t_____________________________________________________________\n";
		cout << "\t\t                                                             \n";
		cout << "\t\t                   Enter new Password below                  \n";
		cout << "\t\t_____________________________________________________________\n";

		cout << "\n\nNew Password: ";
		cin >> new_pass;
		cout << "\n\nConfirm new Password: ";
		cin >> confirm_pass;

		if (new_pass == confirm_pass)
		{
			string file_name = "Records\\" + username + ".txt";
			string del_file_cmd = "del /s /q " + file_name;	// <--- DOS cmd to delete the current file, to store updated data in new file.		
			system(del_file_cmd.c_str()); // <--- Executing the cmd.
			system("cls");

			f.open("Records\\" + username + ".txt", ios::app);	// <--- Makes a "username".txt file again to store updated data.
			
			// Storing data in the file:
			f << username << endl << new_pass << endl << account_number << endl << account_type << endl << balance << endl << repayment << endl;
			f << age << endl << contact << endl << cnic << endl << full_name << endl;
			f.close();

			cout << "\n\n\t\t\tYour password has been changed!";
			cout << "\n\t\t\tPress Enter to return to Account Page...";
			cin.ignore();
			getchar();
			account_page(username);
		}

		else
		{
			cout << "\n\n\t\t\tBoth the entered passwords do not match!";
			cout << "\n\t\t\tPress Enter to return to Account Page...";
			cin.ignore();
			getchar();
			account_page(username);
		}
	}

	else if (ch1 == 3)	// <--- Executes if the user wants to Logout and go to main menu.
	{
		system("cls");
		cout << "\n\n\t\tYou have been logged out! Press ENTER to go back to main menu...";
		cin.ignore();
		getchar();
		main();
	}

	else	// <--- Executes if user enters anything invalid. 
		account_page(username);
}