#include "All_Windows.h"
#include "Styles/custom_styles.h"

void ImGui::Test_Window(bool* p_open)
{
    Begin("BIT FLAG TEST", p_open);

    ELogLevel testVerboseBit = Verbose;
    ELogLevel testInfoBit = Info;
    ELogLevel testWarningBit = Warning;
    ELogLevel testErrorBit = Error;

    Text("Verbose Bit == %d", testVerboseBit);
    Text("Info Bit == %d", testInfoBit);
    Text("Warning Bit == %d", testWarningBit);
    Text("Error Bit == %d", testErrorBit);

    SeparatorText("\"Has Flag\" Test");
    Text("Verbose Bit has Verbose? == %d", has_flag((uMint*)&testVerboseBit, Verbose));
    Text("Verbose Bit has Info Bit == %d", has_flag((uMint*)&testVerboseBit, Info));
    Text("Warning Bit has Warning Bit == %d", has_flag((uMint*)&testWarningBit, Warning));
    Text("Warning Bit has Verbose Bit == %d", has_flag((uMint*)&testWarningBit, Verbose));

    SeparatorText("\"Has Any Flag\" Test");
    Text("Verbose Bit has Verbose? == %d", has_any_flags((uMint*)&testVerboseBit, Verbose));
    Text("Verbose Bit has Verbose and Info Bit == %d", has_any_flags((uMint*)&testVerboseBit, (Verbose || Info)));
    Text("Verbose Bit has Warning and Info Bit == %d", has_any_flags((uMint*)&testWarningBit, (Warning || Info)));

    SeparatorText("\"Set Flag\" Test");
    Text("Verbose is %d", testVerboseBit);
    Text("Verbose is now also Warning too!");
    add_flag((uMint*)&testVerboseBit, Warning);
    Text("Verbose is %d", testVerboseBit);
    Text("Verbose is now JUST Verbose again!");
    remove_flag((uMint*)&testVerboseBit, Warning);
    Text("Verbose is %d", testVerboseBit);
    Text("Verbose Bit has Warning and Info Bit == %d", has_any_flags((uMint*)&testWarningBit, (Warning || Info)));

    SeparatorText("\"Flip Flag\" Test");
    Text("Error is %d", testErrorBit);
    Text("Adding Warning");
    add_flag((uMint*)&testErrorBit, Warning);
    Text("Error is %d", testErrorBit);
    Text("Flipping Just Error...");
    flip_flag((uMint*)&testErrorBit, Error);
    Text("Error is %d", testErrorBit);
    Text("Hello :)");

    End();
}
