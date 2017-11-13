#pragma once
#include "stdafx.h"

namespace StringUtil
{
	void tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters);
}