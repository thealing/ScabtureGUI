#pragma once

class NearestResizer : public BaseResizer
{
public:

	NearestResizer(Vector inputSize, Vector outputSize, const Rect& inputRect, const Rect& outputRect);

	~NearestResizer();

	virtual void resize(const uint32_t* inputPixels, uint32_t* outputPixels) override;

private:

	int* _indexBuffer;
};

