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

void Torch::set(bool torchOn, bool stroboOn, int level, int interval)
{
    if (stroboOn)
    {
        strobotimer->setInterval(interval);
        strobotimer->start();
    }
    else
    {
        strobotimer->stop();
        strobostate = false;
    }

    if (torchOn)
    {
        p_brightness(level);
    }
    else
    {
        p_brightness(0);
    }

    if (level > 0 )
    {
        lastBrightness = level;
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
