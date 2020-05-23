#include "container.h"
//#include "Student.h"

int main() {


    //Vector<int> vec = { 1, 2, 3};
    vector<int> vec = { 1, 2, 3 };
    cout << vec.capacity();
    return 1;


    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed{};
    bool yes;
    cout << "Ar norite testuoti std::vector ir Vector su int (1), ar ne (0)?" << endl;
    cin >> yes;
    while (!cin) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Neteisingai ivestas skaicius, iveskite dar karta!"
             << std::endl;
        cin >> yes;
    }



    if (yes) {

        long long int sz = 10000;  // 100000, 1000000, 10000000, 100000000
        for (; sz <= 100000000; sz*=10) {
            start = hrClock::now();
            vector<int> v;
            for (long long int i = 1; i <= sz; ++i){
                v.push_back(i);
            }
            end = hrClock::now();
            elapsed = end - start;
            cout << "std::vector<int> laikas su " << sz << " irasu: " << elapsed.count() << " sec." << endl;
        }

        // cout << "std::vector" << oof << endl;

        sz = 10000;  // 100000, 1000000, 10000000, 100000000
        for (; sz <= 100000000; sz*=10) {
            start = hrClock::now();
            Vector<int> v;
            for (long long int i = 1; i <= sz; ++i){
                v.push_back(i);
            }
            end = hrClock::now();
            elapsed = end - start;
            cout << "Vector<int> laikas su " << sz << " irasu: " << elapsed.count() << " sec." << endl;
        }
    }



    int cycle;
    int y = 100;
    bool gen;
    cout << "Ar norite generuoti naujus failus, jei dar negeneravote (1), ar ne (0)?" << endl;
    cin >> gen;
    while (!cin) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Neteisingai ivestas skaicius, iveskite dar karta!"
             << std::endl;
        cin >> gen;
    } // ivedama, ar generuoti
    cout << "Failu dydis - nuo 1000 studentu, su kiekvienu failu didinant si skaiciu 10 kartu.\n"
            "Kiek failu skaityti ir/ar generuoti (1-5)?: " << endl;
    cin >> cycle;
    while (cycle < 1 || cycle > 5) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Neteisingai ivestas skaicius, iveskite dar karta!"
             << std::endl;
        cin >> cycle;
    } // ivedama, kiek failu generuoti

    if (gen) {
        for (int i = 0; i < cycle; i++) {
            y = y * 10;
            cout << endl << "Kuriamas sarasas is " << y << " studentu." << endl;
            GenerateRandomFiles(i, y);
        } // generuojami failai
    }

    Vec(true, true, cycle);
}