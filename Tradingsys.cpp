#include <bits/stdc++.h>
using namespace std;
bool isValidUsername(const string& username) {
    if (username.length() < 2 || username.length() > 15) {
        return false;
    }
    for (char ch : username) {
        if (!isalnum(ch)) {
            return false;
        }
    }
    return true;
}

bool askRetry() {
    char choice;
    cout << "Would you like to reenter the information (y/n)? ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        return true;  // Retry the process
    }
    cout << "Exiting registration process." << endl;
    return false;  // Exit the process
}

bool isValidPassword(const string& password) {
    if (password.length() < 8) {
        return false;
    }
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char ch : password) {
        if (isupper(ch)) hasUpper = true;
        if (islower(ch)) hasLower = true;
        if (isdigit(ch)) hasDigit = true;
        if (ispunct(ch)) hasSpecial = true;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

bool isValidEmail(const string& email) {
    const regex pattern("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
    return regex_match(email, pattern);
}

bool isValidPhone(const string& phone) {
    const regex pattern("^\\+?\\d{10}$");
    return regex_match(phone, pattern);
}

class User {
public:
    User() : username(""), password(""), balance(0.0), email(""), phone("") {}  // Default constructor
    User(string username, string password, double balance, string email, string phone) 
    : username(username), password(password), balance(balance), email(email), phone(phone) {}


    string getUsername() const {
        return username;
    }

    void setBalance(double balance) {
        this->balance = balance;
    }

    double getBalance() const {
        return balance;
    }
    string getEmail() const {
        return email;
    }

    void setEmail(const string& email) {
        this->email = email;
    }

    string getPhone() const {
        return phone;
    }

    void setPhone(const string& phone) {
        this->phone = phone;
    }
    bool validatePassword(const string& inputPassword) const {
        return inputPassword == password; // Compare the input password with the stored password
    }
    void resetPassword(const string& newPassword) {
        password = newPassword;
    }

private:
    string username;
    string password;
    double balance;
    string email;  
    string phone;
};

class Transaction {
public:
    Transaction(string type, double amount) : type(type), amount(amount) {
        time(&timestamp);
    }

    void display(long long i) const {
        string timeStrFormatted = ctime(&timestamp);
        cout <<i<< ". Transaction Type: " << type << ", Amount: " << amount << ", Time: " << timeStrFormatted;
    }

private:
    string type;
    double amount;
    time_t timestamp;
};

class TradingSystem {
public:
    TradingSystem() : currentUser(nullptr) {}
    
    void registerUser() {
        string username, password, email, phone;
        double initialBalance;
        while (true) {
            label1:
            cout << "Enter Username: ";
            cin >> username;
            if (!isValidUsername(username)) {
                cout << "Invalid username. It should be 5-15 characters long and contain only letters and numbers.\n";
                if (askRetry()) goto label1;
                else {
                    cout<<"No Registration done\n";
                    return;
                } 
            }
            label2:
            cout << "Enter Password: ";
            cin >> password;
            if (!isValidPassword(password)) {
                cout << "Invalid password. It should contain at least 8 characters, with at least one uppercase letter, one lowercase letter, one digit, and one special character.\n";
                if (askRetry()) goto label2;
                else {
                    cout<<"No Registration done\n";
                    return;
                }
            }

            cout << "Enter Initial Balance: ";
            cin >> initialBalance;

            label3:
            cout << "Enter Email: ";
            cin >> email;
            if (!isValidEmail(email)) {
                cout << "Invalid email format.\n";
                if (askRetry()) goto label3;
                else {
                    cout<<"No Registration done\n";
                    return;
                } 
            }

            label4:
            cout << "Enter Phone Number: ";
            cin >> phone;
            if (!isValidPhone(phone)) {
                cout << "Invalid phone number format. It should be a 10-digit number.\n";
                if (askRetry()) goto label4;
                else {
                    cout<<"No Registration done\n";
                    return;
                }
            }

            if (users.find(username) != users.end()) {
                cout << "Username already exists!" << endl;
                cout<<"Would you like to do New Registration(r/R) or login(l/L) to you Account?\n";
                char c;cin>>c;
                if(c=='r' || c=='R') goto label1;
                else if(c=='l' || c=='L')login(username,password);
                else cout<<"Invalid input\n";
            }

            users[username] = User(username, password, initialBalance, email, phone);
            cout << "User registered successfully!" << endl;
            cout << "Thank You for Registering<3\n";
            break;
        }
    }

    bool login(string username, string password) {
        auto it = users.find(username);
        if (it != users.end() && it->second.validatePassword(password)) {
            currentUser = &it->second;
            cout << "Login successful!" << endl;
            return true;
        }
        cout<<"Forgot Password?\nYes(y/Y) or No(n/N): ";
        char p;cin>>p;
        if(p=='y' || p=='Y'){
            auto it = users.find(username);
            if (it != users.end()) {
                string recoveryChoice;
                cout << "Would you like to reset your password using your email or phone? (e/p): ";
                cin >> recoveryChoice;
    
                if (recoveryChoice == "e" || recoveryChoice == "E") {
                    
                    string email;
                    cout << "Enter your registered email: ";
                    cin >> email;
    
                    if (email == it->second.getEmail()) {
                        string newPassword;
                        cout << "Enter your new password: ";
                        cin >> newPassword;
                        it->second.resetPassword(newPassword);
                        cout << "Password reset successfully! Your new password is: " << newPassword << endl;
                    } else {
                        cout << "Email does not match our records." << endl;
                    }
                } else if (recoveryChoice == "p" || recoveryChoice == "P") {
                    string phone;
                    cout << "Enter your registered phone number: ";
                    cin >> phone;
    
                    if (phone == it->second.getPhone()) {
                        string newPassword;
                        cout << "Enter your new password: ";
                        cin >> newPassword;
                        it->second.resetPassword(newPassword);
                        cout << "Password reset successfully!\nYour new password is: " << newPassword << endl;
                        
                    } else {
                        cout << "Phone number does not match our records." << endl;
                        
                    }
                } else {
                    cout << "Invalid choice. Try again!" << endl;
                }
            } else {
                cout << "Username not found!" << endl;
            }
         }
        else {
            cout << "You can't Login!\n\nSorry we can't help :(" << endl;
            
        }
        return false;
        
    }
    void forgotPassword(string username) {
        
    }
    User* getCurrentUser() {
        return currentUser;
    }

    void deposit(double amount) {
        if (currentUser != nullptr) {
            currentUser->setBalance(currentUser->getBalance() + amount);
            Transaction t("Deposit", amount);
            transactions.push_back(t);
            cout << "\nDeposit successful.\nNew balance: " << currentUser->getBalance() << endl;
        } else {
            cout << "No user logged in!" << endl;
        }
    }

    void withdraw(double amount) {
        if (currentUser != nullptr) {
            if (currentUser->getBalance() >= amount) {
                currentUser->setBalance(currentUser->getBalance() - amount);
                Transaction t("Withdrawal", amount);
                transactions.push_back(t);
                cout << "\nWithdrawal successful.\nNew balance: " << currentUser->getBalance() << endl;
            } else {
                cout << "Insufficient balance!" << endl;
            }
        } else {
            cout << "No user logged in!" << endl;
        }
    }

    void viewTransactions() const {
        cout << "\n***** Transaction History *****\n";
        if(transactions.empty()) cout<<"\n\n  No Transactions done till now!\n\n"<<endl;
        long long i=1;
        for (const auto& t : transactions) {
            t.display(i);i++;
            cout << "-------------------------------\n";
        }
        
    }
    void viewUserDetails() const {
        if (currentUser != nullptr) {
            cout << "\nUser Details:\n";
            cout << "Username: " << currentUser->getUsername() << endl;
            cout << "Balance: " << currentUser->getBalance() << endl;
            cout << "Email: " << currentUser->getEmail() << endl;
            cout << "Phone: " << currentUser->getPhone() << endl;
        } else {
            cout << "No user logged in!" << endl;
        }
    }

    void showBalance() const {
        if (currentUser != nullptr) {
            cout << "\nCurrent Balance: " << currentUser->getBalance() << endl;
        } else {
            cout << "No user logged in!" << endl;
        }
    }
    void updateEmail(string newEmail) {
        if (currentUser != nullptr) {
            currentUser->setEmail(newEmail);
            cout << "Email updated successfully!" << endl;
        } else {
            cout << "No user logged in!" << endl;
        }
    }
    
    void updatePhone(string newPhone) {
        if (currentUser != nullptr) {
            currentUser->setPhone(newPhone);
            cout << "Phone number updated successfully!" << endl;
        } else {
            cout << "No user logged in!" << endl;
        }
    }

    bool isUserLoggedIn() {
        return currentUser != nullptr;
    }

private:
    unordered_map<string, User> users;
    vector<Transaction> transactions;
    User* currentUser;
};

int main() {
    TradingSystem system;

    int choice;
    string username, password,email,phone;
    double amount;

    while (true) {
        // Display options based on whether user is logged in or not
        if (!system.isUserLoggedIn()) {
            label:
            cout << "\n========== Trading System ==========\n";
            cout << "1. Register\n2. Login\n3. Exit\n";
            cout << "=====================================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    system.registerUser();
                    break;

                case 2:
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> password;
                    system.login(username, password);
                    break;

                case 3:
                    cout << "Exiting system.\n";
                    return 0;

                default:
                    cout << "Invalid choice! Try again.\n";
            }
        } else {
            cout << "\n========== Welcome " << username << " ==========\n";
            cout << "1. Deposit\n2. Withdraw\n3. View Transactions\n4. View Balance\n5.View Your Details\n6.Upadate Email or Phone number or both\n7. Logout\n";
            cout << "=========================================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter deposit amount: ";
                    cin >> amount;
                    system.deposit(amount);
                    break;

                case 2:
                    cout << "Enter withdrawal amount: ";
                    cin >> amount;
                    system.withdraw(amount);
                    break;

                case 3:
                    system.viewTransactions();
                    break;

                case 4:
                    system.showBalance();
                    break;
                    
                case 5: // View user details
                    system.viewUserDetails();
                    break;

                case 6:
                        cout << "1. Update Email\n2. Update Phone Number\n3. Update both\n";
                        cout << "-------------------------------------\n";
                        cout << "Enter your choice: ";
                        cin >> choice;
                        if (choice == 1) {
                            cout << "Enter new email: ";
                            cin >> email;
                            system.updateEmail(email);
                        } else if (choice == 2) {
                            cout << "Enter new phone number: ";
                            cin >> phone;
                            system.updatePhone(phone);
                        } else if (choice == 3) {
                            cout << "Enter new email: ";
                            cin >> email;
                            cout << "Enter new phone number: ";
                            cin >> phone;
                            system.updateEmail(email);
                            system.updatePhone(phone);
                        } else {
                            cout << "Invalid choice! Try again.\n";
                        }
                        break;
                                
                case 7:
                    cout << "Logging out...\n";
                    system.login("", "");  // Log out by clearing currentUser
                    goto label;

                default:
                    cout << "Invalid choice! Try again.\n";
                    
            }
            
        }
    }

    return 0;
} 
