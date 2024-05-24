#include "tableView.h"

MyTableModel::MyTableModel(QObject *parent) : QAbstractTableModel(parent) {}

void MyTableModel::setMovies(const std::vector<Movie*>& movies) {
    beginResetModel();
    this->movies = movies;
    endResetModel();
}

int MyTableModel::rowCount(const QModelIndex& parent) const {
    return movies.size();
}

int MyTableModel::columnCount(const QModelIndex& parent) const {
    return 6;
}

QVariant MyTableModel::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return {};

    const Movie* movie = movies.at(index.row());

    switch (index.column()) {
        case 0: return QString::fromStdString(movie->getTitle());
        case 1: return QString::fromStdString(movie->getGenre());
        case 2: return QString::fromStdString(movie->getTrailerLink());
        case 3: return movie->getReleaseYear();
        case 4: return movie->getNumberOfLikes();
        case 5: return movie->getWatchlistStatus() ? "Yes" : "No";
        default: return QVariant();
    }
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Title";
        case 1: return "Genre";
        case 2: return "Trailer Link";
        case 3: return "Release Year";
        case 4: return "Likes";
        case 5: return "Watchlist Status";
        default: return QVariant();
        }
    }
    return QVariant();
}
