#include "settingsmanager.h"

#include <QAudioDeviceInfo>

#include "common.h"
#include "lib/qtmaterialtheme.h"
#include "qtmaterialscrollbar.h"
#include "qtmaterialtextfield.h"
#include "ui_settingsmanager.h"

SettingsManager::SettingsManager(QWidget* parent)
    : QWidget(parent), ui(new Ui::SettingsManager)
{
    ui->setupUi(this);
    this->setMaximumWidth(600);
    this->setMinimumWidth(600);

    this->settings = new Settings;
    this->loadSettings(this->settings);

    this->scanAudioInputDevices();

    // Set up Audio settings
    ui->pbMicrophoneBar->setProgressType(Material::DeterminateProgress);
    ui->pbMicrophoneBar->setValue(30);

    // Set up library settings
    ui->mtfLibraryPath->setLabel("Library Path");

    // Style settings
    common::cardStyle(this, ui->developerSettings);
    common::cardStyle(this, ui->audioSettings);
    common::cardStyle(this, ui->librarySettings);
    QtMaterialScrollBar* scrollBar = new QtMaterialScrollBar(ui->saSettings);
    scrollBar->setSliderColor(QColor(DARKSKY));
    scrollBar->setHideOnMouseOut(false);
    ui->saSettings->setVerticalScrollBar(scrollBar);
    ui->mtfLibraryPath->setInkColor(QColor(DARKSKY));
    ui->pbMicrophoneBar->setProgressColor(QColor(DARKSKY));
}

SettingsManager::~SettingsManager() {}

void SettingsManager::loadSettings(Settings* s) {}

void SettingsManager::resetDefault() {}

void SettingsManager::settingsClicked() 
{

}

void SettingsManager::scanAudioInputDevices()
{
    const auto deviceInfos =
        QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    for (const QAudioDeviceInfo& deviceInfo : deviceInfos)
        ui->cbMicrophone->addItem(deviceInfo.deviceName());
}