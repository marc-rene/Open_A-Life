#include "All_Windows.h"
#include "Styles/custom_styles.h"


struct ConsoleLogger
{
    char                  InputBuf[256];
    ImVector<char*>       Items;
    ImVector<const char*> Commands;
    ImVector<char*>       History;
    int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter       Filter;
    bool                  AutoScroll;
    bool                  ScrollToBottom;
    int                   LogLevel; // 0:Verbose, 1:Info, 2:Warning, 3:Error

    ConsoleLogger()
    {
        ClearLog();
        memset(InputBuf, 0, sizeof(InputBuf));
        HistoryPos = -1;

        // "CLASSIFY" is here to provide the test case where "C"+[tab] completes to "CL" and display multiple matches.
        Commands.push_back("HELP");
        Commands.push_back("HISTORY");
        Commands.push_back("CLEAR");
        Commands.push_back("CLASSIFY");
        AutoScroll = true;
        ScrollToBottom = false;
        //AddLog("Welcome to Dear ImGui!");
    }
    ~ConsoleLogger()
    {
        ClearLog();
        for (int i = 0; i < History.Size; i++)
            ImGui::MemFree(History[i]);
    }

    // Portable helpers
    static int   Stricmp(const char* s1, const char* s2) { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
    static int   Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
    static char* Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = ImGui::MemAlloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
    static void  Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

    void    ClearLog()
    {
        for (int i = 0; i < Items.Size; i++)
            ImGui::MemFree(Items[i]);
        Items.clear();
    }
    

    void    AddLog(ELogLevel verbosity_level, const char* fmt, va_list args) IM_FMTARGS(2)
    {
        char buf[1024] = "";
        static std::string precede;

        switch (verbosity_level)
        {
        case Verbose:
            precede = "\t[-]\t";
            break;

        case Info:
            precede = "\t[+]\t";
            break;

        case Warning:
            precede = "\t[!!!]\t";
            break;

        case Error:
            precede = " [ERROR]\t ";
            break;

        default:
            break;
        }

        precede.append(fmt);
        const char* tempStr = precede.c_str();
        vsnprintf(buf, IM_ARRAYSIZE(buf), tempStr, args);
        buf[IM_ARRAYSIZE(buf) - 1] = 0;
        va_end(args);
        Items.push_back(Strdup(buf));
    }

  

    void    Draw(const char* title, bool* p_open)
    {   
        //ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin(title, p_open))
        {
            ImGui::End();
            return;
        }

        // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar.
        // So e.g. IsItemHovered() will return true when hovering the title bar.
        // Here we create a context menu only available from the title bar.
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Close Console"))
                *p_open = false;
            ImGui::EndPopup();
        }

        // TODO: display items starting from the bottom

        ImGui::PushItemWidth(100.0f);
        ImGui::Combo("Log Level", &LogLevel, "Verbose\0Normal\0Warning\0Errors\0[Debug all]\0");
        ImGui::PopItemWidth();
        
        ImGui::SameLine();
        if (ImGui::SmallButton("Clear")) { ClearLog(); }
        ImGui::SameLine();
        bool copy_to_clipboard = ImGui::SmallButton("Copy");
        
        ImGui::SameLine();
        Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
        ImGui::Separator();

        // Reserve enough left-over height for 1 separator + 1 input text
        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_HorizontalScrollbar))
        {
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::Selectable("Clear")) ClearLog();
                ImGui::EndPopup();
            }

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
            if (copy_to_clipboard)
                ImGui::LogToClipboard();
            for (const char* item : Items)
            {
                if (!Filter.PassFilter(item))
                    continue;

                // Normally you would store more information in your item than just a string.
                // (e.g. make Items[] an array of structure, store color/type etc.)
                ImVec4 color;
                bool has_color = false;

                switch (LogLevel)
                {
                case 0: // -Verbose
                    if (strstr(item, "[-]")) { break; }
                    [[fallthrough]];
                case 1: // -Info
                    if (strstr(item, "[+]")) { 
                        color = WarningColour; 
                        has_color = true; 
                        break;
                    }
                    [[fallthrough]];
                case 2: // -Warning
                    if (strstr(item, "[!!!]")) {
                        color = DangerColour;
                        has_color = true;
                        break;
                    }
                    [[fallthrough]];
                case 3: // -Error
                    if (strstr(item, "[ERROR]")) {
                        color = Accent; color.w = 1.0f;
                        has_color = true;
                        break;
                    }
                    [[fallthrough]];
                case 4:
                    if (LogLevel == 4) {
                        break;
                    }
                    [[fallthrough]];
                default:
                    continue;
                    break;
                }
                
                if (has_color)
                    ImGui::PushStyleColor(ImGuiCol_Text, color);
                ImGui::TextUnformatted(item);
                if (has_color)
                    ImGui::PopStyleColor();
            }
            if (copy_to_clipboard)
                ImGui::LogFinish();

            // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
            // Using a scrollbar or mouse-wheel will take away from the bottom edge.
            if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
                ImGui::SetScrollHereY(1.0f);
            ScrollToBottom = false;

            ImGui::PopStyleVar();
        }
        ImGui::EndChild();
        ImGui::Separator();

        
        ImGui::End();
    }
};
// TODO: FIX THIS REDEFINITION MADNESS!
static ConsoleLogger* consolePtr;
/*
void ALIFE_CoreObject::Log(ELogLevel verbosity_level, const char* fmt, va_list args)
{
    std::string new_fmt;
    try
    {
        new_fmt = std::format("{} :\t\t", Name);
    }
    catch (const std::exception&)
    {
        printf("\n\tERROR: Huge error parsing %s", fmt);
        new_fmt = Name;
    }
    new_fmt.append(fmt);
    
    if (ReadyToLog)
    {
        if (ClearingBackLog == false && BackLoggedLogs.size() > 0)
        {
            RetrieveLogBacklog();
        }
        consolePtr->AddLog(verbosity_level, new_fmt.c_str(), args);
    }
    
    else
    {
        char bLogStr[512];
        vsnprintf(bLogStr, 512, new_fmt.c_str(), args);
        BackLoggedLogs.push_back(bLogStr);
    }
    return;
}

*/
void ImGui::Core_Window(A_LIFE::ALIFE_SCENARIO* core) {
    
    static ConsoleLogger console;
    static bool stayopen = true;
    consolePtr = &console;
        
    core->SetReadyToLog(true);

    console.Draw("Core Logger", &stayopen);

    
}
