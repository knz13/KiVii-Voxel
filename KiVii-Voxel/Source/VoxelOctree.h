#pragma once
#include "GL_CALL.h"

#define VOXEL_SIZE 1
#define STARTING_NODE_SIZE 512

#define TOP_NORTH_LEFT_NODE 0
#define TOP_NORTH_RIGHT_NODE 1
#define TOP_SOUTH_LEFT_NODE 2
#define TOP_SOUTH_RIGHT_NODE 3
#define BOTTOM_NORTH_LEFT_NODE 4
#define BOTTOM_NORTH_RIGHT_NODE 5
#define BOTTOM_SOUTH_LEFT_NODE 6
#define BOTTOM_SOUTH_RIGHT_NODE 7


class CubeVoxel;
class OctreeNode {
	OctreeNode* parentNode;
	vector<OctreeNode*> childNodes;
	CubeVoxel* nodeInformation;
	Vector3i nodePosition;
	short int nodeSize;

	unsigned int CheckQuadrant(Vector3i pos);
	bool CheckIfInNode(Vector3i pos);
	void AddChildNode(unsigned int placement);
public:
	OctreeNode(short int size, Vector3i position);
	~OctreeNode();
	

	void deleteInformation(Vector3i position);
	bool insert(Vector3i position,CubeVoxel* information);
	CubeVoxel* findInNodes(Vector3i position);
	void CleanupCommand();
	void StartCleanup();
	OctreeNode* GetHeadNode();

};

class VoxelOctree {
	
private:
	static OctreeNode* HeadNode;

public:

	static void insert(Vector3i position, CubeVoxel* voxel);
	static bool isClear(Vector3i position);
	static CubeVoxel* GetPositionObject(Vector3i position);
	static void Cleanup();

};