#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <limits.h>
#include <list>

using namespace std;

struct Phone {
    string brand;
    string model;
    int releaseYear;
    float price;
    float screenSize;
};

void displayPhone(const Phone& p) {
    cout << left
    << setw(15) << p.brand
    << setw(35) << p.model
    << setw(15) << p.releaseYear
    << setw(15) << fixed << setprecision(2) << p.price
    << setw(10) << fixed << setprecision(1) << p.screenSize
    << endl;
}

void parsePhone(const string& line, Phone& p) {
    stringstream ss(line);
    string temp;

    getline(ss, p.brand, ',');
    getline(ss, p.model, ',');
    getline(ss, temp, ',');
    p.releaseYear = stoi(temp);
    getline(ss, temp, ',');
    p.price = stof(temp);
    getline(ss, temp, ',');
    p.screenSize = stof(temp);
}

void loadPhones(const string &filename, vector<Phone>& phones) {
    ifstream fin(filename);
    if(fin){
        string line;
        while(getline(fin, line)) {
            Phone p;
            parsePhone(line, p);
            phones.push_back(p);
        }
        fin.close();
    }
    else {
        cout << "Error opening file" << endl;
    }
}

void displayAllPhones(const vector<Phone>& phones) {
    cout << left
    << setw(15) << "Brand"
    << setw(35) << "Model"
    << setw(15) << "Release Year"
    << setw(15) << "Price"
    << setw(10) << "Screen Size"
    << endl;

    for (const Phone& p : phones) {
        displayPhone(p);
    }
}

// Search for a phone by model
int searchPhoneByModel(const vector<Phone>& phones, const string& model) {
    for (int i = 0; i < phones.size(); i++) {
        if (phones[i].model == model) {
            return i;
        }
    }
    return -1;
}

// Function to count the number of phones of each brand
map<string, int> countPhonesByBrand(const vector<Phone>& phones) {
    map<string, int> count;
    for (const Phone& p : phones) {
        count[p.brand]++;
    }
    return count;
}

// Function to display phones of a particular brand
void displayPhonesByBrand(const vector<Phone>& phones, const string& brand) {
    bool found = false;
    cout << "Phones of brand: " << brand << endl;
    cout << left
    << setw(15) << "Brand"
    << setw(35) << "Model"
    << setw(15) << "Release Year"
    << setw(15) << "Price"
    << setw(10) << "Screen Size"
    << endl;

    for (const Phone& p : phones) {
        if (p.brand == brand) {
            displayPhone(p);
            found = true;
        }
    }
    if (!found) {
        cout << "No phones found for brand: " << brand << endl;
    }
}

//Function to find the highest, lowest and average of a discrete numerical field (Integer)
int findMaxMinAvgReleaseYear(const vector<Phone>& phones, Phone& max, Phone& min) {
    int sum = 0;
    int maxReleaseYear = INT_MIN;
    int minReleaseYear = INT_MAX;

    for (const Phone& p : phones) {
        sum += p.releaseYear;

        if (p.releaseYear > maxReleaseYear) {
            maxReleaseYear = p.releaseYear;
            max = p;
        }
        if (p.releaseYear < minReleaseYear) {
            minReleaseYear = p.releaseYear;
            min = p;
        }
    }
    return sum / phones.size();
}

//Function to search for phones that match or partially match a given text input
list<Phone> searchPhoneByPartialText(const vector<Phone>& phones, const string& text) {
    list<Phone> matchingPhones;
    for(auto it = phones.begin(); it != phones.end(); it++) {
        if (it->model.find(text) != string::npos) {
            matchingPhones.push_back(*it);
        }
    }
    return matchingPhones;
}

// Function to display all of the data in descending order of a selected floating point field
void displayPhonesInDescendingOrder(const vector<Phone>& phones){
    vector<Phone> sortedPhones = phones;
    sort(sortedPhones.begin(), sortedPhones.end(), [](const Phone& p1, const Phone& p2) {
        return p1.price > p2.price;
    });

    cout << "\n----Phones in descending order of price----" << endl;
    cout << left
    << setw(15) << "Brand"
    << setw(35) << "Model"
    << setw(15) << "Release Year"
    << setw(15) << "Price"
    << setw(10) << "Screen Size"
    << endl;

    for (const Phone& p : sortedPhones) {
        displayPhone(p);
    }
}

int main() {
    vector<Phone> phones;
    loadPhones("MOCK_DATA.csv", phones);
    displayAllPhones(phones);

    // Search for a phone by model
    string model;
    cout << "\nEnter model to search: ";
    getline(cin, model);
    int index = searchPhoneByModel(phones, model);
    if (index != -1) {
        cout << "Phone found for index: " << index << endl;
        displayPhone(phones[index]);
    }
    else {
        cout << "Phone not found" << endl;
    }

    // Count the number of phones of each brand
    map<string, int> count = countPhonesByBrand(phones);
    cout << "\n----Count of phones by brand----" << endl;
    for (const auto& brandCount : count) {
        cout << brandCount.first << ": " << brandCount.second << endl;
    }

    // Display phones of a particular brand
    string filterBrand;
    cout << "\nEnter brand to filter: ";
    getline(cin, filterBrand);
    displayPhonesByBrand(phones, filterBrand);

    // Find the highest, lowest and average of a discrete numerical field (Integer)
    Phone max, min;
    int avgReleaseYear = findMaxMinAvgReleaseYear(phones, max, min);
    cout << "\nAverage release year: " << avgReleaseYear << endl;
    cout << "Phone with highest release year: \t";
    displayPhone(max);
    cout << "Phone with lowest release year: \t";
    displayPhone(min);

    // Search for phones that match or partially match a given text input
    string text;
    cout << "\nEnter text to search in model: ";
    getline(cin, text);
    list<Phone> matchingPhones = searchPhoneByPartialText(phones, text);
    cout << "\n----Phones with matching text in model----" << endl;
    for (const Phone& p : matchingPhones) {
        displayPhone(p);
    }

    //Display phones in descending order of price
    displayPhonesInDescendingOrder(phones);

    return 0;
}