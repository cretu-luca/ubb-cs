#include "gui.h"

void MainWindow::setUpUserBackButton() {
    this->userBackButton = new QPushButton("Back", this);
    this->userBackButton->setStyleSheet(buttonStyle);
    this->userBackButton->setFixedSize(360, 50);
    connect(this->userBackButton, &QPushButton::clicked, this, &MainWindow::handleBackButtonClick);

    this->userMainMenuLayout->addWidget(userBackButton, 3,  0, 1, 2);
}

void MainWindow::setUpUserFilterOptionButton() {
    this->filterOptionButton = new QPushButton("Filter", this);
    this->filterOptionButton->setStyleSheet(buttonStyle);
    this->filterOptionButton->setFixedSize(buttonSize);
    connect(this->filterOptionButton, &QPushButton::clicked, this, &MainWindow::filterGUI);

    this->userMainMenuLayout->addWidget(filterOptionButton, 0, 0);
}

void MainWindow::setUpNavigateButton() {
    this->navigateOptionButton = new QPushButton("Navigate", this);
    this->navigateOptionButton->setStyleSheet(buttonStyle);
    this->navigateOptionButton->setFixedSize(buttonSize);
    connect(this->navigateOptionButton, &QPushButton::clicked, this, &MainWindow::navigateButtonGUI);

    this->userMainMenuLayout->addWidget(navigateOptionButton, 1, 0);
}

void MainWindow::setUpPreviousButton() {
    this->previousButton = new QPushButton("Previous", this);
    this->previousButton->setStyleSheet(buttonStyle);
    this->previousButton->setFixedSize(buttonSize);
    connect(this->previousButton, &QPushButton::clicked, this, &MainWindow::moveToPreviousMovie);
}

void MainWindow::setUpNextButton() {
    this->nextButton = new QPushButton("Next", this);
    this->nextButton->setStyleSheet(buttonStyle);
    this->nextButton->setFixedSize(buttonSize);
    connect(this->nextButton, &QPushButton::clicked, this, &MainWindow::moveToNextMovie);
}

void MainWindow::setUplikeButton() {
    this->likeButton = new QPushButton("Like", this);
    this->likeButton->setStyleSheet(buttonStyle);
    this->likeButton->setFixedSize(buttonSize);
    connect(this->likeButton, &QPushButton::clicked, this, &MainWindow::likeCurrentMovie);
}

void MainWindow::setUpAddToWatchlistButton() {
    this->addToWatchlistButton = new QPushButton("Watchlist", this);
    this->addToWatchlistButton->setStyleSheet(buttonStyle);
    this->addToWatchlistButton->setFixedSize(buttonSize);
    connect(this->addToWatchlistButton, &QPushButton::clicked, this, &MainWindow::changeWatchlistStatus);
}

void MainWindow::setUpTableViewButton() {
    this->tableViewButton = new QPushButton("View", this);
    this->tableViewButton->setStyleSheet(buttonStyle);
    this->tableViewButton->setFixedSize(360, 50);
    connect(tableViewButton, &QPushButton::clicked, this, handleView);
    this->userMainMenuLayout->addWidget(tableViewButton, 2, 0, 1, 2);
}

void MainWindow::setUpNavigateBackButton() {
    this->navigateBackButton = new QPushButton("Back", this);
    this->navigateBackButton->setStyleSheet(buttonStyle);
    connect(this->navigateBackButton, &QPushButton::clicked, this, MainWindow::handleBackButtonClick);
}

void MainWindow::setUpFilterButton() {
    this->filterButton = new QPushButton("Filter", this);
    this->filterButton->setStyleSheet(buttonStyle);
    //this->filterButton->setFixedSize(buttonSize);
    connect(this->filterButton, &QPushButton::clicked, this, &MainWindow::filterByGenre);
}

void MainWindow::moveToPreviousMovie() {
    if(this->navigationIndex == 0) {
        this->navigationIndex = controller->getAllMovies().size() - 1;
    } else {
        this->navigationIndex--;
    }

    this->updateMovieInformation();
}

void MainWindow::moveToNextMovie() {
    if(this->navigationIndex == this->controller->getAllMovies().size() - 1) {
        this->navigationIndex = 0;
    } else {
        this->navigationIndex++;
    }

    this->updateMovieInformation();
}

void MainWindow::likeCurrentMovie() {
    this->controller->likeMovieAtGivenIndex(this->navigationIndex);
    this->updateMovieInformation();
    this->controller->writeData();
}

void MainWindow::changeWatchlistStatus() {
    auto movie = this->controller->getMovieAtGivenIndex(this->navigationIndex);
    this->controller->handleWatchlistOperation(movie);
    this->updateMovieInformation();
    this->controller->writeData();
}

void MainWindow::navigateButtonGUI() {
    this->stackedWidgets->setCurrentWidget(this->navigateWidget);
    this->updateMovieInformation();
}

void MainWindow::handleView() {
    std::vector<Movie*> watchlistMovies = controller->getWatchlist();
    tableModel->setMovies(watchlistMovies);
    tableView->setModel(tableModel);

    this->stackedWidgets->setCurrentWidget(this->viewTableWidget);
}

void MainWindow::updateMovieInformation() {
    while (this->currentMovieInformation->rowCount() > 0) {
        this->currentMovieInformation->removeRow(0);
    }

    auto movie = this->controller->getMovieAtGivenIndex(navigationIndex);

    auto titleLabel = new QLabel(QString::fromStdString(movie->getTitle()), this);
    auto genreLabel = new QLabel(QString::fromStdString(movie->getGenre()), this);
    auto trailerLinkLabel = new QLabel(QString::fromStdString(movie->getTrailerLink()), this);
    auto releaseYearLabel = new QLabel(QString::number(movie->getReleaseYear()), this);
    auto likesLabel = new QLabel(QString::number(movie->getNumberOfLikes()), this);
    auto watchlistStatusLabel = new QLabel(movie->getWatchlistStatus() ? "Yes" : "No", this);

    QFont labelFont;
    labelFont.setPointSize(14);

    titleLabel->setFont(labelFont);
    genreLabel->setFont(labelFont);
    trailerLinkLabel->setFont(labelFont);
    releaseYearLabel->setFont(labelFont);
    likesLabel->setFont(labelFont);
    watchlistStatusLabel->setFont(labelFont);

    QString labelStyle = "QLabel { color: #333333; background-color: #f2f2f2; padding: 10px; border-radius: 5px; }";
    titleLabel->setStyleSheet(labelStyle);
    genreLabel->setStyleSheet(labelStyle);
    trailerLinkLabel->setStyleSheet(labelStyle);
    releaseYearLabel->setStyleSheet(labelStyle);
    likesLabel->setStyleSheet(labelStyle);
    watchlistStatusLabel->setStyleSheet(labelStyle);

    auto titleLabelKey = new QLabel("Title:", this);
    auto genreLabelKey = new QLabel("Genre:", this);
    auto trailerLinkLabelKey = new QLabel("Trailer link:", this);
    auto releaseYearLabelKey = new QLabel("Release year:", this);
    auto likesLabelKey = new QLabel("Likes:", this);
    auto watchlistStatusLabelKey = new QLabel("Watchlist status:", this);

    int fixedWidth = 100;
    titleLabelKey->setMinimumWidth(fixedWidth);
    genreLabelKey->setMinimumWidth(fixedWidth);
    trailerLinkLabelKey->setMinimumWidth(fixedWidth);
    releaseYearLabelKey->setMinimumWidth(fixedWidth);
    likesLabelKey->setMinimumWidth(fixedWidth);
    watchlistStatusLabelKey->setMinimumWidth(fixedWidth);

    titleLabelKey->setFont(labelFont);
    genreLabelKey->setFont(labelFont);
    trailerLinkLabelKey->setFont(labelFont);
    releaseYearLabelKey->setFont(labelFont);
    likesLabelKey->setFont(labelFont);
    watchlistStatusLabelKey->setFont(labelFont);

    titleLabelKey->setStyleSheet(labelStyle);
    genreLabelKey->setStyleSheet(labelStyle);
    trailerLinkLabelKey->setStyleSheet(labelStyle);
    releaseYearLabelKey->setStyleSheet(labelStyle);
    likesLabelKey->setStyleSheet(labelStyle);
    watchlistStatusLabelKey->setStyleSheet(labelStyle);

    this->currentMovieInformation->addRow(titleLabelKey, titleLabel);
    this->currentMovieInformation->addRow(genreLabelKey, genreLabel);
    this->currentMovieInformation->addRow(trailerLinkLabelKey, trailerLinkLabel);
    this->currentMovieInformation->addRow(releaseYearLabelKey, releaseYearLabel);
    this->currentMovieInformation->addRow(likesLabelKey, likesLabel);
    this->currentMovieInformation->addRow(watchlistStatusLabelKey, watchlistStatusLabel);

    this->currentMovieInformation->setSpacing(10);
    this->currentMovieInformation->setContentsMargins(10, 10, 10, 10);
    this->controller->writeData();
}

void MainWindow::setUpFilterBackButton() {
    this->filterAndBackButton = new QPushButton("Back", this);
    this->filterAndBackButton->setStyleSheet(buttonStyle);
    connect(this->filterAndBackButton, &QPushButton::clicked, this, &MainWindow::handleBackButtonClick);
}

void MainWindow::setUpWatchlistBackButton() {
    this->watchlistBackButton = new QPushButton("Back", this);
    this->watchlistBackButton->setStyleSheet(buttonStyle);
    connect(this->watchlistBackButton, &QPushButton::clicked, this, &MainWindow::handleBackButtonClick);
}

void MainWindow::setUpOpenLinkButton() {
    this->openLinkButton = new QPushButton("Link", this);
    this->openLinkButton->setStyleSheet(buttonStyle);
    this->openLinkButton->setFixedSize(buttonSize);
    connect(openLinkButton, &QPushButton::clicked, this, &MainWindow::openLinkGUI);
}

void MainWindow::setUpViewTableBackButton() {
    this->viewTableBackButton = new QPushButton("Back", this);
    this->viewTableBackButton->setStyleSheet(buttonStyle);
    connect(viewTableBackButton, &QPushButton::clicked, this, handleBackButtonClick);
    this->viewTableLayout->addWidget(viewTableBackButton);
}

void MainWindow::setUpListWatchlistOptionButton() {
    this->listWatchlistOptionButton = new QPushButton("Watchlist", this);
    this->listWatchlistOptionButton->setStyleSheet(buttonStyle);
    this->listWatchlistOptionButton->setFixedSize(buttonSize);
    connect(this->listWatchlistOptionButton, &QPushButton::clicked, this, &MainWindow::listWatchlistGUI);

    this->userMainMenuLayout->addWidget(listWatchlistOptionButton, 0, 1);
}

void MainWindow::setUpShowPieChartButton() {
    this->showPieChartButton = new QPushButton("Chart", this);
    this->showPieChartButton->setStyleSheet(buttonStyle);
    this->showPieChartButton->setFixedSize(buttonSize);
    connect(showPieChartButton, &QPushButton::clicked, this, &MainWindow::showGenrePieChart);

    this->userMainMenuLayout->addWidget(showPieChartButton, 1, 1);
}

void MainWindow::setUpChartBackButton() {
    this->chartBackButton = new QPushButton("Back", this);
    this->chartBackButton->setStyleSheet(buttonStyle);
    connect(chartBackButton, &QPushButton::clicked, this, &MainWindow::handleBackButtonClick);
}

void MainWindow::filterByGenre() {
    QString genre = this->genresComboBox->currentText();

    if (this->genreTable) {
        this->genreFilterLayout->removeWidget(this->genreTable);
        delete this->genreTable;
        this->genreTable = nullptr;
    }

    this->genreTable = getGenreTable(genre);
    this->genreFilterLayout->insertWidget(0, this->genreTable);
}

void MainWindow::filterGUI() {
    QString genre = "";

    if (this->genreTable) {
        this->genreFilterLayout->removeWidget(this->genreTable);
        delete this->genreTable;
        this->genreTable = nullptr;
    }

    this->genresComboBox->clear();
    this->populateGenresComboBox();

    this->genreTable = getGenreTable(genre);
    this->genreFilterLayout->insertWidget(0, this->genreTable);
    this->genreFilterLayout->insertWidget(1, this->genresComboBox);

    this->stackedWidgets->setCurrentWidget(genreFilterWidget);
}

void MainWindow::populateGenresComboBox() {
    set<QString> genres;
    const vector<Movie*> movies = controller->getAllMovies();

    for (auto movie : movies) {
        genres.insert(QString::fromStdString(movie->getGenre()));
    }

    if(this->genresComboBox) {
        delete this->genresComboBox;
        this->genresComboBox = nullptr;
    }
    this->genresComboBox = new QComboBox;
    this->genresComboBox->setFixedSize(650, 40);
    comboBoxFont.setPointSize(12);
    this->genresComboBox->setFont(comboBoxFont);

    this->genresComboBox->addItem("All");
    for (const auto& genre : genres) {
        this->genresComboBox->addItem(genre);
    }
}

QTableWidget* MainWindow::getGenreTable(QString genre) {
    vector<Movie*> movies;

    if(genre == "All")
        movies = this->controller->getAllMovies();
    else
        movies = this->controller->getAllMoviesByGenre(genre.toStdString());
    auto table = new QTableWidget;
    table->setRowCount(movies.size());
    table->setColumnCount(6);

    QStringList headers = {"Title", "Genre", "Trailer Link", "Release Year", "Likes", "Watchlist Status"};
    table->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < movies.size(); i++) {
        Movie* movie = movies[i];
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(movie->getTitle())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(movie->getGenre())));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(movie->getTrailerLink())));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(movie->getReleaseYear())));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(movie->getNumberOfLikes())));
        table->setItem(i, 5, new QTableWidgetItem(movie->getWatchlistStatus() ? "Yes" : "No"));
    }

    return table;
}

QTableWidget* MainWindow::getWatchlistTable() {
    vector<Movie*> movies = controller->getAllMovies();
    vector<Movie*> filteredMovies;

    for(auto movie: movies) {
        if(movie->getWatchlistStatus()) {
            filteredMovies.push_back(movie);
        }
    }

    auto table = new QTableWidget;
    table->setRowCount(filteredMovies.size());
    table->setColumnCount(6);

    QStringList headers = {"Title", "Genre", "Trailer Link", "Release Year", "Likes", "Watchlist Status"};
    table->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < filteredMovies.size(); i++) {
        Movie* movie = filteredMovies[i];
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(movie->getTitle())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(movie->getGenre())));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(movie->getTrailerLink())));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(movie->getReleaseYear())));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(movie->getNumberOfLikes())));
        table->setItem(i, 5, new QTableWidgetItem(movie->getWatchlistStatus() ? "Yes" : "No"));
    }

    return table;
}

void MainWindow::openLinkGUI() {
    auto movie = this->controller->getMovieAtGivenIndex(this->navigationIndex);
    QString trailerLink = QString::fromStdString(movie->getTrailerLink());
    QDesktopServices::openUrl(QUrl(trailerLink));
}

void MainWindow::showGenrePieChart() {
    if (this->genreChartView) {
        this->pieChartLayout->removeWidget(this->genreChartView);
        delete this->genreChartView;
        this->genreChartView = nullptr;
    }

    this->series = new QPieSeries();
    QMap<QString, int> genreCountMap;
    const vector<Movie*> movies = this->controller->getAllMovies();

    for (const auto& movie : movies) {
        QString genre = QString::fromStdString(movie->getGenre());
        genreCountMap[genre]++;
    }

    for (auto it = genreCountMap.begin(); it != genreCountMap.end(); ++it) {
        QPieSlice* slice = series->append(it.key() + " (" + QString::number(it.value()) + ")", it.value());
        slice->setLabelVisible(true);
    }

    this->chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Movies by genre");
    chart->legend()->show();

    this->genreChartView = new QChartView(chart);
    this->genreChartView->setRenderHint(QPainter::Antialiasing);

    this->pieChartLayout->insertWidget(0, genreChartView);
    this->stackedWidgets->setCurrentWidget(pieChartWidget);
}

void MainWindow::listWatchlistGUI() {
    if (this->watchlistTable) {
        this->watchlistLayout->removeWidget(this->watchlistTable);
        delete this->watchlistTable;
        this->watchlistTable = nullptr;
    }

    this->watchlistTable = getWatchlistTable();
    this->watchlistLayout->insertWidget(0, this->watchlistTable);
    this->stackedWidgets->setCurrentWidget(watchlistWidget);
}