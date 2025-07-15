#include<iostream> 
#include<fstream>
#include<string> //for string type data
#include<vector> //container

using namespace std;

//creating costom data type
struct User{
    string username;
    string password;
    string Accountname;
};

ostream& operator<<(ostream& os, const User& user) {
    os << "Username     : " << user.username << "\n";
    os << "Password     : " << user.password << "\n";
    os << "Account Name : " << user.Accountname << "\n";
    return os;
}

class PasswordManager{
    private:
        string LoginUserName;
        string LoginPassword;
        vector<User> ListOfUsers; // container
    
    public:
        void xorEncryptDecrypt(string &data, const char &key);
        void saveToFile(); //To save the data
        void LoadFromFile();  //To load the data
        void MainMenu();
        void addUser();  // TO add the user
        void deleteUser();  // to delete the User
        void updateUser();  // To display the User data
        void displayUsers();  //To display the user data
        void searchUser(); //To search the user 
        void registerUser();  // To register the user 
        void LoginMainMenu();
        void login();  //For user login
        void logout();  // for user logout
};

void PasswordManager::saveToFile() {
    ofstream file(LoginUserName + ".txt");
    if (file.is_open()) {
        file<<LoginUserName<<"\n";
        file<<LoginPassword<<"\n";
        for (const auto& user : ListOfUsers) {
            file << user.username << "\n";
            file << user.password << "\n";
            file << user.Accountname << "\n";
        }
        file.close();
    } else {
        cerr << "Error opening file for writing." << endl;
    }
}

void PasswordManager ::LoadFromFile() {
    ifstream file(LoginUserName + ".txt");
    if (file.is_open()) {
        getline(file, LoginUserName);
        getline(file, LoginPassword);
        User user;
        while (getline(file, user.username) && 
               getline(file, user.password) && 
               getline(file, user.Accountname))
        {
            ListOfUsers.push_back(user);
        }
        file.close();
    } else {
        cout << "Error opening file for reading." << endl;
    }
}

void PasswordManager::addUser() {
    User newUser;
    cout<< "Adding a new user" << endl;
    cout << "\n";
    cout << "Enter username: ";
    getline(cin, newUser.username);
    cout << "Enter password: ";
    getline(cin, newUser.password);
    cout << "Enter account name: ";
    getline(cin, newUser.Accountname);
    
    ListOfUsers.push_back(newUser);
    cout << "User added successfully!" << endl;
}

void PasswordManager::deleteUser() {
    string username;
    cout<< "Deleting a user" << endl;
    cout << "\n";
    cout << "Enter username to delete: ";
    getline(cin, username);

    for( auto it = ListOfUsers.begin(); it != ListOfUsers.end(); ++it) {
        if (it->username == username) {
            ListOfUsers.erase(it);
            cout << "User deleted successfully!" << endl;
            return;
        }
    }
    cout << "User not found." << endl;

}

void PasswordManager::updateUser() {
    string username;
    cout<< "Updating a user password" << endl;
    cout << "\n";
    cout << "Enter username to update: ";
    getline(cin, username);
    
    for (auto& user : ListOfUsers) {
        if (user.username == username) {
            cout << "Enter new password: ";
            getline(cin, user.password);
            cout << "Confirm new password: ";
            getline(cin, user.password);
            cout << "User updated successfully!" << endl;
            return;
        }
    }
    cout << "User not found." << endl;
}

void PasswordManager::displayUsers() {
    if (ListOfUsers.empty()) {
        cout << "No users found." << endl;
        return;
    }
    
    cout << "List of Users:" << endl;
    for (auto& user : ListOfUsers) {
        cout << user << endl; // Using the overloaded operator<< to display user details
    }
}

void PasswordManager::searchUser() {
    string username;
    cout<< "Searching for a user" << endl;
    cout << "\n";
    cout << "Enter username to search: ";
    getline(cin, username);
    
    for (const auto& user : ListOfUsers) {
        if (user.username == username) {
            cout << "User found!" << endl;
            cout << user << "\n"; // Using the overloaded operator<< to display user details
            return;
        }
    }
    cout << "User not found." << endl;
}

void PasswordManager::LoginMainMenu(){
    // Implementation of the login main menu
    
    int choice;
    do{
        cout << "Welcome to the Password Manager!" << endl;
        cout << "------------------------------" << endl;
        cout << "Please choose an option:" << endl;
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer
        system("cls"); // Clear the console screen
        switch(choice){
            case 1:
                registerUser();
                break;
            case 2:
                login();
                break;
            case 3:
                cout << "Exiting the Password Manager. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    }while(choice != 3);
}

void PasswordManager::registerUser() {
    string inputUserName, inputPassword;
    cout << "Register a new user" << endl;
    cout << "Enter username: ";
    getline(cin, inputUserName);
    cout << "Enter password: ";
    getline(cin, inputPassword);

    ifstream file(inputUserName + ".txt");
    if(file.is_open()){
        cerr << "User already exists. Please choose a different username." << endl;
        file.close();
    }else{
        LoginUserName = inputUserName;
        LoginPassword = inputPassword;
        saveToFile();
        cout << "User registered successfully!" << endl;
        file.close();
    }
}

void PasswordManager::login() {
    string inputUserName, inputPassword;
    cout << "Login to your account" << endl;
    cout << "Enter username: ";
    getline(cin, inputUserName);
    
    ifstream file(inputUserName + ".txt");
    if(file.is_open()) {
        file.close();
        LoginUserName = inputUserName;
        LoadFromFile();
        cout << "Enter password: ";
        getline(cin, inputPassword);
        if (inputPassword == LoginPassword) {
            cout << "Login successful!" << endl;  
            MainMenu();
        } else {
            cout << "Invalid password. Please try again." << endl;
        }
    }else{
        cout << "User does not exist. Please register first." << endl;
    }

}

void PasswordManager::logout() {
    saveToFile();
    LoginUserName.clear(); // Clear the username
    LoginPassword.clear(); // Clear the password
    ListOfUsers.clear(); // Clear the user list
    cout << "Logged out successfully!" << endl;
}

void PasswordManager::MainMenu() {
    int choice;
    do {
        cout << "Welcome to the Password Manager!" << endl;
        cout<<"\n";
        cout << "1. Add User" << endl;
        cout << "2. Delete User" << endl;
        cout << "3. Update User" << endl;
        cout << "4. Display Users" << endl;
        cout << "5. Search User" << endl;
        cout << "6. Logout" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer
        system("cls"); // Clear the console screen
        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                deleteUser();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                displayUsers();
                break;
            case 5:
                searchUser();
                break;
            case 6:
                logout();
                break;
            case 7:
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);
}

int main() {
    PasswordManager pm;
    pm.LoginMainMenu(); // Start the application with the login main menu
    cout << "Thank you for using the Password Manager!" << endl;

    return 0;
}