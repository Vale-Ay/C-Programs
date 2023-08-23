#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() 
{
 //Constants
 const double ADULT_TICKET_PRICES = 10.00;
 const double CHILD_TICKET_PRICES = 6.00;

//Variables
string movie;
int adultTickets, childTickets;
double adultTicketsSold, childTicketsSold; 
double grossBoxOfficeProfit, netBoxOfficeProfit;
double amountPaidDistributor;

//Description of the Program
cout << "This program displays a movie theater's gross and net box office profit for a night." << endl;

//User input
cout << "Enter Name of Movie: ";
getline (std:: cin, movie);
cout << "Enter number of Adult tickets: ";
cin >> adultTickets;
cout << "Enter number of Child tickets: ";
cin >> childTickets;

//Process
adultTicketsSold = (adultTickets) * (ADULT_TICKET_PRICES);

childTicketsSold = (childTickets) * (CHILD_TICKET_PRICES);

grossBoxOfficeProfit = (adultTicketsSold + childTicketsSold);

netBoxOfficeProfit = (grossBoxOfficeProfit * 0.20);

amountPaidDistributor = (grossBoxOfficeProfit - netBoxOfficeProfit);

//Output
cout << "\nMovie Name: " << movie << endl;
cout << "Adult Tickets Sold: " << adultTickets <<endl;
cout << "Child Tickets Sold: " << childTickets <<endl;
cout<< fixed << setprecision (2);
cout << "Gross Box Office Profit: " << "$"<< right << grossBoxOfficeProfit<<endl;
cout << "Net Box Office Profit: "<< "$"<< right <<netBoxOfficeProfit<<endl;
cout << "Amount Paid to Distributor: "<< "$"<< right << amountPaidDistributor<<endl;

return 0;
}
