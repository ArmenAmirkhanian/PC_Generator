/*
The MIT License (MIT)

Copyright (c) 2015 Armen N. Amirkhanian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <boost/spirit/include/qi.hpp>
#include <fstream>
#include <vector>
#include <string>

template <typename Iter>
bool parse_into_vec(Iter p_it, Iter p_end, std::vector<int>& vf) {
	using boost::spirit::qi::phrase_parse;
	using boost::spirit::qi::int_;
	using boost::spirit::qi::ascii::space;

	bool ret = phrase_parse(p_it, p_end, *int_, space, vf);
	return p_it != p_end ? false : ret;
}

int main(int argc, char **args) {
	std::string inputF;
	
	// Give the user the option to use the command line
	if (argc < 2) {
		std::cout << "Enter file name: ";
		std::getline(std::cin, inputF);
	}
	else{
		inputF = args[1];
	}
	std::ifstream in(inputF);

	size_t numPoints;
	in >> numPoints;

	std::istreambuf_iterator<char> eos;
	std::istreambuf_iterator<char> it(in);
	std::string strver(it, eos);

	std::vector<int> vf;
	vf.reserve(numPoints);

	if (!parse_into_vec(strver.begin(), strver.end(), vf)) {
		std::cerr << "failed during parsing" << std::endl;
		return -1;
	}
	
	// Debugging print out option
	// Yes, commenting out code is not good practice
	// but this is for research, not commercial use
	/*
	std::vector<int>::iterator countr;
	countr = vf.begin();
	for (countr; countr != vf.end(); countr++)
	{
		std::cout << *countr << "\n";
	}
	system("pause");
	*/

	std::ofstream fileOut("PointCloud.xyz", std::ofstream::out);
	std::vector<int>::iterator OutIter;
	OutIter = vf.begin();
	for (int i = 0; i < 200; i++){
		for (int j = 0; j < 200; j++){
			for (int k = 0; k < 4000; k++){
				fileOut << i << "," << j << "," << k << "," << *OutIter << "\n";
				OutIter++;
			}
		}
	}
	//copy(vf.begin(), vf.end(), std::ostream_iterator<int>(fileOut,"\n"));
	fileOut.close();
	return 0;
}
