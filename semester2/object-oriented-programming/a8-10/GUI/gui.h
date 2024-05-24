#pragma once
#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QHeaderView>
#include "controller/controller.h"
#include <QCheckBox>
#include <QMainWindow>
#include <QStackedWidget>
#include <QComboBox>
#include <QFont>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <set>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>
#include <QShortcut>

#include "tableView.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
protected:
    Controller* controller;

public:
    explicit MainWindow(QWidget* parent = nullptr);

    QStackedWidget* stackedWidgets;

    QWidget* selectFileWidget;
    QVBoxLayout* fileLayout;
    QPushButton* HTMLButton{};
    QPushButton* CSVButton{};
    void setUpHTMLButton();
    void setUpCSVButton();

    QWidget* selectProfileWidget;
    QVBoxLayout* profileLayout;
    QPushButton* selectUserButton{};
    QPushButton* selectAdminButton{};
    void setUpUserButton();
    void setUpAdminButton();

    QWidget* mainAdminMenuWidget;
    QGridLayout* mainAdminMenuLayout;
    QPushButton* undoButton{};
    QPushButton* redoButton{};
    QPushButton* addMovieOptionButton{};
    QPushButton* removeMovieOptionButton{};
    QPushButton* updateMovieOptionButton{};
    QPushButton* listAllMoviesOptionButton{};

    QPushButton* addBackPushButton{};
    QPushButton* listBackPushButton{};
    void setUpAddMovieOptionButton();
    void setUpRemoveMovieOptionButton();
    void setUpUpdateMovieOptionButton();
    void setUpListMoviesOptionButton();
    void setUpAddBackButton();
    void setUpListBackButton();
    void setUpUndoButton();
    void setUpRedoButton();

    QWidget* listMoviesWidget;
    QTableWidget* moviesTableWidget;
    QVBoxLayout* listMoviesLayout;
    void listMovies();

    QWidget* addMovieWidget;
    QVBoxLayout* addMovieLayout;
    QHBoxLayout* addAndBackLayout;
    QPushButton* addMovieButton{};
    void addMovieDetails();
    void setUpAddMovieButton();
    void addMovieGUI();

    QWidget* removeMovieWidget;
    QVBoxLayout* removeMovieLayout;
    QPushButton* removeMovieButton{};
    QLineEdit* movieToRemoveName;
    QPushButton* removeBackButton{};
    QHBoxLayout* removeAndBackLayout;
    void setUpRemoveMovieButton();
    void removeMovieDetails();
    void removeMovieGUI();
    void setUpRemoveBackButton();

    QWidget* updateMovieWidget;
    QVBoxLayout* updateMovieLayout;
    QPushButton* updateMovieButton{};
    QLineEdit* indexOfMovieToUpdate{};
    QHBoxLayout* updateAndBackLayout;
    QPushButton* updateBackButton{};
    void setUpUpdateMovieButton();
    void updateMovieDetails();
    void updateMovieGUI();
    void setUpUpdateBackButton();

    void setUpMovieInformation();

    QFormLayout* movieInformation;
    QLineEdit* titleLine{};
    QLineEdit* genreLine{};
    QLineEdit* linkLine{};
    QLineEdit* releaseYearLine{};
    QLineEdit* likesLine{};
    QCheckBox* inWatchlist{};
    void clearLineEdits() const;

    QLineEdit* updateTitleLine{};
    QLineEdit* updateGenreLine{};
    QLineEdit* updateLinkLine{};
    QLineEdit* updateReleaseYearLine{};
    QLineEdit* updateLikesLine{};
    QCheckBox* updateInWatchlist{};

    QFormLayout* movieInformationRemove;
    QFormLayout* movieInformationUpdate;
    void setUpMovieUpdateInformation();

    QTableWidget* getTable() const;
    QTableWidget* removeMoviesInformationTable;
    QTableWidget* addMoviesInformationTable;
    QTableWidget* updateMoviesInformationTable;
    void clearUpdateLineEdits() const;

    QPushButton* mainMenuBackButton{};
    void setUpMainMenuBackButton();

    const QSize buttonSize = QSize(175, 75);
    const QString buttonStyle = R"(
        QPushButton {
            font-size: 14pt;
            color: black;
            background-color: AliceBlue;
            border: 1px solid #8f8f91;
            border-radius: 6px;
            padding: 6px;
        }
        QPushButton:hover {
            background-color: #dfdfdf;
        }
        QPushButton:pressed {
            background-color: #bfbfbf;
        }
    )";

    QPushButton* userBackButton{};
    QPushButton* listWatchlistOptionButton{};
    QPushButton* filterOptionButton{};
    QPushButton* filterButton{};
    QPushButton* filterAndBackButton{};
    QComboBox* genresComboBox;
    QCheckBox* inWatchlistCheckBoxUser{};
    QTableWidget* genreTable;
    QTableWidget* watchlistTable;
    QTableWidget* getWatchlistTable();

    QTableWidget* getGenreTable(QString genre);

    void setUpUserBackButton();
    void setUpUserFilterOptionButton();
    void setUpListWatchlistOptionButton();
    void filterGUI();
    void listWatchlistGUI();
    void setUpFilterButton();
    void filterByGenre();
    void populateGenresComboBox();
    void setUpFilterBackButton();
    void setUpWatchlistBackButton();
    void setUpOpenFileButton();

    void setUpTableViewButton();
    void handleView();
    QPushButton* tableViewButton;

    void handleOpenFile();

    QWidget* userMainMenuWidget;
    QGridLayout* userMainMenuLayout;
    QWidget* genreFilterWidget;
    QVBoxLayout* genreFilterLayout;
    QHBoxLayout* filterAndBackLayout;

    QFont comboBoxFont;
    QVBoxLayout* watchlistLayout;
    QPushButton* watchlistBackButton{};
    QWidget* watchlistWidget;
    QPushButton* openFileButton{};

    QChartView* genreChartView;
    QVBoxLayout* pieChartLayout;
    QWidget* pieChartWidget;
    QPushButton* showPieChartButton{};

    QPushButton* navigateOptionButton{};

    QChart* chart;
    QPieSeries* series;

    QPushButton* chartBackButton{};

    void setUpNavigateButton();
    void setUpShowPieChartButton();
    void showGenrePieChart();
    void navigateButtonGUI();
    void setUpChartBackButton();

    int navigationIndex;
    QPushButton* previousButton{};
    QPushButton* nextButton{};
    QPushButton* likeButton{};
    QPushButton* addToWatchlistButton{};
    QPushButton* openLinkButton{};

    void setUpPreviousButton();
    void setUpNextButton();
    void setUplikeButton();
    void setUpAddToWatchlistButton();
    void setUpOpenLinkButton();

    void moveToPreviousMovie();
    void moveToNextMovie();
    void likeCurrentMovie();
    void changeWatchlistStatus();

    void updateMovieInformation();
    void setUpNavigateBackButton();

    QWidget* navigateWidget;
    QHBoxLayout* navigateButtonsLayout;
    QVBoxLayout* navigateMovielist;
    QPushButton* navigateBackButton{};

    QFormLayout* currentMovieInformation;

    void openLinkGUI();

    void handleUndo();
    void handleRedo();

    QWidget* viewTableWidget;
    QVBoxLayout* viewTableLayout;
    QPushButton* viewTableBackButton{};

    void setUpViewTableBackButton();

    // void setUpViewTable();
    MyTableModel* tableModel;
    QTableView* tableView;

public slots:
    void selectUser() const;
    void selectAdmin() const;

    void setUpHTMLController();
    void setUpCSVController();
    void handleBackButtonClick() const;
};
