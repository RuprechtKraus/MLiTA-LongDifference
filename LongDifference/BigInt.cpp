#include "BigInt.h"

#define NAMESPACE_BEGIN namespace {
#define NAMESPACE_END }

NAMESPACE_BEGIN

inline int ctoi(char c)
{
	return c - 48;
}

NAMESPACE_END

BigUInt::BigUInt(const std::string& number)
{
	for (char c : number)
	{
		m_nums.push_back(ctoi(c));
	}
}

size_t BigUInt::GetSize() const noexcept
{
	return m_nums.size();
}

uint64_t& BigUInt::operator[](size_t index)
{
	return m_nums[index];
}

const uint64_t& BigUInt::operator[](size_t index) const
{
	return m_nums[index];
}

BigUInt operator-(const BigUInt& left, const BigUInt& right)
{
	size_t sizeDiff{ left.GetSize() - right.GetSize() };
	std::vector<bool> carry(left.GetSize(), false);
	BigUInt tmpLeft(left);
	BigUInt tmpRight(right);

	tmpRight.m_nums.insert(tmpRight.m_nums.cbegin(), sizeDiff, 0);

	for (int i = left.GetSize() - 1; i >= 0; i--)
	{
		if (carry[i])
		{
			if (tmpLeft[i] == 0)
			{
				tmpLeft[i] = tmpLeft[i] + 10;
				if (i > 0)
				{
					carry[static_cast<size_t>(i) - 1] = true;
				}
			}

			tmpLeft[i]--;
		}

		if (tmpLeft[i] < tmpRight[i])
		{
			tmpLeft[i] = tmpLeft[i] + 10 - tmpRight[i];
			if (i > 0)
			{
				carry[static_cast<size_t>(i) - 1] = true;
			}
		}
		else
		{
			tmpLeft[i] -= tmpRight[i];
		}
	}

	if (tmpLeft.m_nums[0] == 0)
	{
		tmpLeft.m_nums.erase(tmpLeft.m_nums.begin(), 
			std::find_if(tmpLeft.m_nums.begin() + 1, tmpLeft.m_nums.end(), [](int i) { 
				return i != 0; 
			}));
	}

	return tmpLeft;
}

std::ostream& operator<<(std::ostream& os, const BigUInt& bigInt)
{
	std::copy(bigInt.m_nums.cbegin(), bigInt.m_nums.cend(), std::ostream_iterator<int>(os));
	return os;
}