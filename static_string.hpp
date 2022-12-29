/*
	static_string.hpp
	Copyright (c) 2022 codectile
	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it freely,
	subject to the following restrictions:
	1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/

#pragma once

class static_string
{
public:
	constexpr static_string() noexcept = default;
	constexpr static_string(const static_string& other) noexcept
	{
		if (other.is_empty())
			return;
		static_string_helper::copy_n(m_String, other.length(), other.m_String);
	}
	constexpr static_string(const char* string) noexcept
	{
		if (!string)
			return;
		const size_t len = static_string_helper::const_string_length(string);
		static_string_helper::copy_n(m_String, len > SIZE - 1 ? SIZE - 1 : len, string);
	}
	constexpr static_string& operator=(const static_string& other) noexcept
	{
		if (this != &other && !other.is_empty())
			static_string_helper::copy_n(m_String, SIZE - 1, other.m_String);
		return *this;
	}
	constexpr char operator[](size_t n) const noexcept { return m_String[n]; }
	constexpr static_string operator+(const static_string& other) const noexcept
	{
		if (other.is_empty())
			return *this;
		const size_t len = length();
		const size_t availability = len < SIZE - 1 ? SIZE - 1 - len : 0;
		if (!availability)
			return *this;
		static_string result;
		static_string_helper::copy_n(result.m_String, len, m_String);
		static_string_helper::copy_n(result.m_String + len, availability, other.m_String);
		return result;
	}
	static_string(static_string&&) noexcept = default;
	static_string& operator=(static_string&&) noexcept = default;
	constexpr const char* data() const noexcept { return m_String; }
	constexpr size_t length() const noexcept { return static_string_helper::const_string_length(m_String); }
	constexpr void clear() noexcept { static_string_helper::fill_n(m_String, SIZE, 0); }
	constexpr bool is_empty() const noexcept { return !static_cast<bool>(m_String[0]); }
	constexpr static_string substr(size_t pos, size_t len) const noexcept
	{
		if (is_empty())
			return *this;
		static_string result;
		const size_t srcLen = length();
		if (pos > srcLen || !len)
			return result;
		const size_t availability = srcLen - pos;
		len = len > availability + 1 ? availability + 1 : len;
		static_string_helper::copy_n(result.m_String, len, m_String + pos);
		return result;
	}
private:
	struct static_string_helper
	{
		static constexpr size_t const_string_length(const char* string) noexcept
		{
			size_t i{ 0 };
			while (string[i++]);
			return i - 1;
		}
		static constexpr void fill_n(char* string, size_t n, char value) noexcept
		{
			for (size_t i = 0; i < n; i++)
				string[i] = value;
		}
		static constexpr void copy_n(char* dest, size_t n, const char* src) noexcept
		{
			for (size_t i = 0; i < n; i++)
				dest[i] = src[i];
		}
	};
private:
	static constexpr size_t SIZE = 512; // can change the max size according to your use case
	char m_String[SIZE]{ 0 };
};
