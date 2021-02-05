#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <qobjectdefs.h>

#include <QWidget>

#include "common.h"
#include "qtmaterialtextfield.h"
#include "ui_settingsmanager.h"

namespace ui
{
class SettingsManager;
}
QT_END_NAMESPACE

class SettingsManager : public QWidget
{
    Q_OBJECT
public:
    SettingsManager(QWidget* parent = nullptr);
    ~SettingsManager();

    void loadSettings(Settings*);
    void resetDefault();

public slots:
    void settingsClicked();

private:
    void scanAudioInputDevices();

    Ui::SettingsManager* ui;
    Settings* settings;

    // library settings
    // audio settings
    // developer options
};

#endif