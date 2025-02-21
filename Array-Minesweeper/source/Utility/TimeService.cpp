#include "../../header/Utility/TimeService.h"

namespace Utility
{
	void TimeService::updateDeltaTime()
	{
		delta_time = calculateDeltaTime();

		updatePreviousTime();
	}
	float TimeService::calculateDeltaTime()
	{
		int delta = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		return static_cast<float>(delta) / 1000000.0f;
	}
	void TimeService::updatePreviousTime()
	{
		previous_time = std::chrono::steady_clock::now();
	}
	void TimeService::initialize()
	{
		previous_time = std::chrono::steady_clock::now();
		delta_time = 0;
	}
	void TimeService::update()
	{
		updateDeltaTime();
	}
	float TimeService::getDeltaTime()
	{
		return delta_time;
	}
}