#include "SettingsPanel.h"

SettingsPanel::SettingsPanel(Window* parent) : Panel(parent)
{
	setAnchor(AnchorBottomRight);
	setBounds(Vector(0, 0), Vector(245, 80));
	_cpuUsageLabel = new Label(this, L"", Label::AlignLeft);
	_cpuUsageLabel->setBounds(Vector(15, 10), Vector(150, 30));
	_memoryUsageLabel = new Label(this, L"", Label::AlignLeft);
	_memoryUsageLabel->setBounds(Vector(15, 40), Vector(150, 30));
	ImageStore& imageStore = ImageStore::getInstance();
	_settingsButton = new CustomButton(this, imageStore.getSettingsImage());
	_settingsButton->setAnchor(AnchorBottomRight);
	_settingsButton->setBounds(Vector(15, 15), Vector(50, 50));
	FontStore& fontStore = FontStore::getInstance();
	setChildrenFont(fontStore.getDisplayFont());
	setCpuUsage(0);
	setMemoryUsage(0);
}

void SettingsPanel::setCpuUsage(int usage)
{
	ControlUtil::setText(_cpuUsageLabel, L"CPU: %2i %%", usage);
}

void SettingsPanel::setMemoryUsage(int usage)
{
	ControlUtil::setText(_memoryUsageLabel, L"MEM: %3i MB", usage);
}

void SettingsPanel::setEnabled(bool enabled)
{
	_settingsButton->setEnabled(enabled);
}

const Event* SettingsPanel::getSettingsClickEvent() const
{
	return _settingsButton->getClickEvent();
}
