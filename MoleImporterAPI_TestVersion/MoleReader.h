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
	/**
	Gets a vector containing the entire list of meshes.
	**/
	const std::vector<read_sMesh>* getMeshList();
	/**
	Gets a vector containing vectors of mesh-child-indices of meshes.
	**/
	const std::vector<read_sMChildHolder>* getMeshChildList();
	/**
	Gets a vector containing the entire list of materials.
	**/
	const std::vector< read_sMaterial>* getMaterialList();
	/**
	Gets a vector containing the entire list of cameras.
	**/
	const std::vector<read_sCamera>* getCameraList();
	/**
	Gets a vector containing the entire list of lights.
	**/
	const std::vector<read_sLight>* getLightList();
	/**
	Gets a vector containing vectors of joints and "joint related stuff".
	Inside the "joint related stuff" are vectors containing meshChildren
	and animationStates. Animationstates are what separates animations from
	one another for each joint.
	**/
	const std::vector<read_sMJHolder>* getJointKeyList();

	const read_sMainHeader* getMainHeader();

	/**
	Get the index of the mesh with the queried name. 
	If no matching mesh is found, -1337 is returned.
	Use this function sparingly, it's algorithm loops
	through ALL of the meshi and compare their names.
	**/
	const int getMeshIndex(string meshName);
	/**
	Gets the mesh at the given meshIndex.
	Usage of this mesh is neccessary for getting
	a bunch of mesh-related data.
	Examples are:
	JointCount
	skelVertexCount
	vertexCount
	isAnimated
	**/
	const read_sMesh* getMesh(int meshIndex);
	/**
	Gets the vector containing keyframes for an animationstate in a joint in a mesh. 
	Animationstates are "groups" that encapsulate keyFrames. Each animationstate represents
	a different animation. Examples of different animationstates are "walking cycle", 
	"attack animation", "idle animation" etc. 
	**/
	const std::vector<read_sKeyFrame>* getKeyList(int meshIndex, int jointIndex, int animationState);
	/**
	Gets the vector containing indexes to meshChildren belonging to a mesh. 
	**/
	const std::vector<read_sMeshChild>* getMeshChildList(int meshIndex);

	const read_sMaterial* getMaterial(int materialIndex);
	/**
	Only useful if mesh has isAnimated == true
	**/
	const read_sJoint* getJoint(int meshIndex, int jointIndex);
	/**
	Gets the vector containing indexes to meshChildren belonging to 
	a joint.
	**/
	const std::vector<read_sMeshChild> getJointMeshChildList(int meshIndex, int jointIndex);
	/**
	Gets the vector containing skeletal vertices belonging to a mesh.
	What separates a skeletal vertex from a regular vertex is that a 
	skeletal vertex has influences and weights.
	An influence is an index to the joint affecting the skeletal vertex.
	A weight is how high of a "percentage" of the joint's transform affects 
	the skeletal vertex, expressed in numbers between 0 and 1.
	Our skeletal vertices will have a maximum of 4 influences and 4 weights.
	The sum of the weights must always be 1, making it "100%".
	**/
	const std::vector<read_sSkelAnimVertex>* getSkelVertexList(int meshIndex);
	/**
	Gets the vector containing vertices belonging to a mesh.
	**/
	const std::vector<read_sVertex>* getVertexList(int meshIndex);

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