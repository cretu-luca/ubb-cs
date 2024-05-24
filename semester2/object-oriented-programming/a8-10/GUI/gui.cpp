#include "gui.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), controller(nullptr) {
    this->resize(650, 800);

    this->selectFileWidget = new QWidget;
    this->selectProfileWidget = new QWidget;
    this->mainAdminMenuWidget = new QWidget;
    this->listMoviesWidget = new QWidget;
    this->removeMovieWidget = new QWidget;
    this->updateMovieWidget = new QWidget;
    this->addMovieWidget = new QWidget;
    this->userMainMenuWidget = new QWidget;
    this->genreFilterWidget = new QWidget;
    this->watchlistWidget = new QWidget;
    this->pieChartWidget = new QWidget;
    this->navigateWidget = new QWidget;
    this->viewTableWidget = new QWidget;

    this->fileLayout = new QVBoxLayout;
    this->profileLayout = new QVBoxLayout;
    this->addMovieLayout = new QVBoxLayout;
    this->removeMovieLayout = new QVBoxLayout;
    this->updateMovieLayout = new QVBoxLayout;
    this->listMoviesLayout = new QVBoxLayout;
    this->genreFilterLayout = new QVBoxLayout;
    this->watchlistLayout = new QVBoxLayout;
    this->pieChartLayout = new QVBoxLayout;
    this->navigateButtonsLayout = new QHBoxLayout;
    this->navigateMovielist = new QVBoxLayout;
    this->viewTableLayout = new QVBoxLayout;

    this->addAndBackLayout = new QHBoxLayout;
    this->removeAndBackLayout = new QHBoxLayout;
    this->updateAndBackLayout = new QHBoxLayout;
    this->filterAndBackLayout = new QHBoxLayout;
    this->mainAdminMenuLayout = new QGridLayout;
    this->userMainMenuLayout = new QGridLayout;

    this->stackedWidgets = new QStackedWidget;
    this->moviesTableWidget = new QTableWidget;
    this->removeMoviesInformationTable = new QTableWidget;
    this->addMoviesInformationTable = new QTableWidget;
    this->updateMoviesInformationTable = new QTableWidget;
    this->genreTable = new QTableWidget;
    this->watchlistTable = new QTableWidget;

    this->movieToRemoveName = new QLineEdit;
    this->movieInformation = new QFormLayout;
    this->movieInformationRemove = new QFormLayout;
    this->movieInformationUpdate = new QFormLayout;
    this->currentMovieInformation = new QFormLayout;

    this->genresComboBox = new QComboBox;

    this->chart = new QChart;
    this->series = new QPieSeries;
    this->genreChartView = new QChartView;

    this->tableView = new QTableView;
    this->tableModel = new MyTableModel;

    this->setUpHTMLButton();
    this->setUpCSVButton();
    this->setUpAdminButton();
    this->setUpUserButton();
    this->setUpAddMovieOptionButton();
    this->setUpRemoveMovieOptionButton();
    this->setUpUpdateMovieOptionButton();
    this->setUpListMoviesOptionButton();
    this->setUpAddBackButton();
    this->setUpListBackButton();
    this->setUpMovieInformation();
    this->setUpAddMovieButton();
    this->setUpRemoveMovieButton();
    this->setUpUndoButton();
    this->setUpRedoButton();
    this->setUpRemoveBackButton();
    this->setUpUpdateBackButton();
    this->setUpUpdateMovieButton();
    this->setUpMovieUpdateInformation();
    this->setUpMainMenuBackButton();
    this->setUpUserBackButton();
    this->setUpUserFilterOptionButton();
    this->setUpListWatchlistOptionButton();
    this->setUpFilterButton();
    this->setUpFilterBackButton();
    this->setUpWatchlistBackButton();
    this->setUpOpenFileButton();
    this->setUpShowPieChartButton();
    this->setUpNavigateButton();
    this->setUpChartBackButton();
    this->setUpPreviousButton();
    this->setUpNextButton();
    this->setUpNavigateButton();
    this->setUplikeButton();
    this->setUpNavigateButton();
    this->setUpAddToWatchlistButton();
    this->setUpOpenLinkButton();
    this->setUpNavigateBackButton();
    this->setUpTableViewButton();
    this->setUpViewTableBackButton();
    // this->setUpViewTable();

    this->removeMovieWidget->setLayout(removeMovieLayout);
    this->selectFileWidget->setLayout(fileLayout);
    this->selectProfileWidget->setLayout(profileLayout);
    this->mainAdminMenuWidget->setLayout(mainAdminMenuLayout);
    this->listMoviesWidget->setLayout(listMoviesLayout);
    this->addMovieWidget->setLayout(addMovieLayout);
    this->updateMovieWidget->setLayout(updateMovieLayout);
    this->userMainMenuWidget->setLayout(userMainMenuLayout);

    this->stackedWidgets->addWidget(selectFileWidget);
    this->stackedWidgets->addWidget(selectProfileWidget);
    this->stackedWidgets->addWidget(mainAdminMenuWidget);
    this->stackedWidgets->addWidget(listMoviesWidget);
    this->stackedWidgets->addWidget(addMovieWidget);
    this->stackedWidgets->addWidget(removeMovieWidget);
    this->stackedWidgets->addWidget(updateMovieWidget);
    this->stackedWidgets->addWidget(userMainMenuWidget);
    this->stackedWidgets->addWidget(genreFilterWidget);
    this->stackedWidgets->addWidget(watchlistWidget);
    this->stackedWidgets->addWidget(pieChartWidget);
    this->stackedWidgets->addWidget(navigateWidget);
    this->stackedWidgets->addWidget(viewTableWidget);

    this->addMovieLayout->addLayout(movieInformation, 4);
    this->addAndBackLayout->addWidget(addMovieButton);
    this->addAndBackLayout->addWidget(addBackPushButton);
    this->addMovieLayout->addLayout(addAndBackLayout);

    this->movieInformationRemove->addRow("Title:", movieToRemoveName);
    this->removeMovieLayout->addLayout(movieInformationRemove);
    this->removeAndBackLayout->addWidget(removeMovieButton);
    this->removeAndBackLayout->addWidget(removeBackButton);
    this->removeMovieLayout->addLayout(removeAndBackLayout);

    this->listMoviesLayout->addWidget(moviesTableWidget);
    this->listMoviesLayout->addWidget(listBackPushButton);

    this->updateMovieWidget->setLayout(updateMovieLayout);
    this->updateMovieLayout->addLayout(movieInformationUpdate);
    this->updateAndBackLayout->addWidget(updateMovieButton);
    this->updateAndBackLayout->addWidget(updateBackButton);
    this->updateMovieLayout->addLayout(updateAndBackLayout);

    this->genreFilterWidget->setLayout(genreFilterLayout);
    this->filterAndBackLayout->addWidget(filterButton);
    this->filterAndBackLayout->addWidget(filterAndBackButton);
    this->genreFilterLayout->addLayout(filterAndBackLayout);
    this->genreFilterLayout->addWidget(genresComboBox);
    this->genreFilterLayout->addWidget(genreTable);

    this->watchlistWidget->setLayout(watchlistLayout);
    this->watchlistLayout->addWidget(openFileButton);
    this->watchlistLayout->addWidget(watchlistBackButton);
    this->watchlistLayout->addWidget(watchlistTable);

    this->pieChartWidget->setLayout(pieChartLayout);
    this->pieChartLayout->addWidget(chartBackButton);

    this->navigateWidget->setLayout(navigateMovielist);
    this->navigateMovielist->addLayout(navigateButtonsLayout);
    this->navigateButtonsLayout->addWidget(previousButton);
    this->navigateButtonsLayout->addWidget(likeButton);
    this->navigateButtonsLayout->addWidget(addToWatchlistButton);
    this->navigateButtonsLayout->addWidget(openLinkButton);
    this->navigateButtonsLayout->addWidget(nextButton);
    this->navigateMovielist->addWidget(navigateBackButton);
    this->navigateMovielist->insertLayout(0, currentMovieInformation);
    this->navigationIndex = 0;

    this->viewTableWidget->setLayout(viewTableLayout);
    this->viewTableLayout->insertWidget(0, tableView);
    this->viewTableWidget->setLayout(viewTableLayout);

    this->fileLayout->setAlignment(Qt::AlignCenter);
    this->profileLayout->setAlignment(Qt::AlignCenter);
    this->mainAdminMenuLayout->setAlignment(Qt::AlignCenter);
    this->listMoviesLayout->setAlignment(Qt::AlignCenter);
    this->addMovieLayout->setAlignment(Qt::AlignCenter);
    this->removeMovieLayout->setAlignment(Qt::AlignCenter);
    this->updateMovieLayout->setAlignment(Qt::AlignCenter);
    this->userMainMenuLayout->setAlignment(Qt::AlignCenter);
    this->genreFilterLayout->setAlignment(Qt::AlignCenter);
    // this->navigateMovielist->setAlignment(Qt::AlignCenter);

    this->setCentralWidget(stackedWidgets);
    this->stackedWidgets->setCurrentWidget(selectFileWidget);

    auto undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    connect(undoShortcut, &QShortcut::activated, this, handleUndo);

    auto redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
    connect(redoShortcut, &QShortcut::activated, this, handleRedo);

    this->show();
}

void MainWindow::setUpHTMLButton() {
    this->HTMLButton = new QPushButton("HTML", this);
    this->HTMLButton->resize(100, 100);
    this->HTMLButton->setGeometry(150, 300, 200, 200);
    HTMLButton->setStyleSheet(buttonStyle);
    this->HTMLButton->setFixedSize(buttonSize);
    connect(this->HTMLButton, &QPushButton::clicked, this, &MainWindow::setUpHTMLController);

    this->fileLayout->addWidget(this->HTMLButton);
}

void MainWindow::setUpCSVButton() {
    this->CSVButton = new QPushButton("CSV", this);
    this->CSVButton->resize(100, 100);
    this->CSVButton->setGeometry(450, 300, 200, 200);
    this->CSVButton->setStyleSheet(buttonStyle);
    this->CSVButton->setFixedSize(buttonSize);
    connect(this->CSVButton, &QPushButton::clicked, this, &MainWindow::setUpCSVController);

    this->fileLayout->addWidget(this->CSVButton);
}

void MainWindow::setUpAdminButton() {
    this->selectAdminButton = new QPushButton("Admin", this);
    this->selectAdminButton->resize(100, 100);
    this->selectAdminButton->setGeometry(450, 300, 200, 200);
    this->selectAdminButton->setStyleSheet(buttonStyle);
    this->selectAdminButton->setFixedSize(buttonSize);
    connect(this->selectAdminButton, &QPushButton::clicked, this, &MainWindow::selectAdmin);

    this->profileLayout->addWidget(selectAdminButton);
}

void MainWindow::setUpUserButton() {
    this->selectUserButton = new QPushButton("User", this);
    this->selectUserButton->resize(100, 100);
    this->selectUserButton->setGeometry(150, 300, 200, 200);
    this->selectUserButton->setStyleSheet(buttonStyle);
    this->selectUserButton->setFixedSize(buttonSize);
    connect(this->selectUserButton, &QPushButton::clicked, this, &MainWindow::selectUser);

    this->profileLayout->addWidget(selectUserButton);
}

void MainWindow::setUpHTMLController() {
    this->HTMLButton->hide();
    this->CSVButton->hide();
    this->controller = new Controller(R"(C:\Users\lucac\CLionProjects\oop-a4-5-kpunkk_67\src\input_output\movies.html)", "HTML");
    this->stackedWidgets->setCurrentWidget(selectProfileWidget);
}

void MainWindow::setUpCSVController () {
    this->HTMLButton->hide();
    this->CSVButton->hide();
    this->controller = new Controller(R"(C:\Users\lucac\CLionProjects\oop-a4-5-kpunkk_67\src\input_output\movies.csv)", "CSV");
    this->stackedWidgets->setCurrentWidget(selectProfileWidget);
}

void MainWindow::selectUser() const {
    this->stackedWidgets->setCurrentWidget(userMainMenuWidget);
}

void MainWindow::selectAdmin() const {
    this->stackedWidgets->setCurrentWidget(mainAdminMenuWidget);
}

void MainWindow::handleUndo() {
    this->controller->undo();
}

void MainWindow::handleRedo() {
    this->controller->redo();
}