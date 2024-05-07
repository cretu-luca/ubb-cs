#pragma once
#include "GUI/gui.h"

class AdminMenuWidget: public QWidget {
    Q_OBJECT
protected:
    Controller* controller;
public:
    explicit AdminMenuWidget(QWidget* parent = nullptr, Controller* controller = nullptr);
    // Main admin menu
    QPushButton* addMovieButton{};
    QPushButton* removeMovieButton{};
    QPushButton* updateMovieButton{};
    QPushButton* listAllMoviesButton{};
    QPushButton* backPushButton{};

    QVBoxLayout* mainLayout;
    QGridLayout* gridLayout;

    QFormLayout* addFormLayout{};
    QFormLayout* removeFormLayout{};
    QFormLayout* updateFormLayout{};
    QTableWidget* tableWidget{};

    // Group box that handles the main QLineEdit's
    QGroupBox* getMovieDetailsGroupBox{};
    QLineEdit* titleLine{};
    QLineEdit* genreLine{};
    QLineEdit* linkLine{};
    QLineEdit* releaseYearLine{};
    QLineEdit* likesLine{};
    QCheckBox* inWatchlist{};

    void setUpGetMovieDetailsGroupBox();
    void hideGetMovieDetailsGroupBox() const;

    // Group box that handles adding
    QGroupBox* addMovieGroupBox{};
    QPushButton* addMovieDetailsButton{};
    void setUpAddGroupBox();

    // Group box that handles removing
    QGroupBox* removeMovieGroupBox{};
    QPushButton* removeMovieDetailsButton{};
    QLineEdit* nameOfMovieToDelete{};
    void setUpRemoveGroupBox();

    // Group box that handles updating
    QGroupBox* updateMovieGroupBox{};
    QPushButton* updateMovieDetailsButton{};
    QLineEdit* indexOfMovieToUpdate{};
    void setUpUpdateGroupBox();

    void showMainPushButtons() const;
    void hideMainPushButtons() const;
    void setUpBackButton();

    const QSize buttonSize = QSize(200, 100);

public slots:
    void addMovieGUI() const;
    void removeMovieGUI() const;
    void updateMovieGUI() const;
    void listMoviesGUI() const ;
    void SetUpAddMoviePushButton();
    void SetUpRemoveMoviePushButton();
    void SetUpUpdateMoviePushButton();
    void setUpListMoviesPushButton();
    void addMovieDetails() const;
    void removeMovieDetails() const;
    void updateMovieDetails() const;
    void backToAdminMenu() const;
};
