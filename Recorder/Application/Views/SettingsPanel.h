#pragma once

class SettingsPanel : public Panel
{
public:

	SettingsPanel(Window* parent);

	void setCpuUsage(int usage);

	void setMemoryUsage(int usage);

	void setEnabled(bool enabled);

	const Event* getSettingsClickEvent() const;

private:

	UniquePointer<Label> _cpuUsageLabel;
	UniquePointer<Label> _memoryUsageLabel;
	UniquePointer<CustomButton> _settingsButton;
};

