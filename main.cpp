#include "stdafx.h"
#include<iostream>
#include <string>
#include<vector>
using namespace std;
class Account
{
protected:
	double balance;
	long int accountNumber;
	string name;
	int pasword;
public:
	Account()
	{
		balance = 0.0;
	}
	Account(string n, long int ac, double bal)
	{
		name = n;
		accountNumber = ac;
		balance = bal;
	}
	void showAccountInfo()
	{
		cout << "name= " << name << endl;
		cout << "account number= " << accountNumber << endl;
		cout << "balance =" << balance << endl;
	}
	void createAccount(string n, long int ac)
	{
		name = n;
		accountNumber = ac;
	}
	void setPasword(int pasw)
	{
		pasword = pasw;
	}
	int getPasword()
	{
		return pasword;
	}

	void setAccountNumber(int ac)
	{
		accountNumber = ac;
	}
	int getAccountNumber()
	{
		return accountNumber;
	}
	void setBalance(double bala)
	{
		balance = bala;
	}

	double getBalance()
	{
		return balance;
	}
	void deposit(double amount)
	{
		balance = balance + amount;
	}
	void withdraw(double amount)
	{
		if (amount <= balance)
		{
			balance = balance - amount;
		}
		else
		{
			cout << "not enough money to withdraw";
		}

	}
	void moneyTransfer(double amount, Account *otherAccount)
	{
		if (balance < 0)
		{
			cout << "no permission to transfer money because you balance below zero" << endl;
		}
		if (balance > 0)
		{
			if (balance >= amount)
			{
				otherAccount->deposit(amount);
				balance = balance - amount;
			}
		}

	}
};
class OverdraftAccount :public Account
{
public:
	OverdraftAccount()
	{

	}
	OverdraftAccount(string n, long int ac, double bal)
	{
		name = n;
		accountNumber = ac;
		balance = bal;
	}
	void withdraw(double amount)
	{
		if (balance >= amount)
		{
			balance = balance - amount;
		}
		else if (balance < amount)
		{

			if (balance - amount > -500)
			{
				balance = balance - amount;
				cout << "your interest rate ==" << 10 << endl;
				cout << "your dept==" << (balance + balance * 0.1)*(-1) << endl;
				balance = balance - (balance*0.1)*(-1);
			}
			if (balance - amount < -500 && balance - amount>-1000)
			{
				balance = balance - amount;
				cout << "your interest rate ==" << 20 << endl;
				cout << "your dept==" << (balance + balance * 0.2)*(-1) << endl;
				balance = balance - (balance*0.2)*(-1);
			}
			if (balance - amount < -1000)
			{
				cout << "your limit is -1000 so you cannot withdraw that much money" << endl;
			}
		}
	}

};
class foreignCurrencyaccount :public Account
{
public:
	string accountKind;
	foreignCurrencyaccount()
	{
		balance = 0;
	}
	foreignCurrencyaccount(string n, long int ac, double bal)
	{
		name = n;
		accountNumber = ac;
		balance = bal;
	}
	void createAccount(string n, long int ac, string kind)
	{
		name = n;
		accountNumber = ac;
		accountKind = kind;
		if (accountKind == "dollar")     //hesabı yarattığımda hesap işletim ücreti çekiyorum 1 kerelik
		{
			balance = balance - 10;
		}
		if (accountKind == "euro")
		{
			balance = balance - 15;
		}
		if (accountKind == "pound")
		{
			balance = balance - 20;
		}
	}
	void showAccountInfo()
	{
		cout << "name= " << name << endl;
		cout << "account number= " << accountNumber << endl;
		cout << "balance= " << balance << " " << accountKind << endl;
	}
	void deposit(double amount)
	{
		balance = balance + amount;
	}
	void withdraw(double amount)
	{
		if (amount <= balance)
		{
			balance = balance - amount;
			if (accountKind == "dollar")     //stopage uyguluyorum parayı çekior ama stopage da uyguluyor
			{
				balance = balance - (amount*0.1);
			}
			if (accountKind == "euro")
			{
				balance = balance - (amount*0.12);
			}
			if (accountKind == "pound")
			{
				balance = balance - (amount*0.15);
			}
		}
		else
		{
			cout << "no enough money to withdraw";
		}

	}
	void exchangeMoney(double Tlkarsiliği, double rate, string kind)
	{
		balance = Tlkarsiliği / rate;
		accountKind = kind;
	}
	string getAccountkind()
	{
		return accountKind;
	}

};


int main()
{

	vector<OverdraftAccount> odhesaplar;
	vector<foreignCurrencyaccount> fohesaplar;
	int odsayaci = 0;
	int fosayaci = 0;
	while (true)
	{
		int secim1;
		cout << "which account system do you want to continue?(1-overDraffAccount)(2-foreignCurrencyaccount)" << endl;
		cin >> secim1;
		cin.ignore();
		if (secim1 == 1) //overDraffAccount seçtik
		{
			while (2)
			{
				int secim2;
				cout << "(1-create OverdraftAccount)(2-deposit)(3-withdraw)(4-money transfer)(5-show my account)(6-done)" << endl;
				cin >> secim2;
				cin.ignore();
				if (secim2 == 1) //create OverdraftAccount
				{
					string name;
					long int ac;
					int pasword;
					OverdraftAccount temp;
					cout << "please enter the (name-accounNumber-pasword)" << endl;
					cout << "name=";
					getline(cin, name);
					cout << "accounNumber=";
					cin >> ac;
					cout << "pasword=";
					cin >> pasword;

					temp.createAccount(name, ac);
					temp.setPasword(pasword);
					odhesaplar.push_back(temp);
					odsayaci++;
					while (2)
					{
						int secim3;
						cout << "(2-deposit)(3-withdraw)(4-money transfer)(5-show my account)(6-done)" << endl;
						cin >> secim3;
						if (secim3 == 2)
						{

							int amount;
							cout << "please enter the amount" << endl;
							cin >> amount;
							odhesaplar[odsayaci - 1].deposit(amount);
						}
						if (secim3 == 3)
						{
							int amount;
							cout << "please enter the amount you want to withdraw" << endl;
							cin >> amount;
							odhesaplar[odsayaci - 1].withdraw(amount);
						}
						if (secim3 == 4)
						{
							if (odsayaci <= 1)
							{
								cout << "there is only you in your overdraffaccount system so you cant transfer money" << endl;
							}
							else
							{

								if (odhesaplar[odsayaci - 1].getBalance() <= 0)
								{
									cout << "you cant transfer money because your balance is below zero" << endl;
								}
								else
								{
									int acNo, amount;
									cout << "please enter account number and amount to transfer money" << endl;
									cin >> acNo;
									cin >> amount;
									for (int j = 0; j < odsayaci; j++)
									{
										if (acNo == odhesaplar[j].getAccountNumber())
										{

											odhesaplar[odsayaci - 1].moneyTransfer(amount, &odhesaplar[j]);


										}
									}
								}



							}
						}
						if (secim3 == 5)
						{
							odhesaplar[odsayaci - 1].showAccountInfo();
						}
						if (secim3 == 6)
						{
							//odsayaci++;
							break;
						}
					}
					break;
				}
				if (secim2 == 2) //deposit
				{
					int psw;
					cout << "please enter pasword of your account " << endl;
					cin >> psw;
					for (int i = 0; i<odsayaci; i++)
					{
						if (psw == odhesaplar[i].getPasword())
						{
							int amount;
							cout << "please enter the amount" << endl;
							cin >> amount;
							odhesaplar[i].deposit(amount);

						}
					}

				}
				if (secim2 == 3)  //withdraw
				{
					int psw;
					cout << "please enter pasword of your account " << endl;
					cin >> psw;
					for (int i = 0; i<odsayaci; i++)
					{
						if (psw == odhesaplar[i].getPasword())
						{
							int amount;
							cout << "please enter the amount you want to withdraw" << endl;
							cin >> amount;
							odhesaplar[i].withdraw(amount);
						}
					}

				}
				if (secim2 == 4) //money transfer
				{

					int psw;
					cout << "please enter pasword of your account " << endl;
					cin >> psw;
					for (int i = 0; i < odsayaci; i++)
					{
						if (psw == odhesaplar[i].getPasword())
						{
							if (odhesaplar[i].getBalance() <= 0)
							{
								cout << "you cant transfer money because your balance is below zero" << endl;
							}
							else
							{
								int acNo, amount;
								cout << "please enter account number and amount to transfer money" << endl;
								cin >> acNo;
								cin >> amount;
								for (int j = 0; j < odsayaci; j++)
								{
									if (acNo == odhesaplar[j].getAccountNumber())
									{

										odhesaplar[i].moneyTransfer(amount, &odhesaplar[j]);
									}
								}
							}

						}
					}

				}
				if (secim2 == 5)
				{
					int psw;
					cout << "please enter pasword of your account " << endl;
					cin >> psw;
					for (int i = 0; i < odsayaci; i++)
					{
						if (psw == odhesaplar[i].getPasword())
						{
							odhesaplar[i].showAccountInfo();
						}
					}

				}
				if (secim2 == 6)
				{
					//odsayaci++;
					break;
				}

			}
		}

		//burada od bitior

		else if (secim1 == 2) //foreignCurrencyaccount seçtik
		{
			while (2)
			{
				int secim5;
				cout << "(1-create foreignCurrencyaccount)(2-deposit)(3-withdraw)(4-money transfer)(5-show my account)(6-done)" << endl;
				cin >> secim5;
				cin.ignore();
				if (secim5 == 1) //create foreignCurrencyaccount
				{
					int what;
					cout << "what foreign currency account u wanna open(1-dollar)(2-euro)(3-pound)" << endl;
					cin >> what;
					cin.ignore();
					string name, accountKind;
					long int ac;
					int pasword;
					foreignCurrencyaccount temp;
					cout << "please enter the (name-accounNumber-pasword)" << endl;
					if (what == 1) //dollar seçti
					{
						cout << "name=";
						getline(cin, name);
						cout << "account Number=";
						cin >> ac;
						cout << "pasword=";
						cin >> pasword;
						temp.createAccount(name, ac, "dollar");
						temp.setPasword(pasword);
						fohesaplar.push_back(temp);
						fosayaci++;
					}
					if (what == 2) //euro seçti
					{
						cout << "name=";
						getline(cin, name);
						cout << "account Number=";
						cin >> ac;
						cout << "pasword=";
						cin >> pasword;
						temp.createAccount(name, ac, "euro");
						temp.setPasword(pasword);
						fohesaplar.push_back(temp);
						fosayaci++;
					}
					if (what == 3) //pound seçti
					{
						cout << "name=";
						getline(cin, name);
						cout << "account Number=";
						cin >> ac;
						cout << "pasword=";
						cin >> pasword;
						temp.createAccount(name, ac, "pound");
						temp.setPasword(pasword);
						fohesaplar.push_back(temp);
						fosayaci++;
					}
					while (2)
					{
						int secim10;
						cout << "(1-exchange money)(2-deposit)(3-withdraw)(4-money transfer)(5-show my account)(6-done)" << endl;
						cin >> secim10;
						if (secim10 == 1)
						{
							if (what == 1) //dolardı
							{
								int whichh;
								cout << "which of these you want to exchance??(1-euro)(2-dollar)(3-pound)" << endl;
								cin >> whichh;
								if (whichh == 1)
								{
									fohesaplar[fosayaci - 1].exchangeMoney(fohesaplar[fosayaci - 1].getBalance()*4.07, 4.93, "euro");
								}
								if (whichh == 2)
								{
									fohesaplar[fosayaci - 1].exchangeMoney(fohesaplar[fosayaci - 1].getBalance()*4.07, 4.07, "dollar");
								}
								if (whichh == 3)
								{
									fohesaplar[fosayaci - 1].exchangeMoney(fohesaplar[fosayaci - 1].getBalance()*4.07, 5.58, "pound");
								}
							}
							if (what == 2) //euro idi
							{
								int whichh;
								cout << "which of these you want to exchance??(1-euro)(2-dollar)(3-pound)" << endl;
								cin >> whichh;
								if (whichh == 1)
								{
									fohesaplar[fosayaci - 1].exchangeMoney(fohesaplar[fosayaci - 1].getBalance()*4.93, 4.93, "euro");
								}
								if (whichh == 2)
								{
									fohesaplar[fosayaci - 1].exchangeMoney(fohesaplar[fosayaci - 1].getBalance()*4.93, 4.07, "dollar");
								}
								if (whichh == 3)
								{
									fohesaplar[fosayaci - 1].exchangeMoney(fohesaplar[fosayaci - 1].getBalance()*4.93, 5.58, "pound");
								}
							}
							if (what == 3) //pound idi
							{
								int whichh;
								cout << "which of these you want to exchance??(1-euro)(2-dollar)(3-pound)" << endl;
								cin >> whichh;
								if (whichh == 1)
								{
									fohesaplar[fosayaci - 1].exchangeMoney(fohesaplar[fosayaci - 1].getBalance()*5.58, 4.93, "euro");
								}
								if (whichh == 2)
								{
									fohesaplar[fosayaci - 1].exchangeMoney(fohesaplar[fosayaci - 1].getBalance()*5.58, 4.07, "dollar");
								}
								if (whichh == 3)
								{
									fohesaplar[fosayaci - 1].exchangeMoney(fohesaplar[fosayaci - 1].getBalance()*5.58, 5.58, "pound");
								}
							}

						}
						if (secim10 == 2) //deposit
						{
							int amount;
							cout << "please enter the amount to deposit" << endl;
							cin >> amount;
							fohesaplar[fosayaci - 1].deposit(amount);
						}
						if (secim10 == 3) //withdraw
						{
							int amount;
							cout << "please enter the amount to withdraw" << endl;
							cin >> amount;
							fohesaplar[fosayaci - 1].withdraw(amount);
						}
						if (secim10 == 4) //money transfer
						{
							if (fosayaci <= 1)
							{
								cout << "there is only you in your foreign account  system so you cant transfer money" << endl;
							}
							else
							{
								if (fohesaplar[fosayaci - 1].getBalance() <= 0)
								{
									cout << "you cant transfer money because your balance is below zero" << endl;
								}
								else
								{
									int acNo, amount;
									cout << "please enter account number and amount to transfer money" << endl;
									cin >> acNo;
									cin >> amount;
									for (int j = 0; j < fosayaci; j++)
									{
										if (acNo == fohesaplar[j].getAccountNumber())
										{
											fohesaplar[fosayaci - 1].moneyTransfer(amount, &fohesaplar[j]);
										}
									}
								}




							}
						}
						if (secim10 == 5)
						{
							fohesaplar[fosayaci - 1].showAccountInfo();
						}
						if (secim10 == 6)
						{
							break;
						}
						//break;;
					}
					break;
				}
				if (secim5 == 2)  //deposit
				{
					int psw;
					cout << "please enter pasword of your account 1" << endl;
					cin >> psw;
					for (int i = 0; i<fosayaci; i++)
					{
						if (psw == fohesaplar[i].getPasword())
						{
							int amount;
							cout << "please enter the amount" << endl;
							cin >> amount;
							fohesaplar[i].deposit(amount);

						}
					}
				}
				if (secim5 == 3) //withdraw
				{
					int psw;
					cout << "please enter pasword of your account 2" << endl;
					cin >> psw;
					for (int i = 0; i<fosayaci; i++)
					{
						if (psw == fohesaplar[i].getPasword())
						{
							int amount;
							cout << "please enter the amount you want to withdraw" << endl;
							cin >> amount;
							fohesaplar[i].withdraw(amount);
						}
					}
				}
				if (secim5 == 4) //money transfer
				{
					int psw;
					cout << "please enter pasword of your account 3" << endl;
					cin >> psw;
					for (int i = 0; i < fosayaci; i++)
					{
						if (psw == fohesaplar[i].getPasword())
						{
							if (fohesaplar[i].getBalance() <= 0)
							{
								cout << "you cant transfer money because your balance is below zero" << endl;
							}
							else
							{
								int acNo, amount;
								cout << "please enter account number and amount to transfer money" << endl;
								cin >> acNo;
								cin >> amount;
								for (int j = 0; j < fosayaci; j++)
								{
									if (acNo == fohesaplar[j].getAccountNumber())
									{
										fohesaplar[i].moneyTransfer(amount, &fohesaplar[j]);
									}
								}
							}

						}
					}
				}
				if (secim5 == 5) //show client info
				{
					int psw;
					cout << "please enter pasword of your account 2" << endl;
					cin >> psw;
					for (int i = 0; i < fosayaci; i++)
					{
						if (psw == fohesaplar[i].getPasword())
						{
							fohesaplar[i].showAccountInfo();
						}
					}
				}
				if (secim5 == 6) //done with foregin account
				{
					break;
				}
			}
		}
	}



	system("pause");
	return 0;
}

