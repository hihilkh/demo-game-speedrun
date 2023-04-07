#pragma once

#include <string>
#include <vector>

namespace Debug::Profiler
{
	class ProfilerSection
	{
	private:
		std::string name;
		std::vector<float> caches;

	protected:
		ProfilerSection(const std::string& name);

	public:
		virtual ~ProfilerSection();

		virtual void Update() = 0;

		std::string GetName() const { return name; }

		void AddCache(float cache);
		virtual void ResetCaches();
		const std::vector<float>& GetCaches() const { return caches; }
		float GetLastCache() const;
		virtual float GetCacheAvg() const;
		float GetCacheMax() const;
		float GetCacheMin() const;
	};
}