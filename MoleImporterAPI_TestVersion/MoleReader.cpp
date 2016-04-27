#include <fstream>
#include <vector>
#include <iostream>
//#include "ReadHeaderData.h"
#include "MoleReader.h"

using namespace std;

void MoleReader::readFromBinary(const char* filePath)
{
	//Read from binary
	std::ifstream infile(filePath, std::ifstream::binary);//		Öppnar filen vi nyss skapade men ska nu läsa istället

	cout << ">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<" << "\n" << "\n" << endl;
	cout << "Binary Reader" << endl;
	cout << "\n" << endl;

	infile.read((char*)&pmRead_mainHeader, sizeof(read_sMainHeader));//				Information av hur många meshes som senare kommer att komma, och efter det hur många material osv, samt hur mycket minne den inten som berättar detta tar upp (reservation för vår header)
	cout << "______________________" << endl;
	cout << "Main Header" << endl;
	cout << "meshCount: " << pmRead_mainHeader.meshCount << endl;
	cout << "materialCount: " << pmRead_mainHeader.materialCount << endl;
	cout << "lightCount: " << pmRead_mainHeader.lightCount << endl;
	cout << "cameraCount: " << pmRead_mainHeader.cameraCount << endl;

	cout << "______________________" << endl;

	if (pmRead_mainHeader.meshCount >= 1)
	{
		pmRead_meshList.resize(pmRead_mainHeader.meshCount + prevMeshes);
		pmRead_mList.resize(pmRead_mainHeader.meshCount + prevMeshes);

		for (int i = 0; i < pmRead_mainHeader.meshCount; i++)
		{
			infile.read((char*)&pmRead_meshList[i + prevMeshes], sizeof(read_sMesh));

			int currMeshIndex = i + prevMeshes;

			cout << "Mesh: " << currMeshIndex << endl;

			cout << "Name: " << pmRead_meshList[currMeshIndex].meshName << endl;

			//Information av hur många vertices som senare kommer att komma, och efter det hur många skelAnim verticear som kommer komma osv, samt hur mycket minne den inten som berättar detta tar upp(reservation för vår header).En int kommer först, den har värdet 100.  Och den inten kommer ta upp 4 bytes.

			cout << "Mesh vector: " << endl;

			cout << "\t";
			cout << "xyz: ";
			cout << pmRead_meshList[currMeshIndex].translate[0] << " ";
			cout << pmRead_meshList[currMeshIndex].translate[1] << " ";
			cout << pmRead_meshList[currMeshIndex].translate[2] << " " << endl;

			cout << "\t";
			cout << "rot: ";
			cout << pmRead_meshList[currMeshIndex].rotation[0] << " ";
			cout << pmRead_meshList[currMeshIndex].rotation[1] << " ";
			cout << pmRead_meshList[currMeshIndex].rotation[2] << " " << endl;

			cout << "\t";
			cout << "scale: ";
			cout << pmRead_meshList[currMeshIndex].scale[0] << " ";
			cout << pmRead_meshList[currMeshIndex].scale[1] << " ";
			cout << pmRead_meshList[currMeshIndex].scale[2] << " " << endl;

			cout << "\t";
			cout << "Vertex Count: ";
			cout << pmRead_meshList[currMeshIndex].vertexCount << endl;
			//cout << "SkelAnimVert Count: 0" << endl;
			//cout << "Joint Count: 0"  << endl;

			cout << "\t";
			cout << "Material ID: ";
			cout << pmRead_meshList[currMeshIndex].materialID << endl;
			//												detta är storleken av innehållet i vList.data()

			cout << "\n";
			cout << "Vertex vector: " << endl;

			cout << "mlist: " << endl;

			cout << "\t";
			cout << pmRead_mList[currMeshIndex].vList.data() << endl;

			cout << "\t";
			cout << "Allocated memory for " << pmRead_meshList[currMeshIndex].vertexCount << " vertices" << endl;
			
			pmRead_mList[currMeshIndex].vList.resize(pmRead_meshList[currMeshIndex].vertexCount);
			infile.read((char*)pmRead_mList[currMeshIndex].vList.data(), sizeof(read_sVertex) * pmRead_meshList[currMeshIndex].vertexCount);//				Skriver ut alla vertices i får vArray, pos, nor, rgba 100 gånger. Och minnet 100 Vertices tar upp.

																												//cout << "SkelAnimVert vector: NULL" << endl;																									//cout << "Joint vector: NULL" << endl;
		}
		prevMeshes += pmRead_mainHeader.meshCount;
	}

	if (pmRead_mainHeader.materialCount >= 1)
	{
		pmRead_materialList.resize(pmRead_mainHeader.materialCount + prevMaterials);

		for (int i = 0; i < pmRead_mainHeader.materialCount; i++)
		{
			int currIndex = i + prevMaterials;

			infile.read((char*)&pmRead_materialList[currIndex], sizeof(read_sMaterial)); //Information av hur många material som senare kommer att komma, samt hur mycket minne den inten som berättar detta tar upp.

			cout << "Material: " << i << " Name: " << pmRead_materialList[currIndex].materialName << endl;

			cout << "Material vector: " << endl;

			cout << "\t";
			cout << &pmRead_materialList[currIndex] << endl;

			cout << "\t";
			cout << "Allocated memory for " << pmRead_mainHeader.materialCount << " materials" << endl;

			cout << "\t";
			cout << "Ambient color: ";
			cout << pmRead_materialList[currIndex].ambientColor[0] << " "
				<< pmRead_materialList[currIndex].ambientColor[1] << " "
				<< pmRead_materialList[currIndex].ambientColor[2] << " " << endl;

			cout << "\t";
			cout << "Diffuse color: ";
			cout << pmRead_materialList[currIndex].diffuseColor[0] << " "
				<< pmRead_materialList[currIndex].diffuseColor[1] << " "
				<< pmRead_materialList[currIndex].diffuseColor[2] << " " << endl;

			cout << "\t";
			cout << "Specular color: ";
			cout << pmRead_materialList[currIndex].specularColor[0] << " "
				<< pmRead_materialList[currIndex].specularColor[1] << " "
				<< pmRead_materialList[currIndex].specularColor[2] << " " << endl;

			cout << "\t";
			cout << "Shiny factor: ";
			cout << pmRead_materialList[currIndex].shinyFactor << endl;

			cout << "\t";
			cout << "Diffuse texture: " << pmRead_materialList[currIndex].diffuseTexture << endl;

			cout << "\t";
			cout << "Specular texture: " << pmRead_materialList[currIndex].specularTexture << endl;

			cout << "\t";
			cout << "Normal texture: " << pmRead_materialList[currIndex].normalTexture << endl;


			cout << "______________________" << endl;
		}

		prevMaterials += pmRead_mainHeader.materialCount;

	}

	if (pmRead_mainHeader.lightCount >= 1)
	{
		pmRead_lightList.resize(pmRead_mainHeader.lightCount + prevLights);

		for (int i = 0; i < pmRead_mainHeader.lightCount; i++)
		{
			int currIndex = i + prevLights;
			infile.read((char*)&pmRead_lightList[currIndex], sizeof(read_sLight));

			cout << "Light: " << i << endl;

			cout << "Light vector: " << endl;

			cout << "\t";
			cout << &pmRead_lightList[currIndex] << endl;

			cout << "\t";
			cout << "Allocated memory for " << pmRead_mainHeader.lightCount << " lights" << endl;

			cout << "\t";
			cout << "Light ID: " << pmRead_lightList[currIndex].lightID << endl;

			cout << "\t";
			cout << "Light position: " << pmRead_lightList[currIndex].lightPos[0] << " "
				<< pmRead_lightList[currIndex].lightPos[1] << " "
				<< pmRead_lightList[currIndex].lightPos[2] << endl;

			cout << "\t";
			cout << "Light rotation: " << pmRead_lightList[currIndex].lightRot[0] << " "
				<< pmRead_lightList[currIndex].lightRot[1] << " "
				<< pmRead_lightList[currIndex].lightRot[2] << endl;

			cout << "\t";
			cout << "Light scale: " << pmRead_lightList[currIndex].lightScale[0] << " "
				<< pmRead_lightList[currIndex].lightScale[1] << " "
				<< pmRead_lightList[currIndex].lightScale[2] << endl;

			cout << "\t";
			cout << "Light color: " << pmRead_lightList[currIndex].color[0] << " "
				<< pmRead_lightList[currIndex].color[1] << " "
				<< pmRead_lightList[currIndex].color[2] << " " << endl;

			cout << "\t";
			cout << "Light intensity: " << pmRead_lightList[currIndex].intensity << endl;

			cout << "______________________" << endl;
		}
		prevLights = pmRead_mainHeader.lightCount;
	}

	if (pmRead_mainHeader.cameraCount >= 1)
	{
		pmRead_cameraList.resize(pmRead_mainHeader.cameraCount + prevCameras);

		for (int i = 0; i < pmRead_mainHeader.cameraCount; i++)
		{
			int currIndex = i + prevCameras;
			infile.read((char*)&pmRead_cameraList[currIndex], sizeof(read_sCamera));
			cout << "Camera: " << i << endl;

			cout << "Camera vector: " << endl;

			cout << "\t";
			cout << &pmRead_cameraList[currIndex] << endl;

			cout << "\t";
			cout << "Allocated memory for " << pmRead_mainHeader.cameraCount << " cameras" << endl;

			cout << "\t";
			cout << "Camera position: " << pmRead_cameraList[currIndex].camPos[0] << " "
				<< pmRead_cameraList[currIndex].camPos[1] << " "
				<< pmRead_cameraList[currIndex].camPos[2] << endl;

			cout << "\t";
			cout << "Camera Up vector: " << pmRead_cameraList[currIndex].upVector[0] << " "
				<< pmRead_cameraList[currIndex].upVector[1] << " "
				<< pmRead_cameraList[currIndex].upVector[2] << endl;

			cout << "\t";
			cout << "FOV: " << pmRead_cameraList[currIndex].fieldOfView << endl;

			cout << "\t";
			cout << "Near plane: " << pmRead_cameraList[currIndex].nearPlane << endl;

			cout << "\t";
			cout << "Far plane: " << pmRead_cameraList[currIndex].farPlane << endl;

			cout << "______________________" << endl;
		}
		prevCameras += pmRead_mainHeader.cameraCount;
	}
	//contains the meshes
	pmRead_meshList;
	//Contains the vertices for each mesh
	pmRead_mList;
	//contains the cameras
	pmRead_cameraList;
	//contains the lights
	pmRead_lightList;
	//contains the materials
	pmRead_materialList;

	infile.close();
}

const std::vector<MoleReader::read_sMesh>* MoleReader::getMeshList()
{
	return &pmRead_meshList;
}

const std::vector<MoleReader::read_m>* MoleReader::getVertexList()
{
	return &pmRead_mList;
}

const std::vector<MoleReader::read_sMaterial>* MoleReader::getMaterialList()
{
	return &pmRead_materialList;
}

const std::vector<MoleReader::read_sCamera>* MoleReader::getCameraList()
{
	return &pmRead_cameraList;
}

const std::vector<MoleReader::read_sLight>* MoleReader::getLightList()
{
	return &pmRead_lightList;
}

MoleReader::MoleReader()
{
	prevMeshes = 0;
	prevCameras = 0;
	prevLights = 0;
	prevMaterials = 0;
}

MoleReader::~MoleReader()
{
}

//cout << "______________________" << endl;
//GLuint vertexBuff;


//glGenVertexArrays(1, &vao);
//glBindVertexArray(vao);

//// It wörks
//glEnableVertexAttribArray(0);
//glEnableVertexAttribArray(1);
//glEnableVertexAttribArray(2);
//glEnableVertexAttribArray(3);
//glEnableVertexAttribArray(4);

//glGenBuffers(1, &vertexBuff);
//glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
//glBufferData(GL_ARRAY_BUFFER, sizeof(read_sVertex) * read_mList[i].vList.size(), read_mList[i].vList.data(), GL_STATIC_DRAW);
//cout << "______________________" << endl;