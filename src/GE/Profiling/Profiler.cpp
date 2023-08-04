#include "Profiler.h"

#if PROFILER_ENABLED

#include "GE/Core/GameObject.h"
#include "GE/Scene/Scene.h"

#include "ProfilerSection.h"
#include "ProfilerSectionFps.h"
#include "ProfilerSectionMemory.h"
#include "ProfilerSectionCpu.h"

#include "ProfilerLogger.h"
#include "ProfilerLoggerConsole.h"
#include "ProfilerLoggerCsv.h"

namespace GE::Profiling
{
	Profiler::Profiler(GameObject& gameObject) :
		Component(gameObject),
		currentSampleSize(0)
	{
	}

	void Profiler::Awake()
	{
		InitSections();
		InitLoggers();

		for (auto& logger : loggers) {
			logger->BeginLog(sections);
		}

		Scene::onLoaded.AddListener(&Profiler::SceneLoadedHandler, *this);
	}

	void Profiler::PreDestroy()
	{
		Scene::onLoaded.RemoveListener(&Profiler::SceneLoadedHandler, *this);

		for (auto& logger : loggers) {
			logger->EndLog(sections);
		}
	}

	void Profiler::StartProfiling()
	{
		GameObject& obj = GameObject::CreatePersistent("Profiler");
		obj.AddComponent<Profiler>();
	}

	void Profiler::Update()
	{
		bool isLastSample = false;

		++currentSampleSize;
		if (currentSampleSize >= sampleSize) {
			isLastSample = true;
		}

		for (auto& section : sections) {
			section->Update(isLastSample);
		}

		if (isLastSample) {
			currentSampleSize = 0;

			for (auto& logger : loggers) {
				logger->Log(sections);
			}

			for (auto& section : sections) {
				section->ResetCaches();
			}
		}
	}

	void Profiler::InitSections()
	{
		sections.clear();
		
		if (isEnableSectionFps)		{ sections.push_back(std::make_unique<ProfilerSectionFps>()); }
		if (isEnableSectionMemory)	{ sections.push_back(std::make_unique<ProfilerSectionMemory>()); }
		if (isEnableSectionCpu)		{ sections.push_back(std::make_unique<ProfilerSectionCpu>()); }
	}

	void Profiler::InitLoggers()
	{
		if (isEnableLoggerConsole)	{ loggers.push_back(std::make_unique<ProfilerLoggerConsole>()); }
		if (isEnableLoggerCsv)		{ loggers.push_back(std::make_unique<ProfilerLoggerCsv>()); }
	}

	void Profiler::InsertMessage(const std::string& message) const
	{
		for (auto& logger : loggers) {
			logger->InsertMessage(message);
		}
	}

	void Profiler::SceneLoadedHandler(const Scene& scene) const
	{
		InsertMessage("Move to scene : " + scene.GetName());
	}
}

#endif