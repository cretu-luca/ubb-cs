#include "GUI/adminGUI.h"

// TODO fix update, clear remove name

AdminMenuWidget::AdminMenuWidget(QWidget* parent, Controller* controller): QWidget(parent), controller(controller) {
    this->setWindowTitle("Admin menu");
    this->resize(800, 800);

    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->setAlignment(Qt::AlignCenter);
    this->gridLayout = new QGridLayout();
    this->tableWidget = new QTableWidget(this);

    this->SetUpAddMoviePushButton();
    this->SetUpRemoveMoviePushButton();
    this->SetUpUpdateMoviePushButton();
    this->setUpListMoviesPushButton();
    this->setUpBackButton();

    this->mainLayout->addLayout(this->gridLayout);
    this->setLayout(this->mainLayout);

    this->setUpGetMovieDetailsGroupBox();
    this->setUpAddGroupBox();
    this->setUpRemoveGroupBox();
    this->setUpUpdateGroupBox();
}

void AdminMenuWidget::hideMainPushButtons() const {
    this->addMovieButton->hide();
    this->removeMovieButton->hide();
    this->updateMovieButton->hide();
    this->listAllMoviesButton->hide();
}

void AdminMenuWidget::showMainPushButtons() const {
    this->addMovieButton->show();
    this->removeMovieButton->show();
    this->updateMovieButton->show();
    this->listAllMoviesButton->show();
}

void AdminMenuWidget::SetUpAddMoviePushButton() {
    this->addMovieButton = new QPushButton("Add movie", this);
    this->addMovieButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->addMovieButton->setFixedSize(buttonSize);
    connect(this->addMovieButton, &QPushButton::clicked, this, &AdminMenuWidget::addMovieGUI);
    this->gridLayout->addWidget(addMovieButton, 0, 0);
}

void AdminMenuWidget::SetUpRemoveMoviePushButton() {
    this->removeMovieButton = new QPushButton("Remove movie", this);
    this->removeMovieButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->removeMovieButton->setFixedSize(buttonSize);
    connect(this->removeMovieButton, &QPushButton::clicked, this, &AdminMenuWidget::removeMovieGUI);
    this->gridLayout->addWidget(removeMovieButton, 0, 1);
}

void AdminMenuWidget::SetUpUpdateMoviePushButton() {
    this->updateMovieButton = new QPushButton("Update movie", this);
    this->updateMovieButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->updateMovieButton->setFixedSize(buttonSize);
    connect(this->updateMovieButton, &QPushButton::clicked, this, &AdminMenuWidget::updateMovieGUI);
    this->gridLayout->addWidget(updateMovieButton, 1, 0);
}

void AdminMenuWidget::setUpListMoviesPushButton() {
    this->listAllMoviesButton = new QPushButton("List movies", this);
    this->listAllMoviesButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    this->listAllMoviesButton->setFixedSize(buttonSize);
    connect(this->listAllMoviesButton, &QPushButton::clicked, this, &AdminMenuWidget::listMoviesGUI);
    this->gridLayout->addWidget(listAllMoviesButton, 1, 1);
}

void AdminMenuWidget::setUpBackButton() {
    this->backPushButton = new QPushButton("Back", this);
    this->backPushButton->setStyleSheet("QPushButton { font-size: 16pt; color: black; background-color: AliceBlue; }");
    connect(backPushButton, &QPushButton::clicked, this, &AdminMenuWidget::backToAdminMenu);
    this->backPushButton->hide();
}

void AdminMenuWidget::setUpGetMovieDetailsGroupBox() {
    getMovieDetailsGroupBox = new QGroupBox(this);

    this->titleLine = new QLineEdit();
    this->genreLine = new QLineEdit();
    this->linkLine = new QLineEdit();
    this->releaseYearLine = new QLineEdit();
    this->likesLine = new QLineEdit();
    this->indexOfMovieToUpdate = new QLineEdit();
    this->inWatchlist = new QCheckBox();

    this->addFormLayout = new QFormLayout();
    this->addFormLayout->addRow("Title:", titleLine);
    this->addFormLayout->addRow("Genre:", genreLine);
    this->addFormLayout->addRow("Trailer Link:", linkLine);
    this->addFormLayout->addRow("Release Year:", releaseYearLine);
    this->addFormLayout->addRow("Likes:", likesLine);
    this->addFormLayout->addRow("In Watchlist:", inWatchlist);

    getMovieDetailsGroupBox->setLayout(addFormLayout);
}

void AdminMenuWidget::hideGetMovieDetailsGroupBox() const {
    this->getMovieDetailsGroupBox->hide();
    this->titleLine->clear();
    this->genreLine->clear();
    this->linkLine->clear();
    this->releaseYearLine->clear();
    this->likesLine->clear();
}

void AdminMenuWidget::setUpAddGroupBox() {
    addMovieGroupBox = new QGroupBox("Add Movie", this);

    auto vbox = new QVBoxLayout();
    vbox->addWidget(this->getMovieDetailsGroupBox);

    addMovieDetailsButton = new QPushButton("Add Movie", addMovieGroupBox);
    vbox->addWidget(addMovieDetailsButton);
    connect(addMovieDetailsButton, &QPushButton::clicked, this, &AdminMenuWidget::addMovieDetails);

    addMovieGroupBox->setLayout(vbox);
    mainLayout->addWidget(addMovieGroupBox);

    this->addMovieGroupBox->hide();
}

void AdminMenuWidget::addMovieDetails() const {
    this->addMovieGroupBox->show();
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

    this->addMovieGroupBox->hide();
    this->hideGetMovieDetailsGroupBox();
    this->controller->writeData();
    this->showMainPushButtons();
}

void AdminMenuWidget::addMovieGUI() const {
    this->hideMainPushButtons();
    this->addMovieGroupBox->show();
    this->getMovieDetailsGroupBox->show();
}

void AdminMenuWidget::setUpRemoveGroupBox() {
    this->removeMovieGroupBox = new QGroupBox("Remove movie", this);

    this->nameOfMovieToDelete = new QLineEdit();
    this->removeFormLayout = new QFormLayout();
    this->removeFormLayout->addRow("Name of movie to Remove", nameOfMovieToDelete);

    auto vbox = new QVBoxLayout();
    vbox->addLayout(removeFormLayout);

    removeMovieDetailsButton = new QPushButton("Remove movie", removeMovieGroupBox);
    vbox->addWidget(removeMovieDetailsButton);
    connect(removeMovieDetailsButton, &QPushButton::clicked, this, &AdminMenuWidget::removeMovieDetails);

    removeMovieGroupBox->setLayout(vbox);
    mainLayout->addWidget(removeMovieGroupBox);

    this->removeMovieGroupBox->hide();
}

void AdminMenuWidget::removeMovieDetails() const {
    QString title = this->nameOfMovieToDelete->text();

    try {
        this->controller->removeMovieByNameController(title.toStdString());
    } catch (const CustomException& e) {
        QMessageBox::information(nullptr, "Error", QString::fromUtf8(e.what()));
    }

    this->controller->writeData();
    this->removeMovieGroupBox->hide();
    this->showMainPushButtons();
}

void AdminMenuWidget::removeMovieGUI() const {
    this->hideMainPushButtons();
    this->removeMovieGroupBox->show();
}

void AdminMenuWidget::updateMovieGUI() const {
    this->hideMainPushButtons();
    this->indexOfMovieToUpdate->setVisible(true);
    this->addFormLayout->insertRow(0, "Movie Index:", indexOfMovieToUpdate);
    this->getMovieDetailsGroupBox->show();
}

void AdminMenuWidget::setUpUpdateGroupBox() {
    this->updateMovieGroupBox = new QGroupBox("Update movie", this);
    this->indexOfMovieToUpdate = new QLineEdit();

    this->updateFormLayout = new QFormLayout();
    this->updateFormLayout->addRow("Index of movie to update", indexOfMovieToUpdate);

    auto vbox = new QVBoxLayout();
    vbox->addLayout(updateFormLayout);

    updateMovieDetailsButton = new QPushButton("Update Movie", updateMovieGroupBox);
    vbox->addWidget(updateMovieDetailsButton);
    connect(updateMovieDetailsButton, &QPushButton::clicked, this, &AdminMenuWidget::updateMovieDetails);

    updateMovieGroupBox->setLayout(vbox);
    mainLayout->addWidget(updateMovieGroupBox);

    this->updateMovieGroupBox->hide();
}

void AdminMenuWidget::updateMovieDetails() const {
    int index = this->indexOfMovieToUpdate->text().toInt();
    QString title = titleLine->text();
    QString genre = genreLine->text();
    QString trailerLink = linkLine->text();
    int releaseYear = releaseYearLine->text().toInt();
    int likes = likesLine->text().toInt();

    auto updatedMovie = new Movie(title.toStdString(), genre.toStdString(), trailerLink.toStdString(), releaseYear, likes, false);

    try {
        this->controller->updateController(index, updatedMovie);
    } catch (const CustomException& e) {
        QMessageBox::information(nullptr, "Error", QString::fromUtf8(e.what()));
    }

    getMovieDetailsGroupBox->hide();
    this->hideGetMovieDetailsGroupBox();
    this->controller->writeData();
    showMainPushButtons();
}

void AdminMenuWidget::listMoviesGUI() const  {
    this->hideMainPushButtons();
    this->controller->readData();
    const vector<Movie*> movies = controller->getAllMovies();

    this->tableWidget->setRowCount(movies.size());
    this->tableWidget->setColumnCount(6);

    QStringList headers = {"Title", "Genre", "Trailer Link", "Release Year", "Likes", "Watchlist Status"};
    this->tableWidget->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < movies.size(); i++) {
        Movie* movie = movies[i];
        this->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(movie->getTitle())));
        this->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(movie->getGenre())));
        this->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(movie->getTrailerLink())));
        this->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(movie->getNumberOfLikes())));
        this->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(movie->getReleaseYear())));
        this->tableWidget->setItem(i, 5, new QTableWidgetItem(movie->getWatchlistStatus() ? "Yes" : "No"));
    }

    this->mainLayout->addWidget(this->tableWidget);
    this->mainLayout->setStretchFactor(this->tableWidget, 3);
    this->tableWidget->show();
    this->mainLayout->addWidget(this->backPushButton);
    this->mainLayout->setStretchFactor(this->backPushButton, 1);
    this->backPushButton->show();
}

void AdminMenuWidget::backToAdminMenu() const {
    this->tableWidget->hide();
    this->backPushButton->hide();
    this->showMainPushButtons();
}