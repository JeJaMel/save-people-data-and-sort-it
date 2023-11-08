#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include<cstdlib>
#include <iomanip>

using namespace std;

struct Persona {
    string name;
    int age;
    string city;
    string country;
    int id;
};

void introduceMe(const Persona&);
void merge(Persona arr[], Persona left[], Persona right[], int left_size, int right_size);
void mergeSort(Persona arr[], int left, int right);
void WhatToDO();

Persona getDataFromUser() {
    Persona p;
    cout << "Enter your first name" << endl;
    cin >> p.name;
    cout << "Enter your age" << endl;
    cin >> p.age;
    cout << "Enter the city where you live" << endl;
    cin >> p.city;
    cout << "Enter the country where you was born" << endl;
    cin >> p.country;
    cout << "Enter your ID:" << endl;
    cin >> p.id;
    return p;
}

const int MAX = 100;

int main() {
    Persona persons[MAX];
    int numPersons = 0;
    int anybutton;
    int FirstChoice;

    cout<<"\n \t\tWelcome to user data management\n\t\tPress any button to continue..."<<endl;
    cin>>anybutton;

    cout<<"\tWhat do you want to do?"<<endl;

    cout<<"\nAdd people to data.csv...      (1)"<<endl;
    cout<<"Remove people from data.csv... (2)"<<endl;
    cout<<"View data.csv on terminal...   (3)"<<endl;
    cout<<"View Sorted_data on terminal...(4)"<<endl;
    cout<<"Sort untracked data...         (5)"<<endl;
    cout<<"save and end program...        (6)"<<endl;
        cin>>FirstChoice;

switch (FirstChoice)
{
case 1:
fstream Archive;
    Archive.open("data.csv", ios::app);

    if (!Archive.is_open()) {
        cout << "Unable to open the file" << endl;
        return 1;
    }

    while (true) {
        Persona person = getDataFromUser();
        if (numPersons < MAX) {
            persons[numPersons++] = person;
        } else {
            cout << "List is full" << endl;
        }
        Archive << person.id << "," << person.name << "," << person.age << "," << person.city << "," << person.country << endl;
        introduceMe(person);

        cout << "Do you want to add more people? (y/n)" << endl;
        string a;
        cin >> a;
        if (a[0] != 'Y' && a[0] != 'y') {
            Archive.close();
            break;
        }
    }

    Archive.close();

    Archive.open("data.csv");
    if (!Archive.is_open()) {
        cout << "Unable to open the file" << endl;
        return 1;
    }

    cout << "Do you want to sort the data? (y/n)" << endl;
    string b;
    cin >> b;
    if (b[0] == 'Y' || b[0] == 'y') {
        mergeSort(persons, 0, numPersons - 1);
        fstream Sorted_data;
        Sorted_data.open("Sorted_data.csv", ios::out);
        if (!Sorted_data.is_open()) {
            cout << "Unable to open the file" << endl;
            return 1;
        }
        for (int i = 0; i < numPersons; i++) {
            Sorted_data << persons[i].id << "," << persons[i].name << "," << persons[i].age << "," << persons[i].city << "," << persons[i].country << endl;
        }
        Sorted_data.close();
        cout << "Sorted data has been written to Sorted_data.csv" << endl;
    } else {
        cout << "Data has not been sorted" << endl;
        for (int i = 0; i < numPersons; i++) {
            introduceMe(persons[i]);
        }
    }

    break;



   
}


    

    return 0;
}

void introduceMe(const Persona& p) {
    cout << "The data |" << p.name << "|, |" << p.age << "|, |" << p.city << "|, |" << p.country << "|, |" << p.id << "| has been saved in the file" << endl;
}

void merge(Persona arr[], Persona left[], Persona right[], int left_size, int right_size) {
    int i = 0, j = 0, k = 0;
    
    while (i < left_size && j < right_size) {
        if (left[i].id <= right[j].id) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    
    while (i < left_size) {
        arr[k++] = left[i++];
    }
    
    while (j < right_size) {
        arr[k++] = right[j++];
    }
}

void mergeSort(Persona arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        int left_size = mid - left + 1;
        int right_size = right - mid;

        Persona leftArray[left_size];
        Persona rightArray[right_size];

        for (int i = 0; i < left_size; i++) {
            leftArray[i] = arr[left + i];
        }

        for (int i = 0; i < right_size; i++) {
            rightArray[i] = arr[mid + 1 + i];
        }

        mergeSort(leftArray, 0, left_size - 1);
        mergeSort(rightArray, 0, right_size - 1);

        merge(arr, leftArray, rightArray, left_size, right_size);
    }
}


