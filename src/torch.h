#ifndef TORCH_H
#define TORCH_H

#include <QObject>
#include <QTimer>
#include <QThread>

class Torch : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int brightness MEMBER m_brightness WRITE setBrightness NOTIFY brightnessChanged)
    Q_PROPERTY(int interval MEMBER m_interval WRITE setIntervall NOTIFY intervalChanged)
    Q_PROPERTY(bool torchState READ getTorchState WRITE setTorchState NOTIFY torchStateChanged)
    Q_PROPERTY(bool stroboState READ getStroboState WRITE setStroboState NOTIFY stroboStateChanged)
public:
    explicit Torch(QObject *parent = 0);

    void setTorchState(bool);
    bool getTorchState();
    void setStroboState(bool);
    bool getStroboState();
    void setBrightness(int);
    void setIntervall(int);

signals:
    void brightnessChanged(int nBrightness);
    void intervalChanged(int nInterval);
    void stroboStateChanged(bool state);
    void torchStateChanged(bool state);

private slots:
    void p_strobotimerTimeout();

private:
    void p_brightness(int level);
    bool m_torchIsOn;
    int m_interval;
    bool m_stroboisOn;
    int m_brightness;


    QTimer *strobotimer;
    bool strobostate;
    int lastBrightness;
};

#endif // TORCH_H
