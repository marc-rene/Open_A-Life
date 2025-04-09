#include "All_Windows.h"
#include "Styles/custom_styles.h"
#include "Modules/Gossiper/Log.h"


struct ConsoleLogger
{
    char InputBuf[256];
    ImVector<std::string> Items;
    ImVector<const char*> Commands;
    ImVector<char*> History;
    int HistoryPos; // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter Filter;
    bool AutoScroll;
    bool ScrollToBottom;
    int LogLevel; // 0:Verbose, 1:Info, 2:Warning, 3:Error

    void AddLog(const spdlog::details::log_msg& msg)
    {
        // Convert msg.payload (which is an fmt::memory_buffer) into a std::string
        std::string logMessage(msg.payload.data(), msg.payload.size());

        // Store in the vector (ensure to duplicate the string to avoid dangling pointers)
        Items.push_back(logMessage);
    }
    
    ConsoleLogger()
    {
        ClearLog();
        auto callback_sink = std::make_shared<spdlog::sinks::callback_sink_mt>([this](const spdlog::details::log_msg& msg)
        {
            INFOc("PLEASE WORK CHRIST");
        });
        callback_sink->set_level(spdlog::level::trace);

        A_LIFE::A_LIFE_Log::GetLogger()->sinks().emplace_back(callback_sink);


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

    void ClearLog()
    {
        /* Clear Logs */
    }

    /*
    void AddLog(ELogLevel verbosity_level, const char* fmt, va_list args) IM_FMTARGS(2)
    {
        // This is terrible, temporary just to test window log
        spdlog::details::log_msg formatted = fmt::vformat(fmt, fmt::make_format_args(args));
        AddLog(formatted);
    }
    */
    


    void Draw(const char* title, bool* p_open)
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
        if (ImGui::SmallButton("Test Log")) {  }

        ImGui::SameLine();
        Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
        ImGui::Separator();

        // Reserve enough left-over height for 1 separator + 1 input text
        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_NavFlattened,
                              ImGuiWindowFlags_HorizontalScrollbar))
        {
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::Selectable("Clear")) ClearLog();
                ImGui::EndPopup();
            }

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
            if (copy_to_clipboard)
                ImGui::LogToClipboard();
            for (std::string item : Items)
            {
                if (!Filter.PassFilter(item.c_str()))
                    continue;

                // Normally you would store more information in your item than just a string.
                // (e.g. make Items[] an array of structure, store color/type etc.)
                ImVec4 color;
                bool has_color = false;

                switch (LogLevel)
                {
                case 0: // -Verbose
                    if (strstr(item.c_str(), "[-]")) { break; }
                    [[fallthrough]];
                case 1: // -Info
                    if (strstr(item.c_str(), "[+]"))
                    {
                        color = WarningColour;
                        has_color = true;
                        break;
                    }
                    [[fallthrough]];
                case 2: // -Warning
                    if (strstr(item.c_str(), "[!!!]"))
                    {
                        color = DangerColour;
                        has_color = true;
                        break;
                    }
                    [[fallthrough]];
                case 3: // -Error
                    if (strstr(item.c_str(), "[ERROR]"))
                    {
                        color = Accent;
                        color.w = 1.0f;
                        has_color = true;
                        break;
                    }
                    [[fallthrough]];
                case 4:
                    if (LogLevel == 4)
                    {
                        break;
                    }
                    [[fallthrough]];
                default:
                    color = Accent;
                    color.w = 1.0f;
                    has_color = true;
                    continue;
                    break;
                }

                if (has_color)
                    ImGui::PushStyleColor(ImGuiCol_Text, color);
                ImGui::TextUnformatted(item.c_str());
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

void ImGui::Core_Window(A_LIFE::ALIFE_SCENARIO* core)
{
    static ConsoleLogger console;
    static bool stayopen = true;


    console.Draw("Core Logger", &stayopen);
    
}
