#include "Mole.h"
//#include "BinaryReader.h"
#include "ReadHeaderData.h"

#include <fstream>
#include <vector>
#include <iostream>
//#include "ReadHeaderData.h"
//#include "BinaryReader.h"

Mole::Mole()
{
}

Mole::~Mole()
{
}

void Mole::readFile(const char * filePath)
{


	//Read from binary


	std::ifstream infile(filePath, std::ifstream::binary);//		Öppnar filen vi nyss skapade men ska nu läsa istället

	infile.read((char*)&read_mainHeader, sizeof(read_sMainHeader));

	read_meshList.resize(read_mainHeader.meshCount);
	read_mList.resize(read_mainHeader.meshCount);

	for (int i = 0; i < read_mainHeader.meshCount; i++)
	{
		cout << "Mesh: " << i << endl;
		//First off is the mesh.
		infile.read((char*)&read_meshList[i], sizeof(read_sMesh));

		//Resizing the vector(parallel with the meshvector) that contains a vector that contains vertices
		read_mList[i].vList.resize(read_meshList[i].vertexCount);

		//Fills the vList with vertices.
		infile.read((char*)read_mList[i].vList.data(), sizeof(read_sVertex) * read_meshList[i].vertexCount);
	}

	read_materialList.resize(read_mainHeader.materialCount);

	for (int i = 0; i < read_mainHeader.materialCount; i++)
	{
		cout << "Material: " << i << endl;

		cout << "Material vector: " << endl;

		cout << "\t";
		cout << &read_materialList[i] << endl;

		cout << "\t";
		cout << "Allocated memory for " << read_mainHeader.materialCount << " materials" << endl;

		infile.read((char*)read_materialList.data(), sizeof(read_sMaterial) * read_mainHeader.materialCount);//				Information av hur många material som senare kommer att komma, samt hur mycket minne den inten som berättar detta tar upp.

		cout << "______________________" << endl;
	}

	infile.close();
}
