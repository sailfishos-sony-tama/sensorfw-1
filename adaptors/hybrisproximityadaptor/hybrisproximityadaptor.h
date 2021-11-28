/****************************************************************************
**
** Copyright (C) 2013 Jolla Ltd
**
**
** $QT_BEGIN_LICENSE:LGPL$
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef HYBRISPROXIMITYADAPTOR_H
#define HYBRISPROXIMITYADAPTOR_H
#include "hybrisadaptor.h"

#include <QString>
#include <QStringList>
#include <linux/input.h>
#include "deviceadaptorringbuffer.h"
#include "datatypes/orientationdata.h"
#include <QTime>


/**
 * @brief Adaptor for hybris proximity sensor.
 *
 * Adaptor for proximity. Uses hybris sensor daemon driver interface.
 *
 * Value output frequency depends on driver decision - only changed values
 * are pushed out of driver.
 */
class HybrisProximityAdaptor : public HybrisAdaptor
{
    Q_OBJECT

public:
    static DeviceAdaptor* factoryMethod(const QString& id) {
        return new HybrisProximityAdaptor(id);
    }
    HybrisProximityAdaptor(const QString& id);
    ~HybrisProximityAdaptor();

    bool startSensor();
    void stopSensor();

    void sendInitialData();

protected:
    void processSample(const sensors_event_t& data);

private:
    DeviceAdaptorRingBuffer<ProximityData>* buffer;
    int sensorType;
    int lastNearValue;
    QByteArray powerStatePath;

};
#endif
