#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;


class CList {
	friend std::ostream& operator<< (std::ostream &os, CList& sort)
	{
		os << "element " << sort.m_list->value << endl;
		return os;
	}
protected:
	struct data_t {
		int value;
	};
	int m_size, m_counter;
	data_t* m_list;
	char m_buffer[512];
	data_t* set(int counter) {
		return reinterpret_cast<data_t *>(m_buffer + sizeof(data_t) * counter);
	}
	data_t* create() {
		m_size++;
		return new (m_buffer + sizeof(data_t) * m_size) data_t;
	}
public:
	CList() {
		m_list = NULL;
		m_size = m_counter = 0;
	}
	CList(int value) {
		m_size = 1, m_counter = 0;
		m_list = new (m_buffer + sizeof(data_t) * m_size) data_t;
		m_list->value = value;
	}
	void get_first() {
		if (!m_list)
			return;
		m_counter = 1;
		m_list = set(m_counter);
	}
	void get_next() {
		if (!m_list || m_size - m_counter < 1)
			return;
		m_counter++;
		m_list = set(m_counter);
	}
	void get_last() {
		if (!m_list)
			return;
		m_counter = m_size - 1;
		m_list = set(m_counter);
	}
	void push(int value) {
		m_list = create();
		m_list->value = value;
	}
	void delete_element() {
		m_list = set(1);
		m_list->value = 0;
		for (int i = 1; i < m_size; i++) {
			m_list = set(i);
			data_t* next = set(i + 1);
			m_list->value = next->value;
		}
		m_list = set(m_size);
		m_list->value = 0;
		m_size--;
	}
	void show() {
		cout << endl;
		for (int i = 1; i <= m_size; i++) {
			m_list = set(i);
			cout << m_list->value << setw(4);
		}
		cout << endl;
	}
	void sort() {
		for (int i = 1; i < m_size; i++) {
			for (int j = 1; j <= m_size - i; j++) {
				m_list = set(j);
				data_t* next = set(j + 1);
				if (next->value < m_list->value) {
					swap(m_list->value, next->value);
				}
			}
		}
	}
};



void input(CList& list) {
	for (int i = 0; i < 9; i++) {
		list.push(rand() % 999);
	}
}

int main() {
	srand(time(NULL));
	CList list(1);
	input(list);
	cout << "unsorted:";
	list.show();
	cout << "sorted:";
	list.sort();
	list.show();
	list.delete_element();	
	list.get_first();
	cout << "current ";
	cout << list;
	list.get_next();
	cout << "next ";
	cout << list;
	system("pause");
	return 0;
}