// Project on - Vendor Cab and Driver Onboarding & Vendor Hierarchy Management
// By - Utkarsh Singh
// Roll no. - E22CSEU0540

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Vendor;  

class Driver {
public:
    string name;
    string licenseNumber;
    bool isVerified;

    Driver(string name, string licenseNumber) {
        this->name = name;
        this->licenseNumber = licenseNumber;
        isVerified = false;
    }

    void verify() { isVerified = true; }
};

class Vehicle {
public:
    string registrationNumber;
    string model;
    bool isActive;

    Vehicle(string regNo, string model) {
        registrationNumber = regNo;
        this->model = model;
        isActive = true;
    }
};

class Vendor {
public:
    string vendorName;
    Vendor* parentVendor;
    vector<Vendor*> subVendors;
    vector<Vehicle> vehicles;
    vector<Driver> drivers;
    bool hasDelegation;

    // Basic vendor details
    Vendor(string name, Vendor* parent = nullptr) {
        vendorName = name;
        parentVendor = parent;
        hasDelegation = false;
        if (parent) parent->subVendors.push_back(this);
    }

    void onboardVehicle() {
        string regNo, model;
        cout << "Vehicle Reg#: ";
        cin >> regNo;
        cout << "Model: ";
        cin >> model;
        vehicles.push_back(Vehicle(regNo, model));
    }

    // For on-board drivers
    void onboardDriver() {
        string name, license;
        cout << "Driver Name: ";
        cin >> name;
        cout << "License: ";
        cin >> license;
        drivers.push_back(Driver(name, license));
    }

    // To verify the drivers
    void verifyDriver() {
        string license;
        cout << "Verify License#: ";
        cin >> license;
        for (auto &driver : drivers) {
            if (driver.licenseNumber == license) {
                driver.verify();
                cout << "Verified: " << driver.name << "!\n";
                return;
            }
        }
        cout << "Driver Not Found\n";
    }

    // For delegate access
    void delegateAccess() {
        char choice;
        cout << "Delegate? (y/n): ";
        cin >> choice;
        hasDelegation = (choice == 'y' || choice == 'Y');
    }

    // To print the details of vendors,vehicles,drivers and delegation
    void details() {
        cout << "Vendor: " << vendorName << "\n"
             << "Vehicles: " << vehicles.size() << "\n"
             << "Drivers: " << drivers.size() << "\n"
             << "Delegation: " << (hasDelegation ? "YES" : "NO") << "\n\n";
    }
};

int main() {
    string vendorName;

    cout << "Super Vendor: ";
    cin >> vendorName;
    Vendor superVendor(vendorName);

    cout << "Regional Vendor: ";
    cin >> vendorName;
    Vendor regionalVendor(vendorName, &superVendor);

    cout << "City Vendor: ";
    cin >> vendorName;
    Vendor cityVendor(vendorName, &regionalVendor);

    // Main UI - Provide options/choice for all features
    int choice;
    while (true) {
        cout << "\n1. Add Vehicle  2. Add Driver  3. Verify Driver  4. Delegate  5. Details  6. Exit\n> ";
        cin >> choice;
        if (choice == 6) {
            cout << "BYE!\n";
            break;
        }
        switch (choice) {
            case 1:
                cityVendor.onboardVehicle();
                break;
            case 2:
                cityVendor.onboardDriver();
                break;
            case 3:
                cityVendor.verifyDriver();
                break;
            case 4:
                cityVendor.delegateAccess();
                break;
            case 5:
                superVendor.details();
                regionalVendor.details();
                cityVendor.details();
                break;
            default:
                cout << "Invalid!\n";
        }
    }
}