#include "SourceManager.h"

template<class Source>
SourceManager<Source>::SourceManager(Source source)
{
	_source = source;
	_selectionEventPool.setEvents();
}

template<class Source>
void SourceManager<Source>::selectSource(Source source)
{
	_source = source;
	_selectionEventPool.setEvents();
}

template<class Source>
Source SourceManager<Source>::getSource() const
{
	return _source;
}

template<class Source>
const Event* SourceManager<Source>::getSelectionEvent() const
{
	return _selectionEventPool.getEvent();
}
