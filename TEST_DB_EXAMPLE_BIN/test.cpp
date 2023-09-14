#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
using namespace std;

class Product
{

public:
    int CKI;
    char name[30];
    double price;
    char category[30];

    Product() {}
    Product(int cki, string n, double pr, string c)
    {

        CKI = cki;
        strcpy(name, n.c_str());
        price = pr;
        strcpy(category, c.c_str());
    }

    void print()
    {
        cout << "CKI :" << CKI << "\tName: " << name << "\tPrice: " << price << "\tCat: " << category << endl;
    }
};
bool isExistProduct(int cki)
{

    bool found = false;
    ifstream file_read("PRODUCTS_DATE.dat", ios::in | ios::binary);
    Product p;
    while (file_read.read((char *)&p, sizeof(p)))
    {
        if (p.CKI == cki)
            found = true;
    }
    file_read.close();
    return found;
}

void create(Product p)
{
    ofstream file_create("PRODUCTS_DATE.dat", ios::binary | ios::app);
    file_create.write((char *)&p, sizeof(p));
    file_create.close();
}
void read_Date()
{
    cout << " ----------------------DATA OF ALL PRODUCTS------------------------- " << endl;
    ifstream file_readDate("PRODUCTS_DATE.dat", ios::binary);
    Product p;
    while (file_readDate.read((char *)&p, sizeof(p)))
        p.print();
    file_readDate.close();
}
bool update(int cki)
{
    if(!isExistProduct(cki)){
        cout<<"THE PRODUCT WITH "<<cki<<"  WAS NOT FOUND!";
        return false;
    }
    fstream f("PRODUCTS_DATE.dat", ios::in | ios::out | ios::binary);
    Product p;
    int choice;
    cout<<"\n1-NAME \n2-PRICE \n3-CATEGORY"<<endl;
    cout<<"What do you want update:";
    cin>>choice;

    while (f.read((char *)&p, sizeof(p)))
    {
        if (p.CKI == cki)
        {
            if(choice==1){
                string name;
                cout<<"New NAME:";
                cin>>name;
                strcpy(p.name, name.c_str());
            }
            if(choice==2){
                double price;
                cout<<"New PRICE:";
                cin>>price;
                p.price = price;
            }
            if(choice==3){
                string category;
                cout<<"New CATEGORY:";
                cin>>category;
                strcpy(p.category, category.c_str());
            }
            int t = f.tellg();
            f.seekp(t - sizeof(p), ios::beg);
            f.write((char *)&p, sizeof(p));
            break;
        }
    }
    f.close();
    return true;
}


bool delet(int cki)
{
    ifstream file_read("PRODUCTS_DATE.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    Product p;

    if (!isExistProduct(cki)){
        cout<<"THE PRODUCT WITH "<<cki<<"  WAS NOT FOUND!";
        return false;
    }

    while (file_read.read((char *)&p, sizeof(p)))
    {
        if (p.CKI != cki)
        {
            temp.write((char *)&p, sizeof(p));
        }
    }
    file_read.close();
    temp.close();
    remove("PRODUCTS_DATE.dat");
    rename("temp.dat", "PRODUCTS_DATE.dat");
    return true;
}

int getNewCKI()
{
    ifstream f("PRODUCTS_DATE.dat", ios::in | ios::binary);
    Product p;
    int newCKI = 0;
    while (f.read((char *)&p, sizeof(p)))
    {
        newCKI = p.CKI;
    }
    return newCKI + 1;
}
int main()
{
    read_Date();

    int choice = 1;
    while (choice != 0)
    {

        cout << "\n1 - Read data"
             << "\n2 - Create product"
             << "\n3 - Remove product"
             << "\n4 - Update "
             << "\n99 - Exit" << endl;
        cout << " Inserisci quale intersezione con i dati vuoi fare: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            read_Date();
        }
        break;
        case 2:
        {
            string n, c;
            double p;
            cout << "Nome : ";
            cin >> n;
            cout << "Price : ";
            cin >> p;
            cout << "Category : ";
            cin >> c;
            int ckin = getNewCKI();
            Product pro(ckin, n, p, c);
            create(pro);
            cout << "Product with cki(code key id) : " << ckin << " was created in file!" << endl;
        }
        break;

        case 3:
        {
            int id;
            cout << "CODE KEY ID of product to remove  :";
            cin >> id;  
            if(delet(id))
              cout << "\nProduct with cki" << id << " has been removed !" << endl;
        }
        break;

        case 4: {
             int id;
             cout<<"CKI of product to update:";
             cin>>id;
             if(update(id))
                cout<<"Product with cki "<<id<<" has been update!"; 
        }

        break;

        case 99:
            break;

        default:
            cout << "Intersezione non valida! RIPROVA" << endl;
            break;
        }
        if (choice == 99)
            break;
    }

    read_Date();
}
