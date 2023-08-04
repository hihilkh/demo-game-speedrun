#pragma once

#include "ProfilingConfig.h"

#if PROFILER_ENABLED

#include "GE/Core/Component.h"
#include <vector>
#include <memory>
#include <string>

namespace GE
{
	class GameObject;
	class Scene;
}

namespace GE::Profiling
{
	class Profiler : public Component
	{
	public:
		explicit Profiler(GameObject& gameObject);

		static void StartProfiling();

	protected:
		void Awake() override;
		void Update() override;
		void PreDestroy() override;

	private:
		std::vector<std::unique_ptr<class ProfilerSection>> sections;
		std::vector<std::unique_ptr<class ProfilerLogger>> loggers;

		unsigned int currentSampleSize;

	private:
		void InitSections();
		void InitLoggers();
		void InsertMessage(const std::string& message) const;

		void SceneLoadedHandler(const Scene& scene) const;
	};
}

#define DEBUG_START_PROFILING() GE::Profiling::Profiler::StartProfiling();

#else

#define DEBUG_START_PROFILING()

#endif