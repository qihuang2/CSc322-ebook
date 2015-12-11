#include "constants.h"
#include <QString>
#include <QDir>

const QString appDir = QDir::homePath() + "/ebook";
const QString docDir = appDir + "/docs";

const QString genres[] = {
    "-- Select --",
    "Biography",
    "Fantasy",
    "History",
    "Horror",
    "Kids",
    "Manga",
    "Mystery",
    "Mythology",
    "Romance",
    "Science Fiction",
    "Young Adult"
};

int genreSize = sizeof (genres) / sizeof (genres[0]);
