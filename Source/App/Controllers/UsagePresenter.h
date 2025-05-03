#pragma once

class UsagePresenter : NonCopyable
{
public:

	UsagePresenter(SettingsPanel* settingsPanel, CpuMonitor* cpuMonitor, MemoryMonitor* memoryMonitor);

	~UsagePresenter();

private:

	void updateCpuUsage();

	void updateMemoryUsage();

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<SettingsPanel> _settingsPanel;
	WeakPointer<CpuMonitor> _cpuMonitor;
	WeakPointer<MemoryMonitor> _memoryMonitor;
};

