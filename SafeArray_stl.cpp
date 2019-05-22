#include <iostream>
#include <memory>
#include <iterator>
#include <algorithm>

template <typename T>
class SA {
	std::shared_ptr<T[]> safe_ary;
	int l, h, size;
	void init_empty_safeary();
public:
	typedef T value_type;
	SA();
	SA(const int);
	SA(const int, const int);
	SA(const int, const int, const std::initializer_list<T> &);
	SA(const std::initializer_list<T> &);

	SA(const SA<T>&);

	~SA();

	void resize(const int, const int);
	SA<T>& operator=(const SA &);
	T &operator[](const int);

	class iterator {
	private:
		std::shared_ptr<T[]> safe_ary;
		int cur_index;
		friend class SafeArray;
	public:
		typedef T value_type;
		typedef std::random_access_iterator_tag iterator_category;
		typedef ptrdiff_t  difference_type;
		typedef T* pointer;
		typedef T& reference;

		iterator(std::shared_ptr<T[]> safe_ary, int cur_index = 0);
		T& operator*(); // dereferencing
		iterator& operator++(); // prefix
		iterator operator++(int); // postfix
		iterator& operator--();
		iterator operator--(int);
		bool operator==(const iterator& x)const;
		bool operator!=(const iterator& x)const;
		bool operator<(const iterator& x)const;
		int operator-(const iterator&rhs)const;
		iterator operator-(int)const;
		iterator operator+(int)const;
	};
	iterator begin() const;
	iterator end() const;

};


template <typename T>
void SA<T>::init_empty_safeary() {
	l = 0; h = -1; size = 0;
	safe_ary = nullptr;
}

template <typename T>
SA<T>::SA() {
	init_empty_safeary();
}

template <typename T>
SA<T>::SA(const int size) {
	if (size < 0) {
		std::cout << "size cannot be negative number." << std::endl;
		exit(1);
	}
	else if (size > 0) {
		l = 0;
		h = size - 1;
		this->size = size;
		safe_ary = std::shared_ptr<T[]>(new T[size]);
	}
	else {
		init_empty_safeary();
	}

}

template <typename T>
SA<T>::SA(const int l, const int h) {
	if (h == -1 && l == 0) {
		init_empty_safeary();
	}
	else if (h - l < 0) {
		std::cout << "size cannot be negative number." << std::endl;
		exit(1);
	}
	else {
		this->l = l;
		this->h = h;
		size = h - l + 1;
		safe_ary = std::shared_ptr<T[]>(new T[size]);

	}

}


template <typename T>
SA<T>::SA(const std::initializer_list<T> & v) {
	this->l = 0;
	this->h = v.size() - 1;
	size = v.size();
	safe_ary = std::shared_ptr<T[]>(new T[size]);
	int i = 0;
	for (auto itr : v) {
		safe_ary[i++] = itr;
	}

}


template <typename T>
SA<T>::SA(const SA<T>& safe_ary) {
	this->l = safe_ary.l;
	this->h = safe_ary.h;
	this->size = safe_ary.size;
	this->safe_ary = std::shared_ptr<T[]>(new T[this->size]);
	for (int i = 0; i < this->size; i++)
		this->safe_ary[i] = safe_ary.safe_ary[i];

}


template <typename T>
SA<T>::~SA() {}

template <typename T>
SA<T>& SA<T>::operator=(const SA & safe_ary) {
	if (this == &safe_ary) {
		return *this;

	}

	this->safe_ary = std::shared_ptr<T[]>(new T[safe_ary.size]);
	for (int i = 0; i < safe_ary.size; i++) {
		this->safe_ary[i] = safe_ary.safe_ary[i];
	}
	this->l = safe_ary.l;
	this->h = safe_ary.h;
	this->size = safe_ary.size;
	return *this;

}

template <typename T>
T& SA<T>::operator[](const int i) {
	if (i<l || i>h) {
		std::cout << "index out of range." << std::endl;
		throw std::out_of_range("index is out of range");
	}

	else
		return safe_ary[i - l];
}


template <typename T>
void SA<T>::resize(const int l, const int h) {
	this->l = l;
	this->h = h;
	this->size = h - l + 1;
	safe_ary = std::shared_ptr<T[]>(new T[SA<T>::size]);

}


template <typename T>
typename SA<T>::iterator SA<T>::begin() const {
	return iterator(safe_ary, 0);

}


template <typename T>
typename SA<T>::iterator SA<T>::end() const {
	return iterator(safe_ary, size);
}



template <typename T>
SA<T>::iterator::iterator(std::shared_ptr<T[]> safe_ary, int index) : cur_index(index), safe_ary(safe_ary) {}
template<typename T>

T& SA<T>::iterator::operator*() {
	return safe_ary[cur_index];

}



template<typename T>
typename SA<T>::iterator& SA<T>::iterator::operator++() {
	cur_index = cur_index + 1;
	return *this;

}



template<typename T>
typename SA<T>::iterator SA<T>::iterator::operator++(int) {
	iterator temp = *this;
	++*this;
	return temp;
}

template<typename T>
bool SA<T>::iterator::operator==(const SA::iterator &rhs) const {
	return (safe_ary == rhs.safe_ary && cur_index == rhs.cur_index);

}

template<typename T>
bool SA<T>::iterator::operator!=(const SA::iterator &rhs) const {
	return !(safe_ary == rhs.safe_ary && cur_index == rhs.cur_index);

}

template<typename T>
int SA<T>::iterator::operator-(const SA::iterator &rhs) const {
	return cur_index - rhs.cur_index;
}

template<typename T>
typename SA<T>::iterator SA<T>::iterator::operator+(int x) const {
	return iterator(safe_ary, cur_index + x);
}

template<typename T>
typename SA<T>::iterator SA<T>::iterator::operator-(int x) const {
	return iterator(safe_ary, cur_index - x);
}

template<typename T>
bool SA<T>::iterator::operator<(const SA::iterator &rhs) const {
	return (safe_ary == rhs.safe_ary && cur_index < rhs.cur_index);

}

template<typename T>
typename SA<T>::iterator& SA<T>::iterator::operator--() {
	cur_index--;
	return *this;

}

template<typename T>
typename SA<T>::iterator SA<T>::iterator::operator--(int x) {
	iterator temp = *this;
	cur_index--;
	return temp;
}

int main() {
	int l = 0, h = 10;
	SA<int> safe_ary(l, h);

	for (int i = l; i <= h; i++) {

		safe_ary[h - i] = i * 10;

	}

	for (auto v : safe_ary) {

		std::cout << v << " ";

	}

	std::cout << std::endl;


	//using find()
	auto found = std::find(safe_ary.begin(), safe_ary.end(), 20);

	if (found == safe_ary.end()) {

		std::cout << "20 not found: " << std::endl;

	}

	else {

		std::cout << "20 is found: " << *found << std::endl;

	}


	std::cout << "original" << std::endl;
	for (auto v : safe_ary) {

		std::cout << v << " ";

	}

	std::cout << std::endl;


	//using sort()
	std::cout << "sorted order" << std::endl;

	std::sort(safe_ary.begin(), safe_ary.end());


	for (auto v : safe_ary) {

		std::cout << v << " ";

	}

	std::cout << std::endl;
	std::cin.get();
}