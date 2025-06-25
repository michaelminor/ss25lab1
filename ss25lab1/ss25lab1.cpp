/*Mike Minor 
Student id: 16358106*/

#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

// Function declarations
void orderInventory(int& l, int& m, int& s);
void fillOrder(int& l, int& m, int& s, int& o);
void printInventory(int l, int m, int s);
double calculateShipping(int pounds);

int main() {
    
    //sets variables to initial values and data types
    int large = 1500;
    int medium = 1200;
    int small = 7000;
    int orderNum = 1;
    char choice;

    //creates the menu and calls the appropriate function depending on which case is selected
    do {
        cout << "Enter your choice:\n";
        cout << "O  : Order Inventory\n";
        cout << "F  : Fill Order\n";
        cout << "P  : Print Inventory\n";
        cout << "E  : Exit\n";
        cin >> choice;

        switch (toupper(choice)) {
        case 'O':
            orderInventory(large, medium, small);
            break;
        case 'F':
            fillOrder(large, medium, small, orderNum);
            break;
        case 'P':
            printInventory(large, medium, small);
            break;
        case 'E':
            cout << "Thank you for using my program!" << endl;
            break;
        default:
            cout << "WARNING: " << choice << " is an invalid choice. Please try again." << endl;
        }
      
    } while (toupper(choice) != 'E');

    return 0;
}

//adds inventory to the correct variable depending on selected case
void orderInventory(int& l, int& m, int& s) {
    int qty;
    char type;

    cout << "Enter the quantity to order: ";
    cin >> qty;
    cout << "Enter the type of bar (L/M/S): ";
    cin >> type;

    switch (toupper(type)) {
    case 'L':
        l += qty;
        cout << ": " << qty << " large bars ordered. New total of large bars = " << l << endl;
        break;
    case 'M':
        m += qty;
        cout << ": " << qty << " medium bars ordered. New total of medium bars = " << m << endl;
        break;
    case 'S':
        s += qty;
        cout << ": " << qty << " small bars ordered. New total of small bars = " << s << endl;
        break;
    default:
        cout << "WARNING: " << type << " is an invalid type. Command ignored." << endl;
    }
}

//handles the correct shipping cost depending on the weight
double calculateShipping(int pounds) {
    if (pounds <= 10) return 8.25;
    if (pounds <= 20) return 12.75;
    if (pounds <= 50) return 15.25;
    return 19.75;
}

//Builds the logic for determining how much of each bar to fill the order. Starts trying to use the largest bars first and working down to lower weight bars.
void fillOrder(int& l, int& m, int& s, int& o) {
    int pounds;
    cout << "Enter pounds of chocolate to order: ";
    cin >> pounds;

    int totalAvailable = l * 5 + m * 3 + s;
    if (pounds > totalAvailable) {
        cout << "WARNING: Unable to fill order of " << pounds << " pounds. We are " << pounds - totalAvailable
            << " pounds short. We are sorry for the inconvenience." << endl;
        return;
    }

    int useL = min(l, pounds / 5);
    pounds -= useL * 5;

    int useM = min(m, pounds / 3);
    pounds -= useM * 3;

    int useS = min(s, pounds);
    pounds -= useS;

    if (pounds > 0) {
        cout << "WARNING: Unable to fill order of " << pounds << " pounds. We are " << pounds
            << " pounds short. We are sorry for the inconvenience." << endl;
        return;
    }

    // Prices
    double largeTot = useL * 41.25;
    double mediumTot = useM * 25.80;
    double smallTot = useS * 13.50;
    double subtotal = largeTot + mediumTot + smallTot;
    double tax = subtotal * 0.072;
    double shipping = calculateShipping((useL * 5 + useM * 3 + useS));
    double totalCost = subtotal + tax + shipping;

    // Print receipt
    cout << fixed << setprecision(2);
    cout << "Chocolate Order #" << o << endl;
    cout << "Large Bars: " << setw(4) << useL << setw(9) << useL * 5 << setw(12) << largeTot << endl;
    cout << "Medium Bars: " << setw(4) << useM << setw(9) << useM * 3 << setw(12) << mediumTot << endl;
    cout << "Small Bars: " << setw(4) << useS << setw(9) << useS << setw(12) << smallTot << endl;
    cout << "Sub Total: " << setw(13) << (useL * 5 + useM * 3 + useS) << setw(12) << subtotal << endl;
    cout << "\nTax Total: " << setw(25) << tax << endl;
    cout << "Shipping: " << setw(25) << shipping << endl;
    cout << "Total Cost: " << setw(25) << totalCost << endl << endl << endl;

    // Update inventory and order number
    l -= useL;
    m -= useM;
    s -= useS;
    o++;
}
//creates the framework for printing out the inventory
void printInventory(int l, int m, int s) {
    cout << "Inventory:\n";
    cout << "Large Bars:  " << setw(4) << l << endl;
    cout << "Medium Bars: " << setw(4) << m << endl;
    cout << "Small Bars:  " << setw(4) << s << endl;
}
