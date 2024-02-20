-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check the description of the crime scene report for the crime commited
SELECT description
FROM crime_scene_reports
WHERE (year, month, date) = (2023, 7, 28)
AND street = 'Humphrey Street';

-- Read the interviews conducted on the witnesses of the crime to try and get an understanding of what have happened
SELECT name, transcript
FROM interviews
WHERE (year, month, date) = (2023, 7, 28)
AND transcript
LIKE "%bakery%";

-- Check license plates of cars that exit bakery within 10 min of crime to try and see thiefs plate
SELECT hour, minute, activity, license_plate
FROM bakery_security_logs
WHERE (year, month, day, hour) = (2023, 7, 28, 10) AND minute > 15 AND minute < 30;

-- Check ATM transactions from witness interview to try and catch any abnormalities
SELECT account_number, transaction_type, amount
FROM atm_transactions
WHERE (year, month, day) = (2023, 7, 28)
AND atm_location = "Leggett Street";

-- Check person_id on all acocunt numbers that withdrew money on the day of the theft
SELECT person_id
FROM bank_accounts
WHERE account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE (year, month, day) = (2023, 7, 28)
    AND atm_location = "Leggett Street");

-- Check all phone calls the day of the crime to see which two numbers talked less than a minute as given by a witness
SELECT caller, receiver, duration
FROM phone_calls
WHERE (year, month, day) = (2023, 7, 28)
AND duration < 60;

-- Get the name of the persons that withdrew money from the ATM at the crime day, left the bakery in the 10 min span of the crime and called someone and had a conversation that was < 1 min
SELECT name FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE (year, month, day) = (2023, 7, 28)
        AND atm_location = "Leggett Street"))
AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE (year, month, day, hour) = (2023, 7, 28, 10)
    AND minute > 15
    AND minute < 30)
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE (year, month, day) = (2023, 7, 28)
    AND duration < 60);

-- Check information about Fiftyville airport
SELECT * FROM airports WHERE city = "Fiftyville";

-- Get the flights that will depart from Fiftyville day after crime, order by hour to get the earliest flight as mentioned by witness
SELECT *
FROM flights
WHERE origin_airport_id IN (
    SELECT id
    FROM airports
    WHERE city = "Fiftyville")
AND (year, month, day) = (2023, 7, 29) ORDER BY hour;

-- Get the destination city of the earliest fligh out of Fiftyville the day after the crime
SELECT city
FROM airports
WHERE id IN (
    SELECT destination_airport_id
    FROM flights
    WHERE origin_airport_id IN (
        SELECT id
        FROM airports
        WHERE city = "Fiftyville")
    AND (year, month, day) = (2023, 7, 29) ORDER BY hour LIMIT 1);

-- Check passenger list for earliest flight out of Fiftyville July 28th
SELECT *
FROM passengers
WHERE flight_id IN (
    SELECT id
    FROM flights
    WHERE origin_airport_id IN (
        SELECT id
        FROM airports
        WHERE id = 8)
    AND destination_airport_id IN (
        SELECT id
        FROM airports
        WHERE id = 4)
    AND (year, month, day) = (2023, 7, 29));

-- Get the name of the person that commited the crime using the fact that we know that they withdrew money from the ATM at the crime day,
-- left the bakery in the 10 min span of the crime and called someone and had a conversation that was < 1 min and was on the first flight out of Fiftyville the day after the crime
SELECT name FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE (year, month, day) = (2023, 7, 28)
        AND atm_location = "Leggett Street"))
AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE (year, month, day, hour) = (2023, 7, 28, 10)
    AND minute > 15
    AND minute < 30)
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE (year, month, day) = (2023, 7, 28)
    AND duration < 60)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN (
        SELECT id
        FROM flights
        WHERE origin_airport_id IN (
            SELECT id
            FROM airports
            WHERE id = 8)
    AND destination_airport_id IN (
            SELECT id
            FROM airports
            WHERE id = 4)
    AND (year, month, day) = (2023, 7, 29)));

-- Check who Bruce called on the day of the crime
SELECT name
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE (year, month, day) = (2023, 7, 28)
    AND duration < 60
    AND caller IN (
        SELECT phone_number
        FROM people
        WHERE name = "Bruce"));
