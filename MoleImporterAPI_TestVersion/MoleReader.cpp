#include <fstream>
#include <vector>
#include <iostream>
//#include "ReadHeaderData.h"
#include "MoleReader.h"

using namespace std;

void MoleReader::readFromBinary(const char* filePath)
{
	/*Reading the binary file that we just have been written to.*/

	std::ifstream infile(filePath, std::ifstream::binary);

	cout << ">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<" << "\n" << "\n" << endl;
	cout << "Binary Reader" << endl;
	cout << "\n" << endl;

	/*Reading the first block of memory that is the main header. This will read
	information about how much of each node type we have from a imported scene and
	how memory they will take up in the binary file.*/

	infile.read((char*)&gRead_mainHeader, sizeof(read_sMainHeader));

	cout << "______________________" << endl;
	cout << "Main Header" << endl;
	cout << "meshCount: " << gRead_mainHeader.meshCount << endl;
	cout << "materialCount: " << gRead_mainHeader.materialCount << endl;
	cout << "lightCount: " << gRead_mainHeader.lightCount << endl;
	cout << "cameraCount: " << gRead_mainHeader.cameraCount << endl;

	cout << "______________________" << endl;

	if (gRead_mainHeader.meshCount >= 1)
	{
		gRead_meshList.resize(gRead_mainHeader.meshCount + prevMeshes);
		gRead_mList.resize(gRead_mainHeader.meshCount + prevMeshes);
		gRead_mkList.resize(gRead_mainHeader.meshCount + prevMeshes);

		for (int i = 0; i < gRead_mainHeader.meshCount; i++)
		{
			/*Reading the block of memory that is the meshes. The information from the meshes
			will be read here, that includes for example vertex count for a normal mesh
			and a skinned mesh. What we do is reserving memory for all the data that is in the
			struct. For example, Vertex count is a integer and will take up to 4 bytes in the
			memory when reading.*/

			infile.read((char*)&gRead_meshList[i + prevMeshes], sizeof(read_sMesh));

			int currMeshIndex = i + prevMeshes;

			cout << "Mesh: " << currMeshIndex << endl;

			cout << "Name: " << gRead_meshList[currMeshIndex].meshName << endl;

			cout << "\t";
			cout << "Material ID: ";
			cout << gRead_meshList[currMeshIndex].materialID << endl;

			cout << "Mesh vector: " << endl;

			cout << "\t";
			cout << "xyz: ";
			cout << gRead_meshList[currMeshIndex].translate[0] << " ";
			cout << gRead_meshList[currMeshIndex].translate[1] << " ";
			cout << gRead_meshList[currMeshIndex].translate[2] << " " << endl;

			cout << "\t";
			cout << "rot: ";
			cout << gRead_meshList[currMeshIndex].rotation[0] << " ";
			cout << gRead_meshList[currMeshIndex].rotation[1] << " ";
			cout << gRead_meshList[currMeshIndex].rotation[2] << " " << endl;

			cout << "\t";
			cout << "scale: ";
			cout << gRead_meshList[currMeshIndex].scale[0] << " ";
			cout << gRead_meshList[currMeshIndex].scale[1] << " ";
			cout << gRead_meshList[currMeshIndex].scale[2] << " " << endl;

			cout << "\t";
			cout << "Vertex Count: ";
			cout << gRead_meshList[currMeshIndex].vertexCount << endl;

			cout << "\t";
			cout << "SkelAnimVert Count: ";
			cout << gRead_meshList[i].skelAnimVertexCount << endl;

			cout << "\t";
			cout << "Joint Count: ";
			cout << gRead_meshList[i].jointCount << endl;
			
			if (gRead_meshList[i].isAnimated == true)
			{
				cout << "\n";
				cout << "Skeleton Vertex vector: " << endl;

				cout << "mkList: " << endl;
				gRead_mkList[i].vskList.resize(gRead_meshList[currMeshIndex].skelAnimVertexCount);
				cout << "\t";
				cout << gRead_mkList[i].vskList.data();

				cout << "\t";
				cout << "Allocated memory for: " << gRead_meshList[i].skelAnimVertexCount << " skel vertices" << endl << endl;

				/*Reading all the vertex lists for each mesh. For example if a mesh have 200 vertices,
				we can multiply the count of vertices with the sizes in bytes that the sVertex struct have.
				This means that we will be reading the pos, nor, uv, tan, bitan 200 times.*/
				infile.read((char*)gRead_mkList[i].vskList.data(), sizeof(read_sSkelAnimVertex) * gRead_meshList[i].skelAnimVertexCount);

				/*Reading the joint list for each mesh. Every joint in the list have individual data
				that we have to process when reading from the file.*/
				gRead_jointList.resize(gRead_meshList[i].jointCount);
				cout << "\n";
				cout << "Joint vector: " << endl;

				cout << "\t";
				cout << gRead_jointList.data() << endl;

				cout << "\t";
				cout << "Allocated memory for: " << gRead_meshList[i].jointCount << " joints" << endl;
				
				/*Reading the data for all the joints that a skinned mesh have.*/
				infile.read((char*)gRead_jointList.data(), sizeof(read_sJoint) * gRead_meshList[i].jointCount);
			}

			else
			{
				cout << "\n";
				cout << "Vertex vector: " << endl;

				cout << "mList: " << endl;
				gRead_mList[currMeshIndex].vList.resize(gRead_meshList[currMeshIndex].vertexCount);
				cout << "\t";
				cout << gRead_mList[currMeshIndex].vList.data() << endl;

				cout << "\t";
				cout << "Allocated memory for " << gRead_meshList[currMeshIndex].vertexCount << " vertices" << endl << endl;

				gRead_mList[currMeshIndex].vList.resize(gRead_meshList[currMeshIndex].vertexCount);

				/*Reading all the vertex lists for each mesh. For example if a mesh have 200 vertices,
				we can multiply the count of vertices with the sizes in bytes that the sVertex struct have.
				This means that we will be reading the pos, nor, uv, tan, bitan 200 times.*/
				infile.read((char*)gRead_mList[currMeshIndex].vList.data(), sizeof(read_sVertex) * gRead_meshList[currMeshIndex].vertexCount);
			}
		}
		prevMeshes += gRead_mainHeader.meshCount;
	}

	if (gRead_mainHeader.materialCount >= 1)
	{
		gRead_materialList.resize(gRead_mainHeader.materialCount + prevMaterials);

		for (int i = 0; i < gRead_mainHeader.materialCount; i++)
		{
			int currIndex = i + prevMaterials;

			/*Reading all the materials from the list with the size in bytes in mind.*/
			infile.read((char*)&gRead_materialList[currIndex], sizeof(read_sMaterial)); 

			cout << "Material: " << i << " Name: " << gRead_materialList[currIndex].materialName << endl;

			cout << "Material vector: " << endl;
			cout << "\t";
			cout << &gRead_materialList[currIndex] << endl;

			cout << "\t";
			cout << "Allocated memory for " << gRead_mainHeader.materialCount << " materials" << endl;

			cout << "\t";
			cout << "Ambient color: ";
			cout << gRead_materialList[currIndex].ambientColor[0] << " "
				<< gRead_materialList[currIndex].ambientColor[1] << " "
				<< gRead_materialList[currIndex].ambientColor[2] << " " << endl;

			cout << "\t";
			cout << "Diffuse color: ";
			cout << gRead_materialList[currIndex].diffuseColor[0] << " "
				<< gRead_materialList[currIndex].diffuseColor[1] << " "
				<< gRead_materialList[currIndex].diffuseColor[2] << " " << endl;

			cout << "\t";
			cout << "Specular color: ";
			cout << gRead_materialList[currIndex].specularColor[0] << " "
				<< gRead_materialList[currIndex].specularColor[1] << " "
				<< gRead_materialList[currIndex].specularColor[2] << " " << endl;

			cout << "\t";
			cout << "Shiny factor: ";
			cout << gRead_materialList[currIndex].shinyFactor << endl;

			cout << "\t";
			cout << "Diffuse texture: " << gRead_materialList[currIndex].diffuseTexture << endl;

			cout << "\t";
			cout << "Specular texture: " << gRead_materialList[currIndex].specularTexture << endl;

			cout << "\t";
			cout << "Normal texture: " << gRead_materialList[currIndex].normalTexture << endl;


			cout << "______________________" << endl;
		}

		prevMaterials += gRead_mainHeader.materialCount;

	}

	if (gRead_mainHeader.lightCount >= 1)
	{
		gRead_lightList.resize(gRead_mainHeader.lightCount + prevLights);

		for (int i = 0; i < gRead_mainHeader.lightCount; i++)
		{
			int currIndex = i + prevLights;

			/*Reading all the lights from the list with the size in bytes in mind.*/
			infile.read((char*)&gRead_lightList[currIndex], sizeof(read_sLight));

			cout << "Light: " << i << endl;

			cout << "Light vector: " << endl;

			cout << "\t";
			cout << &gRead_lightList[currIndex] << endl;

			cout << "\t";
			cout << "Allocated memory for " << gRead_mainHeader.lightCount << " lights" << endl;

			cout << "\t";
			cout << "Light ID: " << gRead_lightList[currIndex].lightID << endl;

			cout << "\t";
			cout << "Light position: " << gRead_lightList[currIndex].lightPos[0] << " "
				<< gRead_lightList[currIndex].lightPos[1] << " "
				<< gRead_lightList[currIndex].lightPos[2] << endl;

			cout << "\t";
			cout << "Light rotation: " << gRead_lightList[currIndex].lightRot[0] << " "
				<< gRead_lightList[currIndex].lightRot[1] << " "
				<< gRead_lightList[currIndex].lightRot[2] << endl;

			cout << "\t";
			cout << "Light scale: " << gRead_lightList[currIndex].lightScale[0] << " "
				<< gRead_lightList[currIndex].lightScale[1] << " "
				<< gRead_lightList[currIndex].lightScale[2] << endl;

			cout << "\t";
			cout << "Light color: " << gRead_lightList[currIndex].color[0] << " "
				<< gRead_lightList[currIndex].color[1] << " "
				<< gRead_lightList[currIndex].color[2] << " " << endl;

			cout << "\t";
			cout << "Light intensity: " << gRead_lightList[currIndex].intensity << endl;

			cout << "______________________" << endl;
		}
		prevLights = gRead_mainHeader.lightCount;
	}

	if (gRead_mainHeader.cameraCount >= 1)
	{
		gRead_cameraList.resize(gRead_mainHeader.cameraCount + prevCameras);

		for (int i = 0; i < gRead_mainHeader.cameraCount; i++)
		{
			int currIndex = i + prevCameras;

			/*Reading all the cameras from the list with the size in bytes in mind.*/
			infile.read((char*)&gRead_cameraList[currIndex], sizeof(read_sCamera));

			cout << "Camera: " << i << endl;

			cout << "Camera vector: " << endl;

			cout << "\t";
			cout << &gRead_cameraList[currIndex] << endl;

			cout << "\t";
			cout << "Allocated memory for " << gRead_mainHeader.cameraCount << " cameras" << endl;

			cout << "\t";
			cout << "Camera position: " << gRead_cameraList[currIndex].camPos[0] << " "
				<< gRead_cameraList[currIndex].camPos[1] << " "
				<< gRead_cameraList[currIndex].camPos[2] << endl;

			cout << "\t";
			cout << "Camera Up vector: " << gRead_cameraList[currIndex].upVector[0] << " "
				<< gRead_cameraList[currIndex].upVector[1] << " "
				<< gRead_cameraList[currIndex].upVector[2] << endl;

			cout << "\t";
			cout << "FOV: " << gRead_cameraList[currIndex].fieldOfView << endl;

			cout << "\t";
			cout << "Near plane: " << gRead_cameraList[currIndex].nearPlane << endl;

			cout << "\t";
			cout << "Far plane: " << gRead_cameraList[currIndex].farPlane << endl;

			cout << "______________________" << endl;
		}
		prevCameras += gRead_mainHeader.cameraCount;
	}
	//contains the meshes
	gRead_meshList;
	//Contains the vertices for each mesh
	gRead_mList;
	//contains the cameras
	gRead_cameraList;
	//contains the lights
	gRead_lightList;
	//contains the materials
	gRead_materialList;

	infile.close();
}

const std::vector<MoleReader::read_sMesh>* MoleReader::getMeshList()
{
	return &gRead_meshList;
}

const std::vector<MoleReader::read_m>* MoleReader::getVertexList()
{
	return &gRead_mList;
}

const std::vector<MoleReader::read_sMaterial>* MoleReader::getMaterialList()
{
	return &gRead_materialList;
}

const std::vector<MoleReader::read_sCamera>* MoleReader::getCameraList()
{
	return &gRead_cameraList;
}

const std::vector<MoleReader::read_sLight>* MoleReader::getLightList()
{
	return &gRead_lightList;
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