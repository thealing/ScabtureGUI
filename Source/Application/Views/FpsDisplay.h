#pragma once

class FpsDisplay : public Frame
{
public:

	FpsDisplay(Window* parent);
	
	void update(int captureFps, int encodeFps);

protected:

	virtual void doPaint(Graphics& graphics) override;

private:

	int _captureFps;
	int _encodeFps;
};

