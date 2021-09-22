#pragma once
#include "GL_CALL.h"
#include "KManager.h"


struct RenderWindowProperties {
	Vector2f size = { 0,0 };
	float nearClipping = 0.01f;
	float farClipping = 300.0f;
	glm::mat4 projectionMatrix;
};

class RenderWindow {

private:
	RenderWindowProperties m_Properties;
	float m_DeltaTime=0;
	double currentTime=0, lastTime=0;
	Camera* m_MainCamera;
	friend class KManager;
public:

	RenderWindow(Vector2f vec,string title);
	~RenderWindow();

	Vector2f GetSize() { return m_Properties.size; }

	void DrawInstances(vector<glm::mat4>& modelMatrices, int instanceCount);


	
	glm::mat4 GetProjection();
	glm::mat4 GetView();
	void SetMainCamera(Camera* camera);
	bool isOpen();
	void SwapBuffers();
	void Clear();

};
