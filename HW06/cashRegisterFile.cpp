
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// funct for item scanning
double ItemScan(int numItems, ofstream& itemFile) {
    int itemNum = 1;
    double subtotal = 0.0;

    while (numItems > 0) {
        cout << "Please enter the cost of item #" << itemNum << ": $";
        double itemCost;
        cin >> itemCost;

        // write item(s) cost to items.txt file
        itemFile << itemCost << endl;

        subtotal += itemCost;

        itemNum++;
        numItems--;
    }

    return subtotal;
}

// funct for payment
double Payment(char response, double total) {
    if (response == 'C' || response == 'c') {
        double cash;
        cout << "Enter the amount of cash received: $";
        cin >> cash;

        while (cash < total) {
            cout << "Please enter the correct amount of cash: $";
            cin >> cash;
        }

        return cash;
    } else if (response == 'T' || response == 't') {
        cout << "Payment successfully processed with credit." << endl;
        return 0.0; // return 0 for credit payment
    }

    return 0.0; // return 0 for an unknown payment method
}
// main
int main() {
    int userItem;
    cout << "How many items? ";
    cin >> userItem;

    // open items.txt 
    ofstream itemFile("items.txt");
    if (!itemFile.is_open()) {
        cout << "Error opening file 'items.txt'." << endl;
        return 1;
    }

    double subtotal = ItemScan(userItem, itemFile);
    // data precision on stdout
    cout.setf(ios::showpoint);
    cout.setf(ios::fixed);

    cout << "Subtotal: $" << subtotal << endl;

    double salesTax = 0.0775;
    cout << "Tax(7.75%): $" << salesTax * subtotal << endl;

    double total = subtotal + (salesTax * subtotal);
    cout << "Total: $" << total << endl;
    // type of payment method
    char payment;
    while (true) {
        cout << "Cash or credit? Enter 'C' for Cash or 'T' for Credit:" << endl;
        cin >> payment;

        if (payment == 'C' || payment == 'T' || payment == 'c' || payment == 't') {
            break;
        } else {
            cout << "Please select the correct options!" << endl;
        }
    }

    double cashReceived = Payment(payment, total);

    // save receipt -> receipt.txt file
    ofstream outFile("receipt.txt");
    if (outFile.is_open()) {
        outFile << "###########################################################" << endl;
        outFile << "                          Receipt" << endl;
        outFile << "###########################################################" << endl;
        outFile << endl;
        outFile << "Items:" << endl;
        // items.txt file
        ifstream itemFileCopy("items.txt");
        if (itemFileCopy.is_open()) {
            double itemCost;
            int itemNum = 1; // initialize item number
            while (itemFileCopy >> itemCost) {
                outFile << "\t#" << itemNum << ": $" << fixed << setprecision(2) << itemCost << endl;
                itemNum++; // increment item number for txt file (item #1... item #2...)
            }
            itemFileCopy.close();
        } else {
            cout << "Error opening file 'items.txt' for reading." << endl;
        }
        // print subtotal, tax, total
        outFile << endl;
        outFile << "Subtotal: $" << subtotal << endl;
        outFile << "Tax(7.75%): $" << salesTax * subtotal << endl;
        outFile << "Total: $" << total << endl;
    

      // cash => calculate change
    if (payment == 'C' || payment == 'c') {
        outFile << endl;
        double change = cashReceived - total;
        outFile << "Cash: $" << cashReceived << endl;
        outFile << "Change: $" << change << endl;

        // print in terminal
        cout << "Cash: $" << cashReceived << endl;
        cout << "Change: $" << change << endl;
    } else if (payment == 'T' || payment == 't') {
        outFile << endl;
        outFile << "Card Payment: $" << total << endl;

        // print in terminal
        cout << "Card Payment: $" << total << endl;
    }

        outFile.close();
        cout << "Receipt saved" << endl;
    } else {
        cout << "Error opening file 'receipt.txt' for writing." << endl;
    }

    return 0;
}
