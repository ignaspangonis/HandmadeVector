# Vector klasės implementacija bei tyrimai 
## Versijos
### [v1.0](https://github.com/ignaspangonis/ObjektinisProgramavimas-4/releases/tag/v1.0)

### Spartos analizės rezultatai:
1. Analizei pasitelkti std::vector ir mano sukurtas Vector konteineriai. Palyginama, kiek  laiko užtrunka std::vector tipo ir Vector tipo tuščių vektorių užpildymas, naudojant push_back() funkciją:

| Įrašų kiekis | std::vector | Vector   |
|--------------|-------------|----------|
| 10000        | 0.00099     | 0.000998 |
| 100000       | 0.003013    | 0.001995 |
| 1000000      | 0.022937    | 0.019946 |
| 10000000     | 0.240359    | 0.228363 |
| 100000000    | 2.40095     | 2.21571  |

2. Lyginami konteinerių (Vector ir std::vector) atminties perskirstymų skaičiai užpildant 100000000 elementų. Perskirstymas įvyksta tada, kai yra patenkinama sąlyga: capacity() == size():

| Konteineris | Perskirtymai |
|-------------|--------------|
| std::vector | 27           |
| Vector      | 27           |

3. Lyginama, kiek laiko užtrunka [programos](https://github.com/ignaspangonis/ObjektinisProgramavimas-3/releases/tag/v2.0) veikimas (*studentų nuskaitymas iš failo ir studentų skirstymas į dvi grupes*) naudojant std::vector ir Vector realizacijas pasitelkiant duomenų failą su 100000 studentų įrašų:

| Konteineris | Studentų nuskaitymas iš failo | Studentų skirstymas į dvi grupes |
|-------------|-------------------------------|----------------------------------|
| std::vector | 0.78617                       | 0.139654                         |
| Vector      | 0.80183                       | 0.139626                         |

5 funkcijų pavyzdžiai:
1. operator!=
```
template<typename T>
bool Vector<T>::operator!=(const Vector<T> &v) const {
    if (v.size() != size())
        return true;
    else {
        size_type g = v.size();
        for (size_type k = 0; k < g; k++) {
            if (itt[k] != v.itt[k]) { return true; }
        }
        return false;
    }
}
```

2. shrink_to_fit()
```
template<typename T>
void Vector<T>::shrink_to_fit() {
    if (avail < limit) {
        limit = avail;
    }
}
```

3. unchecked_append()
```
template<class T>
void Vector<T>::unchecked_append(const T &value) {
    alloc.construct(avail++, value);
} // tariame, kad 'avail' point'ina į išskirtą, bet neinicializuotą vietą
```

4. reserve()
```
template<typename T>
void Vector<T>::reserve(size_type n) {
    if (n > capacity()) {
        size_type new_size = n;

        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = std::uninitialized_copy(itt, avail, new_data);

        uncreate();
        itt = new_data;
        avail = new_avail;
        limit = itt + new_size;
    }
}
```

5. assign()
```
template<class T>
void Vector<T>::assign(size_type n, const value_type& val) {
    clear();
    reserve(n);
    for (size_type i = 0; i < n; ++i) {
        push_back(val);
    }
}
```

## Naudojimosi programa pavyzdys (v1.0):
```
Si programa skirta testuoti std::vector implementacija - Vector
Ar norite testuoti std::vector ir Vector su int (1), ar ne (0)?
0

Pradedame OOP 2 uzduoties v2.0 programos testa - lyginsime Vector su std::vector
Ar norite generuoti naujus failus, jei dar negeneravote (1), ar ne (0)?
0
Failu dydis - nuo 1000 studentu, su kiekvienu failu didinant si skaiciu 10 kartu.
Kiek failu skaityti ir/ar generuoti (1-5)?:
4
std::vector:
Norite skaiciuoti pagal vidurki (iveskite 0), ar mediana (iveskite 1)?
0
Studentu nuskaitymo is failo (su 1000 irasu) laikas: 0.009015 sec.
Failo (su 1000 irasu) rusiavimo i dvi grupes laikas (2 strategija, geresni algoritmai): 0.002034 sec.
Studentu nuskaitymo is failo (su 10000 irasu) laikas: 0.081755 sec.
Failo (su 10000 irasu) rusiavimo i dvi grupes laikas (2 strategija, geresni algoritmai): 0.014959 sec.
Studentu nuskaitymo is failo (su 100000 irasu) laikas: 0.795851 sec.
Failo (su 100000 irasu) rusiavimo i dvi grupes laikas (2 strategija, geresni algoritmai): 0.136635 sec.
Studentu nuskaitymo is failo (su 1000000 irasu) laikas: 8.14095 sec.
Failo (su 1000000 irasu) rusiavimo i dvi grupes laikas (2 strategija, geresni algoritmai): 1.40028 sec.
Vector:
Norite skaiciuoti pagal vidurki (iveskite 0), ar mediana (iveskite 1)?
0
Studentu nuskaitymo is failo (su 1000 irasu) laikas: 0.008938 sec.
Failo (su 1000 irasu) rusiavimo i dvi grupes laikas (2 strategija, geresni algoritmai): 0.001025 sec.
Studentu nuskaitymo is failo (su 10000 irasu) laikas: 0.080822 sec.
Failo (su 10000 irasu) rusiavimo i dvi grupes laikas (2 strategija, geresni algoritmai): 0.014959 sec.
Studentu nuskaitymo is failo (su 100000 irasu) laikas: 0.80183 sec.
Failo (su 100000 irasu) rusiavimo i dvi grupes laikas (2 strategija, geresni algoritmai): 0.141624 sec.
Studentu nuskaitymo is failo (su 1000000 irasu) laikas: 7.99418 sec.
Failo (su 1000000 irasu) rusiavimo i dvi grupes laikas (2 strategija, geresni algoritmai): 1.37034 sec.
```

## Testavimo sistemos parametrai:
1. Procesorius Intel Core i5-7300HQ CPU @ 2.50 GHz
2. RAM 8.00 GB
3. HDD 2 TB
4. Windows OS
