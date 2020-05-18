#ifndef OBJEKTINISPROGRAMAVIMAS_4_VECTOR_H
#define OBJEKTINISPROGRAMAVIMAS_4_VECTOR_H

#include <stdexcept>
#include <utility>
#include <algorithm>
#include <random>
#include <iostream>
#include <memory> // allocator klasė
#include <iterator>


template<class T>
class Vector {
public:
    typedef T *iterator; // paprastos rodyklės turi visas random_access_iterator savybes
    typedef const T *const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef T &reference;
    typedef const T &const_reference;
    typedef std::allocator<T> allocator_type;
    typedef typename std::allocator_traits<allocator_type>::pointer pointer;
    typedef typename std::allocator_traits<allocator_type>::const_pointer const_pointer;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

//    void reallocate(const unsigned int &A, const unsigned int &B) {
//        avail = A;
//        limit = B;
//    }

    T &at(size_type it) {
        return itt[it];
    }

    reference back() { // reference yra T
        return *(avail - 1);
    }
    T &front() {
        if (avail > 0)
            return itt[0];

        else
            throw std::logic_error("Empty container");
    }

    T *data() noexcept;



    /// rule of 3
    /// c-tor
    Vector() { create(); } // create atsakinga už atminties išskyrimą
    // itt ir limit bus nuliai
    explicit Vector(size_type n, const T &t = T{}) { create(n, t); } // kiek elementų ir kokią reikšmę talpinam
    // explicit užtikrina, kad šis konstruktorius bus sukurtas tik būtent taip nurodant vektorių - reikia explicitly
    // nurodyti.
    // '= T{}' yra objekto priskyrimas
    Vector(const Vector &v) { create(v.begin(), v.end()); } // kita create() versija

    /// priskyrimo operatorius
    Vector &operator=(const Vector &);

    /// d-tor
    ~Vector() { uncreate(); }

    T &operator[](size_type i) {
        if (i > size() || i < 0)
            throw std::out_of_range("Out of bounds!");
        return itt[i];
    }
    const T &operator[](size_type i) const {
        if (i > size() || i < 0)
            throw std::out_of_range("Out of bounds!");
        return itt[i];
    }

    size_type max_size() const noexcept;
    size_type size() const { return avail - itt; } // sukonstruotų elementų dydis
    size_type capacity() const { return limit - itt; }  // visas rezervuotas dydis

    // vektoriaus pradžios get'eriai:
    iterator begin() { return itt; }
    const_iterator begin() const { return itt; }
    iterator cbegin() { return itt; }

    reverse_iterator rbegin() noexcept { return reverse_iterator(avail); }
    const_reverse_iterator rbegin() const noexcept { return reverse_iterator(avail); }
    const_reverse_iterator crbegin() const noexcept { return reverse_iterator(avail); }

    iterator end() { return avail; }
    const_iterator end() const { return avail; }
    iterator cend() { return avail; }

    reverse_iterator rend() noexcept { return reverse_iterator(itt); }
    const_reverse_iterator rend() const noexcept { return reverse_iterator(itt); }
    const_reverse_iterator crend() const noexcept { return reverse_iterator(itt); }

    // palyginimo operatoriai:
    bool operator==(const Vector<T> &v) const;
    bool operator!=(const Vector<T> &v) const;
    bool operator<(const Vector<T> &v) const;
    bool operator<=(const Vector<T> &v) const;
    bool operator>(const Vector<T> &v) const;
    bool operator>=(const Vector<T> &v) const;

    // member funkcijos:
    void push_back(const T &t) {
        if (avail == limit)
            grow(); // padidinam atmintį, jei reikia
        unchecked_append(t); // priskiria reikšmę, avail++
    }

    void assign(size_type n, const value_type& val);
    void assign(const_iterator t_start_ptr, const_iterator t_end_ptr);

    void pop_back();
    void insert(const_iterator position, const value_type& val);
    void insert(const_iterator position, size_type n, const value_type& val);
    void insert(iterator position, const_iterator first, const_iterator last);
    void clear();
    void erase(const_iterator it);
    void erase(const_iterator it1, const_iterator it2);
    void resize(size_type n, const value_type& val);
    void resize(size_type n);
    void swap(Vector<T> &v);
    void shrink_to_fit();
    void reserve(size_type n);
    bool empty() { return begin() == end(); }
    void emplace(Vector<T>::const_iterator it, T args);
    void emplace_back(T args);

    inline typename std::remove_reference<T>::type &&move_(T &obj);
    inline typename std::remove_reference<T>::type &&move_(T &&obj);

private:
    iterator itt; // pirmas elementas
    iterator avail; // už paskutinio sukonstruoto elemento
    iterator limit; // už paskutinės rezervuotos vietos
    std::allocator<T> alloc;

    // privačios funkcijos:
    void create(); // išskirti atmintį ir ją inicializuoti
    void create(size_type, const T &);
    void create(const_iterator, const_iterator);
    void uncreate(); // sunaikinti elem ir atlaisvinti atmintį
    void grow();
    void unchecked_append(const T &);
    size_t _capacity;
    size_t _size;

    //template<typename T, typename T, typename T>
};

template<class T>
void Vector<T>::assign(const_iterator t_start_ptr, const_iterator t_end_ptr) {
    clear();
    resize(0);

    for (const_iterator iter = t_start_ptr; iter < t_end_ptr; ++iter) {
        push_back(*iter);
    }
}

template<class T>
void Vector<T>::assign(size_type n, const value_type& val) {
    clear();
    reserve(n);
    for (size_type i = 0; i < n; ++i) {
        push_back(val);
    }
}

// ducopy metodai užpildymui:
template<class ForwardIt, class T>
void uninitialized_fill(ForwardIt first, ForwardIt last, const T &value);
template<class InputIt, class ForwardIt>
ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first);

template<class T>
void Vector<T>::create() {
    itt = avail = limit = nullptr;
}

template<class T>
void Vector<T>::create(size_type n, const T &val) {
    itt = alloc.allocate(n); // grąžina ptr į array pirmą elem
    limit = avail = itt + n; // sustato rodykles į vietas
    std::uninitialized_fill(itt, limit, val); // užpildo elementus val reikšme
}

template<class T>
void Vector<T>::create(const_iterator i, const_iterator j) {
    itt = alloc.allocate(j - i);
    limit = avail = std::uninitialized_copy(i, j, itt);
} // konstruoti naują vektorių iš seno

template<class T>
void Vector<T>::uncreate() {
    if (itt) {
        iterator it = avail;
        while (it != itt) // kol ne pradžioje
            alloc.destroy(--it); // naikiname
        alloc.deallocate(itt, limit - itt); // atlaisviname
    }
    itt = limit = avail = nullptr;
}

template<class T>
void Vector<T>::grow() {
    size_type new_size = std::max(2 * (limit - itt), ptrdiff_t(1)); // padidiname masyvą dvigubai
    iterator new_data = alloc.allocate(new_size); // išskirti naują vietą ir perkopijuoti egzistuojančius elementus
    iterator new_avail = std::uninitialized_copy(itt, avail, new_data);

    uncreate(); // atlaisvinti seną vietą
    itt = new_data; // reset'iname rodykles  į naujai išskirtą vietą
    avail = new_avail;
    limit = itt + new_size;
}

template<class T>
void Vector<T>::unchecked_append(const T &value) {
    alloc.construct(avail++, value);
} // tariame, kad 'avail' point'ina į išskirtą, bet neinicializuotą vietą

template<class T>
Vector<T> &Vector<T>::operator=(const Vector &other) {
    if (&other != this) {
        uncreate(); // atlaisviname seną atmintį
        create(other.begin(), other.end()); // perkopijuojame iš rhs į lhs
    }
    return *this;
}

template<class T>
class alloc {
public:
    T *allocate(size_t); // išskirti raw atmintį
    void deallocate(T *, size_t); // atlaisvinti
    void construct(T *, const T &); // c-tor
    void destroy(T *); //d-tor
};

// funkcijos (de)alokavimams

template<class T>
void Vector<T>::insert(Vector<T>::const_iterator position, const value_type& val) { // prieš 'it' įdedamas
    insert(position, 1, val);
}

template<typename T>
void Vector<T>::insert(const_iterator position, size_type n, const value_type& val) {   // Fill
    if (size() + n < capacity()) {
        size_type index = position - itt;
        iterator true_position = itt + index;

        iterator new_avail = std::move(true_position, avail, true_position + n);
        std::fill(true_position, true_position + n, val);

        avail = new_avail;
    }
    else if (size() + n >= capacity())
    {
        size_type index = position - itt;
        grow();
        iterator new_position = itt + index;
        insert(new_position, n, val);
    }
}
template<typename T>
void Vector<T>::insert(Vector<T>::iterator position, const_iterator first, const_iterator last) {   // Range
    if (size() + (last - first) < capacity()) {
        size_type index = position - itt;
        size_type n = last - first;
        iterator true_position = itt + index;

        iterator new_avail = std::move(true_position, avail, true_position + n);
        std::copy(first, last, position);

        avail = new_avail;
    }
    else if (size() + (last - first) >= capacity())
    {
        size_type index = position - itt;
        grow();
        iterator new_position = itt + index;
        insert(new_position, first, last);
    }
}

template<typename T>
void Vector<T>::clear() {
    resize(0);
}

template<typename T>
void Vector<T>::shrink_to_fit() {
    if (avail < limit) {
        limit = avail;
    }
}

template<typename T>
void Vector<T>::erase(Vector<T>::const_iterator it) {
    erase(it, avail);
}


template<typename T>
void Vector<T>::erase(Vector<T>::const_iterator it1, Vector<T>::const_iterator it2) {
    if (it1 < itt || it2 > avail)
        throw std::out_of_range{"Vector::erase"};

    size_type v = 0, g = 0;

    for (auto k = begin(); k < it1; k++) v++;
    for (auto k = it1; k < it2; ++k) g++;

    for (; v < size() - g; v++) {
        itt[v] = itt[v + g];
    }
    iterator it = avail;
    while (it != itt + v) // kol ne ten
        alloc.destroy(--it); // naikiname

    avail -= g;
}


template<typename T>
void Vector<T>::resize(Vector<T>::size_type n, const Vector<T>::value_type& val) {
    if (n > capacity()) {
        grow();
        resize(n, val);
    } else if (n > size()) {
        size_type sz = size();
        size_type skirtumas = n - size();
        avail += skirtumas;

        for (auto i = sz; i < n; i++) {
            itt[i] = val;
        }
    } else resize(n);
}

template<typename T>
void Vector<T>::resize(size_type n) {
    if (n < size()) {
        erase(itt + n, avail);
    } else if (n > capacity()) {
        grow();
        resize(n);
    } else if (n > size()) {
        auto skirtumas = n - size();
        avail += skirtumas;

        for (auto i = size(); i < n; i++) {
            alloc.destroy(itt + i);
        }
    }
}

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


template<typename T>
T *Vector<T>::data() noexcept {
    return data;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::max_size() const noexcept {
    return (double) (std::numeric_limits<T>::max() - std::numeric_limits<T>::min());
}

template<typename T>
void Vector<T>::swap(Vector<T> &v) {
    iterator data2 = itt, avail2 = avail, limit2 = limit;
    itt = v.itt;
    limit = v.limit;
    avail = v.avail;

    v.itt = data2;
    v.avail = avail2;
    v.limit = limit2;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T> &v) const {
    if (v.size() != size())
        return false;
    else {
        size_type g = v.size();

        for (size_type k = 0; k < g; k++) {
            if (itt[k] != v.itt[k]) { return false; }
        }

        return true;
    }
}

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

template<typename T>
bool Vector<T>::operator<(const Vector<T> &v) const {
    bool tr;
    tr = operator==(v);
    if (tr)
        return false;

    else {
        size_type g = v.size();
        for (size_type a = 0; a < g; a++) {
            if (itt[a] < v.itt[a])
                return true;
            else if (itt[a] > v.itt[a])
                return false;
        }
    }
}

template<typename T>
bool Vector<T>::operator<=(const Vector<T> &v) const {
    bool tr;
    tr = operator==(v);

    if (tr)
        return true;

    else {
        tr = operator<(v);

        return tr; // tr==true or false
    }
}

template<typename T>
bool Vector<T>::operator>(const Vector<T> &v) const {
    bool t;
    t = operator<=(v);

    return !t;
}

template<typename T>
bool Vector<T>::operator>=(const Vector<T> &v) const {
    bool t;
    t = operator<(v);

    return !t;
}

template<typename T>
void Vector<T>::emplace(Vector<T>::const_iterator it, T args) {
    if ((it < itt) || (it > avail)) {
        throw std::out_of_range{"Vector::emplace"};
    }
    size_type v = 0;

    for (auto a = begin(); a < it; a++) {
        v++;
    }

    size_type new_size = (size() + 1);
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(itt, avail + 1, new_data);

    for (size_type i = 0; i < v; i++) {
        new_data[i] = itt[i];
    }

    new_data[v] = args;
    size_type z = v + 1;
    size_type g = size() + 1;

    for (size_type i = z; i < g; i++) {
        new_data[i] = itt[i - 1];
    }

    uncreate();
    itt = new_data;
    avail = new_avail;
    limit = itt + new_size;
}

template<typename T>
void Vector<T>::emplace_back(T args) {
    push_back(args);
}

template<class T>
void Vector<T>::pop_back() {
    iterator itavail = avail;
    alloc.destroy(--itavail); // pirma sumažina, tada atima
    avail = itavail;
}

#endif //OBJEKTINISPROGRAMAVIMAS_4_VECTOR_H
