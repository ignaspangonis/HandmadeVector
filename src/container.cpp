#include "container.h"

void Vec(bool strat, bool enhanced, int cycle) {
    vector<Student> stud;
    std::ofstream fail("neislaike.txt");
    std::ofstream mldc("islaike.txt");
    Vector<Student> stud2;
    if (fail.is_open() && mldc.is_open()) {
        stud.clear();
        ReadSplitGenerateV(stud, fail, mldc, strat, enhanced, cycle);
        cout << "\n\nVECTOR\n\n";
        ReadSplitGenerateV2(stud2, fail, mldc, strat, enhanced, cycle);
        fail.close();
        mldc.close();
    } else {
        cout << "Failo atidarymas nepavyko!" << endl;
    }
}