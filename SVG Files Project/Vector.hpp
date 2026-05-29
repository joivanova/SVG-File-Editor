#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>

template<typename T>
class Vector {
private:
	class Iterator {
	public:
		Iterator(T* curr) : m_curr(curr) {}
		Iterator& operator++()
		{
			++m_curr;
			return *this;
		}

		bool operator!=(Iterator const& other) const
		{
			return m_curr != other.m_curr;
		}

		T& operator*() { return *m_curr; }
		const T& operator*() const { return *m_curr; }

	private:
		T* m_curr;
	};

public:
	using iterator = Iterator;

	//iterators
	iterator begin()
	{
		return Iterator(m_arr);
	}
	iterator end()
	{
		return Iterator(m_arr + m_size);
	}
	const iterator begin() const 
	{
		return Iterator(m_arr);
	}
	const iterator end() const
	{
		return Iterator(m_arr + m_size);
	}

	bool empty() const {
		return m_size == 0;
	}
	operator bool() const {
		return !empty();
	}
	size_t size() const {
		return m_size;
	}

	void print(std::ostream& os = std::cout) const
	{
		for (size_t i = 0; i < m_size; i++)
		{
			os << m_arr[i] << ' ';
		}
	}

	void push_back(const T& el)
	{
		if (m_size >= m_capacity) { resize(); }
		m_arr[m_size++] = el;
	}

	T pop_back()
	{
		if (m_size == 0)
		{
			throw std::out_of_range("Vector is empty!");
		}
		m_size--;
		return m_arr[m_size];
	}

	void clear() { m_size = 0; }
	void erase(size_t index)
	{
		if (index>= m_size)
		{
			throw std::out_of_range("Index out of range!");
		}

		for (size_t i = index; i < m_size - 1; ++i)
		{
			m_arr[i] = m_arr[i + 1];
		}

		m_size--;
	}

	T& operator[](size_t index) { return m_arr[index]; }
	const T& operator[](size_t index) const { return m_arr[index]; }

	T& at(size_t index) {
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range!");
		}
		return m_arr[index];
	}

	const T& at(size_t index) const {
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range!");
		}
		return m_arr[index];
	}

	T& front() {
		if (m_size == 0)
		{
			throw std::out_of_range("Index out of range!");
		}
		return m_arr[0];
	}

	const T& front() const {
		if (m_size == 0)
		{
			throw std::out_of_range("Index out of range!");
		}
		return m_arr[0];
	}

	T& back() {
		if (m_size == 0)
		{
			throw std::out_of_range("Vector is empty!");
		}
		return m_arr[m_size - 1];
	}

	const T& back() const {
		if (m_size == 0)
		{
			throw std::out_of_range("Vector is empty!");
		}
		return m_arr[m_size - 1];
	}

	public:
		Vector() : m_arr(nullptr), m_size(0), m_capacity(0){}

		Vector(const Vector& other)
		{
			copy(other);
		}
		Vector& operator=(const Vector& other)
		{
			if (this != &other)
			{
				free();
				copy(other);
			}
			return *this;
		}

		~Vector()
		{
			free();
		}
private:
	T* m_arr;
	size_t m_size;
	size_t m_capacity;

	void copy(const Vector& other)
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		m_arr = new T[m_capacity];
		for (size_t i = 0; i < m_size; i++)
		{
			m_arr[i] = other.m_arr[i];
		}
	}

	void free()
	{
		delete[] m_arr;
	}

	void resize()
	{
		m_capacity = m_capacity > 0 ? m_capacity * 2 : 1;

		T* newArr = new T[m_capacity];
		for (size_t i = 0; i < m_size; i++)
		{
			newArr[i] = m_arr[i];
		}

		delete[] m_arr;
		m_arr = newArr;
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{
	v.print(os);
	return os;
}

#endif