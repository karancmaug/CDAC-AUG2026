#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

inline double distanceBetween(double x1, double y1, double x2, double y2){
    return sqrt( pow(x2-x1, 2) + pow(y2-y1, 2) );
} 

// sqrt( pow(x2-x1, 2) + pow(y2-y1, 2) )


inline double toRadians(double degrees){
    return degrees * (M_PI / 180.0);
}
// degrees * (M_PI / 180.0)


inline double clamp(double value, double minVal, double maxVal){
    if(value < minVal) return minVal;
    if(value > maxVal) return maxVal;
    return value;
}
// Restrict value to [minVal, maxVal]


inline bool isInSafeZone(double x, double y, double cx, double cy, double radius){
    if(distanceBetween(x,y,cx,cy)<radius){
        return true;
    }else{
        return false;
    }
}
// true if point (x,y) is within the circle centred at (cx,cy) with given radius


int main(){

    int x1 = 3.4 , y1 =5.4;
    int x2 = -35.4 , y2 =55.4;
    int x3 = 35.4 , y3 =555.4;


    cout << " -------------------- 1st Way Point----------------------------" << endl;
    cout << "Distance from Home(0.0,0.0) : " << distanceBetween(x1,y1,0.0,0.0) << endl;
    if(isInSafeZone(x1,y1,0.0,0.0,50.0)){
        cout << "Inside Safezone" << endl;
    }else{
        cout << "Not Inside Safezone" << endl;
    }


    cout << " -------------------- 2nd Way Point----------------------------" << endl;
    cout << "Distance from Home(0.0,0.0) : " << distanceBetween(x2,y2,0.0,0.0) << endl;
    if(isInSafeZone(x2,y2,0.0,0.0,50.0)){
        cout << "Inside Safezone" << endl;
    }else{
        cout << "Not Inside Safezone" << endl;
    }

    cout << " -------------------- 3rd Way Point----------------------------" << endl;
    cout << "Distance from Home(0.0,0.0) : " << distanceBetween(x3,y3,0.0,0.0) << endl;
    if(isInSafeZone(x3,y3,0.0,0.0,50.0)){
        cout << "Inside Safezone" << endl;
    }else{
        cout << "Not Inside Safezone" << endl;
    }
}