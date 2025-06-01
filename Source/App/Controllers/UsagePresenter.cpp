#include "UsagePresenter.h"

UsagePresenter::UsagePresenter(SettingsPanel* settingsPanel, CpuMonitor* cpuMonitor, MemoryMonitor* memoryMonitor)
{
	_settingsPanel = settingsPanel;
	_cpuMonitor = cpuMonitor;
	_memoryMonitor = memoryMonitor;
	_eventDispatcher.addEntry(cpuMonitor->getUpdateEvent(), BIND(UsagePresenter, updateCpuUsage, this));
	_eventDispatcher.addEntry(memoryMonitor->getUpdateEvent(), BIND(UsagePresenter, updateMemoryUsage, this));
	_eventDispatcher.start(settingsPanel);
	_cpuMonitor->start();
	_memoryMonitor->start();
}

UsagePresenter::~UsagePresenter()
{
	_cpuMonitor->stop();
	_memoryMonitor->stop();
	_eventDispatcher.stop();
}

void UsagePresenter::updateCpuUsage()
{
	int usage = _cpuMonitor->getUsage();
	_settingsPanel->setCpuUsage(usage);
}

void UsagePresenter::updateMemoryUsage()
{
	int usage = _memoryMonitor->getUsage();
	_settingsPanel->setMemoryUsage(usage);
}
