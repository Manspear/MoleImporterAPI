#ifndef MOLE_H
#define MOLE_H

#include <vector>

using namespace std;



class Mole
{
public:
	int getMeshCount();

	int getLightCount();

	int getCameraCount();

	int getMaterialCount();

	int getMesh(int id);

	int getLight(int id);

	int getCamera(int id);

	int getMaterial(int id);

	//int check = file.getMaterialIndex(mesh);

	/**
	This function reads the .mole file and loads it's contents into
	internal vectors that may be accessed with get() functions.
	**/
	void readFile(const char* fileName);

	//Macro-steps:
	//1. Import fbx
	//2. Interpret fbx data to exporter_importerdata
	//3. exporter_importerdata save to binary file
	//   Här börjar detta program
	//4. read from binary file
	//5. put shit in vector<structs>
	//6. put vector<struct> shits in classes so that we can use cool getMaterial() functions

	//How to use library:
	//main mainVar;
	//mainVar.readFile("filename"); ---> Stores file info in struct-vectors. Then stores THAT info in classes that may have functions.
	//meshMaterial = materialList[mainVar.meshList[0].materialIndex];
	//meshList[0].getMaterial();
	//getMaterial(){
	//	return materialList[mesh.materialIndex];
	//}
	//mainVar.lightList;
	//mainVar.cameraList;
	//mainVar.materialList;
	//vector<sMesh> meshes;

	Mole();
	~Mole();

private:

	struct mainHeader
	{
		unsigned int meshCount;
		unsigned int materialCount;
		unsigned int lightCount;
		unsigned int cameraCount;
	};

	struct sMesh
	{
		unsigned int materialID; //So that several meshes may reuse the same material settings. 
		unsigned int vertexCount;
		unsigned int jointCount;
		float worldPos[16];
	};

	struct sMaterial
	{
		unsigned int materialIndex;
		float ambientColor[3];
		float diffuseColor[3];

		float specularColor[3];
		float cosinePower;

		char diffuseTexture[256];
		char specularTexture[256];
		char normalTexture[256];
	};

	struct sVertexData
	{
		float vertexPos[3];
		float vertexNormal[3];
		float tangentNormal[3];
		float biTangentNormal[3];
		float vertexUV[2];
		unsigned int boneInfluences[4];
		float boneWeights[4];
	};

	struct sJoint
	{
		unsigned int jointID;
		int parentJointID; //If this is -1, this joint is a root joint
		unsigned int bBoxID;
		
		float pos[3];
		float rot[3];
		float scale[3];

		float bindPoseInverse[16];
		float globalBindPoseInverse[16];
		
		unsigned int animationCount;
	};

	struct sAnimation
	{
		//The number of keyframes
		unsigned int keyCount;
	};

	struct sKey
	{
		float keyTime;

		float keyPos[3];
		float keyRot[3];
		float keyScale[3];
	};

	struct sLight
	{
		int lightID;

		float lightPos[3];
		float lightRot[3];
		float lightScale[3];

		float color[3];
		float intensity;
	};

	struct sCamera
	{
		unsigned int aimUpCameraCount;
	};


};

#endif
