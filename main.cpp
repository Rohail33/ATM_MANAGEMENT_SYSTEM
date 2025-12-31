#include "account_management.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	initSystem();

	int choice;
	bool running = true;

	cout << "\n========================================" << endl;
	cout << "  WELCOME TO ATM MANAGEMENT SYSTEM     " << endl;
	cout << "========================================" << endl;

	while (running) {
		DisplayMainMenu();
		cin >> choice;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error! Invalid input! Please enter a number." << endl;
			PauseScreen();
			continue;
		}

		switch (choice) {
		case 1: {
			ClearScreen();
			string name;
			int pin;
			double initialDeposit;

			cout << "\n==================================" << endl;
			cout << "      CREATE NEW ACCOUNT          " << endl;
			cout << "==================================" << endl;

			cin.ignore();
			cout << "Enter Account Holder Name: ";
			getline(cin, name);

			cout << "Enter 4-digit PIN: ";
			cin >> pin;

			cout << "Enter Initial Deposit (minimum $0): $";
			cin >> initialDeposit;

			createAcc(name, pin, initialDeposit);
			PauseScreen();
			break;
		}

		case 2: {
			ClearScreen();
			Account* loggedInAccount = login();

			if (loggedInAccount != nullptr) {
				bool loggedIn = true;
				while (loggedIn) {
					ClearScreen();
					DisplayAccMenu();
					cin >> choice;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Error! Invalid input!" << endl;
						PauseScreen();
						continue;
					}

					switch (choice) {
					case 1: {
						checkBal(loggedInAccount);
						PauseScreen();
						break;
					}
					case 2: {
						double amount;
						cout << "\nEnter amount to deposit: $";
						cin >> amount;
						deposit(loggedInAccount, amount);
						PauseScreen();
						break;
					}
					case 3: {
						double amount;
						cout << "\nEnter amount to withdraw: $";
						cin >> amount;
						withdraw(loggedInAccount, amount);
						PauseScreen();
						break;
					}
					case 4: {
						showHistory();
						PauseScreen();
						break;
					}
					case 5: {
						undoLast();
						PauseScreen();
						break;
					}
					case 6: {
						Transaction t;
						cout << "\nEnter transaction type (deposit/withdraw): ";
						cin >> t.type;
						cout << "Enter amount: $";
						cin >> t.amount;
						cout << "Enter account number: ";
						cin >> t.accountNumber;
						enqueueTrans(t);
						PauseScreen();
						break;
					}
					case 7: {
						processNext();
						PauseScreen();
						break;
					}
					case 8: {
						showQueue();
						PauseScreen();
						break;
					}
					case 9: {
						cout << "Logged out successfully." << endl;
						loggedIn = false;
						PauseScreen();
						break;
					}
					default:
						cout << "Error! Invalid choice!" << endl;
						PauseScreen();
					}
				}
			}
			break;
		}

		case 3: {
			ClearScreen();
			DisplayAllAcc();
			cout << "\nTotal Accounts: " << getTotalAcc() << endl;
			PauseScreen();
			break;
		}

		case 4: {
			ClearScreen();
			int accNum;
			cout << "\n==================================" << endl;
			cout << "         DELETE ACCOUNT           " << endl;
			cout << "==================================" << endl;

			DisplayAllAcc();

			cout << "\nEnter Account Number to Delete: ";
			cin >> accNum;

			char confirm;
			cout << "Are you sure you want to delete account " << accNum << "? (y/n): ";
			cin >> confirm;

			if (confirm == 'y' || confirm == 'Y') {
				deleteAcc(accNum);
			}
			else {
				cout << "Deletion cancelled." << endl;
			}

			PauseScreen();
			break;
		}

		case 5: {
			ClearScreen();
			cout << "\n==================================" << endl;
			cout << "   Thank you for using ATM System  " << endl;
			cout << "==================================" << endl;

			clearAllAcc();
			running = false;
			break;
		}

		default:
			cout << "Error! Invalid choice! Please select 1-5." << endl;
			PauseScreen();
		}

		if (running) {
			ClearScreen();
		}
	}

	return 0;
}