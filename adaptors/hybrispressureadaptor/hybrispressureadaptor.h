/****************************************************************************
**
** Copyright (C) 2013 Jolla Ltd
**
** Copyright (C) 2017 Matti Lehtimäki
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

#ifndef HYBRISPRESSUREADAPTOR_H
#define HYBRISPRESSUREADAPTOR_H
#include "hybrisadaptor.h"

#include <QString>
#include <QStringList>
#include <linux/input.h>
#include "datatypes/timedunsigned.h"
#include "deviceadaptorringbuffer.h"
#include <QTime>

/**
 * @brief Adaptor for hybris pressure sensor.
 *
 * Adaptor for internal pressure sensor. Provides the amount of ambient
 * pressure detected by the device. Uses hybris sensor daemon driver interface.
 *
 * Value output frequency depends on driver decision - only changed values
 * are pushed out of driver.
 *
 */
class HybrisPressureAdaptor : public HybrisAdaptor
{
    Q_OBJECT

public:
    static DeviceAdaptor* factoryMethod(const QString& id) {
        return new HybrisPressureAdaptor(id);
    }
    HybrisPressureAdaptor(const QString& id);
    ~HybrisPressureAdaptor();

    bool startSensor();
    void stopSensor();

protected:
    void processSample(const sensors_event_t& data);

private:
    DeviceAdaptorRingBuffer<TimedUnsigned>* buffer;
    QByteArray powerStatePath;

};
#endif
