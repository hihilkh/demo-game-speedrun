#include "ProfilerSection.h"
#include <numeric>
#include <algorithm>

namespace GE::Profiling
{
	ProfilerSection::ProfilerSection(const std::string& name) : name(name)
	{
	}

	void ProfilerSection::AddCache(float cache)
	{
		caches.push_back(cache);
	}

	void ProfilerSection::ResetCaches()
	{
		caches.clear();
	}

	float ProfilerSection::GetLastCache() const
	{
		if (caches.empty()) {
			return -1.0f;
		}

		return caches.back();
	}

	float ProfilerSection::GetCacheAvg() const
	{
		if (caches.empty()) {
			return -1.0f;
		}

		return std::reduce(caches.begin(), caches.end()) / caches.size();
	}

	float ProfilerSection::GetCacheMax() const
	{
		if (caches.empty()) {
			return -1.0f;
		}

		return *std::max_element(caches.begin(), caches.end());
	}

	float ProfilerSection::GetCacheMin() const
	{
		if (caches.empty()) {
			return -1.0f;
		}

		return *std::min_element(caches.begin(), caches.end());
	}
}