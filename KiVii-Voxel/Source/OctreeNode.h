#pragma once
#include "GL_CALL.h"


#define STARTING_NODE_SIZE 64
#define TNW 3
#define TNE 7
#define TSW 2
#define TSE 6
#define BNW 1
#define BNE 5
#define BSW 0
#define BSE 4
#define OUT_OF_NODE_BOUNDS 8




//child:	0 1 2 3 4 5 6 7
//x :		- - - - + + + +
//y :		- - + + - - + +
//z :		- + - + - + - +



template<typename T>
class OctreeNode {
	OctreeNode<T>* parentNode;
	Vector3i nodePosition;
	vector<OctreeNode<T>*> childNodes;
	T* nodeInformation;
	int nodeSize;
	char nodePosInVec;

	OctreeNode* GetNodeAt(Vector3i pos);
	char GetPosInVec(Vector3i pos,bool isVoxelSize = false);
	Vector3i GetPosInVec(char posInVec);

	void GetObjectsInView(std::function<bool(Vector3i, float)> functionForFrustrumTesting, vector<KDrawData>& Objects);
	void GetObjectsInView(std::function<bool(Vector3i, float)> functionForFrustrumTesting, vector<KMinMaxBoundData>& Objects);
	void GetObjectsInView(std::function<bool(Vector3i, float)> functionForFrustrumTesting, vector<Vector4f>& positions);
	void GetObjectsInView(std::function<bool(Vector3i, float)> functionForFrustrumTesting, vector<float>& positions);
	

	friend class KManager;
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
inline void OctreeNode<T>::GetObjectsInView(std::function<bool(Vector3i, float)> functionForFrustrumTesting, vector<KMinMaxBoundData>& Objects) {
	if (nodeSize != 1) {
		for (auto& child : childNodes) {
			if (child != nullptr) {

				if (functionForFrustrumTesting(child->nodePosition, child->nodeSize * VOXEL_ENTITY_SIZE)) {
					child->GetObjectsInView(functionForFrustrumTesting, Objects);
				}
			}
		}
	}
	else {
		if (functionForFrustrumTesting(nodePosition, nodeSize * VOXEL_ENTITY_SIZE)) {
			if (nodeInformation != nullptr) {
				Vector3f worldSpaceCoords = nodeInformation->GetPositionInWorldSpace();
				Objects.push_back({{worldSpaceCoords - VOXEL_ENTITY_SIZE/2.0f },{worldSpaceCoords + VOXEL_ENTITY_SIZE/2.0f}});
			}
		}
	}

}

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
			if (pos.x >= nodePosition.x && pos.y >= nodePosition.y && pos.z >= nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x < nodePosition.x && pos.y >= nodePosition.y && pos.z >= nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x >= nodePosition.x && pos.y >= nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x < nodePosition.x && pos.y >= nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x >= nodePosition.x && pos.y < nodePosition.y && pos.z >= nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x < nodePosition.x && pos.y < nodePosition.y && pos.z >= nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->GetNodeAt(pos);
			}
			if (pos.x >= nodePosition.x && pos.y < nodePosition.y && pos.z < nodePosition.z) {
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
inline char OctreeNode<T>::GetPosInVec(Vector3i pos,bool isVoxelSize)
{
	if (nodeSize != 1) {
		if (pos.x > nodePosition.x + nodeSize / 2+1 || pos.x < nodePosition.x - nodeSize / 2-1 || pos.y > nodePosition.y + nodeSize/2+1 || pos.y < nodePosition.y - nodeSize/2-1 || pos.z > nodePosition.z + nodeSize/2+1 || pos.z < nodePosition.z - nodeSize/2-1) {
			return OUT_OF_NODE_BOUNDS;
		}
	}
	char oct = 0;
	if (pos.x >= nodePosition.x) { oct |= 4; }
	if (pos.y >= nodePosition.y) { oct |= 2; }
	if (pos.z >= nodePosition.z) { oct |= 1; }
	return oct;
}

template<typename T>
inline Vector3i OctreeNode<T>::GetPosInVec(char posInVec)
{
	switch (posInVec) {
	case TNE:
		return Vector3i(nodePosition.x + nodeSize / 4, nodePosition.y + nodeSize / 4, nodePosition.z + nodeSize / 4);
		break;
	case TNW:
		return Vector3i(nodePosition.x - nodeSize / 4, nodePosition.y + nodeSize / 4, nodePosition.z + nodeSize / 4);
		break;
	case TSE:
		return Vector3i(nodePosition.x + nodeSize / 4, nodePosition.y + nodeSize / 4, nodePosition.z - nodeSize / 4);
		break;
	case TSW:
		return Vector3i(nodePosition.x - nodeSize / 4, nodePosition.y + nodeSize / 4, nodePosition.z - nodeSize / 4);
		break;
	case BNE:
		return Vector3i(nodePosition.x + nodeSize / 4, nodePosition.y - nodeSize / 4, nodePosition.z + nodeSize / 4);
		break;
	case BNW:
		return Vector3i(nodePosition.x - nodeSize / 4, nodePosition.y - nodeSize / 4, nodePosition.z + nodeSize / 4);
		break;
	case BSE:
		return Vector3i(nodePosition.x + nodeSize / 4, nodePosition.y - nodeSize / 4, nodePosition.z - nodeSize / 4);
		break;
	case BSW:
		return Vector3i(nodePosition.x - nodeSize / 4, nodePosition.y - nodeSize / 4, nodePosition.z - nodeSize / 4);
		break;
	}
}

template<typename T>
inline void OctreeNode<T>::GetObjectsInView(std::function<bool(Vector3i, float)> functionForFrustrumTesting, vector<Vector4f>& positions)
{

	//TODO
	if (nodeSize != 1) {
		for (auto& child : childNodes) {
			if (child != nullptr) {

				if (functionForFrustrumTesting(child->nodePosition, child->nodeSize * VOXEL_ENTITY_SIZE)) {
					child->GetObjectsInView(functionForFrustrumTesting, positions);
				}
			}
		}
	}
	else {
		if (functionForFrustrumTesting(nodePosition, nodeSize * VOXEL_ENTITY_SIZE)) {
			if (nodeInformation != nullptr) {
				positions.emplace_back(Vector4f(nodeInformation->GetPosition(),1.0f));
			}
		}
	}


}
template<typename T>
inline void OctreeNode<T>::GetObjectsInView(std::function<bool(Vector3i, float)> functionForFrustrumTesting, vector<float>& positions)
{

	//TODO
	if (nodeSize != 1) {
		for (auto& child : childNodes) {
			if (child != nullptr) {

				if (functionForFrustrumTesting(child->nodePosition, child->nodeSize * VOXEL_ENTITY_SIZE)) {
					child->GetObjectsInView(functionForFrustrumTesting, positions);
				}
			}
		}
	}
	else {
		if (functionForFrustrumTesting(nodePosition, nodeSize * VOXEL_ENTITY_SIZE)) {
			if (nodeInformation != nullptr) {
				
				KMinMaxBoundData data;
				data.max = nodeInformation->GetPositionInWorldSpace() + VOXEL_ENTITY_SIZE / 2;
				data.min = nodeInformation->GetPositionInWorldSpace() - VOXEL_ENTITY_SIZE / 2;
				positions.push_back(data.max.x);
				positions.push_back(data.max.y);
				positions.push_back(data.max.z);
				positions.push_back(data.min.x);
				positions.push_back(data.min.y);
				positions.push_back(data.min.z);
				
				/*
				Vector3f position = nodeInformation->GetPositionInWorldSpace();
				positions.push_back(position.x);
				positions.push_back(position.y);
				positions.push_back(position.z);
				*/
			}
		}
	}


}


template<typename T>
inline void OctreeNode<T>::GetObjectsInView(std::function<bool(Vector3i, float)> functionForFrustrumTesting,vector<KDrawData>& Objects)
{
	
	//TODO
	if (nodeSize != 1) {
		for (auto& child : childNodes) {
			if (child != nullptr) {
				
				if (functionForFrustrumTesting(child->nodePosition, child->nodeSize * VOXEL_ENTITY_SIZE)) {
				child->GetObjectsInView(functionForFrustrumTesting, Objects);
				}
			}
		}
	}
	else {
		if (functionForFrustrumTesting(nodePosition, nodeSize * VOXEL_ENTITY_SIZE)) {
			if (nodeInformation != nullptr) {
				KDrawData data;
				if (nodeInformation->GetDrawData((unsigned int)Objects.size(), data)) {
					Objects.emplace_back(data);
				}
			}
		}
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
			if (pos.x >= nodePosition.x && pos.y >= nodePosition.y && pos.z >= nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize/2, nodePosition.y + nodeSize/2, nodePosition.z + nodeSize/2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x < nodePosition.x && pos.y >= nodePosition.y && pos.z >= nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x >= nodePosition.x && pos.y >= nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x < nodePosition.x && pos.y >= nodePosition.y && pos.z < nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y + nodeSize / 2, nodePosition.z - nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x >= nodePosition.x && pos.y < nodePosition.y && pos.z >= nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x + nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x < nodePosition.x && pos.y < nodePosition.y && pos.z >= nodePosition.z) {
				parentNode = new OctreeNode<T>(Vector3i(nodePosition.x - nodeSize / 2, nodePosition.y - nodeSize / 2, nodePosition.z + nodeSize / 2), nodeSize * 2);
				char thisPosInVec = parentNode->GetPosInVec(nodePosition);
				parentNode->childNodes[thisPosInVec] = this;
				return parentNode->Insert(pos, information);
			}
			if (pos.x >= nodePosition.x && pos.y < nodePosition.y && pos.z < nodePosition.z) {
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
