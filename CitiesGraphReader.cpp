#include "CitiesGraphReader.hpp"

ListGraph CitiesGraphReader::readFromFile(const std::string &filename)
{
    auto fileStream = openFile(filename);

    size_t numberOfCities;
    fileStream >> numberOfCities;

	return readCostsMatrix(fileStream, numberOfCities);
}

std::ifstream openFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (file.is_open())
        return file;

    throw new std::exception();
}

ListGraph readCostsMatrix(std::ifstream &fileStream, const size_t &numberOfCities)
{
	ListGraph graph;

	for (size_t col = 0; col < numberOfCities; col++) {
		for (size_t row = 0; row < numberOfCities; row++) {
			int weight;

			fileStream >> weight;

#ifdef DEBUG
			if (col == row) {
				assert(weight == -1);
			}
#endif
			if (weight == -1) {
				continue;
			}

			graph.addEdge(col, row, weight);
		}
	}
}
