CREATE TABLE new_students (
    id INTEGER,
    student_name TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    id INTEGER,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE relationships (
    id INTEGER,
    student_id INTEGER,
    house_id INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(student_id) REFERENCES new_students(id),
    FOREIGN KEY(house_id) REFERENCES houses(id)
);
