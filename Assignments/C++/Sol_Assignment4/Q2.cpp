#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// ============================================================================
// Base Class: Vehicle (Abstract Class)
// ============================================================================
class Vehicle {
protected:
  string registrationNo;
  string ownerName;
  int yearOfManufacture;
  double kmDriven;

public:
  // Base Constructor
  Vehicle(const string &reg, const string &owner, int year, double km)
      : registrationNo(reg), ownerName(owner), yearOfManufacture(year),
        kmDriven(km) {
    cout << "[Vehicle Constructor] " << registrationNo << " : " << ownerName
         << endl;
  }

  // Pure virtual functions - makes Vehicle an abstract base class
  virtual double fuelCost(double kmToTravel) const = 0;
  virtual string vehicleType() const = 0;

  // Virtual function - prints common info, can be extended by derived classes
  virtual void describe() const {
    cout << "Reg: " << registrationNo << " | Owner: " << ownerName
         << " | Year: " << yearOfManufacture << " | Km Driven: " << fixed
         << setprecision(1) << kmDriven;
  }

  // Virtual Destructor - ensures proper cleanup of derived objects via base
  // pointers
  virtual ~Vehicle() {
    cout << "[Vehicle Destructor] " << registrationNo << endl;
  }

  // Accessor Getters
  double getKmDriven() const { return kmDriven; }

  string getRegNo() const { return registrationNo; }

  string getOwnerName() const { return ownerName; }

  int getYear() const { return yearOfManufacture; }
};

// ============================================================================
// Derived Class: Car (Single Inheritance from Vehicle)
// ============================================================================
class Car : public Vehicle {
private:
  string fuelType; // "Petrol" / "Diesel"
  double mileageKmpl;

public:
  Car(const string &reg, const string &owner, int year, double km,
      const string &fuel, double mileage)
      : Vehicle(reg, owner, year, km), fuelType(fuel), mileageKmpl(mileage) {
    cout << "[Car Constructor] " << registrationNo << endl;
  }

  // fuelCost(km) = km / mileageKmpl * fuelPricePerLitre (Petrol = 106.00/L,
  // Diesel = 93.00/L)
  virtual double fuelCost(double kmToTravel) const override {
    double pricePerLitre =
        (fuelType == "Diesel" || fuelType == "diesel") ? 93.00 : 106.00;
    return (kmToTravel / mileageKmpl) * pricePerLitre;
  }

  virtual string vehicleType() const override { return "Car"; }

  // describe() calls Vehicle::describe() then adds fuel type and mileage
  virtual void describe() const override {
    Vehicle::describe();
    cout << " | Fuel: " << fuelType << " | Mileage: " << fixed
         << setprecision(2) << mileageKmpl << " km/l" << endl;
  }

  virtual ~Car() override {
    cout << "[Car Destructor] " << registrationNo << endl;
  }

  string getFuelType() const { return fuelType; }

  double getMileage() const { return mileageKmpl; }
};

// ============================================================================
// Derived Class: Truck (Single Inheritance from Vehicle)
// ============================================================================
class Truck : public Vehicle {
protected:
  double payloadCapacityTons;
  double fuelEfficiencyKmpl;

public:
  Truck(const string &reg, const string &owner, int year, double km,
        double payloadCap, double fuelEff)
      : Vehicle(reg, owner, year, km), payloadCapacityTons(payloadCap),
        fuelEfficiencyKmpl(fuelEff) {
    cout << "[Truck Constructor] " << registrationNo << endl;
  }

  // fuelCost(km) accounts for payload: efficiency drops 5% per ton carried
  // (Uses Diesel: 93.00/L)
  virtual double fuelCost(double kmToTravel) const override {
    double effectiveEfficiency =
        fuelEfficiencyKmpl * (1.0 - 0.05 * payloadCapacityTons);
    if (effectiveEfficiency <= 0.0)
      effectiveEfficiency = 0.1; // Guard against division by zero
    return (kmToTravel / effectiveEfficiency) * 93.00;
  }

  virtual string vehicleType() const override { return "Truck"; }

  // describe() calls Vehicle::describe() then adds payload and efficiency
  virtual void describe() const override {
    Vehicle::describe();
    cout << " | Payload: " << fixed << setprecision(1) << payloadCapacityTons
         << " tons"
         << " | Efficiency: " << fixed << setprecision(2) << fuelEfficiencyKmpl
         << " km/l" << endl;
  }

  virtual ~Truck() override {
    cout << "[Truck Destructor] " << registrationNo << endl;
  }

  double getPayloadCapacity() const { return payloadCapacityTons; }

  double getFuelEfficiency() const { return fuelEfficiencyKmpl; }
};

// ============================================================================
// Derived Class: ElectricTruck (Multilevel Inheritance: Vehicle -> Truck ->
// ElectricTruck)
// ============================================================================
class ElectricTruck : public Truck {
private:
  double batteryCapacityKWh;
  double rangePerChargeKm;
  double batteryLevelPercent;

public:
  ElectricTruck(const string &reg, const string &owner, int year, double km,
                double payloadCap, double fuelEff, double batteryCap,
                double range, double batteryPercent = 85.0)
      : Truck(reg, owner, year, km, payloadCap, fuelEff),
        batteryCapacityKWh(batteryCap), rangePerChargeKm(range),
        batteryLevelPercent(batteryPercent) {
    cout << "[ElectricTruck Constructor] " << registrationNo << endl;
  }

  // fuelCost(km) uses electricity cost: (km / rangePerChargeKm) *
  // batteryCapacityKWh * electricityCostPerUnit (9.50/kWh)
  virtual double fuelCost(double kmToTravel) const override {
    return (kmToTravel / rangePerChargeKm) * batteryCapacityKWh * 9.50;
  }

  virtual string vehicleType() const override { return "Electric Truck"; }

  // describe() calls Truck::describe() then adds battery info
  virtual void describe() const override {
    Truck::describe();
    cout << " | Battery: " << fixed << setprecision(1) << batteryCapacityKWh
         << " kWh"
         << " | Range: " << fixed << setprecision(1) << rangePerChargeKm
         << " km"
         << " | Charge: " << fixed << setprecision(0) << batteryLevelPercent
         << "%" << endl;
  }

  virtual ~ElectricTruck() override {
    cout << "[ElectricTruck Destructor] " << registrationNo << endl;
  }

  double getBatteryCapacity() const { return batteryCapacityKWh; }

  double getRange() const { return rangePerChargeKm; }

  double getBatteryLevel() const { return batteryLevelPercent; }
};

// ============================================================================
// Derived Class: Van (Hierarchical Inheritance directly from Vehicle)
// ============================================================================
class Van : public Vehicle {
private:
  int seatingCapacity;
  double mileageKmpl;

public:
  Van(const string &reg, const string &owner, int year, double km, int seating,
      double mileage)
      : Vehicle(reg, owner, year, km), seatingCapacity(seating),
        mileageKmpl(mileage) {
    cout << "[Van Constructor] " << registrationNo << endl;
  }

  // fuelCost(km) = standard petrol calculation (106.00/L)
  virtual double fuelCost(double kmToTravel) const override {
    return (kmToTravel / mileageKmpl) * 106.00;
  }

  virtual string vehicleType() const override { return "Van"; }

  // describe() calls Vehicle::describe() then adds seating and mileage
  virtual void describe() const override {
    Vehicle::describe();
    cout << " | Seats: " << seatingCapacity << " | Mileage: " << fixed
         << setprecision(2) << mileageKmpl << " km/l" << endl;
  }

  virtual ~Van() override {
    cout << "[Van Destructor] " << registrationNo << endl;
  }

  int getSeatingCapacity() const { return seatingCapacity; }

  double getMileage() const { return mileageKmpl; }
};

// ============================================================================
// Helper Formatting Functions for Commas
// ============================================================================
string formatNumber(long long val) {
  string s = to_string(val);
  int n = s.length();
  if (n <= 3)
    return s;

  string result = "";
  int count = 0;
  for (int i = n - 1; i >= 0; --i) {
    result = s[i] + result;
    count++;
    if (count == 3 && i > 0) {
      result = "," + result;
    } else if (count > 3 && (count - 3) % 2 == 0 && i > 0) {
      result = "," + result;
    }
  }
  return result;
}

string formatCurrency(double amount) {
  stringstream ss;
  ss << fixed << setprecision(2) << amount;
  string s = ss.str();
  size_t dotPos = s.find('.');
  string intPart = (dotPos != string::npos) ? s.substr(0, dotPos) : s;
  string fracPart = (dotPos != string::npos) ? s.substr(dotPos) : "";

  long long intVal = stoll(intPart);
  return formatNumber(intVal) + fracPart;
}

// ============================================================================
// Part C — Polymorphic Fleet Report Function
// ============================================================================
void printFleetReport(const vector<Vehicle *> &fleet, double tripKm) {
  cout << "\n===== FLEET REPORT — Trip Distance: " << fixed << setprecision(0)
       << tripKm << " km =====\n";
  cout << left << setw(12) << "Reg" << setw(16) << "Type" << setw(20) << "Owner"
       << right << setw(12) << "Km Driven" << endl;

  for (const auto *v : fleet) {
    cout << left << setw(12) << v->getRegNo() << setw(16) << v->vehicleType()
         << setw(20) << v->getOwnerName() << right << setw(12)
         << formatNumber(static_cast<long long>(v->getKmDriven())) << endl;
  }

  cout << "\n===== FUEL / CHARGE COST ESTIMATE =====\n";

  const Vehicle *mostEfficient = nullptr;
  double minCost = 1e18;

  for (const auto *v : fleet) {
    double cost = v->fuelCost(tripKm);

    if (cost < minCost) {
      minCost = cost;
      mostEfficient = v;
    }

    string regWithType = v->getRegNo() + " (" + v->vehicleType() + ")";
    cout << left << setw(28) << regWithType << ": Rs. " << right << setw(8)
         << formatCurrency(cost);

    // Requirement 4: Use dynamic_cast<ElectricTruck*> to identify electric
    // trucks and print battery status
    if (const ElectricTruck *et = dynamic_cast<const ElectricTruck *>(v)) {
      cout << " [Battery: " << fixed << setprecision(0) << et->getBatteryLevel()
           << "% charged]";
    } else if (const Car *car = dynamic_cast<const Car *>(v)) {
      cout << " (" << car->getFuelType() << ")";
    }
    cout << endl;
  }

  if (mostEfficient != nullptr) {
    cout << "\nMost Efficient Vehicle: " << mostEfficient->getRegNo() << " ("
         << mostEfficient->vehicleType() << ") — Rs. "
         << formatCurrency(minCost) << " for " << fixed << setprecision(0)
         << tripKm << " km" << endl;
  }
}

// ============================================================================
// Main Function
// ============================================================================
int main() {
  // ----------------------------------------------------
  // Part B — Constructor / Destructor Execution Order
  // ----------------------------------------------------
  cout << "========================================================\n";
  cout << " Part B: Constructor / Destructor Chaining Demonstration \n";
  cout << "========================================================\n";
  {
    // Stack-allocated ElectricTruck object demonstrates full
    // construction/destruction chain
    ElectricTruck stackTruck("V-ET001", "Green Logistics", 2023, 15000, 4.0,
                             7.0, 100.0, 400.0, 85.0);
    cout << "...scope ends..." << endl;
  }

  // ----------------------------------------------------
  // Part C — Polymorphic Fleet Report
  // ----------------------------------------------------
  cout << "\n========================================================\n";
  cout << " Part C: Polymorphic Fleet Report & Heap Cleanup        \n";
  cout << "========================================================\n";

  vector<Vehicle *> fleet;

  // Adding at least 5 vehicles of different types using new
  fleet.push_back(
      new Car("KA01AA001", "Ramesh Kumar", 2019, 45200, "Petrol", 18.74447));
  fleet.push_back(
      new Truck("MH04BB002", "Shyam Logistics", 2017, 123500, 1.0, 7.86303));
  fleet.push_back(new ElectricTruck("GJ07CC003", "Green Fleet Co", 2022, 89000,
                                    3.0, 6.5, 80.0, 392.258, 85.0));
  fleet.push_back(
      new Car("DL03XY7890", "Priya Sharma", 2020, 32000, "Diesel", 22.0));
  fleet.push_back(
      new Van("HR26MN4567", "City Express Travels", 2018, 67400, 12, 14.0));

  // Print polymorphic report for a 200 km trip
  printFleetReport(fleet, 200.0);

  // ----------------------------------------------------
  // Virtual Destructor Cleanup Verification
  // ----------------------------------------------------
  cout << "\n========================================================\n";
  cout << " Cleanup: Deleting heap objects via Vehicle* pointers   \n";
  cout << "========================================================\n";
  for (Vehicle *v : fleet) {
    delete v; // Correct derived class destructors are called via virtual
              // destructor
  }
  fleet.clear();

  return 0;
}