#include "oemtabletalsadaptor-asciiplugin.h"
#include "oemtabletalsadaptor-ascii.h"
#include "sensormanager.h"

void OEMTabletALSAdaptorAsciiPlugin::Register(class Loader&)
{
    sensordLogW() << id() << "registering oemtabletalsadaptor-ascii";
    SensorManager& sm = SensorManager::instance();
    sm.registerDeviceAdaptor<OEMTabletALSAdaptorAscii>("alsadaptor");
}
