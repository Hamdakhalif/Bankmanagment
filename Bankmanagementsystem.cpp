//
// Created by Hamda Khalif on 2024-01-01.
//

#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 50
#define INTEREST_RATE 0.02

// Structure to represent a bank account
struct BankAccount {
    int accountNumber;
    char accountHolderName[50];
    char password[20];
    float balance;
    float interestRate;
    float transactionHistory[100];
    int numTransactions;
};

// Function prototypes
void displayMenu();
void createAccount(struct BankAccount accounts[], int* numAccounts);
void authenticateUser(struct BankAccount accounts[], int numAccounts, int* loggedInAccount);
void deposit(struct BankAccount accounts[], int loggedInAccount);
void withdraw(struct BankAccount accounts[], int loggedInAccount);
void checkBalance(struct BankAccount accounts[], int loggedInAccount);
void calculateInterest(struct BankAccount accounts[], int loggedInAccount);
void displayTransactionHistory(struct BankAccount accounts[], int loggedInAccount);
void displayAccountDetails(struct BankAccount accounts[], int loggedInAccount);

int main() {
    struct BankAccount accounts[MAX_ACCOUNTS];
    int numAccounts = 0;
    int loggedInAccount = -1;
    int choice;

    do {
        displayMenu();

        if (loggedInAccount == -1) {
            printf("Enter your choice: ");
        } else {
            printf("Enter your choice (logged in as %s): ", accounts[loggedInAccount].accountHolderName);
        }

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount(accounts, &numAccounts);
                break;
            case 2:
                authenticateUser(accounts, numAccounts, &loggedInAccount);
                break;
            case 3:
                deposit(accounts, loggedInAccount);
                break;
            case 4:
                withdraw(accounts, loggedInAccount);
                break;
            case 5:
                checkBalance(accounts, loggedInAccount);
                break;
            case 6:
                calculateInterest(accounts, loggedInAccount);
                break;
            case 7:
                displayTransactionHistory(accounts, loggedInAccount);
                break;
            case 8:
                displayAccountDetails(accounts, loggedInAccount);
                break;
            case 9:
                printf("Exiting the Bank Management System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}

void displayMenu() {
    printf("\nBank Management System Menu:\n");
    printf("1. Create Account\n");
    printf("2. Login\n");
    printf("3. Deposit Money\n");
    printf("4. Withdraw Money\n");
    printf("5. Check Balance\n");
    printf("6. Calculate Interest\n");
    printf("7. Display Transaction History\n");
    printf("8. Display Account Details\n");
    printf("9. Exit\n");
}

void createAccount(struct BankAccount accounts[], int* numAccounts) {
    if (*numAccounts < MAX_ACCOUNTS) {
        printf("Enter account holder name: ");
        scanf("%s", accounts[*numAccounts].accountHolderName);

        printf("Set a password: ");
        scanf("%s", accounts[*numAccounts].password);

        // Generate a unique account number (can use *numAccounts + 1)
        accounts[*numAccounts].accountNumber = *numAccounts + 1;

        accounts[*numAccounts].balance = 0.0;
        accounts[*numAccounts].interestRate = INTEREST_RATE;
        accounts[*numAccounts].numTransactions = 0;

        printf("Account created successfully!\n");
        (*numAccounts)++;
    } else {
        printf("Sorry, the maximum number of accounts has been reached.\n");
    }
}

void authenticateUser(struct BankAccount accounts[], int numAccounts, int* loggedInAccount) {
    char accountHolderName[50];
    char password[20];

    printf("Enter account holder name: ");
    scanf("%s", accountHolderName);

    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numAccounts; ++i) {
        if (strcmp(accountHolderName, accounts[i].accountHolderName) == 0 &&
            strcmp(password, accounts[i].password) == 0) {
            *loggedInAccount = i;
            printf("Login successful!\n");
            return;
        }
    }

    printf("Login failed. Invalid account holder name or password.\n");
}

void deposit(struct BankAccount accounts[], int loggedInAccount) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    accounts[loggedInAccount].balance += amount;

    // Update transaction history
    accounts[loggedInAccount].transactionHistory[accounts[loggedInAccount].numTransactions] = amount;
    accounts[loggedInAccount].numTransactions++;

    printf("Amount deposited successfully!\n");
}

void withdraw(struct BankAccount accounts[], int loggedInAccount) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount <= accounts[loggedInAccount].balance) {
        accounts[loggedInAccount].balance -= amount;

        // Update transaction history
        accounts[loggedInAccount].transactionHistory[accounts[loggedInAccount].numTransactions] = -amount;
        accounts[loggedInAccount].numTransactions++;

        printf("Amount withdrawn successfully!\n");
    } else {
        printf("Insufficient funds. Withdrawal failed.\n");
    }
}

void checkBalance(struct BankAccount accounts[], int loggedInAccount) {
    printf("Account Balance: %.2f\n", accounts[loggedInAccount].balance);
}

void calculateInterest(struct BankAccount accounts[], int loggedInAccount) {
    float interest = accounts[loggedInAccount].balance * accounts[loggedInAccount].interestRate;
    accounts[loggedInAccount].balance += interest;

    // Update transaction history
    accounts[loggedInAccount].transactionHistory[accounts[loggedInAccount].numTransactions] = interest;
    accounts[loggedInAccount].numTransactions++;

    printf("Interest calculated and added to the account: %.2f\n", interest);
}

void displayTransactionHistory(struct BankAccount accounts[], int loggedInAccount) {
    printf("Transaction History:\n");

    for (int i = 0; i < accounts[loggedInAccount].numTransactions; ++i) {
        if (accounts[loggedInAccount].transactionHistory[i] > 0) {
            printf("Deposit: %.2f\n", accounts[loggedInAccount].transactionHistory[i]);
        } else {
            printf("Withdrawal: %.2f\n", -accounts[loggedInAccount].transactionHistory[i]);
        }
    }
}

void displayAccountDetails(struct BankAccount accounts[], int loggedInAccount) {
    printf("Account Details:\n");
    printf("Account Number: %d\n", accounts[loggedInAccount].accountNumber);
    printf("Account Holder Name: %s\n", accounts[loggedInAccount].accountHolderName);
    printf("Account Balance: %.2f\n", accounts[loggedInAccount].balance);
    printf("Interest Rate: %.2f%%\n", accounts[loggedInAccount].interestRate * 100);
    printf("Number of Transactions: %d\n", accounts[loggedInAccount].numTransactions);
}
