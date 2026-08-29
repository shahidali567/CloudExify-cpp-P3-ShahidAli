#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
#include<sstream>
using namespace std;

struct BankAccount{
    int id;
    string customer;
    double balance;
    string category; 
    };

struct BankTransaction{
    int id;
    string action;
    double amount;
    double newBalance;
};

const string ACCOUNT_DATA="accounts.dat";
const string TRANSACTION_DATA="transactions.dat";
vector<BankAccount> bankAccounts;
vector<BankTransaction> bankTransactions;
int accountCounter=1001;

BankAccount* getAccount(int id){
    for(auto& account:bankAccounts){
        if(account.id==id)
            return &account; }
    return nullptr; }

void recordTransaction(int id,string action,double amount,double balance){
    BankTransaction transaction;
    transaction.id=id;
    transaction.action=action;
    transaction.amount=amount;
    transaction.newBalance=balance;
    bankTransactions.push_back(transaction); }

void createBankAccount(){
    BankAccount account;
    cout<<"\n========== CREATE ACCOUNT ==========\n";
    account.id=accountCounter++;
    cout<<"Customer Name: ";
    cin.ignore();
    getline(cin,account.customer);
    if(account.customer.empty()){
        cout<<"Name cannot be empty!\n";
        accountCounter--;
        return; }
        
    cout<<"Account Type (Savings S /Checking C): ";
    getline(cin,account.category);
    if(account.category!="S"&&account.category!="s"&&
       account.category!="C"&&account.category!="c"){
        cout<<"Invalid account type!\n";
        accountCounter--;
        return;
    }
    if(account.category=="s")
        account.category="Savings";
    if(account.category=="c")
        account.category="Checking";
    cout<<"Opening Balance (Rs): ";
    cin>>account.balance;

    if(cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"Invalid amount!\n";
        accountCounter--;
        return; }

    if(account.balance<0){
        cout<<"Balance cannot be negative!\n";
        accountCounter--;
        return;  }

    bankAccounts.push_back(account);

    if(account.balance>0)
        recordTransaction(account.id,"Opening Balance",account.balance,account.balance);

    cout<<"\nAccount created successfully!\n";
    cout<<"Account Number: "<<account.id<<endl;
    cout<<"Customer Name: "<<account.customer<<endl;
    cout<<"Account Type: "<<account.category<<endl;
    cout<<"Balance: Rs "<<fixed<<setprecision(2)<<account.balance<<endl;
}

void addMoney(){
    if(bankAccounts.empty()){
        cout<<"\nNo accounts available!\n";
        return; }

    int id;
    cout<<"\n========== DEPOSIT MONEY ==========\n";
    cout<<"Account Number: ";
    cin>>id;
    BankAccount* account=getAccount(id);

    if(account==nullptr){
        cout<<"Account not found!\n";
        return; }

    double amount;
    cout<<"Amount to deposit (Rs): ";
    cin>>amount;
    if(cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"Invalid amount!\n";
        return;  }

    if(amount<=0){
        cout<<"Amount must be positive!\n";
        return; }

    account->balance+=amount;
    recordTransaction(account->id,"Deposit",amount,account->balance);
    cout<<"\nDeposit successful!\n";
    cout<<"Deposited: Rs "<<fixed<<setprecision(2)<<amount<<endl;
    cout<<"New Balance: Rs "<<account->balance<<endl;
}

void takeMoney(){
    if(bankAccounts.empty()){
        cout<<"\nNo accounts available!\n";
        return; }

    int id;
    cout<<"\n========== WITHDRAW MONEY ==========\n";
    cout<<"Account Number: ";
    cin>>id;
    BankAccount* account=getAccount(id);
    
    if(account==nullptr){
        cout<<"Account not found!\n";
        return;  }
    double amount;
    cout<<"Amount to withdraw (Rs): ";
    cin>>amount;

    if(cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"Invalid amount!\n";
        return;  }

    if(amount<=0){
        cout<<"Amount must be positive!\n";
        return; }

    if(amount>account->balance){
        cout<<"\nTransaction failed!\n";
        cout<<"Insufficient balance!\n";
        cout<<"Available Balance: Rs "<<fixed<<setprecision(2)<<account->balance<<endl;
        return;  }

    account->balance-=amount;
    recordTransaction(account->id,"Withdraw",amount,account->balance);
    cout<<"\nWithdrawal successful!\n";
    cout<<"Withdrawn: Rs "<<fixed<<setprecision(2)<<amount<<endl;
    cout<<"Remaining Balance: Rs "<<account->balance<<endl;
}

void showBalance(){
    if(bankAccounts.empty()){
        cout<<"\nNo accounts available!\n";
        return;  }

    int id;
    cout<<"\n========== CHECK BALANCE ==========\n";
    cout<<"Account Number: ";
    cin>>id;
    BankAccount* account=getAccount(id);
    if(account==nullptr){
        cout<<"Account not found!\n";
        return; }

    cout<<"\nCustomer: "<<account->customer<<endl;
    cout<<"Account Number: "<<account->id<<endl;
    cout<<"Account Type: "<<account->category<<endl;
    cout<<"Current Balance: Rs "<<fixed<<setprecision(2)<<account->balance<<endl; 
}

void showHistory(){
    if(bankTransactions.empty()){
        cout<<"\nNo transactions available!\n";
        return;  }

    int id;
    cout<<"\n========== TRANSACTION HISTORY ==========\n";
    cout<<"Account Number: ";
    cin>>id;
    BankAccount* account=getAccount(id);

    if(account==nullptr){
        cout<<"Account not found!\n";
        return;  }

    int total=0;
    cout<<"\nLast 10 Transactions\n";
    cout<<string(70,'-')<<endl;
    cout<<left<<setw(20)<<"Type"
        <<setw(18)<<"Amount (Rs)"
        <<setw(18)<<"Balance (Rs)"<<endl;

    cout<<string(70,'-')<<endl;

    for(int i=(int)bankTransactions.size()-1;i>=0&&total<10;i--){
        if(bankTransactions[i].id==id){
            cout<<left<<setw(20)<<bankTransactions[i].action
                <<setw(18)<<fixed<<setprecision(2)<<bankTransactions[i].amount
                <<setw(18)<<bankTransactions[i].newBalance<<endl;
            total++;
        }}

    if(total==0)
        cout<<"No transactions found for this account.\n";

    cout<<string(70,'-')<<endl;
}

void addInterest(){
    if(bankAccounts.empty()){
        cout<<"\nNo accounts available!\n";
        return; }

    int id;
    cout<<"\n========== SAVINGS INTEREST ==========\n";
    cout<<"Account Number: ";
    cin>>id;
    BankAccount* account=getAccount(id);

    if(account==nullptr){
        cout<<"Account not found!\n";
        return; }

    if(account->category!="Savings"){
        cout<<"Interest is only available for Savings accounts!\n";
        return; }

    const double interestRate=5.0;
    double interest=account->balance*interestRate/100;
    account->balance+=interest;
    recordTransaction(account->id,"Interest",interest,account->balance);
    cout<<"\nInterest Rate: "<<interestRate<<"%"<<endl;
    cout<<"Interest Earned: Rs "<<fixed<<setprecision(2)<<interest<<endl;
    cout<<"New Balance: Rs "<<account->balance<<endl;
}

void showAll(){
    if(bankAccounts.empty()){
        cout<<"\nNo accounts available!\n";
        return; }

    cout<<"\n========== ALL ACCOUNTS ==========\n";
    cout<<left<<setw(12)<<"Account No"
        <<setw(22)<<"Customer"
        <<setw(15)<<"Type"
        <<setw(18)<<"Balance"<<endl;

    cout<<string(67,'-')<<endl;

    for(const auto& account:bankAccounts){
        cout<<left<<setw(12)<<account.id
            <<setw(22)<<account.customer
            <<setw(15)<<account.category
            <<setw(18)<<fixed<<setprecision(2)
            <<account.balance<<endl; }
            
    cout<<string(67,'-')<<endl;
}

void saveAccounts(){
    ofstream file(ACCOUNT_DATA);

    if(!file){
        cout<<"Error saving accounts!\n";
        return; }

    for(const auto& account:bankAccounts){
        file<<account.id<<"|"
            <<account.customer<<"|"
            <<account.balance<<"|"
            <<account.category<<endl;  }

    file.close();
}

void loadAccounts(){
    ifstream file(ACCOUNT_DATA);
    if(!file)
        return;
    bankAccounts.clear();
    string line;

    while(getline(file,line)){
        stringstream data(line);
        BankAccount account;
        string id;
        string balance;
        getline(data,id,'|');
        getline(data,account.customer,'|');
        getline(data,balance,'|');
        getline(data,account.category,'|');

        if(id.empty())
            continue;

        account.id=stoi(id);
        account.balance=stod(balance);
        bankAccounts.push_back(account);

        if(account.id>=accountCounter)
            accountCounter=account.id+1;
    }
    file.close();
}

void saveTransactions(){
    ofstream file(TRANSACTION_DATA);

    if(!file){
        cout<<"Error saving transactions!\n";
        return; }

    for(const auto& transaction:bankTransactions){
        file<<transaction.id<<"|"
            <<transaction.action<<"|"
            <<transaction.amount<<"|"
            <<transaction.newBalance<<endl;  }
    file.close();
}

void loadTransactions(){
    ifstream file(TRANSACTION_DATA);
    if(!file)
        return;

    bankTransactions.clear();
    string line;
    while(getline(file,line)){
        stringstream data(line);
        BankTransaction transaction;
        string id;
        string amount;
        string balance;
        getline(data,id,'|');
        getline(data,transaction.action,'|');
        getline(data,amount,'|');
        getline(data,balance,'|');

        if(id.empty())
            continue;

        transaction.id=stoi(id);
        transaction.amount=stod(amount);
        transaction.newBalance=stod(balance);
        bankTransactions.push_back(transaction);
    }
    file.close();
}

void displayMenu(){
    cout<<"\n============================================\n";
    cout<<"           BANKING MANAGEMENT SYSTEM\n";
    cout<<"============================================\n";
    cout<<"1. Create New Account\n";
    cout<<"2. Deposit Money\n";
    cout<<"3. Withdraw Money\n";
    cout<<"4. Check Balance\n";
    cout<<"5. View Last 10 Transactions\n";
    cout<<"6. Calculate Savings Interest\n";
    cout<<"7. Display All Accounts\n";
    cout<<"8. Save Data\n";
    cout<<"9. Exit\n";
    cout<<"Enter your choice: ";
}

int main(){
    loadAccounts();
    loadTransactions();
          int choice;
    do{
        displayMenu();
        cin>>choice;

    if(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"\nInvalid input! Please enter a number.\n";
            continue;  }

 switch(choice){
        case 1:
                createBankAccount();
                break;
        case 2:
                addMoney();
                break;
        case 3:
                takeMoney();
                break;
        case 4:
                showBalance();
                break;
        case 5:
                showHistory();
                break;
        case 6:
                addInterest();
                break;
        case 7:
                showAll();
                break;
        case 8:
                saveAccounts();
                saveTransactions();
                cout<<"\nData saved successfully!\n";
                break;
        case 9:
                saveAccounts();
                saveTransactions();
                cout<<"\nData saved successfully.\n";
                cout<<"Thank you for using the Banking System!\n";
                break;
        default:
                cout<<"\nInvalid choice! Please select 1-9.\n";
        }
    }while(choice!=9);
    return 0;
}