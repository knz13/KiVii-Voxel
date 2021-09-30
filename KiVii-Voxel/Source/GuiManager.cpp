#include "GuiManager.h"
#include "KManager.h"
#include "RenderWindow.h"

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
	ImGui::StyleColorsDark();

	m_IO->ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
}

void GuiManager::Begin()
{
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
	



}

void GuiManager::End()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	GL_CALL(glViewport(0, 0, KManager::GetWindow()->GetSize().x, KManager::GetWindow()->GetSize().y));

}
