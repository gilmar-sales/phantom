#include "gui_layer.h"
 
#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>
#include <GLFW/glfw3.h>

#include <core/application.h>
#include <core/log.h>

#include "styles/styles.h"


PH_NAMESPACE_BEGIN

GUILayer::GUILayer(shared<Window> window) : Layer("GUILayer"), window(window) {}

void GUILayer::on_attach()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;

	// Setup Dear ImGui style
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_WindowBg].w = 1.0f;

	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 0.0f;
	style.WindowPadding = {0.0f, 0.0f};

	style.GrabRounding = 0.0f;

	style.AntiAliasedLines = true;
	style.AntiAliasedFill = true;
	style.IndentSpacing = 22;

	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 0.0f;

	style.ScrollbarRounding = 0.0f;
	style.ScrollbarSize = 16;

	style.TabBorderSize = 1.0f;

	style.FrameRounding = 3.0f;
	style.FrameBorderSize = 1.0f;
	style.FramePadding = { 6.0f, 4.0f };

	style.PopupBorderSize = 0.0f;
	style.PopupRounding = 0.0f;

    style.ItemInnerSpacing = ImVec2(6, 6);
    style.ItemSpacing = ImVec2(6, 8);

	style.Alpha = 1.0f;

	StylePhantomDark();

	auto* native_window = (GLFWwindow*)(window->get_native_window());

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(native_window, true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void GUILayer::on_detach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GUILayer::on_event(Event& event)
{
	if (m_block_events)
	{
		ImGuiIO& io = ImGui::GetIO();
		event.Handled |= event.is_in_category(EventCategoryMouse) & io.WantCaptureMouse;
		event.Handled |= event.is_in_category(EventCategoryKeyboard) & io.WantCaptureKeyboard;
	}
}

void GUILayer::begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUILayer::end()
{

	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)Application::get_window()->get_width(), (float)Application::get_window()->get_height());

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

PH_NAMESPACE_END
