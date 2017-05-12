#ifndef EDGEDETECTOR_H
#define EDGEDETECTOR_H

namespace utl
{

class EdgeDetector
{
public:
	EdgeDetector(bool initState = false);
	~EdgeDetector() = default;

	bool risingEdge(bool newState);
	bool fallingEdge(bool newState);

private:
	bool state;
};

}

#endif // EDGEDETECTOR_H
