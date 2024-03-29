import csv
from cs50 import SQL

def create_house(house, houses, head):
    count = 0
    for h in houses:
        if h["house"] == house:
            count += 1
    if count == 0:
        houses.append({"house": house, "head": head})

def create_student(name, students):
    students.append({"student_name": name})

def create_relationship(name, house, relationships):
    for rel in relationships:
        if rel["student_name"] == name and rel["house"] == house:
            return  # Relationship already exists, no need to add it again
    relationships.append({"student_name": name, "house": house})

db = SQL("sqlite:///roster.db")

students = []
houses = []
relationships = []

with open("students.csv", "r") as csvfile:
    reader = csv.DictReader(csvfile)

    for row in reader:
        name = row["student_name"]
        house = row["house"]
        head = row["head"]

        create_house(house, houses, head)
        create_student(name, students)
        create_relationship(name, house, relationships)

for student in students:
    db.execute("INSERT INTO new_students (student_name) VALUES (?)", student["student_name"])

for house in houses:
    db.execute("INSERT INTO houses (house, head) VALUES (?, ?)", house["house"], house["head"])

for rel in relationships:
    db.execute("INSERT INTO relationships (student_id, house_id) VALUES ((SELECT id FROM students WHERE student_name = ?), (SELECT id FROM houses WHERE house = ?))", rel["student_name"], rel["house"])
