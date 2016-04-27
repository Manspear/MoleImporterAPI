#include "MoleReader.h"
#include <iostream>

using namespace std;
int main()
{
	MoleReader wololo;
	wololo.readFromBinary("testBox.mole");

	const std::vector<MoleReader::read_sMesh>* myMeshList = wololo.getMeshList();
	
	myMeshList[0][0].isAnimated;
	
	if (myMeshList[0][0].isAnimated == false) {
		cout << "I am Kyle" << endl;
	}
	//I am returning a reference to the private variable... Good or bad idéa?
	//Neither good nor bad?
	//Having a reference speeds up file-loading quite a bit since we don't have to do any copying.

	return 0;
}