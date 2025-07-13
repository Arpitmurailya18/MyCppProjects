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


class PasswordManager{
    private:
        string LoginUserName;
        string LoginPassword;
        vector<User> ListOfUsers; // container
    
    public:
        void saveToFile(); //To save the data
        void LoadToFile();  //To load the data
        void MainMenu();
        void addUser();  // TO add the user
        void deleteUser();  // to delete the User
        void updateUser();  // To display the User data
        void displayUser();  //To display the user data
        void searchUser(); //To search the user 
        void xorEncryptDecrypt(string &data, const string &key);
        void registerUser();  // To register the user 
        void LoginMainMenu();
        void login();  //For user login
        void logout();  // for user logout
};


void PasswordManager::saveToFile(){
    string ok;
}