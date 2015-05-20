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