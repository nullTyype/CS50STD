-- Keep a log of any SQL queries you execute as you solve the mystery.
-- SELECT *
-- FROM crime_scene_reports
-- WHERE street = 'Humphrey Street' AND day = 28 AND month = 7 AND year = 2021;
-- overview of crime reports at the crime date;

-- SELECT *
-- FROM interviews
-- WHERE day = 28 AND month = 7 AND year = 2021;
-- exposes people interview, the three witnesses are: Ruth, Eugene and Raymond;
-- the theft took about 10 minutes to occur, began at 10:15 and ended 10:25 approximately;
-- the thief was on morning at ATM on Leggett Street;
-- thief took the earliest flight out of Fiftyville tomorrow;

-- SELECT *
-- FROM flights
-- WHERE day = 29 AND month = 7 AND year = 2021;
-- at 16:00 took a flight from Fiftyville Regional Airport(id:8) to Logan International Airport(id:6);

-- SELECT *
-- FROM phone_calls
-- WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60;
-- subquery to get people name;

-- SELECT *
-- FROM flights
-- WHERE day = 29 AND month = 7 AND year = 2021;
-- at 16:00 took a flight from Fiftyville Regional Airport(id:8) to LaGuardia Airport(id:4);
-- where flight id = 36;
-- subquery to get flight id;

-- SELECT *
-- FROM passengers
-- WHERE flight_id = 18;
-- subquery to get flight passengers;

-- SELECT * FROM bakery_security_logs
-- WHERE day = 28 AND month = 7 AND year = 2021 AND hour BETWEEN 10 AND 17;
-- select within a range of hours the suspects could be at bakkery to identify the license plate;
-- subquery to get license plate;

-- SELECT *
-- FROM atm_transactions
-- WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = 'Leggett Street';

SELECT people.id AS thief_id, people.name AS name, people.phone_number AS number
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute BETWEEN 15 AND 30)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36)
AND id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = 'Leggett Street'))
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60);
-- crosses information using existing subqueries to find thief;

SELECT people.id AS accomplice_id, people.name AS name, people.phone_number AS number
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60 AND caller = '(367) 555-5533');
-- gets accomplice id;

-- finally, the subqueries to discover thief's and accomplice ids are commented to doesn't mess up the query result;