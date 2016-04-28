#pragma once
#include <vector>
#include "MoleImporterHeaders.h"

/**
Things left to be implemented:
1. Parenting between meshes, and joints and meshes.
	Neccessary for having meshes with multiple pieces, like separate 
	pieces of body armor, or weapons being stuck on joints.
2. Joints, and animations.
**/

class MoleReader {
public :
	void readFromBinary(const char* filePath);
	const std::vector<read_sMesh>* getMeshList();
	const std::vector<read_m>* getVertexList();
	const std::vector< read_sMaterial>* getMaterialList();
	const std::vector<read_sCamera>* getCameraList();
	const std::vector<read_sLight>* getLightList();

	MoleReader();
	~MoleReader();

private:

	int prevMeshes;
	int prevCameras;
	int prevLights;
	int prevMaterials;
	int prevJoints;


	//Vectors holding all of the data.
	std::vector<read_sMesh> pmRead_meshList;
	//Holds the meshChildren of meshes.
	std::vector<read_sMChildHolder> pmRead_meshChildList;
	std::vector<read_sMJHolder> pmRead_meshJointHolder;
	std::vector<read_sCamera> pmRead_cameraList;
	std::vector<read_sLight> pmRead_lightList;
	std::vector< read_sMaterial> pmRead_materialList;
	std::vector<read_m> pmRead_mList;
	std::vector<read_mk> pmRead_mkList;
	//std::vector<read_sJoint> pmRead_jointList;
	//std::vector<read_sKeyFrame> pmRead_KeyList;
	//std::vector<read_sAnimationStateTracker> pmRead_animSTrackerList;
	//std::vector<read_sAnimationState> pmRead_animStateList;
	
	//Struct objects
	read_sMainHeader pmRead_mainHeader;
	//read_sVertex gRead_vertex;
	//read_sMaterial gRead_materialData;
	//read_sLight gRead_lightData;
	//read_sCamera gRead_camData;
};