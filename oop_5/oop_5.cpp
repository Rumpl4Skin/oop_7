#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

struct book {
	int regNum;
	string author;
	string name;
	int year;
	string publisher;
	int pages;
};

struct node
{
	book elem;
	node* sled;
	node* pred;
};

class Circle
{
public:
	node* nsp;
	node* activElem;

	Circle();
	Circle(node*);
	void BuiltRing();
	void VyvodLeftRight();
	void Delete(node*);
	void Ochistka();
	void IteratorSled();
	void IteratorPred();
	node* SearchRing(int);
	void InsAfter(node*, book);

	friend class Iterator;
	friend class AlgoInsert;

	friend ostream& operator<< (ostream& out, const Circle& stud);

	Circle& operator ++();

};

class Iterator {
public:
	friend class AlgoInsert;
	Circle* crl;
	Iterator(Circle& c) {
		crl = &c;
	}

	void IteratorSled()
	{
		node* r;

		cout << (*((*crl->activElem).sled)).elem.author << (*((*crl->activElem).sled)).elem.name << (*((*crl->activElem).sled)).elem.pages << (*((*crl->activElem).sled)).elem.publisher << (*((*crl->activElem).sled)).elem.regNum << (*((*crl->activElem).sled)).elem.year << endl;
		crl->activElem = crl->activElem->sled;
	}

	node* IteratorSld()
	{
		crl->activElem = crl->activElem->sled;
		return  crl->activElem;
	}

	node operator [](int x)
	{
		for (int i = 0; i < x - 1; i++) {
			IteratorSld();
		}
		return *IteratorSld();

	}
};

class AlgoInsert {
public:
	int data;
	Circle* crl;
	AlgoInsert(Circle& c) {
		crl = &c;
	}
	friend class Circle;

	void Count()
	{
		node* r;

		Iterator itr(*crl);

		int countEl = 0;

		countEl++;
		r = (*((*crl->nsp).sled)).sled;
		while (r != (*crl->nsp).sled)
		{
			countEl++;
			r = (*r).sled;
		}
		cout << countEl << endl;

		cout << "Количество книг со страницами меньше чем ";
		int user;
		cin >> user;
		int lessThanUser = 0;
		for (int i = 0; i < countEl; i++) {
			auto r = itr.IteratorSld();
			if (r->elem.pages < user) lessThanUser++;
		}
		cout << "Элементов меньше " << user << " вот столько - " << lessThanUser << endl;
	}

	void sort()
	{
		node* r;

		Iterator itr(*crl);

		int countEl = 0;

		countEl++;
		r = (*((*crl->nsp).sled)).sled;
		while (r != (*crl->nsp).sled)
		{
			countEl++;
			r = (*r).sled;
		}

		for (int i = 0; i < countEl - 1; i++) {

			for (int j = 0; j < countEl - 1; j++) {
				auto r = itr.IteratorSld();
				if (r->elem.author > r->sled->elem.author) {
					auto temp = r->elem;
					r->elem = r->sled->elem;
					r->sled->elem = temp;
				}
			}
			auto r = itr.IteratorSld();
		}
	}

	void moveElems()
	{
		node* r;

		Iterator itr(*crl);

		int countEl = 0;

		countEl++;
		r = (*((*crl->nsp).sled)).sled;
		while (r != (*crl->nsp).sled)
		{
			countEl++;
			r = (*r).sled;
		}

		int IDLesserThan;
		cout << "В конец будут перемещены элементы, где ID меньше чем ";
		cin >> IDLesserThan;

		vector<book> firstPartArr;
		vector<book> secondPartArr;

		for (int i = 0; i < countEl; i++) {
			auto r = itr.IteratorSld();
			if (r->elem.regNum < IDLesserThan) {
				firstPartArr.push_back(r->elem);
			}
			else {
				secondPartArr.push_back(r->elem);
			}
		}

		for (int i = 0; i < firstPartArr.size; i++) {
			auto r = itr.IteratorSld();
			r->elem = firstPartArr[i];
		}
		for (int i = 0; i < secondPartArr.size; i++) {
			auto r = itr.IteratorSld();
			r->elem = secondPartArr[i];
		}

	}


};

Circle::Circle() : nsp(nullptr), activElem(nullptr) {};
Circle::Circle(node* el) : nsp(el), activElem(el) {};

ostream& operator<< (ostream& out, const Circle& uzel)
{

	out << "Элементы:" << endl;

	out << (*((*uzel.nsp).sled)).elem.author << " " << (*((*uzel.nsp).sled)).elem.name << " " << (*((*uzel.nsp).sled)).elem.pages << " " << (*((*uzel.nsp).sled)).elem.publisher << " " << (*((*uzel.nsp).sled)).elem.regNum << " " << (*((*uzel.nsp).sled)).elem.year << " " << endl;
	node* r = (*((*uzel.nsp).sled)).sled;
	while (r != (*uzel.nsp).sled)
	{
		out << (*r).elem.author << " " << (*r).elem.name << " " << (*r).elem.pages << " " << (*r).elem.publisher << " " << (*r).elem.regNum << " " << (*r).elem.year << " " << endl;
		r = (*r).sled;
	}
	out << endl;

	return out;
}

void Circle::IteratorSled()
{
	node* r;

	cout << (*((*activElem).sled)).elem.author << " " << (*((*activElem).sled)).elem.name << " " << (*((*activElem).sled)).elem.pages << " " << (*((*activElem).sled)).elem.publisher << " " << (*((*activElem).sled)).elem.regNum << " " << (*((*activElem).sled)).elem.year << endl;
	activElem = (*activElem).sled;
}

void Circle::IteratorPred()
{
	node* r;

	cout << (*((*activElem).pred)).elem.author << " " << (*((*activElem).pred)).elem.name << " " << (*((*activElem).pred)).elem.pages << " " << (*((*activElem).pred)).elem.publisher << " " << (*((*activElem).pred)).elem.regNum << " " << (*((*activElem).pred)).elem.year << endl;
	activElem = (*activElem).pred;
}

node* Circle::SearchRing(int el)
{
	node* q;
	node* p;
	node* Res;

	Res = NULL; p = nsp;
	if ((*((*p).sled)).elem.regNum == el) Res = (*p).sled;
	else
	{
		q = (*((*p).sled)).sled;
		while (q != (*p).sled && Res == NULL)
			if ((*q).elem.regNum == el) Res = q;
			else  q = (*q).sled;
	}
	return Res;
}

void Circle::InsAfter(node* q, book data)
{
	node* insert;

	insert = new(node);

	(*insert).elem = data;
	(*insert).sled = (*q).sled;

	(*insert).pred = (*(*q).sled).pred;

	(*(*q).sled).pred = insert;
	(*q).sled = insert;
}


void main()
{
	setlocale(LC_ALL, "Russian");

	Circle A;

	book ins;
	ins.author = "Inserted";
	ins.name = "book'";
	ins.pages = 412;
	ins.publisher = "Ron";
	ins.regNum = 2000;
	ins.year = 2015;

	A.BuiltRing();
	/*auto var = A.SearchRing(4);
	A.InsAfter(var, ins);*/

	AlgoInsert alIn(A);

	alIn.Count();
	alIn.sort();
	cout << "Перегруженный вывод" << endl;
	cout << A << endl;

	Iterator itr(A);
	auto dunno = itr[3];
	cout << dunno.elem.name << endl;

	cout << "Перемещаем элементы" << endl;
	alIn.moveElems();
	cout << A << endl;

}

void Circle::BuiltRing()
{
	node* re;

	//Построим заглавное звено кольцевого списка.
	nsp = new(node);
	re = nsp;
	(*nsp).pred = NULL;
	(*nsp).sled = NULL;

	cout << "Вводите книги списка: \n";
	book el;
	cout << "Регистрационный номер: \n";
	cin >> el.regNum;
	cout << "Название книги: \n";
	cin >> el.name;
	cout << "Страниц в книге: \n";
	cin >> el.pages;
	cout << "Издатель: \n";
	cin >> el.publisher;
	cout << "Автор: \n";
	cin >> el.author;
	cout << "Год выпуска: \n";
	cin >> el.year;
	cout << endl;
	while (el.regNum != 0)
	{
		(*re).sled = new (node);
		(*((*re).sled)).pred = re; re = (*re).sled;
		(*re).sled = NULL; (*re).elem = el;

		cout << "Регистрационный номер: \n";
		cin >> el.regNum;
		cout << "Название книги: \n";
		cin >> el.name;
		cout << "Страниц в книге: \n";
		cin >> el.pages;
		cout << "Издатель: \n";
		cin >> el.publisher;
		cout << "Автор: \n";
		cin >> el.author;
		cout << "Год выпуска: \n";
		cin >> el.year;
		cout << endl;
	}
	//А теперь - образуем кольцевой список!
	if ((*nsp).sled != NULL)
	{
		(*((*nsp).sled)).pred = re;
		(*re).sled = (*nsp).sled;
		activElem = nsp;
	}
	else
		cout << "Кольцевой список пуст!\n";
}

void Circle::VyvodLeftRight()
// Вывод содержимого двунаправленного кольцевого списка
// с удаленным заглавным звеном "по часовой стрелке".
// nsp - указатель на заглавное звено списка.
{
	node* r;

	cout << "Кольцевой список: ";
	if ((*nsp).sled != NULL)
	{
		cout << (*((*nsp).sled)).elem.author << " " << (*((*nsp).sled)).elem.name << " " << (*((*nsp).sled)).elem.pages << " " << (*((*nsp).sled)).elem.publisher << " " << (*((*nsp).sled)).elem.regNum << " " << (*((*nsp).sled)).elem.year << " " << endl;
		r = (*((*nsp).sled)).sled;
		while (r != (*nsp).sled)
		{
			cout << (*r).elem.author << " " << (*r).elem.name << " " << (*r).elem.pages << " " << (*r).elem.publisher << " " << (*r).elem.regNum << " " << (*r).elem.year << " " << endl;
			r = (*r).sled;
		}
		cout << endl;
	}
	else cout << "пуст!";
}

void Circle::Delete(node* Res)
// Удаление из кольцевого двунаправленного списка
// звена, на которое указывает ссылка Res.
// nsp - указатель на заглавное звено списка.
{
	if ((*Res).sled == Res)
	{
		(*nsp).sled = NULL; delete Res;
	}
	else
	{
		(*(*Res).sled).pred = (*Res).pred;
		(*(*Res).pred).sled = (*Res).sled;
		if ((*nsp).sled == Res)
			// Удаляем "первое" звено кольца.
			(*nsp).sled = (*Res).sled;
		delete Res;
	}
}

