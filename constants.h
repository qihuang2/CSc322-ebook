#ifndef CONSTANTS_H
#define CONSTANTS_H

class QString;

extern const QString appDir;
extern const QString docDir;

typedef enum {
    _SELECT_,
    BIO,
    FANTASY,
    HISTORY,
    HORROR,
    KIDS,
    MANGA,
    MYSTERY,
    MYTH,
    ROMANCE,
    SCIFI,
    YOUNGADULT
} Genre;

extern const QString genres[];
extern int genreSize;

#endif // CONSTANTS_H
