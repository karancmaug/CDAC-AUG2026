#include<iostream>
#include<cmath>
using namespace std;


double computeRMS(double* signal, int n){
    double sumSq = 0;
    for(int i=0;i<n;i++){
        sumSq = sumSq + pow(*(signal + i),2);
    }
    double result=sqrt(sumSq/n);
    return result;
}
// Returns sqrt( sum of (each element squared) / n )



void normalise(double* signal, int n){
    double Max = 0;
    for(int i=0;i<n;i++){
        if((*signal + i)>Max) Max = *(signal +i);
    }
    for(int i=0;i<n;i++){
        *(signal + i) = (*(signal + i))/Max;
    }
}
// Divides every element by the max absolute value in the array (in-place)



int countZeroCrossings(double* signal, int n){
    int count = 0;
    for(int i=0;i<n;i++){
        if(*(signal + i) >= 0){
            if(*(signal + i + 1) < 0 ) {
                count++;
            }
        }else{
            if(*(signal + i + 1) >= 0 ) {
                count++;
            }
        }
    }
    return count;
}
// Returns count of positions where adjacent elements have opposite signs



void applyGain(double* signal, int n, double gainFactor){
     for(int i=0;i<n;i++){
        *(signal + i) = (*(signal + i))*(gainFactor);
    }
}
// Multiplies every element by gainFactor (in-place)



void printArr(double* signal,int n){
     for(int i=0;i<7;i++){
        cout << *(signal + i) << "  ";
    }
    cout << endl;
}
// To print an array



int main(){
    double arr[100] = {0.5, -1.2, 0.8, -0.3, 1.0, -0.9, 0.1};
    
    cout << "Compute Rms : " << computeRMS(arr,7) << endl;

    cout << "CountZeroCrossings : " << countZeroCrossings(arr,7) << endl; 

    cout << " Before Normalize :" << endl;
    printArr(arr,7);

    cout << " After Normalize :" << endl;
    normalise(arr,7);
    printArr(arr,7);

    cout << " Before ApplyGain:" << endl;
    printArr(arr,7);

    cout << " After ApplyGain:" << endl;
    applyGain(arr,7,0.5);
    printArr(arr,7);
}