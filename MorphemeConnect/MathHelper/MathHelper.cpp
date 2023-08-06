#include "MathHelper.h"

float MathHelper::FrameToTime(int frame, int frameRate)
{
	return ((float)frame / (float)frameRate);
}

int MathHelper::TimeToFrame(float time, int frameRate)
{
	float frame = (time * frameRate);

	return (frame + 0.9);
}