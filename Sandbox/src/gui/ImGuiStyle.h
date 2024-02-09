#pragma once

namespace ImGuiEx
{
	/*
	* Display a window for selecting a style from a hue value.
	* @returns				True if user pressed button for setting the style variable.
	*/
	bool BeginStyleFromHueWindow(bool* close = nullptr);
	/*
	* Adjust the ImGui style values from the hue values set from the window.
	*/
	void AdjustStyleFromHue();

}; // End of namespace ImGuiEx.