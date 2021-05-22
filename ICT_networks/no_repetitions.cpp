//Sonia Kedzierska, s173656
//BEZ POWTORZEN
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

int size_of_a = 80;

struct packet {

    int numer;
    int a[80];

    packet() {}
    packet(int k, int f[]) {
        //numer pakietu
        numer = k;
        for (int i=0; i<size_of_a; i++) {
            a[i] = f[i];
        }
    }

    //bit przystosci
    int paritybit(int j) {
        int sum = 0;
        int bp;
        //sumowanie wszytskich bitow rownych 1 w pakiecie
        for (int i = 0; i < j; i++) {
            if (a[i] == 1) {
                sum += 1;
            }
        }
        //je¿eli suma jest podzielna przez 2 bez reszty
        //to znaczy ze bit parzystoœci jest równy jeden je¿eli
        //jest nieparzysta to bp jest rowny 0
        if (sum % 2 != 0) {
            bp = 1;
        }
        else {
            bp = 0;
        }
        return bp;
    }
    //suma kontrolna
    int checksum(int j) {
        int sum = 0;
        for (int i = 0; i < j; i++) {
            if (a[i] == 1) {
                sum += 1;
            }
        }
        return sum;
    }

    //suma modulo
    int modulosum(int j) {
        int sum = 0;
        int b = 28; //jakakoliwek ustalona przez nas liczba
        for (int i = 0; i < j; i++) {
            if (a[i] == 1) {
                sum += 1;
            }
        }
        //sumujemy wszytskie 1 w pakiecie a nastepnie dzielimy przez
        //ustalona liczbe
        int mod = sum % b;
        return mod;
    }
    //CRC
    void crc(int size_of_message, int n, vector<int>& crc, vector<int>& div) {
        //do ciagu zrodlowego dodajemy
        //ciag n o randomowej dlugosci wypelniony zerami
        //dlugosc n mniejsza ni¿ dlugosc pakietu
        int temp[size_of_message+n], message[size_of_message+n];
        //dzielnik CRC
        for (int i=0; i<n+1; i++) {
        //losujemy randomowy dzielnik o wartosciach 0 i 1
        //i zapisujemy go w wektorze
            int d = rand() % 2;
            div.push_back(d);
        }
        for (int i=0; i<size_of_message; i++) {
            message[i] = a[i];
        }
        //ciag n musi byc wypelniony zerami
        for(int i=0;i<n;i++) {
            message[size_of_message+i] = 0;
        }
        for(int i=0;i<size_of_message+n; i++) {
            temp[i] = message[i];
        }
        for(int i=0; i<size_of_message; i++) {
            if (div[0] == temp[i]) {
                for (int j=0,k=i; j<n+1; j++,k++) {
                    //wykonujemy operacje XOR na ciagu danych oraz
                    //na dzielniku CRC
                    if(!(temp[k]^div[j])) {
                        temp[k]=0;
                    } else {
                        temp[k]=1;
                    }
                }
            }
        }
        for(int i=0;i<n;i++) {
            message[size_of_message+i] = temp[size_of_message+i];
            //zapisujemy otrzymane CRC w wektorze
            crc.push_back(temp[size_of_message+i]);
        }
    }
};
//zamiana ciagu danych z pliku zapisanych w wektorze v1 na liczby binarne i zapis w wek. v2
void to_bin(vector<char>& v1, vector<int>& v2) {
    stringstream ss;
    for (int i = 0; i < v1.size(); i++) {
        ss << v1[i];
    }
    string s = ss.str();

    int a[8];
    for (char& c : s) {
        for (int i = 0; i < 8; i++) {
            a[i] = c % 2;
            c = c / 2;
        }
        for (int i = 7; i >= 0; i--) {
            v2.push_back(a[i]);
        }
    }
}

void random_packet(vector<int>& r, vector<int>& f) {
    //ilosc bledow na pakiet
    double p = 0.01;
    //ile bitow zostanie zmienionych
    double n = p * f.size();
    //ilosc otrzymanych pakietow po podzieleniu ciagu zrodlowego z pliku na pakiety
    int s = f.size()/80;
    //losujemy w ktorych pakietach beda zmienione bity
    for(int i=0; i<n; i++) {
        int a = rand() % s + 1;
        r.push_back(a);
    }
    sort(r.begin(), r.end());
}
//dodawanie bledow
void received(int a[], int b[], vector<int>& r, int k) {
    vector<int>:: iterator it;
    //szukanie odpowiedniego numeru pakietu
    it = find(r.begin(), r.end(), k);
    if (it != r.end()) {
        //zliczanie ile razy ma byc wykonana zmiana bitu
        int n = count(r.begin(), r.end(), k);
        int c[n];
        for(int i=0; i<n; i++) {
            bool check;
            int d;
            do {
                check = true;
                //losowanie randomowej liczby mniejszej od 80
                d = rand() % size_of_a;
                for (int j=0; j<i; j++) {
                    if (d == c[j]) {
                        check = false;
                        break;
                        }
                }
            } while (!check);
            c[i] = d;
            //jezeli dany numer randomowego bitu jest równy zero to
            //zamiana na 1 i odwrotnie
            if (a[d] == 0) {
                a[d] = 1;
            } else {
                a[d] = 0;
            }
        }
    }
    for(int i=0; i<size_of_a; i++) {
        b[i] = a[i];
    }
}
//sprawdzanie po kolei czy wyslane dane zgaadzaja sie z otrzymanymi
void check_checksum(int check_sum, int a[], int j) {
    int check_check_sum = 0;
    for (int i = 0; i < j; i++) {
        if (a[i] == 1) {
            check_check_sum += 1;
        }
    }
    if (check_check_sum == check_sum) {
        cout << "Suma kontrolna sie zgadza!" << endl;
        cout << "->Suma wyslana: " << check_sum << endl;
        cout << "->Suma otrzymana: " << check_check_sum << endl;
    } else {
        cout << "Suma kontrolna sie NIE zgadza!" << endl;
        cout << "->Suma wyslana: " << check_sum << endl;
        cout << "->Suma otrzymana: " << check_check_sum << endl;
    }
}

void check_paritybit(int pb, int a[], int j) {
    int sum = 0;
    for (int i = 0; i < j; i++) {
        if (a[i] == 1) {
            sum += 1;
        }
    }
    sum += pb;
    int cpb = sum % 2;
    if (cpb == pb) {
        cout << "Bit parzystosci sie zgadza!" << endl;
        cout << "->Bit wyslany: " << pb << endl;
        cout << "->Bit otrzymany: " << cpb << endl;
    } else {
        cout << "Bit parzystosci sie NIE zgadza!" << endl;
        cout << "->Bit wyslany: " << pb << endl;
        cout << "->Bit otrzymany: " << cpb << endl;
    }
}

void check_modulosum(int ms, int a[], int j, int b) {
    int sum = 0;
    for (int i = 0; i < j; i++) {
        if (a[i] == 1) {
            sum += 1;
        }
    }
    int cms = sum % b;
    if (cms == ms) {
        cout << "Suma modulo sie zgadza!" << endl;
        cout << "->Suma wyslana: " << ms << endl;
        cout << "->Suma otrzymana: " << cms << endl;
    } else {
        cout << "Suma modulo sie NIE zgadza!" << endl;
        cout << "->Suma wyslana: " << ms << endl;
        cout << "->Suma otrzymana: " << cms << endl;
    }
}

void check_crc(int a[], int size_of_message, int n, vector<int>& crc, vector<int>& div) {
    int temp[size_of_message+n], message[size_of_message+n];
    for (int i=0; i<size_of_message; i++) {
        message[i] = a[i];
    }
    for(int i=0;i<n;i++) {
        message[size_of_message+i] = crc[i];
    }
    for(int i=0;i<size_of_message+n; i++) {
        temp[i] = message[i];
    }
    for(int i=0; i<size_of_message; i++) {
        if (div[0] == temp[i]) {
            for (int j=0,k=i; j<n+1; j++,k++) {
                if(!(temp[k]^div[j])) {
                    temp[k]=0;
                } else {
                    temp[k]=1;
                }
            }
        }
    }
    int r = 0;
    for(int i=0; i<n; i++) {
        if (temp[size_of_message+i] != 0) {
            r += 1;
        }
    }
    if (r == 0) {
        cout << "CRC sie zgadza!" << endl;
    } else {
        cout << "CRC sie NIE zgadza!" << endl;
    }
}

int main()
{
    ifstream ist{"file.txt", ios::binary};

    vector<char> v1;
    vector<int> v2;
    vector<int> r;

    //wczytywanie pliku
    if (ist) {
        char c;
        while (ist >> c) {
            v1.push_back(c);
        }
    }
    to_bin(v1, v2);
    int k = 1;
    //dlugosc pakietu dodawanego do ciagu zrodlowego w crc
    int n = rand() % 80;

    random_packet(r, v2);

    for (int i = 0; i < v2.size(); i += 80) {
        //co wysyłamy
        cout << "WYSYLANIE..." << endl;

        int arr[80], b[80];
        vector<int> c;
        vector<int> gen;

        cout << "PAKIET O NUMERZE " << k << " I ROZMIARZE 80 BITOW" << endl;
        //pakiety danych
        for (int j = 0; j < 80; j++) {
            arr[j] = v2[i + j];
            cout << arr[j];
        }
        cout << endl;

        packet* p = new packet;
        p -> numer = k;
        for (int i=0; i<size_of_a; i++) {
            p -> a[i] = arr[i];
        }
        cout << "CO WYSYLA ALICJA" << endl;
        int check_sum = p -> checksum(80);
        int parity_bit = p -> paritybit(80);
        int modulo_sum = p -> modulosum(80);
        p -> crc(80, n, c, gen);

        cout << "Suma kontrolna: " << check_sum << endl;
        cout << "Bit parzystosci: " << parity_bit << endl;
        cout << "Suma modulo: " << modulo_sum << endl;
        cout << "CRC: ";
        for (int i=0; i<c.size(); i++) {
            cout << c[i];
        }
        //wprowadzenie zaklocen
        received(p -> a, b, r, k);

        // porownanie danych wyslanych i otrzymanych
        cout << endl;
        cout << "---SPRAWDZAM---" << endl;
        check_checksum(check_sum, b, 80);
        check_paritybit(parity_bit, b, 80);
        check_modulosum(modulo_sum, b, 80, 28);
        check_crc(b, 80, n, c, gen);
        cout << "---ZAKONCZONO---" << endl;
        delete p;
        k++;
        cout << endl;
    }
    return 0;
}
