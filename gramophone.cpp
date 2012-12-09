#include <QtGui>
#include "gramophone.h"

Gramophone::Gramophone()
{
    audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    videoWidget = new Phonon::VideoWidget(this);

    metaInformationResolver = new Phonon::MediaObject(this);
    mediaObject->setTickInterval(1000);

    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(metaStateChanged(Phonon::State,Phonon::State)));
    connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
            this, SLOT(sourceChanged(Phonon::MediaSource)));
    connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));

    Phonon::createPath(mediaObject, audioOutput);
    Phonon::createPath(mediaObject, videoWidget);

    setupActions();
    setupMenus();
    setupUi();
    timeLcd->display("00:00");
    timeRemaining = false;
}



void Gramophone::addFiles()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Media Files"),
                                                      QDesktopServices::storageLocation(QDesktopServices::MusicLocation));


    if (files.isEmpty())
        return;

    int index = sources.size();
    foreach (QString string, files) {
        Phonon::MediaSource source(string);

        sources.append(source);
    }
    if (!sources.isEmpty())
        metaInformationResolver->setCurrentSource(sources.at(index));

}

void Gramophone::about()
{
    QMessageBox::information(this, tr("About Gramophone"),
                             tr("Media player based on phonon.\nCopyright(c) 2012 Somsubhra."));
}

void Gramophone::stateChanged(Phonon::State newState, Phonon::State /* oldState */)
{
    switch (newState) {
    case Phonon::ErrorState:
        if (mediaObject->errorType() == Phonon::FatalError) {
            QMessageBox::warning(this, tr("Fatal Error"),
                                 mediaObject->errorString());
        } else {
            QMessageBox::warning(this, tr("Error"),
                                 mediaObject->errorString());
        }
        break;
    case Phonon::PlayingState:
        stopAction->setEnabled(true);
        nextAction->setEnabled(true);
        previousAction->setEnabled(true);
        forwardAction->setEnabled(true);
        backwardAction->setEnabled(true);
        gototimeAction->setEnabled(true);
        toggleAction->setEnabled(true);
        toggleAction->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        toggleAction->setToolTip("Pause");
        toggleAction->setText("Pause");
        break;
    case Phonon::StoppedState:
        stopAction->setEnabled(false);
        nextAction->setEnabled(true);
        previousAction->setEnabled(true);
        forwardAction->setEnabled(false);
        backwardAction->setEnabled(false);
        gototimeAction->setEnabled(false);
        toggleAction->setEnabled(true);
        toggleAction->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        toggleAction->setToolTip("Play");
        toggleAction->setText("Play");
        timeLcd->display("00:00");
        break;
    case Phonon::PausedState:
        stopAction->setEnabled(true);
        nextAction->setEnabled(true);
        previousAction->setEnabled(true);
        forwardAction->setEnabled(true);
        backwardAction->setEnabled(true);
        gototimeAction->setEnabled(true);
        toggleAction->setEnabled(true);
        toggleAction->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        toggleAction->setToolTip("Play");
        toggleAction->setText("Play");
        break;
    case Phonon::BufferingState:
        nextAction->setEnabled(true);
        previousAction->setEnabled(true);
        forwardAction->setEnabled(true);
        backwardAction->setEnabled(true);
        gototimeAction->setEnabled(true);
        break;
    default:
        ;
    }
}

void Gramophone::tick(qint64 time)
{
    if(timeRemaining){
        time = mediaObject->totalTime()-time;
    }

    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);

    timeLcd->display(displayTime.toString("mm:ss"));
}

void Gramophone::tableClicked(int row, int /* column */)
{
    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;

    mediaObject->stop();
    mediaObject->clearQueue();

    if (row >= sources.size())
        return;

    mediaObject->setCurrentSource(sources[row]);

    if (wasPlaying)
        mediaObject->play();
    else
        mediaObject->stop();
}

void Gramophone::sourceChanged(const Phonon::MediaSource &source)
{
    musicTable->selectRow(sources.indexOf(source));
    timeLcd->display("00:00");
}

void Gramophone::metaStateChanged(Phonon::State newState, Phonon::State /* oldState */)
{
    if (newState == Phonon::ErrorState) {
        QMessageBox::warning(this, tr("Error opening files"),
                             metaInformationResolver->errorString());
        while (!sources.isEmpty() &&
               !(sources.takeLast() == metaInformationResolver->currentSource())) {}  /* loop */;
        return;
    }

    if (newState != Phonon::StoppedState && newState != Phonon::PausedState)
        return;

    if (metaInformationResolver->currentSource().type() == Phonon::MediaSource::Invalid)
        return;

    QMap<QString, QString> metaData = metaInformationResolver->metaData();

    QString title = metaData.value("TITLE");
    if (title == "")
        title = metaInformationResolver->currentSource().fileName();

    QTableWidgetItem *titleItem = new QTableWidgetItem(title);
    titleItem->setFlags(titleItem->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *artistItem = new QTableWidgetItem(metaData.value("ARTIST"));
    artistItem->setFlags(artistItem->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *albumItem = new QTableWidgetItem(metaData.value("ALBUM"));
    albumItem->setFlags(albumItem->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *yearItem = new QTableWidgetItem(metaData.value("DATE"));
    yearItem->setFlags(yearItem->flags() ^ Qt::ItemIsEditable);

    int currentRow = musicTable->rowCount();
    musicTable->insertRow(currentRow);
    musicTable->setItem(currentRow, 0, titleItem);
    musicTable->setItem(currentRow, 1, artistItem);
    musicTable->setItem(currentRow, 2, albumItem);
    musicTable->setItem(currentRow, 3, yearItem);

    if (musicTable->selectedItems().isEmpty()) {
        musicTable->selectRow(0);
        mediaObject->setCurrentSource(metaInformationResolver->currentSource());
    }

    Phonon::MediaSource source = metaInformationResolver->currentSource();
    int index = sources.indexOf(metaInformationResolver->currentSource()) + 1;
    if (sources.size() > index) {
        metaInformationResolver->setCurrentSource(sources.at(index));
    }
    else {
        musicTable->resizeColumnsToContents();
        if (musicTable->columnWidth(0) > 300)
            musicTable->setColumnWidth(0, 300);
    }
}

void Gramophone::aboutToFinish()
{
    int index = sources.indexOf(mediaObject->currentSource());
    if(index < sources.size()-1){
        index++;
    }
    else{
        index = 0;
    }

    mediaObject->enqueue(sources.at(index));

}

void Gramophone::setupActions()
{

    stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
    stopAction->setShortcut(tr("Ctrl+S"));
    stopAction->setDisabled(true);

    nextAction = new QAction(style()->standardIcon(QStyle::SP_MediaSkipForward), tr("Next Media"), this);
    nextAction->setShortcut(tr("Ctrl+N"));
    nextAction->setDisabled(true);

    previousAction = new QAction(style()->standardIcon(QStyle::SP_MediaSkipBackward), tr("Previous Media"), this);
    previousAction->setShortcut(tr("Ctrl+R"));
    previousAction->setDisabled(true);

    addFilesAction = new QAction(style()->standardIcon(QStyle::SP_FileDialogStart),tr("Add &Media"), this);
    addFilesAction->setShortcut(tr("Ctrl+M"));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+A"));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setShortcut(tr("Ctrl+Q"));

    forwardAction = new QAction(style()->standardIcon(QStyle::SP_MediaSeekForward), tr("Seek Forward"), this);
    forwardAction->setShortcut(tr("Ctrl+F"));
    forwardAction->setDisabled(true);

    backwardAction = new QAction(style()->standardIcon(QStyle::SP_MediaSeekBackward), tr("Seek Backward"), this);
    backwardAction->setShortcut(tr("Ctrl+B"));
    backwardAction->setDisabled(true);

    gototimeAction = new QAction(tr("Jump to time"), this);
    gototimeAction->setShortcut(tr("Ctrl+J"));
    gototimeAction->setDisabled(true);

    toggleAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    toggleAction->setShortcut(tr("Ctrl+P"));
    toggleAction->setDisabled(true);

    toggleTimeLCDAction = new QAction(tr("Time remaining"), this);
    toggleTimeLCDAction->setShortcut(tr("Ctrl+Shift+T"));

    toggleFullScreenAction = new QAction(style()->standardIcon(QStyle::SP_DesktopIcon), tr("Full Screen"), this);
    toggleFullScreenAction->setCheckable(true);
    toggleFullScreenAction->setShortcut(tr("Ctrl+Return"));

    aspectRatioAutoAction = new QAction(tr("Auto"), this);
    aspectRatioAutoAction->setCheckable(true);

    aspectRatioVariableAction = new QAction(tr("Variable"), this);
    aspectRatioVariableAction->setCheckable(true);

    aspectRatio16_9Action = new QAction(tr("16:9"), this);
    aspectRatio16_9Action->setCheckable(true);

    aspectRatio4_3Action = new QAction(tr("4:3"), this);
    aspectRatio4_3Action->setCheckable(true);

    muteAction = new QAction(style()->standardIcon(QStyle::SP_MediaVolumeMuted), tr("Mute"), this);
    muteAction->setShortcut(tr("Ctrl+Shift+M"));
    muteAction->setCheckable(true);

    increaseVolumeAction = new QAction(tr("Increase Volume"), this);
    increaseVolumeAction->setShortcut(tr("Ctrl++"));

    decreaseVolumeAction = new QAction(tr("Decrease Volume"), this);
    decreaseVolumeAction->setShortcut(tr("Ctrl+-"));

    setVolumeAction = new QAction(style()->standardIcon(QStyle::SP_MediaVolume), tr("Set Volume"), this);
    setVolumeAction->setShortcut(tr("Ctrl+V"));

    setBrightnessAction = new QAction(tr("Set Brightness"), this);
    setBrightnessAction->setShortcut(tr("Ctrl+Shift+B"));

    setContrastAction = new QAction(tr("Set Contrast"), this);
    setContrastAction->setShortcut(tr("Ctrl+Shift+C"));

    connect(toggleFullScreenAction, SIGNAL(toggled(bool)), this, SLOT(toggleFullScreen(bool)));
    connect(toggleAction, SIGNAL(triggered()), this, SLOT(play()));
    connect(stopAction, SIGNAL(triggered()), mediaObject, SLOT(stop()));
    connect(addFilesAction, SIGNAL(triggered()), this, SLOT(addFiles()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(previousAction, SIGNAL(triggered()),this, SLOT(previous()));
    connect(nextAction, SIGNAL(triggered()), this, SLOT(next()));
    connect(forwardAction, SIGNAL(triggered()), this, SLOT(forward()));
    connect(backwardAction, SIGNAL(triggered()), this, SLOT(backward()));
    connect(gototimeAction, SIGNAL(triggered()), this, SLOT(gototime()));
    connect(toggleTimeLCDAction, SIGNAL(triggered()), this, SLOT(toggleTimeLCD()));
    connect(aspectRatioAutoAction, SIGNAL(triggered()), this, SLOT(setAspectRatio()));
    connect(aspectRatioVariableAction, SIGNAL(triggered()), this, SLOT(setAspectRatio()));
    connect(aspectRatio16_9Action, SIGNAL(triggered()), this, SLOT(setAspectRatio()));
    connect(aspectRatio4_3Action, SIGNAL(triggered()), this, SLOT(setAspectRatio()));
    connect(muteAction, SIGNAL(toggled(bool)), this, SLOT(setMuted(bool)));
    connect(increaseVolumeAction, SIGNAL(triggered()), this, SLOT(increaseVolume()));
    connect(decreaseVolumeAction, SIGNAL(triggered()), this, SLOT(decreaseVolume()));
    connect(setVolumeAction, SIGNAL(triggered()), this, SLOT(setVolume()));
    connect(setBrightnessAction, SIGNAL(triggered()), this, SLOT(setBrightness()));
    connect(setContrastAction, SIGNAL(triggered()), this, SLOT(setContrast()));
}

void Gramophone::setupMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Media"));
    fileMenu->addAction(addFilesAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    QMenu *playbackMenu = menuBar()->addMenu(tr("&Playback"));
    playbackMenu->addAction(toggleAction);
    playbackMenu->addSeparator();
    playbackMenu->addAction(backwardAction);
    playbackMenu->addAction(forwardAction);
    playbackMenu->addAction(gototimeAction);
    playbackMenu->addSeparator();
    playbackMenu->addAction(stopAction);
    playbackMenu->addAction(previousAction);
    playbackMenu->addAction(nextAction);
    playbackMenu->addSeparator();
    playbackMenu->addAction(toggleTimeLCDAction);

    QMenu *audioMenu = menuBar()->addMenu(tr("&Audio"));
    audioMenu->addAction(muteAction);
    audioMenu->addAction(increaseVolumeAction);
    audioMenu->addAction(decreaseVolumeAction);
    audioMenu->addAction(setVolumeAction);

    QMenu *videoMenu = menuBar()->addMenu(tr("&Video"));
    videoMenu->addAction(toggleFullScreenAction);
    videoMenu->addSeparator();
    QActionGroup *aspectRatioActionGroup = new QActionGroup(this);
    aspectRatioActionGroup->addAction(aspectRatioAutoAction);
    aspectRatioActionGroup->addAction(aspectRatioVariableAction);
    aspectRatioActionGroup->addAction(aspectRatio16_9Action);
    aspectRatioActionGroup->addAction(aspectRatio4_3Action);
    aspectRatioAutoAction->setChecked(true);
    QMenu *aspectRatioMenu = videoMenu->addMenu(tr("Aspect Ratio"));
    aspectRatioMenu->addAction(aspectRatioAutoAction);
    aspectRatioMenu->addAction(aspectRatioVariableAction);
    aspectRatioMenu->addAction(aspectRatio16_9Action);
    aspectRatioMenu->addAction(aspectRatio4_3Action);
    videoMenu->addSeparator();
    videoMenu->addAction(setBrightnessAction);
    videoMenu->addAction(setContrastAction);

    QMenu *aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
    aboutMenu->addAction(aboutQtAction);
}

void Gramophone::setupUi()
{
    QToolBar *bar = new QToolBar;

    bar->addAction(previousAction);
    bar->addAction(backwardAction);
    bar->addAction(toggleAction);
    bar->addAction(forwardAction);
    bar->addAction(nextAction);

    bar->addAction(stopAction);
    bar->addSeparator();
    bar->addAction(toggleFullScreenAction);


    QToolBar *mediaBar = new QToolBar;
    mediaBar->addAction(addFilesAction);



    seekSlider = new Phonon::SeekSlider(this);
    seekSlider->setMediaObject(mediaObject);

    volumeSlider = new Phonon::VolumeSlider(this);
    volumeSlider->setAudioOutput(audioOutput);
    volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QLabel *volumeLabel = new QLabel;
    volumeLabel->setPixmap(QPixmap("images/volume.png"));

    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::black);

    timeLcd = new QLCDNumber;
    timeLcd->setPalette(palette);

    QStringList headers;
    headers << tr("Title") <<tr("Artist") << tr("Album") << tr("Year");

    musicTable = new QTableWidget(0, 4);
    musicTable->setHorizontalHeaderLabels(headers);
    musicTable->setSelectionMode(QAbstractItemView::SingleSelection);
    musicTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(musicTable, SIGNAL(cellPressed(int,int)),
            this, SLOT(tableClicked(int,int)));

    QHBoxLayout *seekerLayout = new QHBoxLayout;
    seekerLayout->addWidget(seekSlider);
    seekerLayout->addWidget(timeLcd);

    QHBoxLayout *playbackLayout = new QHBoxLayout;
    playbackLayout->addWidget(mediaBar);
    playbackLayout->addStretch();
    playbackLayout->addWidget(bar);
    playbackLayout->addStretch();
    playbackLayout->addWidget(volumeLabel);
    playbackLayout->addWidget(volumeSlider);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(videoWidget);
    mainLayout->addWidget(musicTable);
    mainLayout->addLayout(seekerLayout);
    mainLayout->addLayout(playbackLayout);

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);
    setWindowTitle("Gramophone");
}

void Gramophone::next()
{
    if(sources.length()==0){
        return;
    }


    int index = sources.indexOf(mediaObject->currentSource());
    if(index<sources.length()-1){
        index++;
    }else{
        index = 0;
    }

    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;
    mediaObject->stop();
    mediaObject->clearQueue();
    mediaObject->setCurrentSource(sources[index]);

    if(wasPlaying){
        mediaObject->play();
    }
    else{
        mediaObject->stop();
    }
}

void Gramophone::previous()
{
    if(sources.length()==0){
        return;
    }


    int index = sources.indexOf(mediaObject->currentSource());
    if(index>0){
        index--;
    }else{
        index = sources.length()-1;
    }

    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;
    mediaObject->stop();
    mediaObject->clearQueue();

    mediaObject->setCurrentSource(sources[index]);

    if(wasPlaying){
        mediaObject->play();
    }
    else{
        mediaObject->stop();
    }
}


void Gramophone::forward(){

    mediaObject->seek(mediaObject->currentTime()+10000);
}

void Gramophone::backward(){

        mediaObject->seek(mediaObject->currentTime()-10000);

}

void Gramophone::gototime(){
    int time = QInputDialog::getInt(this,"Jump to Time","Jump to time(in seconds)",0,0,mediaObject->totalTime()/1000);
    mediaObject->seek((qint64) time*1000);

}

void Gramophone::play(){

    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;
    if(!wasPlaying){
        mediaObject->play();
    }
    else{
        mediaObject->pause();
    }
}

void Gramophone::toggleTimeLCD(){
    timeRemaining = !(timeRemaining);

    if(timeRemaining){
        toggleTimeLCDAction->setText(tr("Time elapsed"));
    }
    else{
        toggleTimeLCDAction->setText(tr("Time remaining"));
    }

}

void Gramophone::setAspectRatio(){
    if(aspectRatioAutoAction->isChecked()){
        videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatioAuto);
    }
    else if(aspectRatioVariableAction->isChecked()){
        videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatioWidget);
    }
    else if(aspectRatio16_9Action->isChecked()){
        videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatio16_9);
    }
    else if(aspectRatio4_3Action->isChecked()){
        videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatio4_3);
    }
    else{
        return;
    }
}

void Gramophone::setMuted(bool mute){
    if(mute){
        audioOutput->setMuted(true);
    }
    else{
        audioOutput->setMuted(false);
    }
}

void Gramophone::increaseVolume(){
    audioOutput->setVolume(audioOutput->volume()+0.1);
}

void Gramophone::decreaseVolume(){
    audioOutput->setVolume(audioOutput->volume()-0.1);
}

void Gramophone::toggleFullScreen(bool fullScreen){
    if(fullScreen){
        videoWidget->enterFullScreen();
    }
    else{
        videoWidget->exitFullScreen();
    }
}

void Gramophone::setVolume(){
    qreal volume = (qreal)(QInputDialog::getInt(this, "Set Volume", "Set Volume(from 1 to 100)",0,0,100))/100.0;
    audioOutput->setVolume(volume);
}

void Gramophone::setBrightness(){
    QDialog* w = new QDialog;
    //w->setMaximumSize(400,40);
    QSlider *slider = new QSlider(w);
    QHBoxLayout *lay = new QHBoxLayout;
    lay->addWidget(slider);
    w->setLayout(lay);
    w->show();

}

void Gramophone::setContrast(){

}
