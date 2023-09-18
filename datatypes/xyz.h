/**
   @file xyz.h
   @brief QObject based datatype for TimedXYZData

   <p>
   Copyright (C) 2009-2010 Nokia Corporation

   @author Joep van Gassel <joep.van.gassel@nokia.com>
   @author Timo Rongas <ext-timo.2.rongas@nokia.com>

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

#ifndef XYZ_H
#define XYZ_H

#include <math.h>

#include <QDBusArgument>
#include <datatypes/orientationdata.h>

/**
 * QObject facade for #XYZData.
 */
class XYZ : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int x READ x)
    Q_PROPERTY(int y READ y)
    Q_PROPERTY(int z READ z)

public:

    /**
     * Default constructor.
     */
    XYZ() {}

    /**
     * Copy constructor.
     *
     * @param xyzData Source object.
     */
    XYZ(const TimedXyzData& xyzData);

    /**
     * Copy constructor.
     *
     * @param xyz Source object.
     */
    XYZ(const XYZ& xyz);

    /**
     * Returns the contained #XYZData
     * @return Contained TimedXYZData
     */
    const TimedXyzData& XYZData() const { return data_; }

    /**
     * Returns the value for X.
     * @return x value.
     */
    float x() const { return data_.x_; }

    /**
     * Returns the value for Y.
     * @return y value.
     */
    float y() const { return data_.y_; }

    /**
     * Returns the value for Z.
     * @return z value.
     */
    float z() const { return data_.z_; }

    /**
     * Assignment operator.
     *
     * @param origin Source object for assigment.
     */
    XYZ& operator=(const XYZ& origin)
    {
        data_ = origin.XYZData();
        return *this;
    }

private:
    TimedXyzData data_; /**< Contained data. */

    friend const QDBusArgument &operator>>(const QDBusArgument &argument, XYZ& xyz);
};

Q_DECLARE_METATYPE( XYZ )

/**
 * Marshall the XYZ data into a D-Bus argument
 *
 * @param argument dbus argument.
 * @param xyz data to marshall.
 * @return dbus argument.
 */
inline QDBusArgument &operator<<(QDBusArgument &argument, const XYZ &xyz)
{
    // No floats on D-Bus: Implicit float to double conversion
    argument.beginStructure();
    argument << xyz.XYZData().timestamp_ << xyz.XYZData().x_ << xyz.XYZData().y_ << xyz.XYZData().z_;
    argument.endStructure();
    return argument;
}

/**
 * Unmarshall XYZ data from the D-Bus argument
 *
 * @param argument dbus argument.
 * @param xyz unmarshalled data.
 * @return dbus argument.
 */
inline const QDBusArgument &operator>>(const QDBusArgument &argument, XYZ &xyz)
{
    // No floats on D-Bus: Explicit double to float conversion
    argument.beginStructure();
    double x, y, z;
    argument >> xyz.data_.timestamp_ >> x >> y >> z;
    xyz.data_.x_ = float(x);
    xyz.data_.y_ = float(y);
    xyz.data_.z_ = float(z);
    argument.endStructure();
    return argument;
}

#endif // XYZ_H
