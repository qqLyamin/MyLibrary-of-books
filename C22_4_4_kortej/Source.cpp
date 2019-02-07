//«адание 4 std::tuple
	//—оздайте класс book (автор, заглавие, год издани€...). 

	//—оздайте библиотеку таким образом, чтобы книги хранились в упор€доченном виде.
	//„тобы упор€дочить совокупность книжек, нужно сформировать условие сравнени€, то есть
	//перегрузить, например operator<. ѕри реализации оператора хочетс€ сформировать условие
	//tie()   в них пихаю кортеж и их сравниваю < >> <>
	//с учетом всех данных!!! 

	//ѕодсказка: ƒл€ упор€дочени€ удобно использовать шаблон std::tuple,
	//так как дл€ std::tuple перегружены операторы ==,!=,<,<=,>,>=
	//,которые сравнивают два кортежа лексиграфически (в пор€дке следовани€ членов).


	//ƒл€ проверки распечатайте библиотеку

#include <iostream>
#include <string>
#include <tuple>
#include <map>
#include <vector>
#include <algorithm>
#include <set>

class book
{
	std::string author;
	std::string name;
	int date_of_create = 0;

public:

	book() = default;

	bool operator>(const book & right) const
	{
		return std::tie(this->author, this->name, this->date_of_create) > std::tie(right.author, right.name, right.date_of_create);
	};

	bool operator<(const book & right) const
	{
		return std::tie(this->author, this->name, this->date_of_create) < std::tie(right.author, right.name, right.date_of_create);
	};

	book(const char * A, const char * N, int D): author(A), name(N), date_of_create(D) 
	{};

	std::tuple<std::string, std::string, int> my_make_tuple()
	{
		return std::make_tuple(this->author, this->name, this->date_of_create);
	}	

	friend std::ostream& operator<<(std::ostream& mycout, const book & mybook)
	{
		mycout << mybook.author << " " << mybook.name << " " << mybook.date_of_create << std::endl;
		return mycout;
	};	

	//другие операции =default
	~book() = default;
};





int main()
{
	
	book first("David Allen", "Getting things done", 2017);
	book second("Scott Davis", "My Thuth", 2009);
	book another("Dan Brown", "da vinci code", 2014);

	std::vector<book> my_books;
	my_books.reserve(3);

	my_books.push_back(first);
	my_books.push_back(second);
	my_books.push_back(another); //почему нельз€ emplace???
	
	for (size_t i = 0; i < my_books.size() - 1; i++)
	{
		for (size_t j = i + 1; j < my_books.size(); j++)
		{
			//if (my_books[j].my_make_tuple() > my_books[i].my_make_tuple())			
			if (my_books[j] > my_books[i])
			{
				auto tmp = my_books[j];
				my_books[j] = my_books[i];
				my_books[i] = tmp;
			}			
		}	
	}

	std::map<int, book> my_library;
	std::set<book> myset;

	for (size_t i = 0; i < my_books.size(); i++)
	{
		my_library.emplace(i + 1, my_books[i]/*.my_make_tuple()*/);
	}
	
	for (size_t i = 0; i < my_books.size(); i++)
	{
		myset.emplace(my_books[i]);
	}

	for (auto & item : myset)
	{
		std::cout << " set " << item;
	}

	std::cout << std::endl;

	for (auto & item : my_library)
	{
		std::cout << " map " << item.second;
	}

	std::cout << std::endl;
	
	for (auto a : my_books)
	{
		std::cout << " vector " << a;
	}
	system("pause");
}