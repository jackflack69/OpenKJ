/*
 * Copyright (c) 2013-2014 Thomas Isaac Lightburn
 *
 *
 * This file is part of OpenKJ.
 *
 * OpenKJ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QList>
#include <khsettings.h>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    
    void createIcons();
private slots:

    void on_btnClose_clicked();

    void on_checkBoxShowCdgWindow_stateChanged(int arg1);

    void on_groupBoxMonitors_toggled(bool arg1);

    void on_listWidgetMonitors_itemSelectionChanged();

    void on_pushButtonFont_clicked();

    void on_spinBoxTickerHeight_valueChanged(int arg1);

    void on_horizontalSliderTickerSpeed_valueChanged(int value);

    void on_pushButtonTextColor_clicked();

    void on_pushButtonBgColor_clicked();

    void on_radioButtonFullRotation_toggled(bool checked);

    void on_spinBoxTickerSingers_valueChanged(int arg1);

    void on_groupBoxTicker_toggled(bool arg1);

signals:
    void showCdgWindowChanged(bool);
    void cdgWindowFullScreenChanged(bool);
    void cdgWindowFullScreenMonitorChanged(int);

private:
    Ui::SettingsDialog *ui;
    QStringList getMonitors();
//    KhSettings *settings;
};

#endif // SETTINGSDIALOG_H
