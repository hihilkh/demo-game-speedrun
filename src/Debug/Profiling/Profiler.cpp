#include "Profiler.h"

#if DEBUG_IS_ENABLED(DEBUG_PROFILER)

#include "Task/TaskConstant.h"

#include "ProfilerSection.h"
#include "ProfilerSectionFps.h"
#include "ProfilerSectionMemory.h"
#include "ProfilerSectionCpu.h"

#include "ProfilerLogger.h"
#include "ProfilerLoggerConsole.h"
#include "ProfilerLoggerCsv.h"

namespace Debug::Profiler
{
	namespace
	{
		const unsigned int sampleSize = 60;
	}

	Object::Object() : 
		ObjectBase<Object>(TaskConstant::TaskGroupName_Debug, TaskConstant::TaskName_Profiler)
	{
		sections.push_back(std::make_unique<ProfilerSectionFps>());
		sections.push_back(std::make_unique<ProfilerSectionMemory>());
		sections.push_back(std::make_unique<ProfilerSectionCpu>());
		
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