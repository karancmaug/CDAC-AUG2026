#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;
using Header     = pair<string, string>;
using HeaderList = vector<Header>;
using Port       = unsigned int;
using IPAddress  = string;

enum class HttpStatus {
    OK             = 200,
    Created        = 201,
    BadRequest     = 400,
    Unauthorized   = 401,
    NotFound       = 404,
    ServerError    = 500
};

void handleResponse(HttpStatus status, const string& endpoint){
    switch(status){
        case HttpStatus::OK :
        cout <<setw(20)<<left<< "-> 200 OK " << ": " <<endpoint << endl;
        break;
        case HttpStatus::Created :
        cout << setw(20)<<left<<"-> 201 Created " << ": " <<endpoint << endl;
        break;
        case HttpStatus::BadRequest :
        cout << setw(20)<<left<<"-> 400 BadRequest " << ": " << endpoint << endl;
        break;
        case HttpStatus::Unauthorized :
        cout << setw(20)<<left<<"-> 401 Unauthorized " << ": " <<  endpoint <<endl;
        break;
        case HttpStatus::NotFound :
        cout << setw(20)<<left<<"-> 404 Not Found " << ": " <<endpoint << endl;
        break;
        case HttpStatus::ServerError :
        cout << setw(20)<<left<<"-> 500 ServerError " << ": " << endpoint<<endl;
        break;
        default :
        cout << "Write status argument correctly" << endl;

    }
}

void printHeaders(const HeaderList& headers){
for(auto i : headers){
    
    cout << setw(18) << left << i.first << ": " << i.second << endl;
}
}

int main(){
    cout << " Part A" << endl;
    typedef unsigned long long RequestId;
    
    HttpStatus status1 = HttpStatus::OK;
    HttpStatus status2 = HttpStatus::Created;
    HttpStatus status3 = HttpStatus::Unauthorized;
    HttpStatus status4 = HttpStatus::ServerError;

    handleResponse(status1,"Request Succesfull");
    handleResponse(status2,"Created Succesfull");
    handleResponse(status3,"Authentication required");
    handleResponse(status4,"Internal server error-retry late");

    cout <<endl;
    cout<< " B Part" << endl;
    IPAddress addr ="1748293847";
    Port p = 8080;

    cout<<"Request ID   :" << addr << endl;
    cout <<"Server Port  :" << p << endl;
    cout << endl;

    HeaderList v;
    v.push_back({"Content-Type", "application/json"});
    v.push_back({"Authorization", "Bearer eyJhbGci..."});
    v.push_back({"Accept-Language", "en-US"});


    cout << "Headers :" << endl; 
    printHeaders(v);

    return 0;
}