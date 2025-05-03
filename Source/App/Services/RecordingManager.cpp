#include "RecordingManager.h"

RecordingManager::RecordingManager()
{
	WriteLockHolder holder(&_lock);
	_running = false;
	_paused = false;
}

void RecordingManager::start(SinkWriter* sinkWriter, Encoder* videoEncoder, Encoder* audioEncoder)
{
	WriteLockHolder holder(&_lock);
	assert(!_running);
	assert(_sinkWriter == NULL);
	assert(_videoEncoder == NULL);
	assert(_audioEncoder == NULL);
	_running = true;
	_paused = false;
	_sinkWriter = sinkWriter;
	_videoEncoder = videoEncoder;
	_audioEncoder = audioEncoder;
	_eventDispatcher = new EventDispatcher();
	_eventDispatcher->addEntry(_videoEncoder->getEncodeEvent(), BIND(RecordingManager, onEncodedFrame, this));
	_eventDispatcher->start();
	_sinkWriter->start();
	_videoEncoder->start();
	_audioEncoder->start();
	_fpsCounter.reset();
}

void RecordingManager::cleanup()
{
	WriteLockHolder holder(&_lock);
	assert(_sinkWriter != NULL);
	assert(_videoEncoder != NULL);
	assert(_audioEncoder != NULL);
	_videoEncoder = NULL;
	_audioEncoder = NULL;
	_sinkWriter = NULL;
	_eventDispatcher = NULL;
}

void RecordingManager::stop()
{
	WriteLockHolder holder(&_lock);
	assert(_running);
	assert(_sinkWriter != NULL);
	assert(_videoEncoder != NULL);
	assert(_audioEncoder != NULL);
	_running = false;
	_paused = false;
	_videoEncoder->stop();
	_audioEncoder->stop();
	_sinkWriter->finalize();
	_eventDispatcher->stop();
}

void RecordingManager::pause()
{
	WriteLockHolder holder(&_lock);
	assert(_running);
	assert(!_paused);
	assert(_sinkWriter != NULL);
	assert(_videoEncoder != NULL);
	assert(_audioEncoder != NULL);
	_paused = true;
	_videoEncoder->pause();
	_audioEncoder->pause();
}

void RecordingManager::resume()
{
	WriteLockHolder holder(&_lock);
	assert(_running);
	assert(_paused);
	assert(_sinkWriter != NULL);
	assert(_videoEncoder != NULL);
	assert(_audioEncoder != NULL);
	_paused = false;
	_videoEncoder->resume();
	_audioEncoder->resume();
	_fpsCounter.reset();
}

bool RecordingManager::isRunning() const
{
	ReadLockHolder holder(&_lock);
	return _running;
}

bool RecordingManager::isPaused() const
{
	ReadLockHolder holder(&_lock);
	return _paused;
}

void RecordingManager::getVideoStatistics(MF_SINK_WRITER_STATISTICS* statistics) const
{
	ReadLockHolder holder(&_lock);
	if (_videoEncoder != NULL)
	{
		_videoEncoder->getStatistics(statistics);
	}
}

void RecordingManager::getAudioStatistics(MF_SINK_WRITER_STATISTICS* statistics) const
{
	ReadLockHolder holder(&_lock);
	if (_audioEncoder != NULL)
	{
		_audioEncoder->getStatistics(statistics);
	}
}

const wchar_t* RecordingManager::getPath() const
{
	ReadLockHolder holder(&_lock);
	if (_sinkWriter != NULL)
	{
		return _sinkWriter->getPath();
	}
	else
	{
		return NULL;
	}
}

const FpsCounter& RecordingManager::getFpsCounter() const
{
    return _fpsCounter;
}

const Event* RecordingManager::getEncodeEvent() const
{
	return _encodeEventPool.getEvent();
}

void RecordingManager::onEncodedFrame()
{
	_fpsCounter.recordFrame();
	_encodeEventPool.setEvents();
}
