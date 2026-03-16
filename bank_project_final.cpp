#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;
struct client_data
{
    string account;
    string pin_code;
    string name;
    string phone;
    int salary;
    bool mark_delete=false;
};


int main_menu()
{
    int n;
    cout<<"____________________________________________________________________"<<endl;
    cout<<"\t\t\tMAIN MENU SCREEN"<<endl;
    cout<<"____________________________________________________________________"<<endl;
    cout<<"\t[1] show client list"<<endl;
    cout<<"\t[2] add new client"<<endl;
    cout<<"\t[3] delete client"<<endl;
    cout<<"\t[4] update client infos"<<endl;
    cout<<"\t[5] find client"<<endl;
    cout<<"\t[6] transaction"<<endl;
    cout<<"\t[7] exit"<<endl;
    cout<<"____________________________________________________________________"<<endl;
    cout<<"choose what do you want to do? [1 to 6]"<<endl;
    cin>>n;
    return n;
}


bool check_acc(client_data& record,string num,vector<client_data> vf)
{
       for(client_data n: vf)
    {
    if(n.account==num)
    {
    record=n;
    return true;
    }
}
return false;
}



string get_acc_num()
{
    string acc_num;
    cout<<"enter account number: ";
    cin>>acc_num;
    return acc_num;
}


client_data get_data(vector<client_data>vf)
{
    client_data new_client;
   cout << "enter account number: ";
cin >> new_client.account;
while (check_acc(new_client, new_client.account, vf))
 {
    cout << " client with this account number already exists!" << endl;
    cout << "please enter another account number: ";
    cin >> new_client.account;
 }
    cout<<"enter pin_ code: ";
    cin>>new_client.pin_code;
    cout<<"enter your name: ";
    cin>>new_client.name;
    cout<<"enter phone number: ";
    cin>>new_client.phone;
    cout<<"enter your salary: ";
    cin>>new_client.salary;
    return new_client;
}


string convert_rec(client_data client,string space)
{
    string s;
    s=s+client.account+space;
    s=s+client.pin_code+space;
    s=s+client.name+space;
    s=s+client.phone+space;
    s=s+to_string(client.salary)+space;
    s=s.substr(0,s.length()-space.length());
    return s;
}


vector<string>split_string(string line, string space)
{
    vector<string> vword;
    string word;
    int pos;
    while((pos=line.find(space))!=std::string::npos)
    {
        word=line.substr(0,pos);
        if(word!="")
        {
            vword.push_back(word);
        }
        line.erase(0,pos+space.length());
    }
   // if(line!="")
    vword.push_back(line);
    return vword;
}



client_data convert_line(string s,string space)
{
vector<string> vs=split_string(s,space);
client_data record;
record.account=vs[0];
record.pin_code=vs[1];
record.name=vs[2];
record.phone=vs[3];
record.salary=stoi(vs[4]);
return record;
}




vector<client_data> vload(string filename)
{
   
    fstream bank;
    vector<client_data> vfile;
    bank.open(filename,ios::in);
    if(bank.is_open())
    {
         string line;
    client_data client;
        while(getline(bank,line))
        {
            client=convert_line(line,"#//#");
            vfile.push_back(client);
        }
        bank.close();
    }
    return vfile;
}



void save_to_file(string filename,string line)
{
    fstream bank;
    bank.open(filename,ios::app);
    if(bank.is_open())
    {

        bank<<line<<endl;
        bank.close();
    }

}


void save_non_del(string filename,vector<client_data>vf)
{
fstream bank;
string line;
bank.open(filename,ios::out|ios::trunc);
if(bank.is_open())
{
    for(client_data c: vf)
    {
        if(c.mark_delete==false)
        {
            line=convert_rec(c,"#//#");
            bank<<line<<endl;

        }
    }
    bank.close();
}
}



void save_update(string filename,vector<client_data> vf)
{
    fstream bank;
    bank.open(filename,ios::out|ios::trunc);
    string line;
    if(bank.is_open())
    {
        for(client_data c: vf)
        {
        line=convert_rec(c,"#//#");
        bank<<line<<endl;
        }
        bank.close();
    }
}


void ask_for_add( vector<client_data>& vf)
{
     char an='y';
    do
    {
       
    client_data client=get_data(vf);
  
    string s=convert_rec(client,"#//#");
    save_to_file("bank.txt",s);
    cout<<"client was added succesfully"<<endl;
    cout<<"do you want to add morre clients"<<endl;
    cin>>an;
    }
    while(an=='y'||an=='Y');
}


void print_info(client_data data)
{
  cout<<"| "<<data.account<<setw(15)<<"| "<<data.pin_code<<setw(15)<<"| "<<data.name<<setw(25)<<"| "<<data.phone<<setw(10)<<"| "<<data.salary<<endl;

}

void print_interface(vector<client_data> vd)
{
    cout<<"___________________________________________________________________________________________\n";
    cout<<setw(15)<<"\t\t\t\t\tclients list of "<<vd.size()<< " clients"<<endl;
    cout<<"____________________________________________________________________________________________\n";
    cout<<"|account number"<<setw(15)<<"|pin code"<<setw(15)<<"|name"<<setw(30)<<"|phone "<<setw(15)<<"|balance"<<endl;
    cout<<"__________________________________________________________________________________________\n";
   for(client_data c: vd)
   {
    print_info(c);
    cout<<endl;
   }
}


void print_one_client(client_data record)
{
    cout<<"____________________________________________________________________"<<endl;
    cout<<"\t\t\tCLIENT DETAILS"<<endl;
    cout<<"____________________________________________________________________"<<endl;
   

    cout<<"account number: "<<record.account<<endl;
    cout<<"pin_code: "<<record.pin_code<<endl;
    cout<<"client's name: "<<record.name<<endl;
    cout<<"phone number :"<<record.phone<<endl;
    cout<<"client's salary: "<<record.salary<<endl;    
}




bool mark_rec(vector<client_data> &vf,string acc)
{
    for(client_data& c: vf)
    {
        if(c.account==acc)
        {
            c.mark_delete=true;
            return true;
        }
    }
return false;
}


client_data change_record(string acc)
{
    client_data client;
    client.account=acc;
    cout<<"enter the new pin_code: ";
    cin>>client.pin_code;
    cout<<"enter the new name: ";
    cin>>client.name;
    cout<<"enter new phone number: ";
    cin>>client.phone;
    cout<<"enter the salary: ";
    cin>>client.salary;
    return client;
}


bool update_client(vector<client_data> &vf,string acc)
{
    char a='n';
    client_data c;
    if(check_acc(c,acc,vf))
    {
        print_one_client(c);
        cout<<"are you sure you want to update this client? ";
        cin>>a;
        if(a=='y'||a=='Y')
        {
            for(client_data & cc: vf)
            {
                if(cc.account==acc)
                {
                    cc=change_record(acc); 
                break;
                }
               
            }
             save_update("bank.txt",vf);
             cout<<"client updated succesfully"<<endl;
             return true;

        }
        else 
        {
        cout<<"update cancelled"<<endl;
        return false;
        }
    }
    else
    {
    cout<<"client is not found"<<endl;
    return false;
}
    return false;
}


bool delete_client(vector<client_data> &vf, string acc)
{
    char an='n';
    client_data client;
    if(check_acc(client,acc,vf))
    {
        print_one_client(client);
        cout<<"are you sure you want to delete this client? ";
        cin>>an;
        if(an=='y'||an=='Y')
        {
            mark_rec(vf,acc);
            save_non_del("bank.txt",vf);
            cout<<"client deleted succsefully"<<endl;
            return true;
        }
    }
    else{
    cout<<"client is not found"<<endl;
    return false;
    }
    return false;
}
int trans_screen()
{
    int n;
    system("cls");
    cout<<"__________________________________________________________"<<endl;
    cout<<"\t\t\tTRANSACTION SCREEN"<<endl;
    cout<<"__________________________________________________________"<<endl;
    cout<<"[1] deposit money"<<endl;
    cout<<"[2] withdraw money"<<endl;
    cout<<"[3] show all balances"<<endl;
    cout<<"[4] go back to main menu"<<endl;
    cout<<"enter your choice: "<<endl;
    cin>>n;
    return n;
}
void trans_choices();
void show_main_menu()
{
    int choice;
    choice =main_menu();
   do
{
 switch (choice)
 {
 case 1:
 {
 vector<client_data> vf=vload("bank.txt");
 print_interface(vf);
 cout<<"press any key to go back to main menu"<<endl;
 system("pause");
 break;
 }

  case 2:
  {
    system("cls");
    cout<<"__________________________________________________________"<<endl;
    cout<<"\t\t\tADD NEW CLIENT"<<endl;
    cout<<"__________________________________________________________"<<endl;
     vector<client_data> vf=vload("bank.txt");
  ask_for_add(vf);
   cout<<"press any key to go back to main menu"<<endl;
 system("pause>0");
  break;
  }
 
 case 3:
  {
    system("cls");
    cout<<"__________________________________________________________"<<endl;
    cout<<"\t\t\tDELETE CLIENT"<<endl;
    cout<<"__________________________________________________________"<<endl;
    vector<client_data> vf=vload("bank.txt");
     string acc=get_acc_num();
     delete_client(vf,acc);
      cout<<"press any key to go back to main menu"<<endl;
 system("pause>0");
      break;
  }

  case 4:
  {
      system("cls");
    cout<<"__________________________________________________________"<<endl;
    cout<<"\t\t\tUPDATE CLIENT"<<endl;
    cout<<"__________________________________________________________"<<endl;
     vector<client_data> vf=vload("bank.txt");
     string acc=get_acc_num();
     update_client(vf,acc);
      cout<<"press any key to go back to main menu"<<endl;
 system("pause>0");
     break;
  }
 case 5:
 {
    system("cls");
    cout<<"__________________________________________________________"<<endl;
    cout<<"\t\t\tFIND CLIENT"<<endl;
    cout<<"__________________________________________________________"<<endl;
    vector<client_data> vf=vload("bank.txt");
    client_data client;
     string acc=get_acc_num();
if(check_acc(client,acc,vf))
{
    cout<<"client is found: "<<endl;
    print_one_client(client);

}
else
 cout<<"client is not found"<<endl;
  cout<<"press any key to go back to main menu"<<endl;
 system("pause>0");
break;
 }
 case 6:
 {
trans_choices();
 }
 case 7:
 {
    system("cls");
    cout<<"_________________________EXIT__________________________"<<endl;
exit(0);
 }
default:
 cout<<"invalid number"<<endl;
  choice=main_menu();
 }
 if(choice!=7)
 {
system("cls");
    choice=main_menu();
}
}
while(choice!=7);   
}


int get_money_amount()
{ 
    int mon;
   cin>>mon;
   return mon;
}
    void deposit(vector<client_data>& vf,string acc) 
    {
  client_data client;
  
  if(check_acc(client,acc,vf))
  {
     print_one_client(client);
   cout<<"enter the amount of money you want to deposit: ";
   int n=get_money_amount();
   cout<<"are you sure you want to deposit "<<n<<" to your account? (y/n): ";
   char a;
   cin>>a;
   if(a=='y'||a=='Y'){
    int current_salary = client.salary;
    int new_salary = current_salary + n;
    client.salary = new_salary;
   
 for (client_data& c : vf)
        {
            if (c.account == acc)
            {
                c.salary = new_salary;
                 save_update("bank.txt",vf);
                break;
            }
        }
   cout<<"---MONEY DEPOSETED SUCCESFULLY---"<<endl;
   cout<<"New salary is: "<<new_salary<<endl;
    }
    else {
        cout<<"deposition cancelled"<<endl;
    }
   cout<<"press any key to go back to transaction screen"<<endl;
   system("pause");
   trans_choices();

}
else 
{cout<<"this client is not found"<<endl;
system("pause");
trans_choices();}
}

void withdraw(vector<client_data>& vf,string acc)
{
    client_data client;
  if(check_acc(client,acc,vf))
 {
  print_one_client(client); 
    
      cout<<"enter the amount you want to withdraw: ";
   int n= get_money_amount();

  
   while(n>client.salary)
     {
     cout<<"you don't have enough balance"<<endl;
     cout<<"your current balance is "<<client.salary<<endl;
    cout<<"enter another amount: ";
        n=get_money_amount();
     
     }

    
        cout<<"are you sure you want to withdraw "<<n<<" from your account? (y/n): ";
   char a;
   cin>>a;
    if(a=='y'||a=='Y')
    {
      int current_salary = client.salary;
      int new_salary = current_salary - n;
      client.salary = new_salary;
      for (client_data& c : vf)
        {
            if (c.account == acc)
            {
                c.salary = new_salary;
                 save_update("bank.txt",vf);
                 cout<<"---MONEY WITHDRAWN SUCCESFULLY---"<<endl;
         cout<<"New salary is: "<<new_salary<<endl;
                break;
            }
        }}
    
     
     else
        {
            cout<<"withdraw cancelled"<<endl;
        }
     }
       
     
     else 
     {
        cout<<"Client not found"<<endl;
        
     }
      cout<<"press any key to go back to transaction screen"<<endl;
       system("pause");
       trans_choices();

}


void print_sal_info(client_data data)
{
  cout<<"| "<<data.account<<setw(15)<<"| "<<data.name<<setw(30)<<"| "<<data.salary<<endl;

}

void print_sal_interface(vector<client_data> vd)
{
int sum=0;
    cout<<"|account number"<<setw(15)<<"|name"<<setw(30)<<"|balance"<<endl;
    
    cout<<"_________________________________________________________\n";
    for(client_data &c:vd)
    {
      sum=sum+c.salary;
        print_sal_info(c);
    }
    cout<<"_________________________________________________________"<<endl;
  cout<<"\t\ttotal salaries is :"<<sum<<endl;
}


int main()
{ system("cls");
    show_main_menu();
    return 0;
}


void trans_choices()
{
int choice=trans_screen();

  switch(choice)
  {
    case 1:
    {
      system("cls");
      cout<<"______________________________________________________"<<endl;
      cout<<"\t\t\tDEPOSIT SCREEN"<<endl;
      cout<<"______________________________________________________"<<endl;
       string acc=get_acc_num();
       vector<client_data>vf=vload("bank.txt");
       deposit(vf,acc);
         cout<<"press any key to go back to transaction menu"<<endl;
         system("pause");
         trans_choices();
    }
    break;

    case 2:
    {
      system("cls");
      cout<<"______________________________________________________"<<endl;
      cout<<"\t\t\tWITHDRAW SCREEN"<<endl;
      cout<<"______________________________________________________"<<endl;
       string acc=get_acc_num();
       vector<client_data>vf=vload("bank.txt");
       client_data client;
       withdraw(vf,acc);
  }
  break;

case 3:
{
    system("cls");
    cout<<"_________________________________________________________"<<endl;
    cout<<"\t\t\tALL BALANCES SCREEN"<<endl;
    cout<<"_________________________________________________________"<<endl;
    vector<client_data> vf=vload("bank.txt");
     print_sal_interface(vf);
     cout<<"press any key to go back to transaction menu"<<endl;
         system("pause");
          trans_choices();
}

break;

case 4:
{
    system("cls");
    show_main_menu();
    break;
}
}
}