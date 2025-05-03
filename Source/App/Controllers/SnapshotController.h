#pragma once

class SnapshotController : NonCopyable
{
public:

	SnapshotController(VideoCaptureManager* videoCaptureManager, KeyboardListener* keyboardListener);

	~SnapshotController();

private:

	void onSnapshotHotkeyPressed();

	void takeSnapshot();

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<VideoCaptureManager> _videoCaptureManager;
	WeakPointer<KeyboardListener> _keyboardListener;
};

