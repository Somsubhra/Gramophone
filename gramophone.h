#ifndef GRAMOPHONE_H
#define GRAMOPHONE_H

#include <QMainWindow>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <phonon/videowidget.h>
#include <QList>

class QAction;
class QTableWidget;
class QLCDNumber;


class Gramophone : public QMainWindow
{
    Q_OBJECT

public:
    Gramophone();

    QSize sizeHint() const {
        return QSize(500, 300);
    }

private slots:
    void addFiles();
    void about();
    void stateChanged(Phonon::State newState, Phonon::State oldState);
    void tick(qint64 time);
    void sourceChanged(const Phonon::MediaSource &source);
    void metaStateChanged(Phonon::State newState, Phonon::State oldState);
    void aboutToFinish();
    void tableClicked(int row, int column);
    void next();
    void previous();
    void forward();
    void backward();
    void gototime();
    void play();
    void toggleTimeLCD();
    void setAspectRatio();
    void setMuted(bool mute);
    void increaseVolume();
    void decreaseVolume();


private:
    void setupActions();
    void setupMenus();
    void setupUi();

    Phonon::SeekSlider *seekSlider;
    Phonon::MediaObject *mediaObject;
    Phonon::MediaObject *metaInformationResolver;
    Phonon::AudioOutput *audioOutput;
    Phonon::VolumeSlider *volumeSlider;
    QList<Phonon::MediaSource> sources;
    Phonon::VideoWidget *videoWidget;

    QAction *stopAction;
    QAction *nextAction;
    QAction *previousAction;
    QAction *addFilesAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *forwardAction;
    QAction *backwardAction;
    QAction *gototimeAction;
    QAction *toggleAction;
    QAction *fullScreenAction;
    QAction *toggleTimeLCDAction;
    QAction *aspectRatioAutoAction;
    QAction *aspectRatioVariableAction;
    QAction *aspectRatio16_9Action;
    QAction *aspectRatio4_3Action;
    QAction *muteAction;
    QAction *increaseVolumeAction;
    QAction *decreaseVolumeAction;

    QLCDNumber *timeLcd;
    QTableWidget *musicTable;
    bool timeRemaining;
};

#endif
