#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Persona
{
    string name;
    int age;
    string city;
    string country;
    int id;
};

void introduceMe(const Persona&);
void merge(int arr[], int left[], int right[], int left_size, int right_size);
void mergeSort(int arr[], int size);


Persona getDataFromUser() {
    Persona p;
    cout << "What's your name?" << endl;
    cin >> p.name;
    cout << "How old are you?" << endl;
    cin >> p.age;
    cout << "What city are you from?" << endl;
    cin >> p.city;
    cout << "What country are you from?" << endl;
    cin >> p.country;
    cout << "Enter an ID:" << endl;
    cin >> p.id;
    return p;
}

int main() {
    fstream Archive;
    Archive.open("data.csv", ios::out);

    if (!Archive.is_open()) {
        cout << "Unable to create the file" << endl;
        return 1;
    }

    while (true) {
        Persona person = getDataFromUser();
        Archive << person.id << "," << person.name << "," << person.age << "," << person.city << "," << person.country << endl;
        introduceMe(person);

        cout << "Do you want to add more people? (y/n)" << endl;
        string a;
        cin >> a;
        if (a[0] != 'Y' && a[0] != 'y') {
            Archive.close();
            return 0;
        }
    }Archive.close();

    Archive.open("data.csv");
    if(!Archive.is_open()) {
        cout << "Unable to open the file" << endl;
        return 1;
    }



    return 0;
}

void introduceMe(const Persona& p) {
    cout << "The data |" << p.name << "|, |" << p.age << "|, |" << p.city << "|, |" << p.country << "|, |" << p.id << "| has been saved in the file" << endl;
}

void merge(int arr[], int left[], int right[], int left_size, int right_size) {
    int i = 0, j = 0, k = 0;
    
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
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

void mergeSort(int arr[], int size) {
    if (size <= 1) {
        return; 
    }

    int mid = size / 2;
    int left[mid];
    int right[size - mid];

    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }

    mergeSort(left, mid);
    mergeSort(right, size - mid);

    merge(arr, left, right, mid, size - mid);
}
