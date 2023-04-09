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
		ObjectBase<Object>(TaskConstant::TaskGroupName_Debug, TaskConstant::TaskName_Profiler, true),
		currentSampleSize(0)
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
		
		if (isEnableSectionFps)		{ sections.push_back(std::make_unique<ProfilerSectionFps>()); }
		if (isEnableSectionMemory)	{ sections.push_back(std::make_unique<ProfilerSectionMemory>()); }
		if (isEnableSectionCpu)		{ sections.push_back(std::make_unique<ProfilerSectionCpu>()); }
	}

	void Object::InitLoggers()
	{
		if (isEnableLoggerConsole)	{ loggers.push_back(std::make_unique<ProfilerLoggerConsole>()); }
		if (isEnableLoggerCsv)		{ loggers.push_back(std::make_unique<ProfilerLoggerCsv>()); }
	}

	void Object::InsertMessage(const string& message) const
	{
		for (auto& logger : loggers) {
			logger->InsertMessage(message);
		}
	}
}

#endif