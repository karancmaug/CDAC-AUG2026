#include<iostream>
#include<iomanip>
using namespace std;

class Patient{


    int patientId;
    string name;
    int age;
    string ward;
    const string bloodGroup;

    public :

    Patient() : patientId(0), name("Unknown"), age(0), ward("General"), bloodGroup("O+"){
        cout << " [Constructor] Default patient registered." << endl;
    }


    Patient(int id, const string& name) : patientId(id), name(name), age(0), ward("General"), bloodGroup("O+"){
        cout << " [Constructor] Emergency:" << name << endl;
    }


    Patient(int id, const string& name, int age, const string& ward, const string& bg) : patientId(id), name(name), age(age), ward(ward), bloodGroup(bg){
        cout << " [Constructor] Full admission:" << name << endl;
    }


    string getName(){
        return name;
    }


    ~Patient(){
        cout << " Patient " << getName() << " discharged. " << endl;
    }


    void displayRecord() const{
        cout << "Patient Record :" << endl;
        cout << setw(10)<< left<< " ID"<<":"<<patientId << endl;
        cout << setw(10)<< left<< " Name"<<":"<<name << endl;
        cout << setw(10)<< left<< " Age"<<":"<<age << endl;
        cout << setw(10)<< left<< " Ward"<<":"<<ward<< endl;
        cout << setw(10)<< left<< " Blood Grp"<<":"<<bloodGroup << endl;
        cout << endl;
    }
    
    
    void transferWard(const string& newWard){
        ward = newWard ;
        cout << "Ward Transfer : " << name << "->" << ward << endl;
    }


};


int main(){

    Patient p1;

    Patient p2(101, "Jeevan" );

    Patient p3(121, "Given", 18, "General", "O-");

    Patient *arr = new Patient[4];

    cout<<endl;

    // arr[1]->transferWard("ICU");

    for (int i = 0; i < 4; i++) {
        arr[i].displayRecord();
    }

    p1.transferWard("ICU");
    cout<<endl;

    delete[] arr;

    return 0;


}