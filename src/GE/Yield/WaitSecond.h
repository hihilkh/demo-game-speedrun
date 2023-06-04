#pragma once

namespace GE::Yield
{
	class WaitSecond
	{
	public:
		explicit WaitSecond(float waitSecond);

		bool operator()() const;

	private:
		float waitSecond;
		float startSecond;
	};
}
