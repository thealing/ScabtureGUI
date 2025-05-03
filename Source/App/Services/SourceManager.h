#pragma once

template<class Source>
class SourceManager : NonCopyable
{
public:

	SourceManager(Source source);

	void selectSource(Source source);

	Source getSource() const;

	const Event* getSelectionEvent() const;

private:

	Source _source;
	EventPool _selectionEventPool;
};
