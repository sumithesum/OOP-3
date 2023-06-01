
#include <bits/stdc++.h>

using namespace std;

class exceptie_repetare:public std::exception{
public:
    exceptie_repetare();
    const char* what() const noexcept override;
};
exceptie_repetare::exceptie_repetare()=default;
const char* exceptie_repetare::what() const noexcept{
    return "Trebuie sa fie elemente distincte\n";
}

class exceptie_multeElemente:public std::exception{
public:
    exceptie_multeElemente();
    const char* what() const noexcept override;
};
exceptie_multeElemente::exceptie_multeElemente()=default;
const char* exceptie_multeElemente::what() const noexcept{
    return "Atentie sunt multe elemente\n";
}

template <typename T>
class Observer {
public:
    virtual void update(const std::vector<T>& items) = 0;
};


template<typename T>
class IdGen {
    inline static int LastId;

    const string Id;
public:
    IdGen() : Id("P" + to_string(LastId++)){}

    const string getId() const {
        return Id;
    }
};

template<typename T>
bool find(T item , vector<T> items){
    for(auto i : items)
        if( i == item)
            return true;
    return false;
};


template <typename T>
class Set{
    vector<Observer<T>> obss;
    vector<T> items;
public:

    virtual ~Set() {}

    class Iterator {
    private:
        typename vector<T>::const_iterator iter;

    public:

        Iterator(typename vector<T>::const_iterator it) : iter(it) {}

        const T& operator*() const {
            return *iter;
        }

        Iterator& operator++() {
            ++iter;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return iter != other.iter;
        }
    };
    Set();



    Set(const vector<T> &items){
        for (auto k: items) {
            auto iteratorul = find(items.begin(), items.end(), k);
            items.erase(iteratorul);
            iteratorul = find(items.begin(), items.end(), k);
            if (iteratorul != items.end())
                throw exceptie_repetare();
        }
    }

    void push(T elemet){
        if(find(elemet , items))
            items.push_back(elemet);
        if(items.size() > 1000000)
            throw exceptie_multeElemente();
        alerteaza();
    }
    void afisare(ostream &os){
        for(auto k: items)
            os << k << ' ';
    os << '\n';
    }
    void registerObserver(Observer<T>* obs) {
        obss.push_back(obs);
    }

    void unregisterObserver(Observer<T>* obs) {
        obss.erase(std::remove(obss.begin(), obss.end(), obs), obss.end());
    }

    friend std::ostream& operator<<(ostream& os, const Set<T>& set) {
        for (auto& k : set.items) {
            os << k << ' ';
        }
        os << '\n';
        return os;
    }

    virtual Set* clone() const {
        return new Set(*this);
    }

    void alerteaza() {
        for (auto obs : obss) {
            obs->update(items);
        }
    }




};




int main(){

    Set<int> s;
    s.push(2);
    s.push(3);
    s.push(5);
    s.afisare(cout);
    cout << find(3,s);
    cout << find(6,s);
    s.afisare(cout);
    cout << s;

    Set<int> s2 = *s.clone();
    vector<int> v3 = { 1 , 2, 3, 1};
    try{
        Set<int> s3(v3);
        s3.push(100);
    }catch(const exceptie_multeElemente &e1) {
        cout << e1.what();
    }catch (const exceptie_repetare &e2){
        cout << e2.what();
        Set<int> s3;
        for (auto k : v3)
            s3.push(k);

    }


    return 0;

}
