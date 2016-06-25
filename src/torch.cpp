#include "torch.h"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>

Torch::Torch(QObject *parent) :
    QObject(parent)
{
    m_deviceName = "";
    m_deviceSupported = false;
    m_hasBrightness = true;
    m_controlPath = "/sys/class/leds/led:flash_torch/brightness";

    checkDevice();

    strobotimer = new QTimer();
    strobotimer->setSingleShot(false);

    connect(strobotimer, SIGNAL(timeout()), this, SLOT(p_strobotimerTimeout()));

    lastBrightness = 1;
    strobostate = false;
}

void Torch::setTorchState(bool val)
{
    if(m_stroboisOn)
    {
        setStroboState(false);
    }
    
    if(!val)
    {
        p_brightness(0);
        m_torchIsOn = false;
        Q_EMIT torchStateChanged(false);
    }else
    {
        p_brightness(m_brightness);
        m_torchIsOn = true;
        Q_EMIT torchStateChanged(false);


        if(m_brightness > 0)
        {
            lastBrightness = m_brightness;
        }
    }
}

bool Torch::getTorchState()
{
    return m_torchIsOn;
}

void Torch::setStroboState(bool val)
{
    if(!val)
    {
        strobotimer->stop();
        m_stroboisOn = false;
        p_brightness(0);
        Q_EMIT stroboStateChanged(false);
    }
    else
    {
        strobotimer->setInterval(m_interval);
        strobotimer->start();
        m_stroboisOn = true;
        Q_EMIT stroboStateChanged(true);

        if(m_brightness > 0)
        {
            lastBrightness = m_brightness;
        }
    }
}

bool Torch::getStroboState()
{
    return m_stroboisOn;
}

void Torch::setHasBrightness(bool has)
{
    m_hasBrightness = has;
}

bool Torch::getHasBrightness()
{
    return m_hasBrightness;
}

bool Torch::getDeviceSupported()
{
    return m_deviceSupported;
}

void Torch::setDeviceSupported(bool supported)
{
    m_deviceSupported = supported;
}

QString Torch::getDeviceName()
{
    return m_deviceName;
}

void Torch::setDeviceName(QString name)
{
    m_deviceName = name;
}

void Torch::setBrightness(int val)
{
    m_brightness = val;
    if(this->getStroboState())
    {
        setStroboState(true);
    }
    if(this->getTorchState())
    {
        setTorchState(true);
    }

}

void Torch::setIntervall(int val)
{
    m_interval = val;
    if(this->getStroboState())
    {
        setStroboState(true);
    }
}

void Torch::p_strobotimerTimeout()
{
    strobostate = !strobostate;
    p_brightness( strobostate ? lastBrightness : 0);
}

void Torch::p_brightness(int level)
{
    int fd = open(m_controlPath.toLocal8Bit().constData(), O_WRONLY);
    int tmp;
    Q_UNUSED(tmp)

    if (!(fd < 0))
    {
        if (level != lastBrightness && level > 0)
        {
            tmp = write (fd, "0", 1);
            QThread::msleep(10);
        }
        tmp = write (fd, QString("%1").arg(level).toLocal8Bit().constData(), QString("%1").arg(level).length());
        close(fd);
    }
    QThread::msleep(10);
}

void Torch::checkDevice()
{
    int res = false;

    if (!QDBusConnection::systemBus().isConnected())
    {
        qDebug() << "Cannot connect to the D-Bus systemBus" << QDBusConnection::systemBus().lastError().message();
        return;
    }


    QDBusInterface ssuCall("org.nemo.ssu", "/org/nemo/ssu", "org.nemo.ssu", QDBusConnection::systemBus());
    ssuCall.setTimeout(1000);

    QList<QVariant> args;
    args.append(2);

    QDBusMessage ssuCallReply = ssuCall.callWithArgumentList(QDBus::Block, "displayName", args);

    if (ssuCallReply.type() == QDBusMessage::ErrorMessage)
    {
        qDebug() << "Error" << ssuCallReply.errorMessage();
        return;
    }

    QList<QVariant> outArgs = ssuCallReply.arguments();
    if (outArgs.count() == 0)
    {
        qDebug() << "Reply is epmty";
        return;
    }

    qDebug() << "device name is" << outArgs.at(0).toString();

    m_deviceName = outArgs.at(0).toString();

    if (m_deviceName == "JP-1301") /* The one and only original Jolla phone */
    {
        m_hasBrightness = false;
        m_controlPath = "/sys/kernel/debug/flash_adp1650/mode";

        res = true;
    }
    else if (m_deviceName == "onyx") /* OneplusX */
    {
        m_hasBrightness = true;
        m_controlPath = "/sys/class/leds/led:flash_torch/brightness";

        res = true;
    }
    else if (m_deviceName == "fp2-sibon")
    {
        m_hasBrightness = true;
        m_controlPath = "/sys/class/leds/led:flash_torch/brightness";

        res = true;
    }

    emit deviceNameChanged(m_deviceName);

    m_deviceSupported = res;
    emit deviceSupportedChanged(m_deviceSupported);

    emit hasBrightnessChanged(m_hasBrightness);
}
