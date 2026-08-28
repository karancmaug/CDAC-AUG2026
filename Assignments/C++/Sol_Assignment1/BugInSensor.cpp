#include<iostream>
using namespace std;

void resetSensorPairV1(int reading1,int reading2){
    int temp = reading1;
    reading1 = reading2;
    reading2 = temp;
}

void resetSensorPairV2(int &reading1,int &reading2){
    int temp = reading1;
    reading1 = reading2;
    reading2 = temp;
}

void resetSensorPairV3(int *reading1,int *reading2){
    int temp = *reading1;
    *reading1 = *reading2;
    *reading2 = temp;
}

int main(){
    int reading_1=10,reading_2=7;
    
    
    cout << "--- V1 : Call by value ---" << endl;
    cout << "Before : " << "A = " << reading_1 << "  " << "B = " << reading_2 <<endl;
    resetSensorPairV1(reading_1,reading_2);
    cout << "After  : " << "A = " << reading_1 << "  " << "B = " << reading_2 <<"   <---Value unchanged"<<endl;
    //In this cases we are creating a copy of these value in the function scope which have different memory address but same value
    // i.e they are not the same as in main function thatswhy when we swap these values the main reading does not change.

    
    cout << "--- V2 : Call by Reference ---" << endl;
    cout << "Before : " << "A = " << reading_1 << "  " << "B = " << reading_2 <<endl;
    resetSensorPairV2(reading_1,reading_2);
    cout << "After  : " << "A = " << reading_1 << "  " << "B = " << reading_2 <<"   <---Value swapped"<<endl;
    // In this case we are using & to take reference of the main readings which means the function is also dealing with
    // the original values directly so if we swap the values in function they get swapped in main function to.



    cout << "--- V3 : Call by Pointer ---" << endl;
    cout << "Before : " << "A = " << reading_1 << "  " << "B = " << reading_2 <<endl;
    resetSensorPairV2(reading_1,reading_2);
    cout << "After  : " << "A = " << reading_1 << "  " << "B = " << reading_2 <<"   <---Value swapped back"<<endl;
     // In this case we are using pointer(*) to take reference(address) of the main readings which means the function is also dealing with
    // the original values directly so if we swap the values in function they get swapped in main function to.

}