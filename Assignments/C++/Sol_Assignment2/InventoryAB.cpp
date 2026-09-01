#include<iostream>
#include<iomanip>
using namespace std;

class Product{

    private:

    int productId;
    string name;
    double price;
    int quantity;

    public :

    void acceptDetails(){
        cout << " Enter ProductID :";
        cin >> productId;
        cout << " Enter Name :";
        cin >> name;
        cout << " Enter Price :";
        cin >> price;
        cout << " Enter Quantity :";
        cin >> quantity;
    }

    double totalValue() const {

        return price * quantity ;
    }

    void displayDetails() const {
        cout << setw(10) << left << productId<< "  " <<setw(15) << name << "  "<<setw(10) << price << "  "<<setw(10) << quantity << "  " << setw(10) << totalValue()<< endl;
    }

    

    bool isLowStock(int threshold) const {
        if (threshold > quantity) return true;
        return false;

    }

    string getName() const {
        return name;
    }
};

double reorderCost(int qty, double unitprice){
    return qty*unitprice;
}


double reorderCost(double qty, double unitprice){
    return qty*unitprice;
}
double reorderCost(int qty, double unitprice, double taxrate){
    return qty * unitprice * (1+taxrate);
}

double applyDiscount(double price, double discountPercent = 10.0){
    return price * (1-(discountPercent/100));
}// If no discount is passed, apply 10% by default


int main(){
    Product arr[2];

    for(int i = 0; i<2 ; i++){
        arr[i].acceptDetails();
    }
    
    cout <<"===== INVENTORY MANAGEMENT =====" << endl;
    cout << setw(10) << left << "ID"  << "  " <<setw(15) << "NAME" << "  " <<setw(10) << "Price" << "  " << setw(10) <<"Qty" << "  " << setw(10) <<"Total Value " << endl;
    for(int i = 0; i<2 ; i++){
        arr[i].displayDetails();
    }
    cout<< "............." << endl;
    double high = 0;
    string highname;
    for(int i = 0; i<2 ; i++){
        if(high<arr[i].totalValue()) {
            high =arr[i].totalValue();
            highname = arr[i].getName();
        }
    }

    cout<< "Highest Value Product :" << highname << " (" << high << ")" << endl;

    cout<< "Low Stock (threshhold : 10) :";

    for(int i = 0; i<2 ; i++){
        if(arr[i].isLowStock(10)){
            cout << arr[i].getName() << "," ;
        }
    }
    cout<< "............." << endl;


    cout<<reorderCost(10, 12.80)<<endl;
	cout<<reorderCost(20.7, 200.8)<<endl;
	cout<<reorderCost(45, 250, 10)<<endl;
	cout<<applyDiscount(2000, 20.1)<<endl;

    return 0;
}