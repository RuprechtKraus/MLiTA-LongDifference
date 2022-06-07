#pragma once
#include <array>
#include <iostream>
#include <string>
#include <vector>

class BigUInt
{
public:
	BigUInt() = default;
	BigUInt(const std::string& number);
	size_t GetSize() const noexcept;

	uint64_t& operator[](size_t index);
	const uint64_t& operator[](size_t index) const;
	friend BigUInt operator-(const BigUInt& left, const BigUInt& right);
	friend std::ostream& operator<<(std::ostream& os, const BigUInt& bigInt);

private:
	std::vector<uint64_t> m_nums;
};