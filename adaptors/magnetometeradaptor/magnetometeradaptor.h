/**
   @file magnetometeradaptor.h
   @brief MagnetometerAdaptor

   <p>
   Copyright (C) 2009-2010 Nokia Corporation

   @author Timo Rongas <ext-timo.2.rongas@nokia.com>
   @author Ustun Ergenoglu <ext-ustun.ergenoglu@nokia.com>
   @author Antti Virtanen <antti.i.virtanen@nokia.com>

   This file is part of Sensord.

   Sensord is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 2.1 as published by the Free Software Foundation.

   Sensord is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with Sensord.  If not, see <http://www.gnu.org/licenses/>.
   </p>
*/

#ifndef MAGNETOMETERADAPTOR_H
#define MAGNETOMETERADAPTOR_H

#include "sysfsadaptor.h"
#include "deviceadaptorringbuffer.h"
#include "datatypes/genericdata.h"
#include <QString>
#include "datatypes/orientationdata.h"

/**
 * @brief Adaptor for internal magnetometer.
 *
 * Uses Input Device system as driver interface. Measures values from the magnetometer
 * with sysfsadaptor IntervalMode.
 */
class MagnetometerAdaptor : public SysfsAdaptor
{
    Q_OBJECT;
public:

    Q_PROPERTY(int overflowLimit READ overflowLimit WRITE setOverflowLimit);

    /**
     * Factory method for gaining a new instance of MagnetometerAdaptor class.
     * @param id Identifier for the adaptor.
     */
    static DeviceAdaptor* factoryMethod(const QString& id)
    {
        return new MagnetometerAdaptor(id);
    }

protected:
    /**
     * Constructor.
     * @param id Identifier for the adaptor.
     */
    MagnetometerAdaptor(const QString& id);
    ~MagnetometerAdaptor();

    bool setInterval(const int sessionId, const unsigned int interval_us);

private:

    /**
     * Read and process data. Run when sysfsadaptor has detected new available
     * data.
     * @param pathId PathId for the file that had event. Always 0, as we monitor
     *               only single file and don't set any proper id.
     * @param fd     Open file descriptor with new data. See #SysfsAdaptor::processSample()
     */
    void processSample(int pathId, int fd);

    /**
     * Sets the overflow limit of the sensor, checked when calibrated
     *
     * @param limit overflow limit.
     */
    void setOverflowLimit(int limit);

    /**
     * Get the overflow limit.
     *
     * @return overflow limit.
     */
    int overflowLimit() const;

    DeviceAdaptorRingBuffer<CalibratedMagneticFieldData> *m_magnetometerBuffer;
    int m_intervalCompensation_us;
    int m_overflowLimit;
};

#endif
