#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
typedef size_t var;

using namespace std;

var memory = 2048;

// blok w pamięci
struct node {
	var start_address, space, value, end_address;
	bool allocated;

	// blok wolny do alokowania
	node(var space): space(space), value(0), allocated(false) {}
	// blok z alokowaną już pamięcią
	node(var space, var value): space(space), value(value), allocated(true) {}
};

vector<node*> m;

// funkcja dokonuje fragmentacji bloku pamięci na równe części
vector<node*> give_slots(var space, var fitter) {
	var number_of_slots = 2;
	// porównujemy rozmiar bloku z maksymalnym zapotrzebowaniem na pamięć dla danego procesu
	if(space != fitter) {
        // liczymy, na ile bloków jesteśmy w stanie podzielić nasz obszar
		number_of_slots = 1 + (log(space/fitter)/log(2));
	}
	vector<node*> v(number_of_slots, NULL);
	v[0] = new node(fitter);

	// na podstawie wyliczonej ilości bloków, dokonujemy fragmentacji
	for(var i=1, s=fitter; i<number_of_slots; i++, s *= 2) {
        v[i] = new node(s);
    }
	return v;
}

// wpisanie procesu do pamięci
bool allocate(var value) {
    if(m.size() == 0) {
        return false;
    }
    // maksymalna potrzebna pamięć dla danej wartości alokowanej
	var fitter = pow(2, ceil(log(value)/log(2)));

	for(var i=0; i<m.size(); i++) {
        // sprawdzamy, czy maksymalna potrzebna pamięć jest równa wolnej pamięci danego bloku
        // oraz czy blok nie jest zajęty
	    if(m[i]->space == fitter && !m[i]->allocated) {
            m[i]->value = value;
            m[i]->allocated = true;

            return true;
        }
	}

	for(auto it = m.begin(); it != m.end(); it++) {
		node *temp = *it;
        // sprawdzamy, czy dany blok jest wolny
        // oraz czy maksymalna potrzebna pamięć jest mniejsza od wolnej pamięci danego bloku
		if(!temp->allocated && temp->space > fitter) {
            // dokonujemy fragmentacji
			auto slots = give_slots(temp->space, fitter);
            // w pierwszym bloku stworzonym po fragmentacji zapisujemy naszą pamięć
            // reszta bloków jest wolna
			slots[0]->value = value;
			slots[0]->allocated = true;
			slots[0]->start_address = temp->start_address;
			slots[0]->end_address = temp->start_address + slots[0]->space;

            // zmieniamy adresy kolejnych bloków w pamięci
			for(var i = 1; i<slots.size(); i++) {
				slots[i]->start_address= slots[i-1]->end_address;
				slots[i]->end_address = slots[i]->start_address + slots[i]->space;
			}

			auto previous_it = it;
			--previous_it;
			m.erase(it);

			for(var i=0; i<slots.size(); i++) {
				previous_it = m.insert(++previous_it, slots[i]);
			}
			slots.clear();
			return true;
		}
	}
	return false;
}

// sprawdzenie, czy sąsiadujące ze sobą bloki pamięci są identyczne
bool buddies(node *a, node *b) {
	var add = 2*memory;
	if(floor((add+a->start_address)/(2*a->space)) == floor((add+b->start_address)/(2*b->space))) {
		return true;
	}
	return false;
}

// sprawdzenie, czy można wykonać scalenia bloków pamięci
void check_merge() {
	auto it = m.begin(), previous_it = it; it++;
	// wykonujemy iterację po każdym bloku pamięci
	while(it != m.end()) {
		auto previous_node = *previous_it, current_node = *it;
		// sprawdzamy, czy poprzedni blok pamięci i aktualny są wolne i identyczne
		if(previous_node->allocated || current_node->allocated || (previous_node->space != current_node->space) || !buddies(previous_node, current_node)) {
			previous_it = it;
			it++;
			continue;
		}

		// scalamy dwa bloki pamięci
		previous_node->space *= 2;
		previous_node->end_address = previous_node->start_address + previous_node->space;

		m.erase(it);
		previous_it = m.begin();
		it = previous_it;
		it++;
	}
}

// zwolnienie pamięci pod podanym adresem
bool deallocate(var address) {
	if(address >= memory) {
        return false;
    }
	for(auto i: m) {
        // iterując, szukamy adresu pamięci, który chcemy zwolnić
        // sprawdzamy, czy ten blok był alokowany
		if(address == i->start_address && !i->allocated) {
            return false;
        }

		if(address == i->start_address) {
            // dokonujemy zwolnienia pamięci
			i->allocated = false;
			i->value = 0;
			check_merge();
			return true;
		}
	}
	return false;
}

int main()
{
    vector<var> a;
    vector<var> v;

    // tworzymy blok pamięci o wartości 2048
	m.emplace_back(new node(memory));
	m[0]->start_address = 0;
	m[0]->end_address = m[0]->start_address + m[0]->space;

	// wprowadzamy 6 procesów o różnych zapotrzebowaniach na pamięć
	var p[6] = {45, 90, 70, 450, 140, 23};
	var value = 0;
	cout << "PROCESSES: ";
    for (var i=0; i<6; i++) {
        cout << "P" << i+1 << ": " << p[i] << " ";
    }

    cout << endl;
    cout << endl;

    // dokonujemy alokacji
	cout << "ALLOCATION" << endl;
	for (var i=0; i<6; i++) {
        value = p[i];
        cout << endl;
        cout << "VALUE: " << value << endl;
        allocate(value);

        // wyświetlamy bloki w pamięci po wpisaniu do nich procesu
        cout << "THE BLOCKS IN MEMORY: " << endl;
        for(auto i: m) {
            var start_address = i->start_address;
            var value = i->value;
            var space = i->space;
            var end_address = i->end_address;

			cout << "START ADDRESS: " << start_address << "\t END_ADDRESS: " << end_address << "\t SIZE: "  << space << "\t VALUE: " <<  value << endl;
        }
	}
	cout << endl;

	// zapisujemy ostateczny podział pamięci po 6 alokacjach i wprowadzone rozmiary pamięci
	for(auto i: m) {
        var start_address = i->start_address;
        var value = i->value;
        a.push_back(start_address);
        v.push_back(value);
    }

    vector<size_t>::iterator it;
    // losujemy procesy do dealokacji
    random_shuffle(p,p+6);

    cout << "PROCESSES SELECTED FOR DEALLOCATION: ";
    for (var i=0; i<4; i++) {
        it = find(v.begin(), v.end(), value);
        cout << "P" << i+1 << ": " << p[i] << " ";
    }
    cout << endl;
    cout << endl;

    // dokonujemy dealokacji
    cout << "DEALLOCATION" << endl;
	for (var i=0; i<4; i++) {
        value = p[i];
        cout << endl;
        cout << "VALUE: " << value << endl;
        // sprawdzamy, pod jakim indeksem znajduje się proces do dealokacji
        // aby znaleźć adres startowy bloku, który chcemy zwolnić
        it = find(v.begin(), v.end(), value);
        deallocate(a[it-v.begin()]);

        // wyświetlamy bloki po zwolnieniu w nich pamięci
        cout <<"THE BLOCKS IN MEMORY" << endl;
        for(auto i: m) {
            var start_address = i->start_address;
            var value = i->value;
            var space = i->space;
            var end_address = i->end_address;

            cout << "START ADDRESS: " << start_address << "\t END ADDRESS: " << end_address << "\t SIZE: "  << space << "\t VALUE: " <<  value << endl;;
        }
	}

	return 0;
}
