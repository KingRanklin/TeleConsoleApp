#include "pch.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	//Variables
	char status, answer, verify;
	int customer_Age;
	double transfer_Amount;
	string customer_Firstname, customer_Lastname, address, customer_Number;
	const double prefered_Interestrate = 7.9, notprefered_Interestrate = 12.9, aarp_Preferred = 7.4, aarp_Nonprefered = 12.4;

	//open both files here
	ifstream input;
	ofstream output;
	input.open("morepotentials.txt");
	output.open("confirmed.txt");
	while (!input.eof())
		//while it is not the end of the potentials file
	{
		//read one potential customer here
		input >> status >> customer_Firstname >> customer_Lastname >> customer_Age >> customer_Number;


		//process that customer
		cout << "\t\t\tName:" << customer_Firstname << " " << customer_Lastname << " Number:" << customer_Number << " Interest rate:" <<
			(customer_Age >= 65 ? (status == 'X' ? aarp_Preferred : aarp_Nonprefered) : (status == 'X' ? prefered_Interestrate : notprefered_Interestrate));



		//Menu
		cout << "\n\tCall customer and ask if they would like credit card with interest rate. Press Enter to continue." << endl;
		cin.get();
		cout << "\t\t\tWould they like to Accept, Tranfer, or Decline?\n" <<
			"\t\t\t\t\tA for Accept.\n"
			"\t\t\t\t\tT for Transfer.\n"
			"\t\t\t\t\tD for Decline." << endl;
		cin >> answer;
		cin.ignore(); // Program wasnt working untill I put this at every Cin.get. or Cin. IDK but it works.

		// If customer Accepts new Buisness or Accepts and Wants to Transfer money over
		if (answer == 'A' || answer == 'T')
		{
			// If they want to transfer and ARE preferred or AARP(Over 65)
			if (answer == 'T' && (customer_Age >= 65 || status == 'X')) {

				cout << "\t\t\tCongratulations! There is no transfer limit!\n\t\t\tWhat amount Would you like to transfer?" << endl;
				cin >> transfer_Amount;
				cin.ignore();

			} // If they want to transfer but ARENT prefered or AAPR(Over 65)
			else if (answer == 'T') {

				cout << "\t\t\tCongratulations! You can transfer up to $1000! How much would you like to transfer?" << endl;
				cin >> transfer_Amount;
				cin.ignore();

				//Creates a loop to make sure nothing over $1000 is imputed
				while (transfer_Amount > 1000)
				{
					cout << "\t\t\tThats too much money for the transfer! Please pick an amount up to $1000. How much would you like to transfer?" << endl;
					cin >> transfer_Amount;
					cin.ignore();
				}
			}
			// If User just wants to Become new buisness they start here. Transfers exit from statement above to here.
			//              Asks for Address
			cout << "\t\t\tWhat address can I send this card to?" << endl;
			getline(cin, address);
			cout << "\t\t\tIs this address correct? Y/N?\n" << address << endl;
			cin >> verify;
			cin.ignore();

			// Creates Loop to get correct address, Only way to break to is verify the address is correct 2 times.
			while (verify == 'N' || verify == 'n')
			{
				cout << "\t\t\tWhat is the correct address?" << endl;
				getline(cin, address);
				cout << "\t\t\tLets double check this time. Is this address correct? Y/N?\n" << address << endl;
				cin >> verify;
				cin.ignore();
			}
			// End of Processing for Transfers and New Buisness 			
			cout << "\tThank you so much for your buisness today!" <<
				"You should be recieving your card in the next 3 to 5 buisness days!\n\t\t\t\t\tHappy Charging!\n" << endl;

			// Outputs To Confirmed file if New Buisness or Transfer.
			output << "\nNAME:" << customer_Firstname << " " << customer_Lastname <<
				"\nADDRESS:" << address << "\nSTATUS:" << status << "\nACCOUNT:" << (answer == 'T' ? "Transfer" : "New") << " " <<
				// Terniary Expressions to simplify output. One Checks of over 65, The other Displays transfer amount if any. 
				(customer_Age >= 65 ? "\n65+" : "") << "\nAMOUNT TRANSFERED:$" << (answer == 'T' ? transfer_Amount : 0) << endl;

			// Imput Buffer to Wait for Telemarketer to be ready for Next Customer
			cout << "\t\t\tPress Enter to recieve next customer" << endl;
			cin.get();
		}
		// If Customer Declines but is Prefered OR AARP(Over 65)
		else if (answer == 'D' && (status == 'X' || customer_Age >= 65))
		{

			cout <<
				"\t\t\tIm sorry to hear that. Our new cashback rewards card might be better suited to fit your needs." <<
				"Call them at 555-555-5555. Thank you so much for your time today!" << endl;
			// Imput Buffer
			cout << "\t\t\tPress Enter to recieve next customer" << endl;
			cin.get();

		}       // If customer declines and isnt preferred or AARP(Over 65)
		else {

			cout << "\t\t\tThank you so much for your time today! Have a good one!\n" << endl;
			// Imput Buffer
			cout << "\t\t\tPress Enter to recieve next customer" << endl;
			cin.get();
		}

	}

	//close both files
	input.close();
	output.close();
	system("PAUSE");
	return EXIT_SUCCESS;
}
