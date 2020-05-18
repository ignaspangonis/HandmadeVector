#include "func.h"

void ReadSplitGenerateV(vector<Student> &stud, std::ofstream &fail, std::ofstream &mldc, bool strat, bool enhanced,
                        int cycle) {
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed{};
    ifstream fin;
    string line;
    string ignore_s;
    string dest;
    int n;
    int y = 100;
    vector<Student> geri;
    vector<Student> blogi;
    Student temp;
    cout << endl << endl;
    bool med;
    cout << "Norite skaiciuoti pagal vidurki (iveskite 0), ar mediana (iveskite 1)?" << endl;
    cin >> med;
    while (!cin) {
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Neteisingai ivestas skaicius, iveskite dar karta!"
             << std::endl;
        cin >> med;
    }

    for (int m = 1; m <= cycle; m++) {
        n = 0;
        start = hrClock::now();
        fin.open("sarasas" + std::to_string(m) + ".txt");
        if (!fin.is_open()) {
            std::cerr << "Nepavyko failo 'sarasas" + std::to_string(m) + ".txt' atidarymas! Sugeneruokite " << cycle
                      << " failus." << endl;
            exit(1);
        }
        y *= 10;
        stud.reserve(y);
        for (int l = -1; std::getline(fin, line); l++) {
            std::istringstream iss(line);
            if (l == -1) {
                for (;; n++) {
                    if (!(iss >> ignore_s)) {
                        n -= 3;
                        break;
                    }
                }
                continue;
            }
            iss >> temp;
            stud.push_back(temp);
        } //irasom i studentu vektoriu

        end = hrClock::now();
        elapsed = end - start;
        cout << "Studentu nuskaitymo is failo (su " << y << " irasu) laikas: " << elapsed.count() << " sec." << endl;

        CalculateV(stud, med); // suskaiciuojam vidurki

        // isskirstom vektoriu i du vektorius:
        // blogi studentai lieka "stud", geri pereina i "good"
        if (strat) {
            if (enhanced) {
                start = hrClock::now();
                auto ptrGood = stable_partition(stud.begin(), stud.end(), [](Student &s) { return (s < 5); });
                geri.reserve(stud.end() - ptrGood);
                std::copy(ptrGood, stud.end(), std::back_inserter(geri));
                stud.resize(ptrGood - stud.begin());

                end = hrClock::now();
                elapsed = end - start;
                cout << "Failo (su " << y
                     << " irasu) rusiavimo i dvi grupes laikas (2 strategija, geresni algoritmai): "
                     << elapsed.count() << " sec." << endl;
            } else {
                start = hrClock::now();
                std::sort(stud.begin(), stud.end(), [](Student &s1, Student &s2) { return s1 < s2; });
                int numberOfBad = 0;
                while (stud[numberOfBad] < 5.0) {
                    numberOfBad++;
                }
                geri.reserve(stud.size() - numberOfBad);
                std::copy(stud.begin() + numberOfBad, stud.end(), std::back_inserter(geri));
                stud.resize(numberOfBad);
                stud.shrink_to_fit();
                end = hrClock::now();
                elapsed = end - start;
                cout << "Failo (su " << y
                     << " irasu) rusiavimo i dvi grupes laikas (2 strategija, be geresniu algoritmu): "
                     << elapsed.count() << " sec." << endl;
            }
        } else {
            start = hrClock::now();
            std::sort(stud.begin(), stud.end(), [](Student &s1, Student &s2) { return s1 < s2; });
            int numberOfBad = 0;
            while (stud[numberOfBad] < 5.0) {
                numberOfBad++;
            }
            geri.reserve(stud.size() - numberOfBad);
            blogi.reserve(numberOfBad);
            std::copy(stud.begin() + numberOfBad, stud.end(), std::back_inserter(geri));
            std::copy(stud.begin(), stud.begin() + numberOfBad, std::back_inserter(blogi));
            stud.clear();

            end = hrClock::now();
            elapsed = end - start;
            cout << "Failo (su " << y << " irasu) rusiavimo i dvi grupes laikas (1 strategija): " << elapsed.count()
                 << " sec." << endl;
        }


        fail << y << " studentu:" << endl << endl;
        fail << left << setw(17) << "Vardas" << left << std::setw(19) << "Pavarde";
        for (long long int i = 0; i < stud[0].getNd().size(); i++) {
            fail << left << setw(10) << "ND" + std::to_string(i + 1);
        }
        fail << "Egzaminas" << endl;

        mldc << y << " studentu:" << endl << endl;
        mldc << left << setw(17) << "Vardas" << left << std::setw(19) << "Pavarde";
        for (long long int i = 0; i < geri[0].getNd().size(); i++) {
            mldc << left << setw(10) << "ND" + std::to_string(i + 1);
        }
        mldc << "Egzaminas" << endl;

        for (auto &i : geri) {
            mldc << i;
        }
        if (strat) {
            for (auto &i : stud) {
                fail << i;
            } // 2 strategija
        } else {
            for (auto &i : blogi) {
                fail << i;
            } // 1 strategija
        } // Ä¯raÅ¡omi studentai Ä¯ 2 failus

        mldc << endl;
        fail << endl;
        stud.clear();
        geri.clear();
        blogi.clear();
        fin.close();
    }
}

void GenerateRandomFiles(int x, int y) {
    int ran;
    int size = 5;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10);
    std::ofstream sarasas("sarasas" + std::to_string(x + 1) + ".txt");

    sarasas << left << std::setw(17) << "Vardas" << left << std::setw(19) << "Pavarde";
    sarasas << left << std::setw(10) << "Egzaminas";
    for (int i = 0; i < size; i++) {
        sarasas << left << std::setw(10) << "ND" + std::to_string(i + 1);
    }
    sarasas << endl;

    for (int i = 0; i < y; i++) {
        sarasas << left << std::setw(17) << "Vardenis" + std::to_string(i + 1)
                << left << std::setw(19) << "Pavardenis" + std::to_string(i + 1);
        for (int j = 0; j < size + 1; j++) { // size + 1, nes egzaminas
            ran = dist(rng);
            sarasas << left << std::setw(10) << ran;
        } // sugeneruojam pazymius ir egzamina
        sarasas << endl;
    } // generacijos ciklas
    sarasas.close();
}

void CalculateV(vector<Student> &stud, bool isMed) {
    if (isMed) {            // mediana:
        double med;
        vector<Student>::iterator it;
        for (it = stud.begin(); it != stud.end(); it++) {
            // mediana:
            //sort((*it)->getNd().begin(), (*it)->getNd().end());
            it->sortNd();
            if ((*it).getNd().size() % 2 != 0) {
                med = (*it).getNd()[(*it).getNd().size() / 2];
            } else {
                med = ((*it).getNd()[((*it).getNd().size() / 2) - 1] +
                       (*it).getNd()[(*it).getNd().size() / 2]) / 2.0;
            }
            (*it).setRes(0.4 * med + 0.6 * (*it).getExam());
        }
    } else {                 // vidurkis:
        double avg;
        vector<Student>::iterator it;
        for (it = stud.begin(); it != stud.end(); it++) {
            avg = 0;
            // vidurkis:
            for (double j : (*it).getNd()) {
                avg += j;
            }
            avg /= (*it).getNd().size();
            (*it).setRes(0.4 * avg + 0.6 * (*it).getExam());
        }
    }
}

void ReadSplitGenerateV2(Vector<Student> &stud, std::ofstream &fail, std::ofstream &mldc, bool strat, bool enhanced,
                        int cycle) {
    using hrClock = std::chrono::high_resolution_clock;
    hrClock::time_point start, end;
    std::chrono::duration<double> elapsed{};
    ifstream fin;
    string line;
    string ignore_s;
    string dest;
    int n;
    int y = 100;
    Vector<Student> geri;
    Vector<Student> blogi;
    Student temp;
    cout << endl << endl;
    bool med;
    cout << "Norite skaiciuoti pagal vidurki (iveskite 0), ar mediana (iveskite 1)?" << endl;
    cin >> med;
    while (!cin) {
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Neteisingai ivestas skaicius, iveskite dar karta!"
             << std::endl;
        cin >> med;
    }

    for (int m = 1; m <= cycle; m++) {
        n = 0;
        start = hrClock::now();
        fin.open("sarasas" + std::to_string(m) + ".txt");
        if (!fin.is_open()) {
            std::cerr << "Nepavyko failo 'sarasas" + std::to_string(m) + ".txt' atidarymas! Sugeneruokite " << cycle
                      << " failus." << endl;
            exit(1);
        }
        y *= 10;
        stud.reserve(y);
        for (int l = -1; std::getline(fin, line); l++) {
            std::istringstream iss(line);
            if (l == -1) {
                for (;; n++) {
                    if (!(iss >> ignore_s)) {
                        n -= 3;
                        break;
                    }
                }
                continue;
            }
            iss >> temp;
            stud.push_back(temp);
        } //irasom i studentu vektoriu

        end = hrClock::now();
        elapsed = end - start;
        cout << "Studentu nuskaitymo is failo (su " << y << " irasu) laikas: " << elapsed.count() << " sec." << endl;

        CalculateV2(stud, med); // suskaiciuojam vidurki

        // isskirstom vektoriu i du vektorius:
        // blogi studentai lieka "stud", geri pereina i "good"
        if (strat) {
            if (enhanced) {
                start = hrClock::now();
                auto ptrGood = std::stable_partition(stud.begin(), stud.end(), [](Student &s) { return (s < 5); });
                geri.reserve(stud.end() - ptrGood);
                std::copy(ptrGood, stud.end(), std::back_inserter(geri));
                stud.resize(ptrGood - stud.begin());

                end = hrClock::now();
                elapsed = end - start;
                cout << "Failo (su " << y
                     << " irasu) rusiavimo i dvi grupes laikas (2 strategija, geresni algoritmai): "
                     << elapsed.count() << " sec." << endl;
            } else {
                start = hrClock::now();
                std::sort(stud.begin(), stud.end(), [](Student &s1, Student &s2) { return s1 < s2; });
                int numberOfBad = 0;
                while (stud[numberOfBad] < 5.0) {
                    numberOfBad++;
                }
                geri.reserve(stud.size() - numberOfBad);
                std::copy(stud.begin() + numberOfBad, stud.end(), std::back_inserter(geri));
                stud.resize(numberOfBad);
                stud.shrink_to_fit();
                end = hrClock::now();
                elapsed = end - start;
                cout << "Failo (su " << y
                     << " irasu) rusiavimo i dvi grupes laikas (2 strategija, be geresniu algoritmu): "
                     << elapsed.count() << " sec." << endl;
            }
        } else {
            start = hrClock::now();
            std::sort(stud.begin(), stud.end(), [](Student &s1, Student &s2) { return s1 < s2; });
            int numberOfBad = 0;
            while (stud[numberOfBad] < 5.0) {
                numberOfBad++;
            }
            geri.reserve(stud.size() - numberOfBad);
            blogi.reserve(numberOfBad);
            std::copy(stud.begin() + numberOfBad, stud.end(), std::back_inserter(geri));
            std::copy(stud.begin(), stud.begin() + numberOfBad, std::back_inserter(blogi));
            stud.clear();

            end = hrClock::now();
            elapsed = end - start;
            cout << "Failo (su " << y << " irasu) rusiavimo i dvi grupes laikas (1 strategija): " << elapsed.count()
                 << " sec." << endl;
        }


        fail << y << " studentu:" << endl << endl;
        fail << left << setw(17) << "Vardas" << left << std::setw(19) << "Pavarde";
        for (long long int i = 0; i < stud[0].getNd().size(); i++) {
            fail << left << setw(10) << "ND" + std::to_string(i + 1);
        }
        fail << "Egzaminas" << endl;

        mldc << y << " studentu:" << endl << endl;
        mldc << left << setw(17) << "Vardas" << left << std::setw(19) << "Pavarde";
        for (long long int i = 0; i < geri[0].getNd().size(); i++) {
            mldc << left << setw(10) << "ND" + std::to_string(i + 1);
        }
        mldc << "Egzaminas" << endl;

        for (auto &i : geri) {
            mldc << i;
        }
        if (strat) {
            for (auto &i : stud) {
                fail << i;
            } // 2 strategija
        } else {
            for (auto &i : blogi) {
                fail << i;
            } // 1 strategija
        } // Ä¯raÅ¡omi studentai Ä¯ 2 failus

        mldc << endl;
        fail << endl;
        stud.clear();
        geri.clear();
        blogi.clear();
        fin.close();
    }
}

void CalculateV2(Vector<Student> &stud, bool isMed) {
    if (isMed) {            // mediana:
        double med;
        Vector<Student>::iterator it;
        for (it = stud.begin(); it != stud.end(); it++) {
            // mediana:
            //sort((*it)->getNd().begin(), (*it)->getNd().end());
            it->sortNd();
            if ((*it).getNd().size() % 2 != 0) {
                med = (*it).getNd()[(*it).getNd().size() / 2];
            } else {
                med = ((*it).getNd()[((*it).getNd().size() / 2) - 1] +
                       (*it).getNd()[(*it).getNd().size() / 2]) / 2.0;
            }
            (*it).setRes(0.4 * med + 0.6 * (*it).getExam());
        }
    } else {                 // vidurkis:
        double avg;
        Vector<Student>::iterator it;
        for (it = stud.begin(); it != stud.end(); it++) {
            avg = 0;
            // vidurkis:
            for (double j : (*it).getNd()) {
                avg += j;
            }
            avg /= (*it).getNd().size();
            (*it).setRes(0.4 * avg + 0.6 * (*it).getExam());
        }
    }
}

