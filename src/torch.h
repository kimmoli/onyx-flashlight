#ifndef TORCH_H
#define TORCH_H

#include <QObject>
#include <QTimer>
#include <QThread>

class Torch : public QObject
{
    Q_OBJECT
public:
    explicit Torch(QObject *parent = 0);
    Q_INVOKABLE void set(bool torchOn, bool stroboOn, int level, int interval);

private slots:
    void p_strobotimerTimeout();

private:
    void p_brightness(int level);

    QTimer *strobotimer;
    bool strobostate;
    int lastBrightness;
};

#endif // TORCH_H
