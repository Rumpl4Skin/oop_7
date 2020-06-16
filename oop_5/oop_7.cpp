
#include <iostream>
#include <iomanip>
#include<fstream>
#include <string>
#include <deque>
#include <list>

using namespace std;

template<class T>
T vvod() {
	for (;;) {
		try {
			T n = NULL;
			if (!(cin >> n)) throw 1;
			return n;
		}
		catch (int) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Error!" << endl;
		}
	}
}

template<class T>
T vvod(T i, T j) {
	for (;;) {
		try {
			T n = vvod <int>();
			if (n < i || n > j) throw 1.5;
			return n;

		}
		catch (double) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Err" << i << " до " << j << endl;
		}
	}
}

class Sotrudnik {
private:
	char Name[100];
	char Doljn[100];
	int Staj;
public:
	Sotrudnik() {};
	void in(char NAME[100], char Doljn[100], int Staj);
	friend ostream& operator<< (ostream &out, const Sotrudnik &sotr);
	bool operator <(Sotrudnik &sotr);
	bool operator >(Sotrudnik &sotr);
	void operator =(Sotrudnik &sotr);
	friend bool operator==(const Sotrudnik &st, char* &gr);
	char* getName();
	char* getDoljn();
	int getStaj();;
};


void Sotrudnik::in(char NAME[100], char Doljn[100], int Staj)
{
	strcpy_s(this->Name, NAME);
	strcpy_s(this->Doljn, Doljn);
	this->Staj = Staj;
}
char* Sotrudnik::getName()
{
	return Name;
}

char* Sotrudnik::getDoljn()
{
	return Doljn;
}

int Sotrudnik::getStaj()
{
	return Staj;
}

bool Sotrudnik::operator<(Sotrudnik &pr)
{
	char f[100];
	strcpy_s(f, pr.getName());
	if ((int)Name[0] < (int)f[0])
		return true;
	else return false;
}

bool Sotrudnik::operator>(Sotrudnik &pr)
{
	char f[100];
	strcpy_s(f, pr.getName());
	if ((int)Name[0] > (int)f[0])
		return true;
	else return false;
}

void Sotrudnik::operator=(Sotrudnik &pr)
{
	strcpy_s(this->Name, pr.getName());
	strcpy_s(this->Doljn, pr.getDoljn());
	this->Staj = pr.getStaj();
}

bool operator==(const Sotrudnik &sotr, char* &gr) {
	if (strcmp(sotr.Name, gr) == 0)
		return true;
	else return false;
}

ostream& operator<< (ostream &out, const Sotrudnik &sotr)
{
	out << "Имя:" << endl;
	out << sotr.Name << endl;
	out << "Должность:" << endl;
	out << sotr.Doljn << endl;
	out << "Стаж:" << endl;
	out << sotr.Staj << " ";
	return out;
}

//template <class T>
//void quickSort(int left, int right, deque<T> &itr);
//
//template <class T>
//void find(deque<T> &deq, char* group);
//
//template <class T>
//void del(deque<T> &deq, char* group);

class Algoritm
{
public:
	Algoritm();
	~Algoritm();
	template <class T>
	void quickSort(int left, int right, deque<T> &deq) {
		int l = left, r = right;
		T mid = deq[(r + l) / 2], help;
		while (l < r) {
			while (deq[l] < mid)
			{
				l++;
			}
			while (deq[r] > mid)
			{
				r--;
			}
			if (l <= r) {
				help = deq[l];
				deq[l] = deq[r];
				deq[r] = help;
				l++; r--;
			}
		}
		if (left < r)
			quickSort(left, r, deq);
		if (l < right)
			quickSort(l, right, deq);
	}

	template <class T>
	void find(deque<T> &deq, char* group) {
		deque<Sotrudnik>::const_iterator itr_b = deq.begin();
		deque<Sotrudnik>::const_iterator itr_e = deq.end();
		bool fl = true;
		while (itr_b != itr_e) {
			if (*itr_b == group)
			{
				cout << *itr_b << endl;
				fl = false;
				break;
			}
			itr_b++;
		}
		if (fl) throw 1;
	}

	template <class T>
	void del(deque<T> &deq, char* group) {
		deque<Sotrudnik>::iterator itr_b = deq.begin();
		deque<Sotrudnik>::iterator itr;

		bool fl = true;
		while (itr_b != deq.end()) {
			if (*itr_b == group)
			{
				for (itr = itr_b; itr != deq.end() - 1; itr++) {
					*itr = *(itr + 1);
				}
				deq.pop_back();
			}
			itr_b++;
		}
	}

};

Algoritm::Algoritm()
{
}

Algoritm::~Algoritm()
{
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите количество Сотрудников:" << endl;
	int n = vvod<int>();
	deque<Sotrudnik> deq;
	Sotrudnik sotr;
	char Name[100];
	char Doljn[100];
	int Staj;
	Algoritm al;
	for (int i = 0; i < n; i++) {
		cout << "Введите Имя: " << endl;
		cin.ignore();
		cin.getline(Name, 100);
		cout << "Введите должность: " << endl;
		cin.ignore();
		cin.getline(Doljn, 100);
		cout << "Введите стаж: " << endl;
		Staj = vvod<int>();
		sotr.in(Name, Doljn, Staj);
		deq.push_back(sotr);
	}
	int ch = 0;
	while (ch != 7)
	{
		cout << "1. Вывести список Сотрудников" << endl;
		cout << "2. Вывести список Сотрудников в обратном порядке" << endl;
		cout << "3. Сортировать список Сотрудников" << endl;
		cout << "4. Просмотреть информацию о Сотрудниках" << endl;
		cout << "5. Найти сотрудника" << endl;
		cout << "6. Удалить сотрудника" << endl;
		cout << "7. Выход" << endl;
		cout << "Выбор меню:" << endl;
		ch = vvod<int>(1, 7);
		switch (ch)
		{
		case 1:
		{
			deque<Sotrudnik>::const_iterator pt;
			if (deq.empty()) {
				cout << "Список пуст" << endl;
			}
			cout << "Количество Сотрудников: " << deq.size() << endl;
			for (pt = deq.begin(); pt != deq.end(); pt++)
				cout << *pt << endl;
		}
		break;
		case 2:
		{
			deque<Sotrudnik>::reverse_iterator pt;
			if (deq.empty()) {
				cout << "Список пуст" << endl;
			}
			cout << "Количество Сотрудников: " << deq.size() << endl;
			for (pt = deq.rbegin(); pt != deq.rend(); pt++)
				cout << *pt << endl;
		}
		break;
		case 3:
		{
			al.quickSort(0, deq.size() - 1, deq);
			cout << "   Отсортировано!" << endl;
		}
		break;
		case 4:
		{
			cout << "Введите порядковый Сотрудников:" << endl;
			int num = vvod<int>() - 1;
			cout << deq[num] << endl;
		}
		break;
		case 5:
		{
			try
			{
				cout << "Введите имя: " << endl;
				cin.ignore();
				cin.getline(Name, 100);
				al.find(deq, Name);
			}
			catch (int)
			{
				cout << "Совпадений не найдено" << endl;
			}
		}
		case 6:
		{
			cout << "Введите имя: " << endl;
			cin.ignore();
			cin.getline(Name, 10);
			al.del(deq, Name);
		}
		case 7:
			break;
		default:
			cout << "Err" << endl;
			break;
		}
	}
	return 0;
}