#include "plugin.h"

static bool cbCommand(int argc, char* argv[])
{
    using namespace Script;

    BridgeList<Module::ModuleInfo> modules;
    if(!Module::GetList(&modules))
    {
        _plugin_logputs("Module::GetList failed...");
        return false;
    }

    char addr[32] = "";
    auto ptr2str = [&addr](duint ptr)
    {
        sprintf_s(addr, "%p", ptr);
        return addr;
    };

    GuiReferenceInitialize("Modules");
    GuiReferenceAddColumn(sizeof(duint) * 2, "Base");
    GuiReferenceAddColumn(sizeof(duint) * 2, "Size");
    GuiReferenceAddColumn(sizeof(duint) * 2, "Entry");
    GuiReferenceAddColumn(0, "Path");
    GuiReferenceSetRowCount(int(modules.Count()));

    for(int i = 0; i < modules.Count(); i++)
    {
        auto & mod = modules[i];
        GuiReferenceSetCellContent(i, 0, ptr2str(mod.base));
        GuiReferenceSetCellContent(i, 1, ptr2str(mod.size));
        GuiReferenceSetCellContent(i, 2, ptr2str(mod.entry));
        GuiReferenceSetCellContent(i, 3, mod.path);
    }
    GuiReferenceReloadData();

    return true;
}

//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    if(!_plugin_registercommand(pluginHandle, PLUGIN_NAME, cbCommand, false))
        _plugin_logputs("[" PLUGIN_NAME "] Error registering the \"" PLUGIN_NAME "\" command!");
    return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here (clearing menus optional).
bool pluginStop()
{
    return true;
}

//Do GUI/Menu related things here.
void pluginSetup()
{
}
