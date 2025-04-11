#include <iostream> 
#include <string> 
#include <vector>
#include <iomanip>
#include <fstream>


using namespace std;

//create a function that is called transaction

struct Transaction{
    /*the type veriable is going to hold either income or expense

    description is going to be exactly that
    for example :
    expense, car note 
    expense, gas 
    income, paycheck 
    income, cashapp 
    */

    string type; 
    double amount; 
    string description; 
}; 

//create a vector that is going to store the transactions 
vector<Transaction> transactions; 

//create a function that allows the user to add into the transactions vector
void addTransaction(){
    Transaction t; 

    // ask the user to enter type of transaction 
    cout << "Enter type (income/expense): "; 
    cin >> t.type;
    cin.ignore(); 

    cout << "Enter the amount: $"; 
    cin >> t.amount;
    //make sure the amount is not less than or equal to zero
    while(t.amount <= 0){
        cout << "ERROR.Transaction amount can't be negative.\nEnter the amount: $";
        cin >> t.amount; 
    }

    cin.ignore(); // clear newline for getline 

    cout << "Enter description: "; 
    getline(cin,t.description); 

    transactions.push_back(t); 

    cout << "Transaction successfully added!\n"; 
}


//create a function that allows you to view the transactions

void viewTransactions(){
    //create an edge case incase the vector is empty
    if(transactions.empty()){
        cout << "No transactions at this moment.\n"; 
    }


    //print the vector 
    for(auto t: transactions){
        cout << t.type << "|$" << fixed <<setprecision(2) << t.amount << "|" << t.description << "\n"; 
    }
    cout << endl; 
}


//view the balance in the account
void viewBalance(){
    //set double veriable of balance to 0
    double balance = 0; 
     //create an edge case incase the vector is empty
     if(transactions.empty()){
        cout << "No bal at this moment.\n"; 
    }

  //create a for-loop to go through the transactions vector 
  for(auto t: transactions){
    /*create two different cases
    if the user added an income transaction it will add to the balance 
    if the user added an expense transaction it will be deducted from the balance
    */
    if(t.type == "income"){
        balance += t.amount;
    }else if(t.type == "expense"){
        balance -= t.amount;
    }
    cout << "Current balance: $" << fixed << setprecision(2) << balance << endl;
}
    
  
}

    //create a function that adds the items into a file 
void saveFile(){
    //create the transactions text file
    ofstream file("transactions.txt");
    //with a for loop, add the items into the text file  
    for(auto t: transactions){
        file << t.type << "," << t.amount << "," << t.description << endl;
    }
    //close the file 
    file.close(); 
    cout << "Transaction successfully saved to file!\n"; 
}

//create a function that loads items from the txt  file 
void loadFromFile(){
    ifstream file("transactions.txt");
    string type,description; 
    double amount; 
    char comma; 

    transactions.clear();

    while(file >> type >> comma >> amount >> comma){
        getline(file,description); 
        transactions.push_back({type,amount,description});
    }
    file.close(); 
    cout << "Transactions loaded from file.\n"; 
}

int main(){
   int choice; 

   bool running = true; 
    //create a menu
   while(running){
        cout << "\n\tBudget Tracker Menu\n";
        cout << "1. Add Transaction\n";
        cout << "2. View Transactions\n";
        cout << "3. View Balance\n";
        cout << "4. Save to File\n";
        cout << "5. Load from File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; 
        cout << "\n"; 

        switch (choice) {
            case 1: addTransaction(); break;
            case 2: viewTransactions(); break;
            case 3: viewBalance(); break;
            case 4: saveFile(); break;
            case 5: loadFromFile(); break;
            case 6: running = false; break;
            default: cout << "Invalid choice.\n"; break;
        }

        
   }

   cout << "Goodbye!\n"; 

   return 0; 
}