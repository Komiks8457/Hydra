#ifndef STRINGFUNCTIONS_H
#define STRINGFUNCTIONS_H

#define __stringa(x) stdext::_stringa(x)
#define __stringw(x) stdext::_stringw(x)
#define __tostra(x) stdext::tostra(x)
#define __tostrw(x) stdext::tostrw(x)
#define __inifile stdext::inifile
#define __chkfile(x) stdext::filechk(x)

namespace stdext
{
    struct strutil {
    protected:
        template<typename T>
        static bool compare_range_no_case(const T* base, size_t baseOffset, const T* find, size_t len)
        {
            for (size_t i = 0; i < len; ++i) {
                if (towlower(static_cast<unsigned short>(base[baseOffset + i])) !=
                    towlower(static_cast<unsigned short>(find[i])))
                    return false;
            }
            return true;
        }
        static bool compare_range_no_case_ansi(const char* base, size_t baseOffset, const char* find, size_t len)
        {
            for (size_t i = 0; i < len; ++i) {
                if (tolower(static_cast<unsigned char>(base[baseOffset + i])) !=
                    tolower(static_cast<unsigned char>(find[i])))
                    return false;
            }
            return true;
        }
    };

    class _stringa : public std::string, private strutil {
    public:
        _stringa(const std::string& s) : std::string(s) {}
        _stringa(const char* s) : std::string(s) {}

        bool startwith(const std::string& prefix) const {
            if (this->length() < prefix.length()) return false;
            return compare_range_no_case_ansi(this->c_str(), 0, prefix.c_str(), prefix.length());
        }

        bool endswith(const std::string& suffix) const {
            if (this->length() < suffix.length()) return false;
            return compare_range_no_case_ansi(this->c_str(), this->length() - suffix.length(), suffix.c_str(), suffix.length());
        }

        bool contains(const std::string& root) const {
            if (root.empty()) return true;
            if (this->length() < root.length()) return false;

            size_t limit = this->length() - root.length();
            for (size_t i = 0; i <= limit; ++i) {
                if (compare_range_no_case_ansi(this->c_str(), i, root.c_str(), root.length()))
                    return true;
            }
            return false;
        }

        bool equal(const std::string& str) const {
            if (this->length() != str.length()) return false;
            return compare_range_no_case_ansi(this->c_str(), 0, str.c_str(), str.length());
        }
    };

    class _stringw : public std::wstring, private strutil {
    public:
        _stringw(const std::wstring& s) : std::wstring(s) {}
        _stringw(const wchar_t* s) : std::wstring(s) {}

        bool startwith(const std::wstring& prefix) const {
            if (this->length() < prefix.length()) return false;
            return compare_range_no_case(this->c_str(), 0, prefix.c_str(), prefix.length());
        }

        bool endswith(const std::wstring& suffix) const {
            if (this->length() < suffix.length()) return false;
            return compare_range_no_case(this->c_str(), this->length() - suffix.length(), suffix.c_str(), suffix.length());
        }

        bool contains(const std::wstring& root) const {
            if (root.empty()) return true;
            if (this->length() < root.length()) return false;

            size_t limit = this->length() - root.length();
            for (size_t i = 0; i <= limit; ++i) {
                if (compare_range_no_case(this->c_str(), i, root.c_str(), root.length()))
                    return true;
            }
            return false;
        }

        bool equal(const std::wstring& str) const {
            if (this->length() != str.length()) return false;
            return compare_range_no_case(this->c_str(), 0, str.c_str(), str.length());
        }
    };

    class inifile {
    private:
        typedef std::map<std::string, std::string> map_str_str_t;
        typedef std::map<std::string, map_str_str_t> m_data_t;
        typedef std::vector<std::string> v_section_t;
        typedef std::map<std::string, v_section_t> m_key_t;

    public:
        ~inifile()
        {
            m_data.clear();
            m_sectionOrder.clear();
            m_keyOrder.clear();
        }

        bool load(const std::wstring& filename) {
            m_file = filename;

            // VC80 ifstream doesn't take wstring; we must convert to const char*
            // This assumes the file path uses the system's current code page (ANSI)
            std::string ansiPath(filename.begin(), filename.end());
            return load(ansiPath);
        }

        // New string version (The "Worker" function)
        bool load(const std::string& filename) {
            m_data.clear();
            m_sectionOrder.clear();
            m_keyOrder.clear();
            // If m_file is wstring, convert this back or store it separately
            // m_file = std::wstring(filename.begin(), filename.end());

            std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
            if (!file.is_open()) return false;

            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string content = buffer.str();
            file.close();

            return parse(content);
        }

        bool save()
        {
            std::stringstream ss;

            for (size_t i = 0; i < m_sectionOrder.size(); ++i)
            {
                const std::string& section = m_sectionOrder[i];
                ss << "[" << section << "]\r\n";

                const std::vector<std::string>& keys = m_keyOrder[section];
                for (size_t j = 0; j < keys.size(); ++j)
                {
                    const std::string& key = keys[j];
                    ss << key << "=" << m_data[section][key] << "\r\n";
                }

                if (i < m_sectionOrder.size() - 1)
                    ss << "\r\n";
            }

            std::ofstream file(m_file.c_str(), std::ios::out | std::ios::binary);
            if (!file.is_open()) return false;
            file << ss.str();
            file.close();

            return true;
        }

        void setvalue(const std::string& section, const std::string& key, const std::string& value)
        {
            if (m_data.find(section) == m_data.end()) {
                m_sectionOrder.push_back(section);
            }

            if (m_data[section].find(key) == m_data[section].end()) {
                m_keyOrder[section].push_back(key);
            }

            m_data[section][key] = value;
        }

        const std::string& getvalue(const std::string& section, const std::string& key, const std::string& defaultValue = "NULL")
        {
            m_data_t::iterator itSect = m_data.find(section);
            if (itSect != m_data.end()) {
                map_str_str_t::iterator itKey = itSect->second.find(key);
                if (itKey != itSect->second.end()) {
                    return itKey->second;
                }
            }
            return defaultValue;
        }

        bool sectionexists(const std::string& section) const
        {
            return m_data.find(section) != m_data.end();
        }

        bool keyexists(const std::string& section, const std::string& key) const
        {
            m_data_t::const_iterator itSection = m_data.find(section);
            if (itSection != m_data.end())
            {
                const map_str_str_t& sectionMap = itSection->second;
                return sectionMap.find(key) != sectionMap.end();
            }
            return false;
        }

        void delsection(const std::string& section)
        {
            m_data.erase(section);

            v_section_t::iterator it = std::find(m_sectionOrder.begin(), m_sectionOrder.end(), section);
            if (it != m_sectionOrder.end()) {
                m_sectionOrder.erase(it);
            }

            m_keyOrder.erase(section);
        }

        void delkey(const std::string& section, const std::string& key)
        {
            m_data_t::iterator itSection = m_data.find(section);
            if (itSection != m_data.end()) {
                itSection->second.erase(key);
            }

            m_key_t::iterator itKeyOrder = m_keyOrder.find(section);
            if (itKeyOrder != m_keyOrder.end())
            {
                v_section_t& keys = itKeyOrder->second;
                v_section_t::iterator it = std::find(keys.begin(), keys.end(), key);
                if (it != keys.end()) {
                    keys.erase(it);
                }
            }
        }

    private:
        bool parse(const std::string& content)
        {
            std::stringstream ss(content);
            std::string line;
            std::string currentSection;

            while (std::getline(ss, line))
            {
                trim(line);
                if (line.empty() || line[0] == ';' || line[0] == '#') continue;

                if (line[0] == '[' && line[line.length() - 1] == ']') {
                    currentSection = line.substr(1, line.length() - 2);
                    trim(currentSection);
                } else {
                    size_t pos = line.find('=');
                    if (pos != std::string::npos) {
                        std::string key = line.substr(0, pos);
                        std::string value = line.substr(pos + 1);
                        trim(key);
                        trim(value);

                        setvalue(currentSection, key, value);
                    }
                }
            }
            return true;
        }

        static void trim(std::string& s)
        {
            static const char* spaces = " \t\r\n";
            size_t first = s.find_first_not_of(spaces);
            if (first == std::string::npos) {
                s.clear();
                return;
            }
            size_t last = s.find_last_not_of(spaces);
            s = s.substr(first, (last - first + 1));
        }

        m_data_t m_data;
        v_section_t m_sectionOrder;
        m_key_t m_keyOrder;

        std::wstring m_file; // Updated to wstring
    };

    inline std::string tostra(const WCHAR* wstr)
    {
        if (!wstr || !wstr[0]) return std::string("");

        // 1. Calculate the required buffer size
        int size_needed = WideCharToMultiByte(CP_ACP, 0, wstr, -1,
                                              NULL, 0, NULL, NULL);

        if (size_needed <= 0) return std::string("");

        // 2. Allocate buffer
        std::vector<char> buffer(size_needed);

        // 3. Perform the actual conversion
        WideCharToMultiByte(CP_ACP, 0, wstr, -1, &buffer[0],
                            size_needed, NULL, NULL);

        // 4. Convert to std::string (size_needed includes null terminator, so we subtract 1)
        return std::string(&buffer[0], size_needed - 1);
    }

    inline std::wstring tostrw(const char* str)
    {
        if (!str || !str[0]) return std::wstring(L"");

        // 1. Calculate the required buffer size (in wide characters)
        // CP_ACP uses the current system ANSI code page
        int size_needed = MultiByteToWideChar(CP_ACP, 0, str, -1,
                                              NULL, 0);

        if (size_needed <= 0) return std::wstring(L"");

        // 2. Allocate buffer for wide characters
        std::vector<wchar_t> buffer(size_needed);

        // 3. Perform the actual conversion
        MultiByteToWideChar(CP_ACP, 0, str, -1, &buffer[0],
                            size_needed);

        // 4. Convert to std::wstring
        // size_needed includes the null terminator, so we subtract 1 for the string object
        return std::wstring(&buffer[0], size_needed - 1);
    }

    class filechk {
    private:
        std::string  m_sName;
        std::wstring m_wsName;
        bool m_isWide;

    public:
        // Constructor for standard strings
        filechk(const std::string& filename) : m_sName(filename), m_isWide(false)
        {}

        // Constructor for wide strings (L"")
        filechk(const std::wstring& filename) : m_wsName(filename), m_isWide(true)
        {}

        bool exists() const
        {
            if (m_isWide)
            {
                // VS2005 wifstream accepts const wchar_t*
                std::wifstream fileStream(m_wsName.c_str());
                return fileStream.good();
            }
            else
            {
                std::ifstream fileStream(m_sName.c_str());
                return fileStream.good();
            }
        }
    };

    template<typename Signature>
    class function;

    template<typename R, typename T1>
    class function<R(T1)> {
    private:
        typedef R (*FuncPtr)(T1);
        FuncPtr func_ptr;

    public:
        function() : func_ptr(NULL) {}
        function(FuncPtr ptr) : func_ptr(ptr) {}

        R operator()(T1 arg) {
            if (func_ptr) return func_ptr(arg);
            return R();
        }
    };
}

inline ULONGLONG GetTickCount64()
{
    static LARGE_INTEGER frequency = { 0 };
    static BOOL hasQPC = -1; // -1 means uninitialized

    // Initialize frequency only once
    if (hasQPC == -1) {
        hasQPC = QueryPerformanceFrequency(&frequency);
    }

    if (!hasQPC) {
        return (ULONGLONG)GetTickCount();
    }

    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);

    // Optimized math to prevent overflow:
    // (Ticks / Frequency) * 1000 + ((Ticks % Frequency) * 1000) / Frequency
    return (ULONGLONG)((count.QuadPart / frequency.QuadPart) * 1000 +
                       ((count.QuadPart % frequency.QuadPart) * 1000) / frequency.QuadPart);
}

#endif
