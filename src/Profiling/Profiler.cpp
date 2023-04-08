#include "Profiler.h"

#if PROFILER_ENABLED

#include "Task/TaskConstant.h"

#include "ProfilerSection.h"
#include "ProfilerSectionFps.h"
#include "ProfilerSectionMemory.h"
#include "ProfilerSectionCpu.h"

#include "ProfilerLogger.h"
#include "ProfilerLoggerConsole.h"
#include "ProfilerLoggerCsv.h"

namespace Profiling
{
	Object::Object() : 
		ObjectBase<Object>(TaskConstant::TaskGroupName_Debug, TaskConstant::TaskName_Profiler)
	{
		InitSections();
		InitLoggers();

		for (auto& logger : loggers) {
			logger->BeginLog(sections);
		}
	}

	Object::~Object()
	{
		for (auto& logger : loggers) {
			logger->EndLog(sections);
		}
	}

	void Object::UpDate()
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

	void Object::Render2D_AF()
	{
	}

	void Object::InitSections()
	{
		sections.clear();
		
		if (enableSectionFps)		{ sections.push_back(std::make_unique<ProfilerSectionFps>()); }
		if (enableSectionMemory)	{ sections.push_back(std::make_unique<ProfilerSectionMemory>()); }
		if (enableSectionCpu)		{ sections.push_back(std::make_unique<ProfilerSectionCpu>()); }
	}

	void Object::InitLoggers()
	{
		if (enableLoggerConsole)	{ loggers.push_back(std::make_unique<ProfilerLoggerConsole>()); }
		if (enableLoggerCsv)		{ loggers.push_back(std::make_unique<ProfilerLoggerCsv>()); }
	}
}

#endif