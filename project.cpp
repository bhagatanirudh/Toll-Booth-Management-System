#include <iostream>
#include <string.h>
#include <fstream>   //to create files, write information to files, and read information from files
#include <windows.h> //contains declarations for all of the functions in the Windows API
#include <conio.h>   //to provide console input/output.
using namespace std;

void login(); // function for login section

class Customer // to get the customer details
{
public:
    char cus_name[50];
    string cus_id, cus_regno;
    char cus_vehno[20];
    int cus_vehType;
    char vech1[20] = "Two Wheeler", vech2[80] = "Three Wheeler - Auto-rickshaws / trishaws", vech3[100] = "Four Wheeler - Car/ Jeep/ Van/ and similar mini light commercial vehicles", vech4[50] = "Light Commercial Vehicles", vech5[50] = "Three Axle Commercial Vehicles", vech6[20] = "Bus / Truck", vech7[50] = "4 to 6 Axle Vehicles", vech8[50] = "7 or More Axle Vehicles", vech9[100] = "Heavy Construction Machinery(HCM) / Earth Moving Equipment(EME)", vech10[50] = "Tractor / Tractor with trailor";
    void get();
    void vehcile_Type();
    void display();
};

class CalculateBill : public Customer // to calculate the bill based upon entered details
{
public:
    int journey, pay_choice;
    float bill = 0.0;
    double weight = 0.0;
    int weightFlag = 0;
    void findWeight();
    void findJourney();
    void calculate_bill();
    void showbill();
};

class Payment : public CalculateBill // conatin various payment option
{
public:
    char upi_id[30];
    long long int card_no;
    char fastTag_id[20];
    int expireYear;
    double cash;
    void payment_opt();
    void UPI_payment();
    void Manual_payment();
    void FastTag_payment();
    void DebitCredit_payment();
};

class Summary : public Payment
{
public:
    void display_summary()
    {
        get();
        if (cus_vehType == 1 || cus_vehType == 10) // if vechile type is two wheeler or is tractor then end the program
            return;

        findWeight();
        payment_opt();
    }
};

void Customer ::get()
{
    system("cls");
    cout << "\n\t|--------------------------------------------------------------------------|";
    cout << "\n\t|               -----Enter Customer Details-----                           |";
    cout << "\n\t|--------------------------------------------------------------------------|";
    cin.sync(); // used to ignore or clear one or more characters from the input buffer
    try
    {
        cout << "\n\n\tPlease enter customer name : ";
        cin.getline(cus_name, 50);
        cout << "\n\tPlease enter customer ID   : ";
        cin >> cus_id;
        cout << "\n\tPlease enter customer vehicle registration number : ";
        cin >> cus_regno;
        cout << "\n\tPlease enter customer vehicle plate number : ";
        cin >> cus_vehno;
    }
    catch (...)
    { // to catch all exceptions
        cout << "\nException Caught\n";
    }
    system("CLS");
    vehcile_Type();
}
void Customer ::vehcile_Type()
{
    do
    {
        cout << "\nPlease select the vehicle type of the customer from following " << endl;
        cout << "\n---------------------------------------------------------------------------------------------------------------------\n\n";
        ifstream veh("vehicleType.txt");
        char str[300];
        while (veh)
        {
            veh.getline(str, 300);
            if (veh)
                cout << str << endl;
        }
        veh.close();
        cout << "\n---------------------------------------------------------------------------------------------------------------------\n";
        cout << "\n\tEnter the choice : ";
        cin >> cus_vehType;

    } while (cus_vehType < 1 || cus_vehType > 10);

    system("cls");
    display();
}
void Customer ::display()
{
    cout << "\n\t|------------------------------------------------------------------------------------------------------------|";
    cout << "\n\t|                                         -----Customer Details-----                                         |";
    cout << "\n\t|------------------------------------------------------------------------------------------------------------|";
    cout << "\n\n\t\tCustomer name : " << cus_name << endl;
    cout << "\n\t\tCustomer ID   : " << cus_id << endl;
    cout << "\n\t\tCustomer vehicle registration number : " << cus_regno << endl;
    cout << "\n\t\tCustomer vehicle plate number : " << cus_vehno << endl;
    cout << "\n\t\tCustomer vehicle type   : ";
    if (cus_vehType == 1)
        cout << vech1 << endl;
    else if (cus_vehType == 2)
        cout << vech2 << endl;
    else if (cus_vehType == 3)
        cout << vech3 << endl;
    else if (cus_vehType == 4)
        cout << vech4 << endl;
    else if (cus_vehType == 5)
        cout << vech5 << endl;
    else if (cus_vehType == 6)
        cout << vech6 << endl;
    else if (cus_vehType == 7)
        cout << vech7 << endl;
    else if (cus_vehType == 8)
        cout << vech8 << endl;
    else if (cus_vehType == 9)
        cout << vech9 << endl;
    else if (cus_vehType == 10)
        cout << vech10 << endl;

    cout << "\n\t------------------------------------------------------------------------------------------------------------|\n\n";

    if (cus_vehType == 1 || cus_vehType == 10)
        cout << "\n\t\tYou are excempted from paying toll tax!!!\n\n";

    system("pause");
    system("cls");
}

void CalculateBill ::findWeight()
{
    if (cus_vehType > 1 && cus_vehType <= 10)
    {
        cout << "\nThe following show the estimated weight of particular vechile type" << endl;
        cout << "\n---------------------------------------------------------------------------------------------------------------------\n";
        ifstream vehweg("vehicleWeight.txt");
        char str[300];
        while (vehweg)
        {
            vehweg.getline(str, 300);
            if (vehweg)
                cout << str << endl;
        }
        vehweg.close();
        cout << "\n---------------------------------------------------------------------------------------------------------------------\n";
        cout << "\nEnter the gross vehicle weight rating (GVWR) of the vechile : ";
        cin >> weight;
    }
    cout << "\n\n\n\t\t\tProcessing.....";
    Sleep(3000);
    system("cls");
    findJourney();
}
void CalculateBill ::findJourney()
{
    try
    {
        do
        {
            cout << "\n\nSelect your choice based upon following travelling options " << endl;
            cout << "\n1. Single Journey \n2. Return Journey\n";
            cout << "\nPlease enter the choice : ";
            cin >> journey;
            if (journey > 2 || journey < 1)
                cout << "\nInvalid Choice !! Enter again ";
        } while (journey > 2 || journey < 1);
    }
    catch (...)
    {
        cout << "\nException Caught\n";
    }
    calculate_bill();
}
void CalculateBill ::calculate_bill()
{
    if (journey == 1)
    {
        if (cus_vehType == 2)
            bill += 80;
        else if (cus_vehType == 3)
            bill += 110;
        else if (cus_vehType == 4)
            bill += 160;
        else if (cus_vehType == 5)
            bill += 300;
        else if (cus_vehType == 6)
            bill += 380;
        else if (cus_vehType == 7)
            bill += 500;
        else if (cus_vehType == 8)
            bill += 600;
        else if (cus_vehType == 9)
            bill += 550;
        else if (cus_vehType == 10)
            bill += 0;
    }
    else
    {
        if (cus_vehType == 2)
            bill += 120;
        else if (cus_vehType == 3)
            bill += 160;
        else if (cus_vehType == 4)
            bill += 250;
        else if (cus_vehType == 5)
            bill += 500;
        else if (cus_vehType == 6)
            bill += 550;
        else if (cus_vehType == 7)
            bill += 800;
        else if (cus_vehType == 8)
            bill += 1000;
        else if (cus_vehType == 9)
            bill += 850;
        else if (cus_vehType == 10)
            bill += 0;
    }
    // Bill calculate due to overweight of vechile
    if (cus_vehType == 2)
    {
        if (weight >= 5000)
        {
            bill = bill * 2; // Double charges due to overweight
            weightFlag += 1;
        }
    }
    else if (cus_vehType == 3)
    {
        if (weight >= 7500)
        {
            bill = bill * 2; // Double charges due to overweight
            weightFlag += 1;
        }
    }
    else if (cus_vehType == 4)
    {
        if (weight > 7500 && weight <= 12000)
            bill = bill; // No changes in bill
        else
        {
            bill = bill * 2;
            weightFlag += 1;
        }
    }
    else if (cus_vehType == 5)
    {
        if (weight > 16000 && weight <= 25000)
            bill = bill;
        else
        {
            bill = bill * 2;
            weightFlag += 1;
        }
    }
    else if (cus_vehType == 6)
    {
        if (weight > 25000 && weight <= 30000)
            bill = bill;
        else
        {
            bill = bill * 2;
            weightFlag += 1;
        }
    }
    else if (cus_vehType == 7)
    {
        if (weight > 35000 && weight <= 45000)
            bill = bill;
        else
        {
            bill = bill * 2;
            weightFlag += 1;
        }
    }
    else if (cus_vehType == 8)
    {
        if (weight > 54000)
            bill = bill;
        else
        {
            bill = bill * 2;
            weightFlag += 1;
        }
    }
    else if (cus_vehType == 9)
    {
        if (weight > 44000 && weight < 50000)
            bill = bill;
        else
        {
            bill = bill * 2;
            weightFlag += 1;
        }
    }
    showbill();
}

void CalculateBill ::showbill()
{
    cout << "\n\n\t\tGenerating the bill..........\n\n\n";
    Sleep(3000);
    system("cls");
    cout << "\n\t\t	-------------------------------------------------------------------  " << endl;
    cout << "\t\t\t |          Toll Booth Management System - Customer Invoice         |   " << endl;
    cout << "\n\t\t	-------------------------------------------------------------------  " << endl;
    cout << "\t\t\t| Invoice Number              : "
         << "#SacZ" << rand() << " |" << endl;
    cout << "\t\t\t| Customer Name               : " << cus_name << " |" << endl;
    cout << "\t\t\t| Customer ID                 : " << cus_id << " |" << endl;
    cout << "\t\t\t| Vehicle registration number : " << cus_regno << " |" << endl;
    cout << "\t\t\t| Vehicle plate number        : " << cus_vehno << " |" << endl;
    cout << "\t\t\t| Customer vehicle class      : ";
    if (cus_vehType == 2)
        cout << vech2;
    else if (cus_vehType == 3)
        cout << vech3;
    else if (cus_vehType == 4)
        cout << vech4;
    else if (cus_vehType == 5)
        cout << vech5;
    else if (cus_vehType == 6)
        cout << vech6;
    else if (cus_vehType == 7)
        cout << vech7;
    else if (cus_vehType == 8)
        cout << vech8;
    else if (cus_vehType == 9)
        cout << vech9;

    cout << " |" << endl;
    cout << "\t\t\t| Customer Journey            : ";
    (journey == 1) ? cout << "Single" : cout << "Return";
    cout << " |" << endl;
    cout << "\t\t\t| Customer vehicle weight     : " << weight << " KG"
         << " |" << endl;
    cout << "\t\t\t| Customer vehicle weight is ";
    (weightFlag > 0) ? cout << "Overweight" : cout << "Underweight";
    cout << " |" << endl;
    cout << "\t\t\t| Caution Money     : "
         << "Rs. 0"
         << " |" << endl;
    cout << "\t\t\t| Advanced          : "
         << "Rs. 0"
         << " |" << endl;
    cout << "\t\t	 _______________________________________________________________" << endl;
    cout << "\n";
    cout << "\t\t\t| Total Toll Amount : "
         << " Rs. " << bill << " |" << endl;
    cout << "\t\t	 _______________________________________________________________" << endl;
    cout << "\n\t\t	 # This is a computer generated invoce and it does not" << endl;
    cout << "\t\t	 require an authorised signture #" << endl;
    cout << " " << endl;
    cout << "\t\t	----------------------------------------------------------------------" << endl;
    cout << "\t\t	You are advised to pay up the amount." << endl;
    cout << "\t\t	----------------------------------------------------------------------\n\n"
         << endl;
    system("pause");
    system("cls");
}

void Payment ::payment_opt()
{
    system("cls");
    do
    {
        cout << "\nPlease select the payment option from the following as per your convenient \n";
        cout << "\n1. UPI payment(Amazon pay/ PhonePe/ GPay/patym,.etc) \n2. Manual Payment(Cash) \n3. Fast Tag \n4. Debit/credit card\n";
        try
        {
            cout << "\n\tEnter your choice : ";
            cin >> pay_choice;
        }
        catch (...)
        {
            cout << "\nException Caught\n";
        }

        switch (pay_choice)
        {
        case 1:
            UPI_payment();
            break;
        case 2:
            Manual_payment();
            break;
        case 3:
            FastTag_payment();
            break;
        case 4:
            DebitCredit_payment();
            break;
        default:
            cout << "\nInvalid choice! Re-enter your Choice ! ";
            break;
        }
    } while (pay_choice < 1 || pay_choice > 4);
}
void Payment ::UPI_payment()
{
    int opt;
    cout << "\n\nChoice the method of UPI payment" << endl;
    cout << "\n1. Scan QR code and make payment\n2. Enter the UPI ID to make payment" << endl;

    try
    {
        cout << "\n\tEnter the choice : ";
        cin >> opt;
        if (opt == 2)
        {
            cout << "\nEnter the UPI ID : ";
            cin >> upi_id;
        }
    }
    catch (...)
    {
        cout << "\nException Caught\n";
    }
    cout << "\n\n\tConfirming the payment !" << endl;
    Sleep(3000);
    cout << "\n\n\t\t\tPayment Successful !!!" << endl;
    Sleep(3000);
    system("cls");
}

void Payment ::Manual_payment()
{
    try
    {
        cout << "\n\nEnter the cash amount Submitted by customer : ";
        cin >> cash;
    }
    catch (...)
    {
        cout << "\nException Caught\n";
    }
    cout << "\nAmount tobe return to customer is : " << cash - bill << endl;
    cout << "\n\n\t\t\tPayment Successful !!!" << endl;
    Sleep(3000);
    system("cls");
}

void Payment ::FastTag_payment()
{
    try
    {
        cout << "\n\nEnter fast Tag Id : ";
        cin >> fastTag_id;
    }
    catch (...)
    {
        cout << "\nException Caught\n";
    }

    fstream ftagUser;
    ftagUser.open("FastTagUsers.txt");
    char str[20];
    int flag = 0;
    while (!ftagUser.eof())
    {
        ftagUser >> str; // to take a particular word from file
        if (strcmp(fastTag_id, str) == 0)
        {
            flag += 1;
            cout << "\n\n\tConfirming the payment !" << endl;
            Sleep(3000);
            cout << "\n\n\t\t\tPayment Successful !!!" << endl;
            Sleep(3000);
            system("cls");
            break;
        }
    }
    ftagUser.close();

    if (flag == 0)
    {
        cout << "\n\nFast Tag ID not found ! Please try another payment option !!!";
        Sleep(3000);
        system("cls");
        payment_opt();
    }
}
void Payment ::DebitCredit_payment()
{
    cout << "\nPlease provide the following information " << endl;
    try
    {
        cout << "\nEnter the card number : ";
        cin >> card_no;
        cout << "\nEnter expiry year : ";
        cin >> expireYear;

        string cvv = "";
        char c;
        cout << "\nEnter CVV : ";
    p:
        c = getch();
        cout << "*"; // for printing * instead for password
        if (c != 13)
        {
            cvv = cvv + c; // for concatenating the string
            goto p;
        }
    }
    catch (...)
    {
        cout << "\nException Caught\n";
    }

    cout << "\n\n\tConfirming the payment !" << endl;
    Sleep(3000);
    cout << "\n\n\t\t\tPayment Successful !!!" << endl;
    Sleep(3000);
    system("cls");
}

int main()
{
    char ch;
    login();
    do
    {
        class Summary S;
        S.display_summary();

        ifstream info("thank.txt");
        char str[300];
        while (info)
        {
            info.getline(str, 300);
            if (info)
                cout << str << endl;
        }
        info.close();
        cout << "\n\n\nDo you want to continue with the application [y/n] : ";
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');
}
void login()
{
    ifstream inf("TollBooth.txt");
    char str[300];
    while (inf)
    {
        inf.getline(str, 300);
        if (inf)
            cout << str << endl;
    }
    inf.close();

    cout << "\n\t\t|---------------------------------------------------------|";
    cout << "\n\t\t|            Toll Booth Management System                 |";
    cout << "\n\t\t|---------------------------------------------------------|";

    cout << "\n\n\n\t\t-----------Administration Login-----------" << endl;
d:
    long userId;
    cout << "\n\n\t\t\tEnter Login Id = ";
    try
    {
        cin >> userId;
        if (userId != 123)
        {
            cout << "\nWrong ID.....Enter correct ID\n";
            goto d;
        }
    }
    catch (...)
    {
        cout << "\nPlease enter a valid User ID." << endl;
    }
z:
    string pwd = "pass";
    string pass = "";
    char c;
    cout << "\n\n\t\t\tPassword = ";
p:
    c = getch();
    cout << "*"; // for printing * instead for password
    if (c != 13)
    {
        pass = pass + c; // for concatenating the string
        goto p;
    }
    if (pass == pwd)
    {
        cout << "\n\n\n\n\t\t\t\tAccess Granted. Welcome to our system\n\n\n\n";
        system("PAUSE");
        system("CLS");
    }
    else
    {
        cout << "\nWrong Password\n";
        goto z;
    }
}
