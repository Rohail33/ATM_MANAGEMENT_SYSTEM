#include "account_management.h"
#include <iomanip>
#include <limits>

// global vars
Account* head = nullptr;
int counter = 1000;
Transaction stackArr[MAX_TRANS];
int topIndex = -1;
Transaction queueArr[MAX_TRANS];
int frontIndex = -1, rearIndex = -1;

// ============================================
// init system
// ============================================
void initSystem() {
	head = nullptr;
	counter = 1000;
	topIndex = -1;
	frontIndex = -1;
	rearIndex = -1;
	cout << "ATM System Initilized Successfully! " << endl;
}

// ============================================
// create account
// ============================================
bool createAcc(string name, int pin, double firstDep) {
	if (name.empty()) {
		cout << "Error! Name Cannot be empty!" << endl;
		return false;
	}
	if (pin < 1000 || pin > 9999) {
		cout << "Error! Pin must be of 4 digits." << endl;
		return false;
	}
	if (firstDep < 0) {
		cout << "Error! Initial Deposite can not be negative." << endl;
		return false;
	}

	counter++;
	Account* newAcc = new Account;
	newAcc->accountNumber = counter;
	newAcc->holder = name;
	newAcc->pin = pin;
	newAcc->balance = firstDep;
	newAcc->next = nullptr;

	if (head == nullptr)
		head = newAcc;
	else {
		Account* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newAcc;
	}
	cout << "\n==================================" << endl;
	cout << "   ACCOUNT CREATED SUCCESSFULLY   " << endl;
	cout << "==================================" << endl;
	cout << "Account Number: " << counter << endl;
	cout << "Account Holder: " << name << endl;
	cout << "Initial Deposite: $" << fixed << setprecision(2) << firstDep << endl;
	cout << "==================================" << endl;

	return true;
}

// ============================================
// search account
// ============================================
Account* searchAcc(int AccNumber) {
	Account* temp = head;
	while (temp != nullptr) {
		if (temp->accountNumber == AccNumber) {
			return temp;
		}
		temp = temp->next;
	}
	return nullptr;
}

// ============================================
// delete account
// ============================================
bool deleteAcc(int AccNumber) {
	if (head == nullptr) {
		cout << "No Account Exists!" << endl;
		return false;
	}

	Account* temp = head;
	Account* prev = nullptr;

	if (temp != nullptr && temp->accountNumber == AccNumber) {
		head = temp->next;
		delete temp;
		cout << "Sucessfully Deleted: " << AccNumber << endl;
		return true;
	}
	while (temp != nullptr && temp->accountNumber != AccNumber) {
		prev = temp;
		temp = temp->next;
	}
	if (temp == nullptr) {
		cout << "Error! Account Not Found." << endl;
		return false;
	}
	prev->next = temp->next;
	delete temp;
	cout << "Sucessfully Deleted: " << AccNumber << endl;
	return true;
}

// ============================================
// display all accounts
// ============================================
void DisplayAllAcc() {
	if (head == nullptr) {
		cout << "Error! No Accounts in System!" << endl;
		return;
	}
	cout << "\n========================================" << endl;
	cout << "         ALL ACCOUNTS IN SYSTEM         " << endl;
	cout << "========================================" << endl;
	cout << left << setw(12) << "Acc No."
		<< setw(20) << "Holder Name"
		<< setw(15) << "Balance" << endl;
	cout << "----------------------------------------" << endl;

	Account* temp = head;
	while (temp != nullptr) {
		cout << left << setw(12) << temp->accountNumber
			<< setw(20) << temp->holder
			<< "$" << fixed << setprecision(2) << temp->balance << endl;
		temp = temp->next;
	}

	cout << "========================================" << endl;
}

// ============================================
// update balance
// ============================================
bool UpdateBalance(int AccNumber, double NewBalance) {
	Account* account = searchAcc(AccNumber);
	if (account == nullptr) {
		cout << "Error! Account not found!" << endl;
		return false;
	}
	account->balance = NewBalance;
	return true;
}

// ============================================
// validate pin
// ============================================
bool validatePin(int AccNumber, int pin) {
	Account* account = searchAcc(AccNumber);
	if (account == nullptr) {
		return false;
	}
	return (account->pin == pin);
}

// ============================================
// login
// ============================================
Account* login() {
	int accountNumber, pin;
	int attempts = 0;
	const int MAX_ATTEMPTS = 3;

	while (attempts < MAX_ATTEMPTS) {
		cout << "\n==================================" << endl;
		cout << "          ACCOUNT LOGIN           " << endl;
		cout << "==================================" << endl;
		cout << "Enter Account Number: ";
		cin >> accountNumber;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error! Invalid input! Please enter numbers only." << endl;
			attempts++;
			continue;
		}

		Account* account = searchAcc(accountNumber);

		if (account == nullptr) {
			cout << "Error! Account not found!" << endl;
			attempts++;
			cout << "Attempts remaining: " << (MAX_ATTEMPTS - attempts) << endl;
			continue;
		}

		cout << "Enter 4-digit PIN: ";
		cin >> pin;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error! Invalid PIN format!" << endl;
			attempts++;
			continue;
		}

		if (validatePin(accountNumber, pin)) {
			cout << "Login successful!" << endl;
			cout << "Welcome, " << account->holder << "!" << endl;
			return account;
		}
		else {
			cout << "Error! Incorrect PIN!" << endl;
			attempts++;
			cout << "Attempts remaining: " << (MAX_ATTEMPTS - attempts) << endl;
		}
	}

	cout << "Too many failed attempts. Access denied!" << endl;
	return nullptr;
}

// ============================================
// check if empty
// ============================================
bool isEmpty() {
	return (head == nullptr);
}

// ============================================
// get total accounts
// ============================================
int getTotalAcc() {
	int count = 0;
	Account* temp = head;
	while (temp != nullptr) {
		count++;
		temp = temp->next;
	}
	return count;
}

// ============================================
// clear all accounts
// ============================================
void clearAllAcc() {
	Account* current = head;
	Account* next = nullptr;

	while (current != nullptr) {
		next = current->next;
		delete current;
		current = next;
	}

	head = nullptr;
	topIndex = -1;
	frontIndex = -1;
	rearIndex = -1;
	cout << "All accounts cleared from memory." << endl;
}

// ============================================
// menu functions
// ============================================
void DisplayMainMenu() {
	cout << "\n========================================" << endl;
	cout << "     ATM MANAGEMENT SYSTEM - MAIN       " << endl;
	cout << "========================================" << endl;
	cout << "1. Create New Account" << endl;
	cout << "2. Login to Existing Account" << endl;
	cout << "3. Display All Accounts (Admin)" << endl;
	cout << "4. Delete Account (Admin)" << endl;
	cout << "5. Exit" << endl;
	cout << "========================================" << endl;
	cout << "Enter your choice: ";
}

void DisplayAccMenu() {
	cout << "\n========================================" << endl;
	cout << "          ACCOUNT OPERATIONS            " << endl;
	cout << "========================================" << endl;
	cout << "1. Check Balance" << endl;
	cout << "2. Deposit Money" << endl;
	cout << "3. Withdraw Money" << endl;
	cout << "4. Transaction History" << endl;
	cout << "5. Undo Last Transaction" << endl;
	cout << "6. Enqueue Transaction (Pending)" << endl;
	cout << "7. Process Next Pending Transaction" << endl;
	cout << "8. Show Pending Queue" << endl;
	cout << "9. Logout" << endl;
	cout << "========================================" << endl;
	cout << "Enter your choice: ";
}

void ClearScreen() {
	system("cls");
}

void PauseScreen() {
	cout << "\nPress Enter to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

// ============================================
//  TRANSACTIONS
// ============================================
// get current time
string getTime() {
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);
	char buff[30];
	strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", &localTime);
	return string(buff);
}

// ============================================
// stack operations (undo)
// ============================================
void pushTrans(Transaction t) {
	if (topIndex < MAX_TRANS - 1) {
		stackArr[++topIndex] = t;
	}
	else {
		cout << "Undo Stack Full" << endl;
	}
}

Transaction popTrans() {
	if (topIndex == -1) {
		Transaction t;
		t.type = "none";
		return t;
	}
	return stackArr[topIndex--];
}

void showHistory() {
	if (topIndex == -1) {
		cout << "No Transaction History" << endl;
		return;
	}
	cout << "\n========================================" << endl;
	cout << "       TRANSACTION HISTORY              " << endl;
	cout << "========================================" << endl;
	for (int i = topIndex; i >= 0; i--) {
		cout << (topIndex - i + 1) << ". " << stackArr[i].type
			<< " | $" << fixed << setprecision(2) << stackArr[i].amount
			<< " | " << stackArr[i].timestamp
			<< " | Acc: " << stackArr[i].accountNumber << endl;
	}
	cout << "========================================" << endl;
}

bool isStackEmpty() {
	return (topIndex == -1);
}

// ============================================
// queue operations (pending transactions)
// ============================================
void enqueueTrans(Transaction t) {
	if (rearIndex == MAX_TRANS - 1) {
		cout << "Queue Full" << endl;
		return;
	}
	if (frontIndex == -1) frontIndex = 0;
	queueArr[++rearIndex] = t;
	cout << "Transaction added to pending queue | Account: " << t.accountNumber << endl;
}

Transaction dequeueTrans() {
	if (frontIndex == -1 || frontIndex > rearIndex) {
		Transaction t;
		t.type = "none";
		return t;
	}
	return queueArr[frontIndex++];
}

void showQueue() {
	if (frontIndex == -1 || frontIndex > rearIndex) {
		cout << "Queue Empty" << endl;
		return;
	}
	cout << "\n========================================" << endl;
	cout << "       PENDING TRANSACTIONS             " << endl;
	cout << "========================================" << endl;
	for (int i = frontIndex; i <= rearIndex; i++) {
		cout << (i - frontIndex + 1) << ". " << queueArr[i].type
			<< " | $" << fixed << setprecision(2) << queueArr[i].amount
			<< " | Acc: " << queueArr[i].accountNumber << endl;
	}
	cout << "========================================" << endl;
}

bool isQueueEmpty() {
	return (frontIndex == -1 || frontIndex > rearIndex);
}

// ============================================
// transaction operations
// ============================================
void deposit(Account* acc, double amt) {
	if (amt <= 0) {
		cout << "Invalid Amount" << endl;
		return;
	}
	acc->balance += amt;
	Transaction t;
	t.type = "deposit";
	t.amount = amt;
	t.timestamp = getTime();
	t.accountNumber = acc->accountNumber;
	pushTrans(t);
	cout << "Deposit Successful | Account: " << acc->accountNumber
		<< " | Amount: $" << fixed << setprecision(2) << amt << endl;
	cout << "New Balance: $" << acc->balance << endl;
}

void withdraw(Account* acc, double amt) {
	if (amt <= 0) {
		cout << "Invalid Amount" << endl;
		return;
	}
	if (amt > acc->balance) {
		cout << "Insufficient Balance" << endl;
		return;
	}
	acc->balance -= amt;
	Transaction t;
	t.type = "withdraw";
	t.amount = amt;
	t.timestamp = getTime();
	t.accountNumber = acc->accountNumber;
	pushTrans(t);
	cout << "Withdrawal Successful | Account: " << acc->accountNumber
		<< " | Amount: $" << fixed << setprecision(2) << amt << endl;
	cout << "New Balance: $" << acc->balance << endl;
}

void checkBal(Account* acc) {
	cout << "\n========================================" << endl;
	cout << "         ACCOUNT BALANCE                " << endl;
	cout << "========================================" << endl;
	cout << "Account Number: " << acc->accountNumber << endl;
	cout << "Account Holder: " << acc->holder << endl;
	cout << "Current Balance: $" << fixed << setprecision(2) << acc->balance << endl;
	cout << "========================================" << endl;
}

void undoLast() {
	Transaction last = popTrans();
	if (last.type == "none") {
		cout << "No transactions to undo" << endl;
		return;
	}
	Account* acc = searchAcc(last.accountNumber);
	if (acc == nullptr) {
		cout << "Error! Account not found for undo!" << endl;
		return;
	}
	if (last.type == "deposit") {
		acc->balance -= last.amount;
		cout << "Undo Deposit | Account: " << last.accountNumber
			<< " | Amount: $" << fixed << setprecision(2) << last.amount << endl;
	}
	else if (last.type == "withdraw") {
		acc->balance += last.amount;
		cout << "Undo Withdrawal | Account: " << last.accountNumber
			<< " | Amount: $" << fixed << setprecision(2) << last.amount << endl;
	}
	cout << "New Balance: $" << acc->balance << endl;
}

void processNext() {
	Transaction t = dequeueTrans();
	if (t.type == "none") {
		cout << "No pending transactions" << endl;
		return;
	}
	Account* acc = searchAcc(t.accountNumber);
	if (acc == nullptr) {
		cout << "Account not found for transaction." << endl;
		return;
	}
	if (t.type == "deposit") {
		acc->balance += t.amount;
		cout << "Processed Deposit of $" << fixed << setprecision(2)
			<< t.amount << " to Account: " << t.accountNumber << endl;
		t.timestamp = getTime();
		pushTrans(t);
	}
	else if (t.type == "withdraw") {
		if (t.amount > acc->balance) {
			cout << "Cannot Process (Insufficient Balance) | Account: "
				<< t.accountNumber << endl;
			return;
		}
		acc->balance -= t.amount;
		cout << "Processed Withdrawal of $" << fixed << setprecision(2)
			<< t.amount << " from Account: " << t.accountNumber << endl;
		t.timestamp = getTime();
		pushTrans(t);
	}
	cout << "New Balance: $" << acc->balance << endl;
}