#include <iostream>
#include <string>       // for using string functions like length()
#include <cctype>       // for isalpha() and isdigit()
#include <windows.h>    // for coloring
#include <fstream>      // for file handling

using namespace std;


// Colors function
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


// Structure for user
struct user
{
    string username;
    string password;    // Password contains alphabets, numbers and special characters
};


// Function for checking password
bool ValidPassword(string password)
{
    bool hasAlphabet = false;
    bool hasNumber = false;
    bool hasSpecial = false;

    for (int i = 0; i < password.length(); i++)
    {
        if (isalpha(password[i]))
        {
            hasAlphabet = true;
        }

        else if (isdigit(password[i]))
        {
            hasNumber = true;
        }

        else
        {
            hasSpecial = true;
        }
    }

    if (hasAlphabet && hasNumber && hasSpecial)
    {
        return true;
    }
    else
    {
        return false;
    }

} // ValidPassword function end



// Function for checking whether username already exists
bool UserExists(string username)
{
    ifstream file("users.txt");

    string storedUsername;
    string storedPassword;

    while (getline(file, storedUsername, '|') &&
           getline(file, storedPassword))
    {
        if (storedUsername == username)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}



// Registration function
int Registration()
{
    user u;

    setColor(7); // White

    cout << "\n========== REGISTRATION ==========\n";

    cout << "Enter user name: ";
    getline(cin, u.username);


    // Check duplicate username
    if (UserExists(u.username))
    {
        setColor(12); // Red

        cout << "\nUsername already exists!\n";

        setColor(7); // White

        return 0;
    }


    cout << "Enter Password: ";

password:

    getline(cin, u.password);


    // Check password
    if (ValidPassword(u.password))
    {
        setColor(3); // Blue

        cout << "Strong password.\n";
    }

    else
    {
        setColor(12); // Red

        cout << "Password must contain alphabets, numbers "
             << "and special characters.\n";

        setColor(3); // Blue

        cout << "Please enter password again: ";

        setColor(7); // White

        goto password;
    }


    // Open file for adding new user
    ofstream file("users.txt", ios::app);


    if (!file)
    {
        setColor(12); // Red

        cout << "Error opening file.\n";

        setColor(7); // White

        return 0;
    }


    // Save username and password in file
    file << u.username << "|" << u.password << endl;
    file.flush();
    file.close();


    setColor(10); // Light green

    cout << "\nRegistration successful!\n";

    setColor(7); // White

    return 0;
}



// Login function
int Login()
{
    user u;

    setColor(7); // White

    cout << "\n========== LOGIN ==========\n";

    cout << "Enter user name: ";
    getline(cin, u.username);

    cout << "Enter Password: ";
    getline(cin, u.password);


    ifstream file("users.txt");

    if (!file)
    {
        setColor(12); // Red

        cout << "\nNo registered users found.\n";

        setColor(7); // White

        return 0;
    }


    string storedUsername;
    string storedPassword;

    bool loginSuccessful = false;


    // Read users from file
    while (getline(file, storedUsername, '|') &&
           getline(file, storedPassword))
    {
        if (storedUsername == u.username &&
            storedPassword == u.password)
        {
            loginSuccessful = true;
            break;
        }
    }


    file.close();


    if (loginSuccessful)
    {
        setColor(10); // Green

        cout << "\nLogin successful! Welcome "
             << u.username << ".\n";
    }
    else
    {
        setColor(12); // Red

        cout << "\nInvalid username or password.\n";
    }


    setColor(7); // White

    return 0;
}



// Main function
int main()
{
    setColor(11); // Sky blue

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "       LOGIN AND REGISTRATION SYSTEM\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";


    int choice;


    while (true)
    {
        setColor(7); // White

        cout << "\n1. Register( create an account)\n";
        cout << "2. Login(if you have an account)\n";
        cout << "3. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        cin.ignore();


        if (choice == 1)
        {
            Registration();
        }

        else if (choice == 2)
        {
            Login();
        }

        else if (choice == 3)
        {
            setColor(11);

            cout << "\nThank you for using the system.\n";

            setColor(7);

            break;
        }

        else
        {
            setColor(12); // Red

            cout << "\nInvalid choice. Please try again.\n";

            setColor(7);
        }
    }


    return 0;
}
