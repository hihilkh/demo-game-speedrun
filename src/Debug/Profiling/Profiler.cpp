#include "Profiler.h"

#if DEBUG_IS_ENABLED(DEBUG_PROFILER)

#include "Task/TaskConstant.h"

#include "ProfilerSection.h"
#include "ProfilerSectionFps.h"

#include "ProfilerLogger.h"
#include "ProfilerLoggerConsole.h"
#include "ProfilerLoggerCsv.h"

namespace Debug::Profiler
{
	Object::Object() : 
		ObjectBase<Object>(TaskConstant::TaskGroupName_Debug, TaskConstant::TaskName_Profiler)
	{
		sections.push_back(std::make_unique<ProfilerSectionFps>());

		logger = std::make_unique<ProfilerLoggerConsole>();
		//logger = std::make_unique<ProfilerLoggerCsv>();

		logger->BeginLog(sections);
	}

	Object::~Object()
	{
		logger->EndLog(sections);
	}

	void Object::UpDate()
	{
		for (auto& section : sections) {
			section->Update();
		}

		++currentSampleSize;
		if (currentSampleSize >= logger->GetSampleSize()) {
			currentSampleSize = 0;

			logger->Log(sections);
			for (auto& section : sections) {
				section->ResetCaches();
			}
		}
	}

	void Object::Render2D_AF()
	{
	}
}

#endif