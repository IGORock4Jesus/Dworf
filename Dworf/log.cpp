#include "stdafx.h"
#include "log.h"


namespace dlog
{
	void writeLine(std::string text) {
#ifdef _DEBUG
		OutputDebugString((text + "\n").c_str());
#endif // _DEBUG
	}
}
