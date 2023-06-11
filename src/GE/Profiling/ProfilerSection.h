#pragma once

#include <string>
#include <vector>

namespace GE::Profiling
{
	class ProfilerSection
	{
	private:
		std::string name;
		std::vector<float> caches;

	protected:
		explicit ProfilerSection(const std::string& name);

	public:
		virtual ~ProfilerSection() = default;

		virtual void Update(bool isLastSample) = 0;

		std::string GetName() const { return name; }

		void AddCache(float cache);
		virtual void ResetCaches();
		const std::vector<float>& GetCaches() const { return caches; }
		float GetLastCache() const;
		float GetCacheAvg() const;
		float GetCacheMax() const;
		float GetCacheMin() const;
	};
}