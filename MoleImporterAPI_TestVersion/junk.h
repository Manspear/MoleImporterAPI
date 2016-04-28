//#pragma once
//#include <vector>
//
//struct read_sMainHeader
//{
//	unsigned int meshCount;
//	unsigned int materialCount;
//	unsigned int lightCount;
//	unsigned int cameraCount;
//};
//
//struct  read_sVertex
//{
//	float vertexPos[3];
//	float vertexNormal[3];
//	float vertexUV[2];
//	float tangentNormal[3];
//	float biTangentNormal[3];
//};
//
//struct  read_sMesh
//{
//	char meshName[256];
//
//	unsigned int materialID;
//
//	float translate[3];
//	float rotation[3];
//	float scale[3];
//
//	bool isBoundingBox;
//	bool isAnimated;
//
//	unsigned int vertexCount;
//	unsigned int skelAnimVertexCount;
//	unsigned int jointCount;
//};
//
///**
//This struct is used to be "parallell" to the
//mesh struct. They are connected implicitly.
//**/
//struct  read_m
//{
//	std::vector< read_sVertex> vList;
//};
//
//struct  read_sSkelAnimVertex
//{
//	float vertexPos[3];
//	float vertexNormal[3];
//	float vertexUV[2];
//	float tangentNormal[3];
//	float biTangentNormal[3];
//	float influences[4];
//	float weights[4];
//};
//
//struct read_mk
//{
//	std::vector<read_sSkelAnimVertex> vskList;
//};
//
//struct read_sJoint
//{
//	int jointID;
//	int parentJointID;
//	int bBoxID;
//
//	float pos[3];
//	float rot[3];
//	float scale[3];
//
//	float bindPoseInverse[16];
//	float globalBindPoseInverse[16];
//
//	int animationStateCount;
//};
//
//struct read_sAnimationState
//{
//	int keyFrames;
//};
//
//struct read_sKeyFrame
//{
//	float keyTime;
//	float keyPos[3];
//	float keyRotate[3];
//	float keyScale[3];
//};
//
//struct  read_sMaterial
//{
//	char materialName[256];
//
//	float ambientColor[3];
//	float diffuseColor[3];
//	float specularColor[3];
//
//	float shinyFactor;
//
//	char diffuseTexture[256];
//	char specularTexture[256];
//	char normalTexture[256];
//};
//
//struct  read_sLight
//{
//	int lightID;
//
//	float lightPos[3];
//	float lightRot[3];
//	float lightScale[3];
//
//	float color[3];
//	float intensity;
//};
//
//struct  read_sCamera
//{
//	float camPos[3];
//	float upVector[3];
//
//	float fieldOfView;
//	float nearPlane;
//	float farPlane;
//};