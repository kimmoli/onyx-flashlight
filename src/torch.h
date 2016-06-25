#ifndef TORCH_H
#define TORCH_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QDBusConnection>
#include <QDBusInterface>

class Torch : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int brightness MEMBER m_brightness WRITE setBrightness NOTIFY brightnessChanged)
    Q_PROPERTY(int interval MEMBER m_interval WRITE setIntervall NOTIFY intervalChanged)
    Q_PROPERTY(bool torchState READ getTorchState WRITE setTorchState NOTIFY torchStateChanged)
    Q_PROPERTY(bool stroboState READ getStroboState WRITE setStroboState NOTIFY stroboStateChanged)
    Q_PROPERTY(bool hasBrightness READ getHasBrightness WRITE setHasBrightness NOTIFY hasBrightnessChanged)
    Q_PROPERTY(bool deviceSupported READ getDeviceSupported WRITE setDeviceSupported NOTIFY deviceSupportedChanged)
    Q_PROPERTY(QString deviceName READ getDeviceName WRITE setDeviceName NOTIFY deviceNameChanged)

public:
    explicit Torch(QObject *parent = 0);

    void setTorchState(bool);
    bool getTorchState();
    void setStroboState(bool);
    bool getStroboState();
    void setBrightness(int);
    void setIntervall(int);
    bool getHasBrightness();
    void setHasBrightness(bool);
    QString getDeviceName();
    void setDeviceName(QString);
    bool getDeviceSupported();
    void setDeviceSupported(bool);

    void checkDevice();

signals:
    void brightnessChanged(int nBrightness);
    void intervalChanged(int nInterval);
    void stroboStateChanged(bool state);
    void torchStateChanged(bool state);
    void hasBrightnessChanged(bool state);
    void deviceSupportedChanged(bool state);
    void deviceNameChanged(QString name);

private slots:
    void p_strobotimerTimeout();

private:
    void p_brightness(int level);
    bool m_torchIsOn;
    int m_interval;
    bool m_stroboisOn;
    int m_brightness;
    bool m_hasBrightness;
    QString m_controlPath;

    QTimer *strobotimer;
    bool strobostate;
    int lastBrightness;

    bool m_deviceSupported;
    QString m_deviceName;
};

#endif // TORCH_H
