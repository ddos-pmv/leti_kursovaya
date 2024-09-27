CREATE TABLE drivers (
                         id INTEGER PRIMARY KEY AUTOINCREMENT,
                         name TEXT NOT NULL,
                         age INTEGER NOT NULL,
                         team TEXT,
                         points INTEGER NOT NULL,
                         UNIQUE (name)
);

CREATE TABLE mechanics (
                           id INTEGER PRIMARY KEY AUTOINCREMENT,
                           name TEXT NOT NULL,
                           age INTEGER NOT NULL,
                           team TEXT,
                           specialty TEXT NOT NULL,
                           UNIQUE (name)
);

CREATE TABLE team_managers (
                              id INTEGER PRIMARY KEY AUTOINCREMENT,
                              name TEXT NOT NULL,
                              age INTEGER NOT NULL,
                              team TEXT,
                              UNIQUE (name)
);

CREATE TABLE tracks (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        name TEXT NOT NULL,
                        location TEXT NOT NULL,
                        UNIQUE (name, location)
);

CREATE TABLE races (
                       id INTEGER PRIMARY KEY AUTOINCREMENT,
                       track_id INTEGER,
                       date TEXT NOT NULL,
                       FOREIGN KEY(track_id) REFERENCES Tracks(id)
);

CREATE TABLE race_participation (
                                   id INTEGER PRIMARY KEY AUTOINCREMENT,
                                   race_id INTEGER,
                                   driver_id INTEGER,
                                   team TEXT NOT NULL,
                                   position INTEGER,
                                   FOREIGN KEY(race_id) REFERENCES races(id),
                                   FOREIGN KEY(driver_id) REFERENCES drivers(id),
                                   UNIQUE (driver_id, race_id)
);
