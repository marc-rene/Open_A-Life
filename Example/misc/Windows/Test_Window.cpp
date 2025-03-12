#include "All_Windows.h"
#include "Styles/custom_styles.h"

void ImGui::Test_Window(bool* p_open)
{
    ImGui::Begin("BIT FLAG TEST", p_open);

    ELogLevel testVerboseBit = ELogLevel::Verbose;
    ELogLevel testInfoBit = ELogLevel::Info;
    ELogLevel testWarningBit = ELogLevel::Warning;
    ELogLevel testErrorBit = ELogLevel::Error;

    ImGui::Text("Verbose Bit == %d", testVerboseBit);
    ImGui::Text("Info Bit == %d", testInfoBit);
    ImGui::Text("Warning Bit == %d", testWarningBit);
    ImGui::Text("Error Bit == %d", testErrorBit);

    ImGui::SeparatorText("\"Has Flag\" Test");
    ImGui::Text("Verbose Bit has Verbose? == %d", has_flag((uMint*)&testVerboseBit, ELogLevel::Verbose));
    ImGui::Text("Verbose Bit has Info Bit == %d", has_flag((uMint*)&testVerboseBit, ELogLevel::Info));
    ImGui::Text("Warning Bit has Warning Bit == %d", has_flag((uMint*)&testWarningBit, ELogLevel::Warning));
    ImGui::Text("Warning Bit has Verbose Bit == %d", has_flag((uMint*)&testWarningBit, ELogLevel::Verbose));

    ImGui::SeparatorText("\"Has Any Flag\" Test");
    ImGui::Text("Verbose Bit has Verbose? == %d", has_any_flags((uMint*)&testVerboseBit, ELogLevel::Verbose));
    ImGui::Text("Verbose Bit has Verbose and Info Bit == %d", has_any_flags((uMint*)&testVerboseBit, (ELogLevel::Verbose || ELogLevel::Info)));
    ImGui::Text("Verbose Bit has Warning and Info Bit == %d", has_any_flags((uMint*)&testWarningBit, (ELogLevel::Warning || ELogLevel::Info)));

    ImGui::SeparatorText("\"Set Flag\" Test");
    ImGui::Text("Verbose is %d", testVerboseBit);
    ImGui::Text("Verbose is now also Warning too!");
    add_flag((uMint*)&testVerboseBit, ELogLevel::Warning);
    ImGui::Text("Verbose is %d", testVerboseBit);
    ImGui::Text("Verbose is now JUST Verbose again!");
    remove_flag((uMint*)&testVerboseBit, ELogLevel::Warning);
    ImGui::Text("Verbose is %d", testVerboseBit);
    ImGui::Text("Verbose Bit has Warning and Info Bit == %d", has_any_flags((uMint*)&testWarningBit, (ELogLevel::Warning || ELogLevel::Info)));

    ImGui::SeparatorText("\"Flip Flag\" Test");
    ImGui::Text("Error is %d", testErrorBit);
    ImGui::Text("Adding Warning");
    add_flag((uMint*)&testErrorBit, ELogLevel::Warning);
    ImGui::Text("Error is %d", testErrorBit);
    ImGui::Text("Flipping Just Error...");
    flip_flag((uMint*)&testErrorBit, ELogLevel::Error);
    ImGui::Text("Error is %d", testErrorBit);
    ImGui::Text("Hello :)");

    ImGui::End();
} 