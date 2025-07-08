#pragma once

class BilinearResizer : public BaseResizer
{
public:

	BilinearResizer(Vector inputSize, Vector outputSize, const Rect& inputRect, const Rect& outputRect);

	~BilinearResizer();

	virtual void resize(const uint32_t* inputPixels, uint32_t* outputPixels) override;

private:

	int* _indexBuffer;
	int* _weightBuffer;
};

