#include <fstream>
#include <vector>
#include <iostream>
#include "ReadHeaderData.h"
#include "BinaryReader.h"

using namespace std;

void BinaryReader::readFromBinary(const char* filePath)
{

	//Read from binary
	std::ifstream infile("testBin.bin", std::ifstream::binary);//		Öppnar filen vi nyss skapade men ska nu läsa istället

	cout << ">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<" << "\n" << "\n" << endl;
	cout << "Binary Reader" << endl;
	cout << "\n" << endl;

	infile.read((char*)&gRead_mainHeader, sizeof(read_sMainHeader));//				Information av hur många meshes som senare kommer att komma, och efter det hur många material osv, samt hur mycket minne den inten som berättar detta tar upp (reservation för vår header)
	cout << "______________________" << endl;
	cout << "Main Header" << endl;
	cout << "meshCount: " << gRead_mainHeader.meshCount << endl;
	cout << "materialCount: " << gRead_mainHeader.materialCount << endl;
	cout << "lightCount: " << gRead_mainHeader.lightCount << endl;
	cout << "cameraCount: " << gRead_mainHeader.cameraCount << endl;

	cout << "______________________" << endl;

	if (gRead_mainHeader.meshCount >= 1)
	{
		gRead_meshList.resize(gRead_mainHeader.meshCount);
		gRead_mList.resize(gRead_mainHeader.meshCount);

		for (int i = 0; i < gRead_mainHeader.meshCount; i++)
		{
			infile.read((char*)&gRead_meshList[i], sizeof(read_sMesh));

			cout << "Mesh: " << i << endl;

			cout << "Name: " << gRead_meshList[i].meshName << endl;

			//Information av hur många vertices som senare kommer att komma, och efter det hur många skelAnim verticear som kommer komma osv, samt hur mycket minne den inten som berättar detta tar upp(reservation för vår header).En int kommer först, den har värdet 100.  Och den inten kommer ta upp 4 bytes.

			cout << "Mesh vector: " << endl;

			cout << "\t";
			cout << "xyz: ";
			cout << gRead_meshList[i].translate[0];
			cout << gRead_meshList[i].translate[1];
			cout << gRead_meshList[i].translate[2] << endl;

			cout << "\t";
			cout << "rot: ";
			cout << gRead_meshList[i].rotation[0];
			cout << gRead_meshList[i].rotation[1];
			cout << gRead_meshList[i].rotation[2] << endl;

			cout << "\t";
			cout << "scale: ";
			cout << gRead_meshList[i].scale[0];
			cout << gRead_meshList[i].scale[1];
			cout << gRead_meshList[i].scale[2] << endl;

			cout << "\t";
			cout << "Vertex Count: ";
			cout << gRead_meshList[i].vertexCount << endl;
			//cout << "SkelAnimVert Count: 0" << endl;
			//cout << "Joint Count: 0"  << endl;

			cout << "\t";
			cout << "Material ID: ";
			cout << gRead_meshList[i].materialID << endl;
			//												detta är storleken av innehållet i vList.data()

			cout << "\n";
			cout << "Vertex vector: " << endl;

			cout << "mlist: " << endl;
			gRead_mList[i].vList.resize(gRead_meshList[i].vertexCount);
			cout << "\t";
			cout << gRead_mList[i].vList.data() << endl;

			cout << "\t";
			cout << "Allocated memory for " << gRead_meshList[i].vertexCount << " vertices" << endl;

			gRead_mList[i].vList.resize(gRead_meshList[i].vertexCount);

			infile.read((char*)gRead_mList[i].vList.data(), sizeof(read_sVertex) * gRead_meshList[i].vertexCount);//				Skriver ut alla vertices i får vArray, pos, nor, rgba 100 gånger. Och minnet 100 Vertices tar upp.

																												//cout << "SkelAnimVert vector: NULL" << endl;																									//cout << "Joint vector: NULL" << endl;
		}
	}

	if (gRead_mainHeader.materialCount >= 1)
	{
		gRead_materialList.resize(gRead_mainHeader.materialCount);

		for (int i = 0; i < gRead_mainHeader.materialCount; i++)
		{
			infile.read((char*)&gRead_materialList[i], sizeof(read_sMaterial)); //Information av hur många material som senare kommer att komma, samt hur mycket minne den inten som berättar detta tar upp.

			cout << "Material: " << i << " Name: " << gRead_materialList[i].materialName << endl;

			cout << "Material vector: " << endl;

			cout << "\t";
			cout << &gRead_materialList[i] << endl;

			cout << "\t";
			cout << "Allocated memory for " << gRead_mainHeader.materialCount << " materials" << endl;

			cout << "\t";
			cout << "Ambient color: ";
			cout << gRead_materialList[i].ambientColor[0] << " "
				<< gRead_materialList[i].ambientColor[1] << " "
				<< gRead_materialList[i].ambientColor[2] << " " << endl;

			cout << "\t";
			cout << "Diffuse color: ";
			cout << gRead_materialList[i].diffuseColor[0] << " "
				<< gRead_materialList[i].diffuseColor[1] << " "
				<< gRead_materialList[i].diffuseColor[2] << " " << endl;

			cout << "\t";
			cout << "Specular color: ";
			cout << gRead_materialList[i].specularColor[0] << " "
				<< gRead_materialList[i].specularColor[1] << " "
				<< gRead_materialList[i].specularColor[2] << " " << endl;

			cout << "\t";
			cout << "Shiny factor: ";
			cout << gRead_materialList[i].shinyFactor << endl;

			cout << "\t";
			cout << "Diffuse texture: " << gRead_materialList[i].diffuseTexture << endl;

			cout << "\t";
			cout << "Specular texture: " << gRead_materialList[i].specularTexture << endl;

			cout << "\t";
			cout << "Normal texture: " << gRead_materialList[i].normalTexture << endl;


			cout << "______________________" << endl;
		}

	}

	if (gRead_mainHeader.lightCount >= 1)
	{
		gRead_lightList.resize(gRead_mainHeader.lightCount);

		for (int i = 0; i < gRead_mainHeader.lightCount; i++)
		{
			infile.read((char*)&gRead_lightList[i], sizeof(read_sLight));

			cout << "Light: " << i << endl;

			cout << "Light vector: " << endl;

			cout << "\t";
			cout << &gRead_lightList[i] << endl;

			cout << "\t";
			cout << "Allocated memory for " << gRead_mainHeader.lightCount << " lights" << endl;

			cout << "\t";
			cout << "Light ID: " << gRead_lightList[i].lightID << endl;

			cout << "\t";
			cout << "Light position: " << gRead_lightList[i].lightPos[0] << " "
				<< gRead_lightList[i].lightPos[1] << " "
				<< gRead_lightList[i].lightPos[2] << endl;

			cout << "\t";
			cout << "Light rotation: " << gRead_lightList[i].lightRot[0] << " "
				<< gRead_lightList[i].lightRot[1] << " "
				<< gRead_lightList[i].lightRot[2] << endl;

			cout << "\t";
			cout << "Light scale: " << gRead_lightList[i].lightScale[0] << " "
				<< gRead_lightList[i].lightScale[1] << " "
				<< gRead_lightList[i].lightScale[2] << endl;

			cout << "\t";
			cout << "Light color: " << gRead_lightList[i].color[0] << " "
				<< gRead_lightList[i].color[1] << " "
				<< gRead_lightList[i].color[2] << " " << endl;

			cout << "\t";
			cout << "Light intensity: " << gRead_lightList[i].intensity << endl;

			cout << "______________________" << endl;
		}
	}

	if (gRead_mainHeader.cameraCount >= 1)
	{
		gRead_cameraList.resize(gRead_mainHeader.cameraCount);

		for (int i = 0; i < gRead_mainHeader.cameraCount; i++)
		{
			infile.read((char*)&gRead_cameraList[i], sizeof(read_sCamera));
			cout << "Camera: " << i << endl;

			cout << "Camera vector: " << endl;

			cout << "\t";
			cout << &gRead_cameraList[i] << endl;

			cout << "\t";
			cout << "Allocated memory for " << gRead_mainHeader.cameraCount << " cameras" << endl;

			cout << "\t";
			cout << "Camera position: " << gRead_cameraList[i].camPos[0] << " "
				<< gRead_cameraList[i].camPos[1] << " "
				<< gRead_cameraList[i].camPos[2] << endl;

			cout << "\t";
			cout << "Camera Up vector: " << gRead_cameraList[i].upVector[0] << " "
				<< gRead_cameraList[i].upVector[1] << " "
				<< gRead_cameraList[i].upVector[2] << endl;

			cout << "\t";
			cout << "FOV: " << gRead_cameraList[i].fieldOfView << endl;

			cout << "\t";
			cout << "Near plane: " << gRead_cameraList[i].nearPlane << endl;

			cout << "\t";
			cout << "Far plane: " << gRead_cameraList[i].farPlane << endl;

			cout << "______________________" << endl;
		}
	}

	infile.close();
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