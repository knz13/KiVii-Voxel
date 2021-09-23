#include "VoxelOctree.h"
#include "KManager.h"

//Meu amooooor Eu te amo muitoooooooo sabia?????? Sua lindaaaaaa!!!!

OctreeNode* VoxelOctree::HeadNode = new OctreeNode(STARTING_NODE_SIZE, Vector3i(0, STARTING_NODE_SIZE / 2, 0));
void VoxelOctree::Cleanup()
{
	HeadNode = HeadNode->GetHeadNode();
	HeadNode->StartCleanup();
}

void VoxelOctree::insert(Vector3i position, CubeVoxel* voxel) 
{
	HeadNode->insert(position, voxel);
}

OctreeNode::OctreeNode(short int size,Vector3i position)
	:parentNode(nullptr),nodePosition(position),nodeSize(size),nodeInformation(nullptr)
{
	if (size == VOXEL_SIZE) {

	}
	else {
		childNodes.reserve(8);
		for (char i = 0; i < 8; i++) {
			childNodes.push_back(nullptr);
		}
	}
}

OctreeNode::~OctreeNode()
{

}
CubeVoxel* OctreeNode::findInNodes(Vector3i position)
{
	if (parentNode == nullptr) {
		if (this->CheckIfInNode(position)) {
			unsigned int quadrant = this->CheckQuadrant(position);
			return childNodes[quadrant]->findInNodes(position);
		}
		else {
			if (position.x > nodePosition.x + nodeSize / 2 && position.z > nodePosition.z + nodeSize / 2) {
				parentNode = new OctreeNode(nodeSize * 2, Vector3f(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2));
				unsigned int myQuadrant = parentNode->CheckQuadrant(nodePosition);
				parentNode->childNodes[myQuadrant] = this;
				return parentNode->findInNodes(position);
			}
			else if (position.x > nodePosition.x + nodeSize / 2 && position.z < nodePosition.z - nodeSize / 2) {
				parentNode = new OctreeNode(nodeSize * 2, Vector3f(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2));
				unsigned int myQuadrant = parentNode->CheckQuadrant(nodePosition);
				parentNode->childNodes[myQuadrant] = this;
				return parentNode->findInNodes(position);
			}
			else if (position.x < nodePosition.x - nodeSize / 2 && position.z > nodePosition.z + nodeSize / 2) {
				parentNode = new OctreeNode(nodeSize * 2, Vector3f(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2));
				unsigned int myQuadrant = parentNode->CheckQuadrant(nodePosition);
				parentNode->childNodes[myQuadrant] = this;
				return parentNode->findInNodes(position);
			}
			else if (position.x < nodePosition.x - nodeSize / 2 && position.z < nodePosition.z - nodeSize / 2) {
				parentNode = new OctreeNode(nodeSize * 2, Vector3f(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2));
				unsigned int myQuadrant = parentNode->CheckQuadrant(nodePosition);
				parentNode->childNodes[myQuadrant] = this;
				return parentNode->findInNodes(position);
			}
		}
	}

	else {
		if (nodeSize > VOXEL_SIZE) {
			unsigned int placement = this->CheckQuadrant(position);
			if (childNodes[placement] != nullptr) {
				return childNodes[placement]->findInNodes(position);
			}
			else {
				this->AddChildNode(placement);
				return childNodes[placement]->findInNodes(position);
			}
		}
		else {
			return nodeInformation;
		}
	}
}

bool OctreeNode::insert(Vector3i position,CubeVoxel* information) {

	if (this->parentNode == nullptr) {
		if (this->CheckIfInNode(position)) {
			unsigned int quadrant = this->CheckQuadrant(position);
			return childNodes[quadrant]->insert(position, information);
		}
		else {
			if (position.x > nodePosition.x + nodeSize / 2 && position.z > nodePosition.z + nodeSize / 2) {
				parentNode = new OctreeNode(nodeSize * 2, Vector3f(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2));
				unsigned int myQuadrant = parentNode->CheckQuadrant(nodePosition);
				parentNode->childNodes[myQuadrant] = this;
				return parentNode->insert(position, information);
			}
			else if (position.x > nodePosition.x + nodeSize / 2 && position.z < nodePosition.z - nodeSize / 2) {
				parentNode = new OctreeNode(nodeSize * 2, Vector3f(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2));
				unsigned int myQuadrant = parentNode->CheckQuadrant(nodePosition);
				parentNode->childNodes[myQuadrant] = this;
				return parentNode->insert(position, information);
			}
			else if (position.x < nodePosition.x - nodeSize / 2 && position.z > nodePosition.z + nodeSize / 2) {
				parentNode = new OctreeNode(nodeSize * 2, Vector3f(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2));
				unsigned int myQuadrant = parentNode->CheckQuadrant(nodePosition);
				parentNode->childNodes[myQuadrant] = this;
				return parentNode->insert(position, information);
			}
			else if (position.x <nodePosition.x - nodeSize / 2 && position.z < nodePosition.z - nodeSize / 2) {
				parentNode = new OctreeNode(nodeSize * 2, Vector3f(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2));
				unsigned int myQuadrant = parentNode->CheckQuadrant(nodePosition);
				parentNode->childNodes[myQuadrant] = this;
				return parentNode->insert(position, information);
			}
		}
	}
	else {
		unsigned int quadrant = this->CheckQuadrant(position);
		if (nodeSize > VOXEL_SIZE) {
			if (childNodes[quadrant] != nullptr) {
				return childNodes[quadrant]->insert(position,information);
				
			}
			else {
				this->AddChildNode(quadrant);
				return childNodes[quadrant]->insert(position,information);
				
			}
		}
		else {
			if (nodeInformation != nullptr) {
				return false;
			}
			else {
				nodeInformation = information;
				return true;
			}
		}

	}
}

void OctreeNode::deleteInformation(Vector3i position)
{
	CubeVoxel* cube = this->findInNodes(position);
	if (cube != nullptr) {
		KManager::DeleteCube(cube);
	}
	else {
		return;
	}
}

bool OctreeNode::CheckIfInNode(Vector3i pos)
{
	if (pos.x > nodePosition.x + nodeSize / 2 || pos.x < nodePosition.x - nodeSize / 2) {
		return false;

	}
	else if (pos.y > nodePosition.y + nodeSize / 2 || pos.y < nodePosition.y - nodeSize / 2) {
		return false;
	}
	else if (pos.z > nodePosition.z + nodeSize / 2 || pos.z < nodePosition.z - nodeSize / 2) {
		return false;
	}
	else {
		return true;
	}
}

void OctreeNode::AddChildNode(unsigned int placement)
{
	switch (placement) {
	case TOP_NORTH_LEFT_NODE:
		childNodes[TOP_NORTH_LEFT_NODE] = new OctreeNode(this->nodeSize / 8, Vector3f(nodePosition.x-nodeSize/2, nodePosition.y+nodeSize/2, nodePosition.z+nodeSize/2));
		break;
	case TOP_NORTH_RIGHT_NODE:
		childNodes[TOP_NORTH_RIGHT_NODE] = new OctreeNode(this->nodeSize / 8, Vector3f(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2));
		break;
	case TOP_SOUTH_LEFT_NODE:
		childNodes[TOP_SOUTH_LEFT_NODE] = new OctreeNode(this->nodeSize / 8, Vector3f(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2));
		break;
	case TOP_SOUTH_RIGHT_NODE:
		childNodes[TOP_SOUTH_RIGHT_NODE] = new OctreeNode(this->nodeSize / 8, Vector3f(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2));
		break;
	case BOTTOM_NORTH_LEFT_NODE:
		childNodes[BOTTOM_NORTH_LEFT_NODE] = new OctreeNode(this->nodeSize / 8, Vector3f(nodePosition.x - nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2));
		break;
	case BOTTOM_NORTH_RIGHT_NODE:
		childNodes[BOTTOM_NORTH_RIGHT_NODE] = new OctreeNode(this->nodeSize / 8, Vector3f(nodePosition.x + nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2));
		break;
	case BOTTOM_SOUTH_LEFT_NODE:
		childNodes[BOTTOM_SOUTH_LEFT_NODE] = new OctreeNode(this->nodeSize / 8, Vector3f(nodePosition.x - nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z - nodeSize / 2));
		break;
	case BOTTOM_SOUTH_RIGHT_NODE:
		childNodes[BOTTOM_SOUTH_RIGHT_NODE] = new OctreeNode(this->nodeSize / 8, Vector3f(nodePosition.x + nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z - nodeSize / 2));
		break;
	}
}

unsigned int OctreeNode::CheckQuadrant(Vector3i pos)
{
	if (nodePosition.x >= pos.x && nodePosition.y >= pos.y && nodePosition.z >= pos.z) {
		return TOP_NORTH_RIGHT_NODE;
	} 
	else if (nodePosition.x < pos.x && nodePosition.y >= pos.y && nodePosition.z >= pos.z)
	{
		return TOP_NORTH_LEFT_NODE;
	}
	else if (nodePosition.x >= pos.x && nodePosition.y >= pos.y && nodePosition.z < pos.z)
	{
		return TOP_SOUTH_RIGHT_NODE;
	}
	else if (nodePosition.x < pos.x && nodePosition.y >= pos.y && nodePosition.z < pos.z)
	{
		return TOP_SOUTH_LEFT_NODE;
	}
	else if (nodePosition.x >= pos.x && nodePosition.y < pos.y && nodePosition.z >= pos.z) {
		return BOTTOM_NORTH_RIGHT_NODE;
	}
	else if (nodePosition.x < pos.x && nodePosition.y < pos.y && nodePosition.z >= pos.z)
	{
		return BOTTOM_NORTH_LEFT_NODE;
	}
	else if (nodePosition.x >= pos.x && nodePosition.y < pos.y && nodePosition.z < pos.z)
	{
		return BOTTOM_SOUTH_RIGHT_NODE;
	}
	else if (nodePosition.x < pos.x && nodePosition.y < pos.y && nodePosition.z < pos.z)
	{
		return BOTTOM_SOUTH_LEFT_NODE;
	}

}

void OctreeNode::CleanupCommand()
{
	if (parentNode != nullptr) {
		for (auto& child : childNodes) {
			if (child != nullptr) {
				delete child;
			}
		}
		parentNode->CleanupCommand();
	}
	else {
		delete this;
	}
}

OctreeNode* OctreeNode::GetHeadNode()
{
	if (parentNode == nullptr) {
		return this;
	}
	else {
		return parentNode->GetHeadNode();
	}
}

void OctreeNode::StartCleanup()
{
	if (nodeSize != VOXEL_SIZE) {
		for (auto& child : childNodes) {
			if(child != nullptr){
				child->StartCleanup();
			}
		}
	}
	else {
		parentNode->CleanupCommand();
	}
}


bool VoxelOctree::isClear(Vector3i position) {
	CubeVoxel* voxel = HeadNode->findInNodes(position);
	if (voxel != nullptr) {
		return false;
	}
	else {
		return true;
	}

}

CubeVoxel* VoxelOctree::GetPositionObject(Vector3i position) {
	return HeadNode->findInNodes(position);
}