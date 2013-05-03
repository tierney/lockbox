#pragma once

#include <string>

using std::string;

namespace lockbox {

bool IsPrefixOf(const string& first, const string& second);

string RemoveBaseFromInput(const string& base, const string& input);

} // namespace lockbox
