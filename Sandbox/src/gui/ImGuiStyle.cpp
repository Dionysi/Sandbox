#include "stdfax.h"
#include "ImGuiStyle.h"
#include "imgui_internal.h"

namespace ImGuiEx
{

	static int hue = 140;
	static constexpr int hue_reset = 140;

	static int sat_main = 180;
	static constexpr int sat_main_reset = 180;
	static int val_main = 161;
	static constexpr int val_main_reset = 161;

	static int sat_area = 124;
	static constexpr int sat_area_reset = 124;
	static int val_area = 100;
	static constexpr int val_area_reset = 100;

	static int sat_back = 59;
	static constexpr int sat_back_reset = 59;
	static int val_back = 40;
	static constexpr int val_back_reset = 40;

	bool BeginStyleFromHueWindow(bool* close)
	{
		ImGuiStyle& style = ImGui::GetStyle();


		if (!ImGui::Begin("Hue Style", close, ImGuiWindowFlags_::ImGuiWindowFlags_NoDocking))
		{
			ImGui::End();
			return false;
		}
		
		ImGui::Text("Master Hue");
		ImGui::Text("Hue");
		ImGui::SameLine();
		ImGui::SliderInt("##master hue", &hue, 0, 255);
		ImGui::SameLine();
		if (ImGui::Button("Reset##hue")) { hue = hue_reset; }
		ImGui::Dummy(ImVec2(0.0f, style.ItemSpacing.y));

		ImGui::Text("Main color");
		ImGui::Text("Sat"); 
		ImGui::SameLine();
		ImGui::SliderInt("##main sat", &sat_main, 0, 255);
		ImGui::SameLine();
		if (ImGui::Button("Reset##sat_main")) { sat_main = sat_main_reset; }
		ImGui::Text("Val");
		ImGui::SameLine();
		ImGui::SliderInt("##main val", &val_main, 0, 255);
		ImGui::SameLine();
		if (ImGui::Button("Reset##val_main")) { val_main = val_main_reset; }

		ImGui::Text("Area color");
		ImGui::Text("Sat");
		ImGui::SameLine();
		ImGui::SliderInt("##area sat", &sat_area, 0, 255);
		ImGui::SameLine();
		if (ImGui::Button("Reset##sat_area")) { sat_area = sat_area_reset; }
		ImGui::Text("Val");
		ImGui::SameLine();
		ImGui::SliderInt("##area val", &val_area, 0, 255);
		ImGui::SameLine();
		if (ImGui::Button("Reset##val_area")) { val_area = val_area_reset; }

		ImGui::Text("Background color");
		ImGui::Text("Sat");
		ImGui::SameLine();
		ImGui::SliderInt("##back sat", &sat_back, 0, 255);
		ImGui::SameLine();
		if (ImGui::Button("Reset##sat_back")) { sat_back = sat_back_reset; }
		ImGui::Text("Val");
		ImGui::SameLine();
		ImGui::SliderInt("##back val", &val_back, 0, 255);
		ImGui::SameLine();
		if (ImGui::Button("Reset##val_back")) { val_back = val_back_reset; }

		ImGui::End();

		AdjustStyleFromHue();

		return true;
	}

	void AdjustStyleFromHue()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		//style.WindowRounding = 9.0f;
		//style.FrameRounding = 3.0f;

		ImVec4 col_text = ImColor::HSV(hue / 255.f, 20.f / 255.f, 235.f / 255.f);
		ImVec4 col_main = ImColor::HSV(hue / 255.f, sat_main / 255.f, val_main / 255.f);
		ImVec4 col_back = ImColor::HSV(hue / 255.f, sat_back / 255.f, val_back / 255.f);
		ImVec4 col_area = ImColor::HSV(hue / 255.f, sat_area / 255.f, val_area / 255.f);

		style.Colors[ImGuiCol_Text] = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(col_text.x, col_text.y, col_text.z, 0.58f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(col_back.x, col_back.y, col_back.z, 1.00f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(col_area.x, col_area.y, col_area.z, 0.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(col_text.x, col_text.y, col_text.z, 0.30f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.68f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(col_main.x, col_main.y, col_main.z, 0.45f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(col_main.x, col_main.y, col_main.z, 0.35f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(col_area.x, col_area.y, col_area.z, 0.57f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(col_main.x, col_main.y, col_main.z, 0.31f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(col_main.x, col_main.y, col_main.z, 0.80f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(col_main.x, col_main.y, col_main.z, 0.24f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(col_main.x, col_main.y, col_main.z, 0.44f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(col_main.x, col_main.y, col_main.z, 0.76f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(col_main.x, col_main.y, col_main.z, 0.20f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(col_main.x, col_main.y, col_main.z, 0.43f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(col_area.x, col_area.y, col_area.z, 0.92f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(col_area.x, col_area.y, col_area.z, 0.72f);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

		// Color tab-buttons as well.
		style.Colors[ImGuiCol_Tab] = ImLerp(style.Colors[ImGuiCol_Header], style.Colors[ImGuiCol_TitleBgActive], 0.80f);
		style.Colors[ImGuiCol_TabHovered] = style.Colors[ImGuiCol_HeaderHovered];
		style.Colors[ImGuiCol_TabActive] = ImLerp(style.Colors[ImGuiCol_HeaderActive], style.Colors[ImGuiCol_TitleBgActive], 0.60f);
		style.Colors[ImGuiCol_TabUnfocused] = ImLerp(style.Colors[ImGuiCol_Tab], style.Colors[ImGuiCol_TitleBg], 0.80f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImLerp(style.Colors[ImGuiCol_TabActive], style.Colors[ImGuiCol_TitleBg], 0.40f);

		style.Colors[ImGuiCol_HeaderHovered] = ImLerp(ImVec4(col_area.x, col_area.y, col_area.z, 0.86f), ImVec4(col_area.x, col_area.y, col_area.z, 0.86f), 0.6f);


		//style.Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
	}


}; // End of namespace ImGuiEx.