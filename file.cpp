#include<bits/stdc++.h>
// Header Files End

using namespace std;


class Item{

    string name;
    bool isImported;
    string category;
    float price;

public:

    Item(string name,bool imported,string category,float price){
        this->name=name;
        this->isImported=imported;
        this->category=category;
        this->price=price;
    }

    string getName(){
        return name;
    }

    float getPrice(){
        return price;
    }

    string getCategory(){
        return category;
    }


    bool imported(){
        return isImported;
    }

    // setters can also be declared but not needed here

};

class BilledItem{

public:

    string name;
    int quantity;
    float totalPrice;
};
class GenerateInvoice{

    float salesTaxPercentage=10.0;
    float importedTaxPercentage=5.0;

    map<string,bool> salesTaxNotApplicable;


public:

    GenerateInvoice(){
        salesTaxNotApplicable["books"]=true;
        salesTaxNotApplicable["medical"]=true;
        salesTaxNotApplicable["food"]=true;
    }

    float calculateTotalItemPrice(Item currItem,int quantity){
        return currItem.getPrice()*quantity;
    }

    float calculateSalesTax(float itemTotal,string itemCategory){

        if(salesTaxNotApplicable[itemCategory]==true)return 0.0;

        float salesTax=(salesTaxPercentage*itemTotal)/100.00;

        return salesTax;
    }

    float calculateImportTax(float itemTotal,bool isImported){

        if(isImported==false)return 0.0;

        float importTax=(importedTaxPercentage*itemTotal)/100.00;

        return importTax;

    }

    void printInvoice(vector<BilledItem> allBilledItems,float totalSalesTax,float totalImportTax){

        cout<<"Item Name  "<<" Quantity  "<<"TotalPrice"<<endl;

        float nettPrice=0.0;

        for(int i=0;i<allBilledItems.size();i++){
            
            cout<<allBilledItems[i].name<<"        "<<allBilledItems[i].quantity<<"          "<<allBilledItems[i].totalPrice<<endl;
            nettPrice+=allBilledItems[i].totalPrice;
        }

        cout<<"\nTotal Sales Tax: "<<totalSalesTax<<endl;
        cout<<"Total Import Tax: "<<totalImportTax<<endl;

        nettPrice+=totalSalesTax+totalImportTax;

        cout<<"Nett Price: "<<nettPrice<<endl;
    }

    void generateBill(vector<pair<Item,int>> items){

        vector<BilledItem> allBilledItems;

        float totalSalesTax=0.0;
        float totalImportTax=0.0;

        for(int i=0;i<items.size();i++){

            BilledItem currItem;
            currItem.name=items[i].first.getName();
            currItem.quantity=items[i].second;

            currItem.totalPrice=calculateTotalItemPrice(items[i].first,items[i].second);

            allBilledItems.push_back(currItem);

            totalSalesTax+=calculateSalesTax(currItem.totalPrice,items[i].first.getCategory());

            totalImportTax+=calculateImportTax(currItem.totalPrice,items[i].first.imported());
        }

        printInvoice(allBilledItems,totalSalesTax,totalImportTax);
    }
};



int main(){

    int totalItemsBought;
    cin>>totalItemsBought;

    vector<pair<Item,int>> allItems;

    for(int i=0;i<totalItemsBought;i++){
         
        string name,category;
        int imported,quantity;
        float price;
        cin>>name>>price>>imported>>category>>quantity;

        Item currItem(name,imported,category,price);

        allItems.push_back({currItem,quantity});

    }

    GenerateInvoice invoice;

    invoice.generateBill(allItems);
    
}

