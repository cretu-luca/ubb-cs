#include "gui.h"

void MainWindow::setUpAddMovieOptionButton() {
    this->addMovieOptionButton = new QPushButton("Add movie", this);
    this->addMovieOptionButton->setStyleSheet(buttonStyle);
    this->addMovieOptionButton->setFixedSize(buttonSize);
    connect(this->addMovieOptionButton, &QPushButton::clicked, this, &MainWindow::addMovieGUI);

    this->mainAdminMenuLayout->addWidget(addMovieOptionButton, 0, 0);
}

void MainWindow::setUpRemoveMovieOptionButton() {
    this->removeMovieOptionButton = new QPushButton("Remove movie", this);
    this->removeMovieOptionButton->setStyleSheet(buttonStyle);
    this->removeMovieOptionButton->setFixedSize(buttonSize);
    connect(this->removeMovieOptionButton, &QPushButton::clicked, this, &MainWindow::removeMovieGUI);

    this->mainAdminMenuLayout->addWidget(removeMovieOptionButton, 0, 1);
}

void MainWindow::setUpUpdateMovieOptionButton() {
    this->updateMovieOptionButton = new QPushButton("Update movie", this);
    this->updateMovieOptionButton->setStyleSheet(buttonStyle);
    this->updateMovieOptionButton->setFixedSize(buttonSize);
    connect(this->updateMovieOptionButton, &QPushButton::clicked, this, &MainWindow::updateMovieGUI);

    this->mainAdminMenuLayout->addWidget(updateMovieOptionButton, 1, 0);
}

void MainWindow::setUpListMoviesOptionButton() {
    this->listAllMoviesOptionButton = new QPushButton("List movies", this);
    this->listAllMoviesOptionButton->setStyleSheet(buttonStyle);
    this->listAllMoviesOptionButton->setFixedSize(buttonSize);
    connect(this->listAllMoviesOptionButton, &QPushButton::clicked, this, &MainWindow::listMovies);

    this->mainAdminMenuLayout->addWidget(listAllMoviesOptionButton, 1, 1);
}

void MainWindow::setUpAddMovieButton() {
    this->addMovieButton = new QPushButton("Add movie", this);
    this->addMovieButton->setStyleSheet(buttonStyle);
    connect(this->addMovieButton, &QPushButton::clicked, this, &MainWindow::addMovieDetails);
}

void MainWindow::setUpAddBackButton() {
    this->addBackPushButton = new QPushButton("Back", this);
    this->addBackPushButton->setStyleSheet(buttonStyle);
    connect(addBackPushButton, &QPushButton::clicked, this, &MainWindow::handleBackButtonClick);
}

void MainWindow::setUpRemoveBackButton() {
    this->removeBackButton = new QPushButton("Back", this);
    this->removeBackButton->setStyleSheet(buttonStyle);
    connect(removeBackButton, &QPushButton::clicked, this, &MainWindow::handleBackButtonClick);
}

void MainWindow::setUpListBackButton() {
    this->listBackPushButton = new QPushButton("Back", this);
    this->listBackPushButton->setStyleSheet(buttonStyle);
    connect(this->listBackPushButton, &QPushButton::clicked, this, &MainWindow::handleBackButtonClick);
}

void MainWindow::setUpRemoveMovieButton() {
    this->removeMovieButton = new QPushButton("Remove movie", this);
    this->removeMovieButton->setStyleSheet(buttonStyle);
    connect(this->removeMovieButton, &QPushButton::clicked, this, &MainWindow::removeMovieDetails);
}

void MainWindow::setUpUndoButton() {
    this->undoButton = new QPushButton("Undo", this);
    this->undoButton->setStyleSheet(buttonStyle);
    this->undoButton->setFixedSize(buttonSize);
    connect(this->undoButton, &QPushButton::clicked, this, &MainWindow::handleUndo);

    this->mainAdminMenuLayout->addWidget(undoButton);
}

void MainWindow::setUpRedoButton() {
    this->redoButton = new QPushButton("Redo", this);
    this->redoButton->setStyleSheet(buttonStyle);
    this->redoButton->setFixedSize(buttonSize);
    connect(this->redoButton, &QPushButton::clicked, this, &MainWindow::handleRedo);

    this->mainAdminMenuLayout->addWidget(redoButton);
}

void MainWindow::setUpUpdateMovieButton() {
    this->updateMovieButton = new QPushButton("Update movie", this);
    this->updateMovieButton->setStyleSheet(buttonStyle);
    connect(this->updateMovieButton, &QPushButton::clicked, this, &MainWindow::updateMovieDetails);
}

void MainWindow::setUpMainMenuBackButton() {
    this->mainMenuBackButton = new QPushButton("Back", this);
    this->mainMenuBackButton->setStyleSheet(buttonStyle);
    this->mainMenuBackButton->setFixedSize(360, 50);
    connect(this->mainMenuBackButton, &QPushButton::clicked, this, &MainWindow::handleBackButtonClick);

    this->mainAdminMenuLayout->addWidget(mainMenuBackButton, 3, 0, 1, 2);
}

void MainWindow::setUpOpenFileButton() {
    this->openFileButton = new QPushButton("Open file", this);
    this->openFileButton->setStyleSheet(buttonStyle);
    connect(openFileButton, &QPushButton::clicked, this, &MainWindow::handleOpenFile);
}

void MainWindow::handleBackButtonClick() const {
    if(stackedWidgets->currentWidget() == listMoviesWidget || stackedWidgets->currentWidget() == addMovieWidget ||
        stackedWidgets->currentWidget() == removeMovieWidget || stackedWidgets->currentWidget() == updateMovieWidget) {
        this->stackedWidgets->setCurrentWidget(mainAdminMenuWidget);
        return;
    }

    if(stackedWidgets->currentWidget() == mainAdminMenuWidget) {
        this->stackedWidgets->setCurrentWidget(selectProfileWidget);
        return;
    }

    if(stackedWidgets->currentWidget() == userMainMenuWidget) {
        this->stackedWidgets->setCurrentWidget(selectProfileWidget);
        return;
    }

    if(stackedWidgets->currentWidget() == genreFilterWidget) {
        this->stackedWidgets->setCurrentWidget(userMainMenuWidget);
        return;
    }

    if(stackedWidgets->currentWidget() == watchlistWidget) {
        this->stackedWidgets->setCurrentWidget(userMainMenuWidget);
        return;
    }

    if(stackedWidgets->currentWidget() == pieChartWidget) {
        this->stackedWidgets->setCurrentWidget(userMainMenuWidget);
        return;
    }

    if(stackedWidgets->currentWidget() == navigateWidget) {
        this->stackedWidgets->setCurrentWidget(userMainMenuWidget);
        return;
    }

    if(stackedWidgets->currentWidget() == viewTableWidget) {
        this->stackedWidgets->setCurrentWidget(userMainMenuWidget);
        return;
    }
}

void MainWindow::addMovieGUI() {
    if(this->addMoviesInformationTable) {
        this->addMovieLayout->removeWidget(this->addMoviesInformationTable);
        delete this->addMoviesInformationTable;
        this->addMoviesInformationTable = nullptr;
    }

    this->addMoviesInformationTable = getTable();
    this->addMovieLayout->insertWidget(0, addMoviesInformationTable, 13);

    this->stackedWidgets->setCurrentWidget(addMovieWidget);
}

void MainWindow::removeMovieGUI() {
    if (this->removeMoviesInformationTable) {
        this->removeMovieLayout->removeWidget(this->removeMoviesInformationTable);
        delete this->removeMoviesInformationTable;
        this->removeMoviesInformationTable = nullptr;
    }

    this->removeMoviesInformationTable = getTable();
    this->removeMovieLayout->insertWidget(0, removeMoviesInformationTable);

    this->stackedWidgets->setCurrentWidget(removeMovieWidget);
}

void MainWindow::updateMovieGUI() {
    if (this->updateMoviesInformationTable) {
        this->updateMovieLayout->removeWidget(this->updateMoviesInformationTable);
        delete this->updateMoviesInformationTable;
        this->updateMoviesInformationTable = nullptr;
    }

    this->updateMoviesInformationTable = getTable();
    this->updateMovieLayout->insertWidget(0, updateMoviesInformationTable);

    this->stackedWidgets->setCurrentWidget(updateMovieWidget);
}

void MainWindow::handleOpenFile() {
    this->controller->repository->openSelectedFile();
}

void MainWindow::updateMovieDetails() {
    int index = this->indexOfMovieToUpdate->text().toInt() - 1;
    QString title = updateTitleLine->text();
    QString genre = updateGenreLine->text();
    QString trailerLink = updateLinkLine->text();
    int releaseYear = updateReleaseYearLine->text().toInt();
    int likes = updateLikesLine->text().toInt();
    bool inWatchlist = updateInWatchlist->isChecked();

    auto updatedMovie = new Movie(title.toStdString(), genre.toStdString(), trailerLink.toStdString(), releaseYear, likes, inWatchlist);

    try {
        this->controller->updateController(index, updatedMovie);
    } catch (const CustomException& e) {
        QMessageBox::information(nullptr, "Error", QString::fromUtf8(e.what()));
    }

    this->clearUpdateLineEdits();
    this->controller->writeData();

    if (this->updateMoviesInformationTable) {
        this->updateMovieLayout->removeWidget(this->updateMoviesInformationTable);
        delete this->updateMoviesInformationTable;
        this->updateMoviesInformationTable = nullptr;
    }

    this->updateMoviesInformationTable = getTable();
    this->updateMovieLayout->insertWidget(0, this->updateMoviesInformationTable, 13);
}

void MainWindow::setUpUpdateBackButton() {
    this->updateBackButton = new QPushButton("Back", this);
    this->updateBackButton->setStyleSheet(buttonStyle);
    connect(this->updateBackButton, &QPushButton::clicked, this, &MainWindow::handleBackButtonClick);
}

void MainWindow::listMovies() {
    this->stackedWidgets->setCurrentWidget(listMoviesWidget);

    this->listMoviesLayout->removeWidget(this->moviesTableWidget);
    delete this->moviesTableWidget;

    this->moviesTableWidget = getTable();
    this->listMoviesLayout->insertWidget(0, this->moviesTableWidget);
}

QTableWidget* MainWindow::getTable() const {
    this->controller->readData();
    const vector<Movie*> movies = controller->getAllMovies();

    auto table = new QTableWidget;
    table->setRowCount(movies.size());
    table->setColumnCount(6);

    QStringList headers = {"Title", "Genre", "Trailer Link", "Release Year", "Likes", "Watchlist Status"};
    table->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < movies.size(); i++) {
        Movie* movie = movies[i];
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(movie->getTitle())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(movie->getGenre())));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(movie->getTrailerLink())));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(movie->getNumberOfLikes())));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(movie->getReleaseYear())));
        table->setItem(i, 5, new QTableWidgetItem(movie->getWatchlistStatus() ? "Yes" : "No"));
    }

    return table;
}

void MainWindow::addMovieDetails() {
    QString title = titleLine->text();
    QString genre = genreLine->text();
    QString trailerLink = linkLine->text();
    int releaseYear = releaseYearLine->text().toInt();
    int likes = likesLine->text().toInt();
    bool inWatchlist = this->inWatchlist->checkState();

    auto newMovie = new Movie(title.toStdString(), genre.toStdString(), trailerLink.toStdString(), releaseYear, likes, inWatchlist);

    try {
        controller->addMovieController(newMovie);
    } catch (const CustomException& e) {
        QMessageBox::information(nullptr, "Error", QString::fromUtf8(e.what()));
    }

    this->clearLineEdits();
    this->controller->writeData();

    if (this->addMoviesInformationTable) {
        this->addMovieLayout->removeWidget(this->addMoviesInformationTable);
        delete this->addMoviesInformationTable;
        this->addMoviesInformationTable = nullptr;
    }

    this->addMoviesInformationTable = getTable();
    this->addMovieLayout->insertWidget(0, this->addMoviesInformationTable, 13);
}

void MainWindow::removeMovieDetails() {
    QString title = movieToRemoveName->text();
    try {
        controller->removeMovieByNameController(title.toStdString());
    } catch (const CustomException& e) {
        QMessageBox::information(nullptr, "Error", QString::fromUtf8(e.what()));
        return;
    }

    this->movieToRemoveName->clear();
    this->controller->writeData();

    if (this->removeMoviesInformationTable) {
        this->removeMovieLayout->removeWidget(this->removeMoviesInformationTable);
        delete this->removeMoviesInformationTable;
        this->removeMoviesInformationTable = nullptr;
    }

    this->removeMoviesInformationTable = getTable();
    this->removeMovieLayout->insertWidget(0, this->removeMoviesInformationTable);
}

void MainWindow::clearLineEdits() const {
    this->titleLine->clear();
    this->genreLine->clear();
    this->linkLine->clear();
    this->releaseYearLine->clear();
    this->likesLine->clear();
    this->inWatchlist->setCheckState(Qt::Unchecked);
}

void MainWindow::setUpMovieInformation() {
    this->titleLine = new QLineEdit();
    this->genreLine = new QLineEdit();
    this->linkLine = new QLineEdit();
    this->releaseYearLine = new QLineEdit();
    this->likesLine = new QLineEdit();
    this->indexOfMovieToUpdate = new QLineEdit();
    this->inWatchlist = new QCheckBox();

    this->movieInformation = new QFormLayout();
    this->movieInformation->addRow("Title:", titleLine);
    this->movieInformation->addRow("Genre:", genreLine);
    this->movieInformation->addRow("Trailer Link:", linkLine);
    this->movieInformation->addRow("Release Year:", releaseYearLine);
    this->movieInformation->addRow("Likes:", likesLine);
    this->movieInformation->addRow("In Watchlist:", inWatchlist);

    // this->addMovieLayout->addLayout(movieInformation);
}

void MainWindow::clearUpdateLineEdits() const {
    this->indexOfMovieToUpdate->clear();
    this->updateTitleLine->clear();
    this->updateGenreLine->clear();
    this->updateLinkLine->clear();
    this->updateReleaseYearLine->clear();
    this->updateLikesLine->clear();
    this->updateInWatchlist->setCheckState(Qt::Unchecked);
    this->indexOfMovieToUpdate->clear();
}

void MainWindow::setUpMovieUpdateInformation() {
    this->updateTitleLine = new QLineEdit();
    this->updateGenreLine = new QLineEdit();
    this->updateLinkLine = new QLineEdit();
    this->updateReleaseYearLine = new QLineEdit();
    this->updateLikesLine = new QLineEdit();
    this->updateInWatchlist = new QCheckBox();
    this->indexOfMovieToUpdate = new QLineEdit();

    this->movieInformationUpdate->addRow("Index:", indexOfMovieToUpdate);
    this->movieInformationUpdate->addRow("New title:", updateTitleLine);
    this->movieInformationUpdate->addRow("New genre:", updateGenreLine);
    this->movieInformationUpdate->addRow("New trailer Link:", updateLinkLine);
    this->movieInformationUpdate->addRow("New release Year:", updateReleaseYearLine);
    this->movieInformationUpdate->addRow("New likes:", updateLikesLine);
    this->movieInformationUpdate->addRow("In Watchlist:", updateInWatchlist);
}