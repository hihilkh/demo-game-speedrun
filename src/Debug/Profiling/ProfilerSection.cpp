#include "ProfilerSection.h"
#include <numeric>
#include <algorithm>

namespace Debug::Profiler
{
	ProfilerSection::ProfilerSection(const std::string& name) : name(name)
	{
	}

	ProfilerSection::~ProfilerSection()
	{
	}

	void ProfilerSection::AddCache(float cache)
	{
		caches.push_back(cache);
	}

	void Debug::Profiler::ProfilerSection::ResetCaches()
	{
		caches.clear();
	}

	float Debug::Profiler::ProfilerSection::GetLastCache() const
	{
		if (caches.empty()) {
			return -1.0f;
		}

		return caches.back();
	}

	float Debug::Profiler::ProfilerSection::GetCacheAvg() const
	{
		if (caches.empty()) {
			return -1.0f;
		}

		return std::reduce(caches.begin(), caches.end()) / caches.size();
	}

	float Debug::Profiler::ProfilerSection::GetCacheMax() const
	{
		if (caches.empty()) {
			return -1.0f;
		}

		return *std::max_element(caches.begin(), caches.end());
	}

	float Debug::Profiler::ProfilerSection::GetCacheMin() const
	{
		if (caches.empty()) {
			return -1.0f;
		}

		return *std::min_element(caches.begin(), caches.end());
	}
}