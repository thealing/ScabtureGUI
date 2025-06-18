#pragma once

template<class Source>
class SourceManager : NonCopyable
{
public:

	SourceManager(Source source);

	const Event* getSelectionEvent();

	void selectSource(Source source);

	Source getSource() const;

private:

	Source _source;
	EventPool _selectionEventPool;
};
