#ifndef SILKROAD_CONFIG_READER_H
#define SILKROAD_CONFIG_READER_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#define __cfgfile CConfigParser

// Typedefs for C++98 readability
typedef std::map<std::string, std::string> KeyValueMap;
typedef std::map<std::string, KeyValueMap> ConfigData;

class CConfigParser {
public:
    CConfigParser()
    {}

    // Main load function
    bool Load(const std::string& filename) {
        std::ifstream file(filename.c_str());
        if (!file.is_open()) return false;

        m_data.clear();
        std::string line;
        std::string currentSection = "Global";
        bool inMultiLineComment = false;

        while (std::getline(file, line)) {
            Trim(line);
            if (line.empty()) continue;

            if (HandleComments(line, inMultiLineComment)) continue;
            if (inMultiLineComment || line.empty()) continue;

            // Detect Section Start (e.g., MachineManager {)
            size_t bracePos = line.find('{');
            if (bracePos != std::string::npos) {
                std::string sectionName = line.substr(0, bracePos);
                Trim(sectionName);
                if (!sectionName.empty()) currentSection = sectionName;
                continue;
            }

            // Detect Section End (})
            if (line.find('}') != std::string::npos) {
                currentSection = "Global";
                continue;
            }

            ParseLine(line, currentSection);
        }
        file.close();
        return true;
    }

    // --- Data Retrieval Helpers ---

    std::string GetString(const std::string& section, const std::string& key) const {
        ConfigData::const_iterator sit = m_data.find(section);
        if (sit != m_data.end()) {
            KeyValueMap::const_iterator kit = sit->second.find(key);
            if (kit != sit->second.end()) return kit->second;
        }
        return "";
    }

    int GetInt(const std::string& section, const std::string& key) const {
        std::string val = GetString(section, key);
        if (val.empty()) return 0;

        char* endPtr;
        long result = strtol(val.c_str(), &endPtr, 10);

        if (endPtr == val.c_str()) {
            return 0;
        }

        return static_cast<int>(result);
    }

    bool GetBool(const std::string& section, const std::string& key) const {
        std::string val = GetString(section, key);
        if (val.empty()) return false;

        std::string upperVal = val;
        for (size_t i = 0; i < upperVal.length(); ++i) {
            upperVal[i] = (char)toupper((unsigned char)upperVal[i]);
        }

        return (upperVal == "1" ||
                upperVal == "ON" ||
                upperVal == "TRUE" ||
                upperVal == "YES" ||
                upperVal == "EVENT_ON");
    }

    void GetAddress(const std::string& section, const std::string& key, std::string& outIp, int& outPort) const {
        std::string val = GetString(section, key);
        std::vector<std::string> parts = Split(val);

        if (parts.size() >= 2) {
            outIp = parts[0];

            char* endPtr;
            long portResult = strtol(parts[1].c_str(), &endPtr, 10);

            if (endPtr != parts[1].c_str()) {
                outPort = static_cast<int>(portResult);
            } else {
                outPort = 0;
            }
        }
    }

    // --- Iteration Helpers ---

    const KeyValueMap* GetSection(const std::string& section) const {
        ConfigData::const_iterator it = m_data.find(section);
        return (it != m_data.end()) ? &(it->second) : NULL;
    }

    std::vector<std::string> FindKeysWithPrefix(const std::string& section, const std::string& prefix) const {
        std::vector<std::string> foundKeys;
        const KeyValueMap* sectionMap = GetSection(section);
        if (sectionMap) {
            for (KeyValueMap::const_iterator it = sectionMap->begin(); it != sectionMap->end(); ++it) {
                if (it->first.compare(0, prefix.length(), prefix) == 0) {
                    foundKeys.push_back(it->first);
                }
            }
        }
        return foundKeys;
    }

private:
    ConfigData m_data;

    void Trim(std::string& s) {
        size_t first = s.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) { s = ""; return; }
        size_t last = s.find_last_not_of(" \t\r\n");
        s = s.substr(first, (last - first + 1));
    }

    bool HandleComments(std::string& line, bool& inMultiLine) {
        if (inMultiLine) {
            size_t endComment = line.find("*/");
            if (endComment != std::string::npos) {
                inMultiLine = false;
                line = line.substr(endComment + 2);
                Trim(line);
            } else return true;
        }
        if (line.find("/*") == 0) { inMultiLine = true; return true; }
        size_t commentPos = line.find("//");
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
            Trim(line);
        }
        return line.empty();
    }

    void ParseLine(const std::string& line, const std::string& section) {
        size_t splitPos = line.find_first_of(" \t");
        if (splitPos != std::string::npos) {
            std::string key = line.substr(0, splitPos);
            std::string value = line.substr(splitPos);
            Trim(key);
            Trim(value);

            std::string cleanVal;
            for(size_t i=0; i<value.length(); ++i) {
                if(value[i] != '"') cleanVal += value[i];
            }
            if (!key.empty()) m_data[section][key] = cleanVal;
        }
    }

    std::vector<std::string> Split(const std::string& s) const {
        std::vector<std::string> elems;
        std::string item;
        for (size_t i = 0; i < s.length(); ++i) {
            if (s[i] == ',' || isspace(s[i])) {
                if (!item.empty()) { elems.push_back(item); item.clear(); }
            } else { item += s[i]; }
        }
        if (!item.empty()) elems.push_back(item);
        return elems;
    }
};

#endif