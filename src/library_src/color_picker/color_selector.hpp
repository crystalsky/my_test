/**

@author Mattia Basaglia

@section License

    Copyright (C) 2013-2015 Mattia Basaglia

    This software is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Color Widgets.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef COLOR_SELECTOR_HPP
#define COLOR_SELECTOR_HPP

#include "color_preview.hpp"
#include "color_wheel.hpp"

/**
 * Color preview that opens a color dialog
 */
class QCP_EXPORT Color_Selector : public Color_Preview
{
    Q_OBJECT
    Q_ENUMS(Update_Mode)
    Q_PROPERTY(Update_Mode updateMode READ updateMode WRITE setUpdateMode )
    Q_PROPERTY(Qt::WindowModality dialogModality READ dialogModality WRITE setDialogModality )
    Q_PROPERTY(Color_Wheel::Display_Flags wheelFlags READ wheelFlags WRITE setWheelFlags NOTIFY wheelFlagsChanged)

public:
    enum Update_Mode {
        Confirm, ///< Update color only after the dialog has been accepted
        Continuous ///< Update color as it's being modified in the dialog
    };

    explicit Color_Selector(QWidget *parent = 0);
    ~Color_Selector();

    void setUpdateMode(Update_Mode m);
    Update_Mode updateMode() const;

    Qt::WindowModality dialogModality() const;
    void setDialogModality(Qt::WindowModality m);

    Color_Wheel::Display_Flags wheelFlags() const;

signals:
    void wheelFlagsChanged(Color_Wheel::Display_Flags flags);

public slots:
    void showDialog();
    void setWheelFlags(Color_Wheel::Display_Flags flags);

private slots:
    void accept_dialog();
    void reject_dialog();
    void update_old_color(const QColor &c);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent * event);

private:
    /// Connect/Disconnect colorChanged based on Update_Mode
    void connect_dialog();

    /// Disconnect from dialog update
    void disconnect_dialog();

    class Private;
    Private * const p;
    
};

#endif // COLOR_SELECTOR_HPP
