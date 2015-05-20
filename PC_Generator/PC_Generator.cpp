#include <boost/iostreams/device/mapped_file.hpp> // for mmap
#include <algorithm>  // for std::find
#include <iostream>   // for std::cout
#include <cstring>

int main()
{
	boost::iostreams::mapped_file mmap("input.txt", boost::iostreams::mapped_file::readonly);
	auto f = mmap.const_data();
	auto l = f + mmap.size();

	uintmax_t m_numLines = 0;
	while (f && f != l)
		if ((f = static_cast<const char*>(memchr(f, '\n', l - f))))
			m_numLines++, f++;

	std::cout << "m_numLines = " << m_numLines << "\n";
}