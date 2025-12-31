#pragma once
#ifndef ACCOUNT_MANAGEMENT_H
#define ACCOUNT_MANAGEMENT_H
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// =======================================================
// Structures
// =======================================================
struct Account {
	int accountNumber = 0;
	string holder = "";
	int pin = 0;
	double balance = 0.0;
	Account* next = nullptr;
};
struct Transaction {
	string type;
	double amount;
	string timestamp;
	int accountNumber;
	Transaction() {
		type = "";
		amount = 0.0;
		timestamp = "";
		accountNumber = 0;
	}
};
// =======================================================
// global vars
// =======================================================
extern Account* head;
extern int counter;
const int MAX_TRANS = 100;
extern Transaction stackArr[MAX_TRANS];
extern int topIndex;
extern Transaction queueArr[MAX_TRANS];
extern int frontIndex, rearIndex;

// =======================================================
// Function Signatures
// =======================================================
void initSystem();
bool createAcc(string name, int pin, double firstDep);
Account* searchAcc(int AccNumber);
bool deleteAcc(int AccNumber);
void DisplayAllAcc();
bool UpdateBalance(int AccNumber, double NewBalance);
bool validatePin(int AccNumber, int pin);
Account* login();
bool isEmpty();
int getTotalAcc();
void clearAllAcc();
void DisplayMainMenu();
void DisplayAccMenu();
void ClearScreen();
void PauseScreen();
string getTime();
void pushTrans(Transaction t);
Transaction popTrans();
void showHistory();
bool isStackEmpty();
void enqueueTrans(Transaction t);
Transaction dequeueTrans();
void showQueue();
bool isQueueEmpty();
void deposit(Account* acc, double amt);
void withdraw(Account* acc, double amt);
void checkBal(Account* acc);
void undoLast();
void processNext();

#endif
