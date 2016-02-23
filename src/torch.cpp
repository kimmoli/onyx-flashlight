#include "torch.h"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

Torch::Torch(QObject *parent) :
    QObject(parent)
{

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
    int fd = open("/sys/class/leds/led:flash_torch/brightness", O_WRONLY);
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
