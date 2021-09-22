#include "GuiManager.h"
#include "KManager.h"

ImGuiIO* GuiManager::m_IO = nullptr;
void GuiManager::Cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
}

void GuiManager::Init()
{
	ImGui::CreateContext();
	m_IO = &ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(KManager::GetGLFWwindowPointer(),true);
	ImGui_ImplOpenGL3_Init();

}

void GuiManager::Begin()
{
	
}

void GuiManager::End()
{
}
