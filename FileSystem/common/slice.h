#pragma once

#include "assert.h"

// Random access range
template<class T>
struct Slice
{
private:
	T* begin_;
	size_t len_;

public:
	Slice() : begin_(nullptr), len_(0) { }
	Slice(const Slice&) = default;

	Slice(T* begin_, size_t len_gth)
		: begin_(begin_), len_(len_gth) { }

	/*template<class T>
	Slice<T>(const T& stl_like_container) :
		begin_(&stl_like_container.begin()_()),
		end(&stl_like_container.end()) { }*/

	T* begin() { return begin_; }
	const T* begin() const { return begin_; }

	T& front() { check(); return *begin_; }
	const T& front() const { check(); return *begin_; }

	T& back() { check(); return *(begin_ + len_ - 1); }
	const T& back() const { check(); return *(begin_ + len_ - 1); }

	T& operator[](size_t pos) { check(pos); return begin_[pos]; }
	const T& operator[](size_t pos) const { check(pos); return begin_[pos]; }

	bool empty() { return !begin_ || !len_; }
	bool empty() const { return !begin_ || !len_; }

	size_t size() { return len_; }

	void pop_front() { check(); begin_++; len_--;  }

	void pop_back() { check(); len_--; }

	// Returns the [start_idx, end_idx) sub-range (subslice).
	Slice slice(size_t start_idx, size_t end_idx)
	{
		check();
		auto result = *this;
		result.begin_ += start_idx;
		result.len_ = end_idx - start_idx;
		return result;
	}

	friend bool operator==(Slice lhs, Slice rhs)
	{
		return lhs.begin_ == rhs.begin_ &&
			lhs.len_ == rhs.len_;
	}

	friend bool operator!=(Slice lhs, Slice rhs)
	{
		return !(lhs == rhs);
	}

private:
	void check()
	{
		fs_assert(!empty(), L"Access out of range!", __func__);
	}

	void check(size_t pos)
	{
		fs_assert(!empty() && pos < len_, L"Access out of range!", __func__);
	}
};

using CharType = wchar_t;
using String = Slice<const CharType>;


inline String make_str(const wchar_t* str)
{
	return String{str, wcslen(str)};
}

inline Slice<const char> make_narrow_str(const char* str)
{
	return Slice<const char>{ str, strlen(str) };
}