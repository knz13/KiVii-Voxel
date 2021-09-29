#pragma once
#include "GL_CALL.h"

#define STARTING_NODE_SIZE 64
#define TNW 0
#define TNE 1
#define TSW 2
#define TSE 3
#define BNW 4
#define BNE 5
#define BSW 6
#define BSE 7
#define OUT_OF_NODE_BOUNDS 8



template<typename T>
class OctreeNode {
	OctreeNode<T>* parentNode;
	Vector3i nodePosition;
	vector<OctreeNode<T>*> childNodes;
	T* nodeInformation;
	int nodeSize;
	char nodePosInVec;

	OctreeNode* GetNodeAt(Vector3i pos);
	char GetPosInVec(Vector3i pos);
	Vector3i GetPosInVec(char posInVec);
	
public:
	OctreeNode(Vector3i pos, int size, OctreeNode* parent = nullptr);
	OctreeNode(OctreeNode* parent, char posInVec);

	OctreeNode* GetHeadNode();
	bool Insert(Vector3i pos, T* information);
	bool RemoveInformation(Vector3i pos);
	T* GetNodeInformationAt(Vector3i pos);
	void BeginCleanup();

	


};

template<typename T>
inline OctreeNode<T>* OctreeNode<T>::GetNodeAt(Vector3i pos)
{
	if (parentNode == nullptr) {
		char posInVec = this->GetPosInVec(pos);
		if (posInVec != OUT_OF_NODE_BOUNDS) {
			if (childNodes[posInVec] != nullptr) {
				return childNodes[posInVec]->GetNodeAt(pos);
			}
			else {
				childNodes[posInVec] = new OctreeNode<T>(this, posInVec);
				return childNodes[posInVec]->GetNodeAt(pos);
			}
		}
		else {
			if (pos.x > nodePosition.x && pos.y > nodePosition.y && pos.z > nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x < nodePosition.x && pos.y > nodePosition.y && pos.z > nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x > nodePosition.x && pos.y > nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x < nodePosition.x && pos.y > nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x > nodePosition.x && pos.y < nodePosition.y && pos.z > nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x < nodePosition.x && pos.y < nodePosition.y && pos.z > nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x > nodePosition.x && pos.y < nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x < nodePosition.x && pos.y < nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
		}
	}
	else {
		if (nodeSize != 1) {
			char posInVec = this->GetPosInVec(pos);
			if (childNodes[posInVec] != nullptr) {
				return childNodes[posInVec]->GetNodeAt(pos);
			}
			else {
				childNodes[posInVec] = new OctreeNode<T>(this, posInVec);
				return childNodes[posInVec]->GetNodeAt(pos);
			}
		}
		else {
			return this;
		}
	}
}

template<typename T>
inline char OctreeNode<T>::GetPosInVec(Vector3i pos)
{
	if (pos.x >= nodePosition.x && pos.x < nodePosition.x + nodeSize  && pos.y >= nodePosition.y && pos.y < nodePosition.y + nodeSize && pos.z >= nodePosition.z && pos.z < nodePosition.z + nodeSize ) {
		return TNE;
	}
	if (pos.x < nodePosition.x && pos.x >= nodePosition.x - nodeSize  && pos.y >= nodePosition.y && pos.y < nodePosition.y + nodeSize && pos.z >= nodePosition.z && pos.z < nodePosition.z + nodeSize ) {
		return TNW;
	}
	if (pos.x >= nodePosition.x && pos.x < nodePosition.x + nodeSize  && pos.y >= nodePosition.y && pos.y < nodePosition.y + nodeSize && pos.z < nodePosition.z && pos.z >= nodePosition.z - nodeSize) {
		return TSE;
	}
	if (pos.x < nodePosition.x && pos.x >= nodePosition.x - nodeSize && pos.y >= nodePosition.y && pos.y < nodePosition.y + nodeSize && pos.z < nodePosition.z && pos.z >= nodePosition.z - nodeSize) {
		return TSW;
	}
	if (pos.x >= nodePosition.x && pos.x < nodePosition.x + nodeSize && pos.y < nodePosition.y && pos.y >= nodePosition.y - nodeSize && pos.z >= nodePosition.z && pos.z < nodePosition.z + nodeSize) {
		return BNE;
	}
	if (pos.x < nodePosition.x && pos.x >= nodePosition.x - nodeSize && pos.y < nodePosition.y && pos.y >= nodePosition.y - nodeSize && pos.z >= nodePosition.z && pos.z < nodePosition.z + nodeSize) {
		return BNW;
	}
	if (pos.x >= nodePosition.x && pos.x < nodePosition.x + nodeSize && pos.y < nodePosition.y && pos.y >= nodePosition.y - nodeSize && pos.z < nodePosition.z && pos.z >= nodePosition.z - nodeSize) {
		return BSE;
	}
	if (pos.x < nodePosition.x && pos.x >= nodePosition.x - nodeSize && pos.y < nodePosition.y && pos.y >= nodePosition.y - nodeSize && pos.z < nodePosition.z && pos.z >= nodePosition.z - nodeSize) {
		return BSW;
	}
	else {
		return OUT_OF_NODE_BOUNDS;
	}
}

template<typename T>
inline Vector3i OctreeNode<T>::GetPosInVec(char posInVec)
{
	switch (posInVec) {
	case TNE:
		return Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2);
		break;
	case TNW:
		return Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2);
		break;
	case TSE:
		return Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2);
		break;
	case TSW:
		return Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2);
		break;
	case BNE:
		return Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2);
		break;
	case BNW:
		return Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2);
		break;
	case BSE:
		return Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z - nodeSize / 2);
		break;
	case BSW:
		return Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z - nodeSize / 2);
		break;
	}
}


template<typename T>
inline OctreeNode<T>::OctreeNode(Vector3i pos, int size, OctreeNode* parent)
	:nodeInformation(nullptr),nodePosInVec(OUT_OF_NODE_BOUNDS),nodePosition(pos),nodeSize(size),parentNode(parent)
{
	if (nodeSize != 1) {
		childNodes.reserve(8);
		for (char i = 0; i < 8; i++) {
			childNodes.push_back(nullptr);
		}
	}
}

template<typename T>
inline OctreeNode<T>::OctreeNode(OctreeNode* parent, char posInVec)
	:nodeSize(parent->nodeSize/2),nodePosInVec(posInVec),nodeInformation(nullptr),parentNode(parent)
{
	nodePosition = parent->GetPosInVec(posInVec);
	if (nodeSize != 1) {
		childNodes.reserve(8);
		for (char i = 0; i < 8; i++) {
			childNodes.push_back(nullptr);
		}
	}
}

template<typename T>
inline OctreeNode<T>* OctreeNode<T>::GetHeadNode()
{
	if (parentNode != nullptr) {
		return parentNode->GetHeadNode();
	}
	else {
		return this;
	}
}

template<typename T>
inline bool OctreeNode<T>::Insert(Vector3i pos, T* information)
{
	if (parentNode == nullptr) {
		char posInVec = this->GetPosInVec(pos);
		if (posInVec != OUT_OF_NODE_BOUNDS) {
			if (childNodes[posInVec] != nullptr) {
				return childNodes[posInVec]->Insert(pos, information);
			}
			else {
				childNodes[posInVec] = new OctreeNode<T>(this, posInVec);
				
				return childNodes[posInVec]->Insert(pos, information);
			}
		}
		else {
			if (pos.x > nodePosition.x && pos.y > nodePosition.y && pos.z > nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize/2, nodePosition.y + nodeSize/2, nodePosition.z + nodeSize/2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x < nodePosition.x && pos.y > nodePosition.y && pos.z > nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x > nodePosition.x && pos.y > nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x < nodePosition.x && pos.y > nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x > nodePosition.x && pos.y < nodePosition.y && pos.z > nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x < nodePosition.x && pos.y < nodePosition.y && pos.z > nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x > nodePosition.x && pos.y < nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x < nodePosition.x && pos.y < nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
		}
	}
	else {
		if (nodeSize != 1) {
			char posInVec = this->GetPosInVec(pos);
			if (childNodes[posInVec] != nullptr) {
				return childNodes[posInVec]->Insert(pos, information);
			}
			else {
				childNodes[posInVec] = new OctreeNode<T>(this, posInVec);
				return childNodes[posInVec]->Insert(pos, information);
				
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

template<typename T>
inline bool OctreeNode<T>::RemoveInformation(Vector3i pos)
{
	if (parentNode == nullptr) {
		char posInVec = this->GetPosInVec(pos);
		if (posInVec != OUT_OF_NODE_BOUNDS) {
			if (childNodes[posInVec] != nullptr) {
				return childNodes[posInVec]->RemoveInformation(pos);
			}
			else {
				childNodes[posInVec] = new OctreeNode<T>(this, posInVec);
				return childNodes[posInVec]->RemoveInformation(pos);
			}
		}
		else {
			if (pos.x > nodePosition.x && pos.y > nodePosition.y && pos.z > nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->RemoveInformation(pos);
			}
			if (pos.x < nodePosition.x && pos.y > nodePosition.y && pos.z > nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->RemoveInformation(pos);
			}
			if (pos.x > nodePosition.x && pos.y > nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->RemoveInformation(pos);
			}
			if (pos.x < nodePosition.x && pos.y > nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->RemoveInformation(pos);
			}
			if (pos.x > nodePosition.x && pos.y < nodePosition.y && pos.z > nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->RemoveInformation(pos);
			}
			if (pos.x < nodePosition.x && pos.y < nodePosition.y && pos.z > nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->RemoveInformation(pos);
			}
			if (pos.x > nodePosition.x && pos.y < nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->RemoveInformation(pos);
			}
			if (pos.x < nodePosition.x && pos.y < nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->RemoveInformation(pos);
			}
		}
	}
	else {
		if (nodeSize != 1) {
			char posInVec = this->GetPosInVec(pos);
			if (childNodes[posInVec] != nullptr) {
				return childNodes[posInVec]->RemoveInformation(pos);
			}
			else {
				childNodes[posInVec] = new OctreeNode<T>(this, posInVec);
				return childNodes[posInVec]->RemoveInformation(pos);
			}
		}
		else {
			if (nodeInformation != nullptr) {
				nodeInformation = nullptr;
				return true;
			}
			else {
				return false;
			}
		}
	}
}

template<typename T>
inline T* OctreeNode<T>::GetNodeInformationAt(Vector3i pos)
{
	return this->GetNodeAt(pos)->nodeInformation;
}

template<typename T>
inline void OctreeNode<T>::BeginCleanup()
{
	char childNodesThatExist = 0;
	for (auto& child : childNodes) {
		if (child != nullptr) {
			child->BeginCleanup();
			childNodesThatExist++;
		}
	}
	if (childNodes.size() > 0 || childNodesThatExist != 0) {
		for (auto& child : childNodes) {
			if (child != nullptr) {
				child->BeginCleanup();
			}
		}
	}
	else {
		if (parentNode != nullptr) {
			char myLocation = parentNode->GetPosInVec(nodePosition);
			parentNode->childNodes[myLocation] = nullptr;
			delete this;
		}
		else {
			return;
		}
	}
}
