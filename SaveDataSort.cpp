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
        Archive << person.name << "," << person.age << "," << person.city << "," << person.country << "," << person.id << endl;
        introduceMe(person);

        cout << "Do you want to add more people? (y/n)" << endl;
        string a;
        cin >> a;
        if (a[0] != 'Y' && a[0] != 'y') {
            cout << "Bye!" << endl;
            Archive.close();
            return 0;
        }
    }

    return 0;
}

void introduceMe(const Persona& p) {
    cout << "The data |" << p.name << "|, |" << p.age << "|, |" << p.city << "|, |" << p.country << "|, |" << p.id << "| has been saved in the file" << endl;
}
