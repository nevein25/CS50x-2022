-- Keep a log of any SQL queries you execute as you solve the mystery.
-- SELECT * FROM airports;
-- SELECT * FROM crime_scene_reports;
-- SELECT * FROM people;
-- SELECT * FROM atm_transactions;
-- SELECT * FROM flights;
-- SELECT * FROM phone_calls;
-- SELECT * FROM bakery_security_logs;
-- SELECT * FROM interviews;
-- SELECT * FROM bank_accounts;
-- SELECT * FROM passengers;

--All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street.
--SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street" AND month >= 7 AND day = 28;
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | id  | year | month | day |     street      |                                                                                                       description                                                                                                        |
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
-- | 297 | 2021 | 7     | 28  | Humphrey Street | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


--SELECT * FROM interviews WHERE month >= 7 AND day >= 28 AND transcript LIKE "%bakery%";
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | id  |  name   | year | month | day |                                                                                                                                                     transcript                                                                                                                                                      |
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+



-- SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28;

-- SELECT  p.name, b.year, b.hour, b.minute, p.phone_number
-- FROM people p, bakery_security_logs b
-- WHERE p.license_plate = b.license_plate
-- AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 10 AND 35;



-- +---------+------+------+--------+
-- |  name   | year | hour | minute |
-- +---------+------+------+--------+
-- | Sophia  | 2021 | 10   | 14     |
-- | Vanessa | 2021 | 10   | 16     |
-- | Bruce   | 2021 | 10   | 18     |
-- | Barry   | 2021 | 10   | 18     |
-- | Luca    | 2021 | 10   | 19     |
-- | Sofia   | 2021 | 10   | 20     |
-- | Iman    | 2021 | 10   | 21     |
-- | Diana   | 2021 | 10   | 23     |
-- | Kelsey  | 2021 | 10   | 23     |
-- | Taylor  | 2021 | 10   | 35     |
-- +---------+------+------+--------+
-- SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration <=70 ;

-- +-----+----------------+----------------+------+-------+-----+----------+
-- | id  |     caller     |    receiver    | year | month | day | duration |
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
-- | 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
-- | 234 | (609) 555-5876 | (389) 555-5198 | 2021 | 7     | 28  | 60       |
-- | 240 | (636) 555-4198 | (670) 555-8598 | 2021 | 7     | 28  | 69       |
-- | 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
-- | 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
-- | 260 | (669) 555-6918 | (971) 555-6468 | 2021 | 7     | 28  | 67       |
-- | 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
-- | 271 | (751) 555-6567 | (594) 555-6254 | 2021 | 7     | 28  | 61       |
-- | 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
-- | 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
-- +-----+----------------+----------------+------+-------+-----+----------+

-- SELECT  p.name, b.year, b.hour, b.minute, p.phone_number, p.passport_number
-- FROM people p, bakery_security_logs b
-- WHERE p.license_plate = b.license_plate AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND p.phone_number IN(
--     SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration <=60
-- );

-- +--------+------+------+--------+----------------+-----------------+
-- |  name  | year | hour | minute |  phone_number  | passport_number |
-- +--------+------+------+--------+----------------+-----------------+
-- | Bruce  | 2021 | 10   | 18     | (367) 555-5533 | 5773159633      |
-- | Sofia  | 2021 | 10   | 20     | (130) 555-0289 | 1695452385      |
-- | Diana  | 2021 | 10   | 23     | (770) 555-1861 | 3592750733      |
-- | Kelsey | 2021 | 10   | 23     | (499) 555-9472 | 8294398571      |
-- +--------+------+------+--------+----------------+-----------------+



-- SELECT * FROM flights WHERE day = 29 AND hour <= 12;
-- --SELECT * FROM airports;


-- SELECT * FROM passengers WHERE flight_id IN (

-- SELECT f.id FROM flights f  WHERE day = 29 AND hour <= 12
-- ) AND passport_number IN (
--     SELECT p.passport_number
-- FROM people p, bakery_security_logs b
-- WHERE p.license_plate = b.license_plate AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND p.phone_number IN(
--     SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration <=60
-- )
-- );
-- -- +-----------+-----------------+------+
-- | flight_id | passport_number | seat |
-- +-----------+-----------------+------+
-- | 36        | 1695452385      | 3B   |
-- | 36        | 5773159633      | 4A   |
-- | 36        | 8294398571      | 6C   |
-- +-----------+-----------------+------+


-- SELECT * FROM atm_transactions WHERE atm_location = "Leggett Street" AND transaction_type = "withdraw" AND month = 7 AND day = 28;

-- SELECT * FROM bank_accounts;
-- SELECT DISTINCT p.name
-- FROM people p , bank_accounts bc
-- WHERE bc.person_id = p.id AND passport_number = "1695452385" OR passport_number= "5773159633" OR passport_number = "8294398571";

-- +--------+
-- |  name  |
-- +--------+
-- | Kelsey |
-- | Bruce  |
-- +--------+
-- SELECT * FROM  bakery_security_logs WHERE hour = 10 AND minute >= 20 AND license_plate IN (
-- SELECT license_plate FROM people WHERE name = "Kelsey" OR name ="Bruce");

-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | id  | year | month | day | hour | minute | activity | license_plate |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
-- +-----+------+-------+-----+------+--------+----------+---------------+

-- SELECT passport_number FROM people WHERE license_plate = "0NTHK55";

-- SELECT * FROM flights WHERE id IN (
-- SELECT flight_id FROM passengers WHERE passport_number IN (SELECT passport_number FROM people WHERE license_plate = "0NTHK55"));

-- SELECT * FROM  people WHERE license_plate = "0NTHK55"
-- SELECT * FROM airports;

-- select * from people where phone_number = "(717) 555-1342";

--------------------------------------STARTING AGAIN------------------------------------------------------------
--INFO
-- theft took place on July 28, 2021
-- took place on Humphrey Street.
-- took place at 10:15am
-- took place at bakery
-- within ten minutes of the thef thief get into a car in the bakery parking lot and drive away.
-- ATM on (Leggett Street) , thief there (withdrawing) some money.
-- flight out of Fiftyville tomorrow.


--------------------------------------------------------------------------------------------------------


-- SELECT * FROM crime_scene_reports;
-- SELECT * FROM interviews;

-- SELECT * FROM bakery_security_logs;
-- SELECT * FROM atm_transactions;
-- SELECT * FROM bank_accounts;
-- SELECT * FROM phone_calls;

-- SELECT * FROM flights;
-- SELECT * FROM passengers;
-- SELECT * FROM airports;

-- SELECT * FROM people;

--1
--SELECT * FROM crime_scene_reports WHERE year = 2021 AND month =7 AND day = 28 AND street = "Humphrey Street"  ;
----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | id  | year | month | day |     street      |                                                                                                       description                                                                                                        |
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
-- | 297 | 2021 | 7     | 28  | Humphrey Street | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

--2
--SELECT * FROM interviews WHERE year = 2021 AND month =7 AND day = 28 AND transcript LIKE "%bakery%";

-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | id  |  name   | year | month | day |                                                                                                                                                     transcript                                                                                                                                                      |
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- SELECT * FROM bakery_security_logs  WHERE year = 2021 AND month =7 AND day = 28 ;
-- SELECT * FROM atm_transactions WHERE atm_location = "Leggett Street" AND transaction_type = "withdraw" AND year = 2021 AND month =7 AND day = 28;
-- SELECT * FROM phone_calls WHERE year = 2021 AND month =7 AND day = 28 AND duration <= 70;





--3
-- People who made withdrawed money in Leggett Street in the specified hour and
-- who seen within ten minutes of the thief get into a car and drove away and
-- who made the phone call in the specified hour and
-- who and had flight the next day
SELECT DISTINCT p.name, p.phone_number, ba.account_number, pc.receiver,p.passport_number , pass.flight_id, bsl.hour,bsl.minute, f.destination_airport_id
FROM people p
    JOIN bank_accounts ba
    ON p.id = ba.person_id

    JOIN atm_transactions atm
    ON ba.account_number = atm.account_number
        AND atm.atm_location = "Leggett Street"
        AND atm.transaction_type = "withdraw"
        AND atm.year = 2021 AND atm.month =7 AND atm.day = 28

    JOIN phone_calls pc
    ON p.phone_number = pc.caller
        AND pc.year = 2021 AND pc.month =7 AND pc.day = 28 AND pc.duration <= 60

    JOIN bakery_security_logs bsl
    ON p.license_plate = bsl.license_plate
        AND bsl.year = 2021 AND bsl.month =7 AND bsl.day = 28 AND bsl.hour = 10 AND bsl.minute BETWEEN 15 AND 25

    JOIN passengers pass
    ON pass.passport_number = p.passport_number

    JOIN flights f
    ON f.id = pass.flight_id
        AND f.year = 2021 AND f.month = 7 AND f.day = 29 AND f.hour <= 12;

-- +-------+----------------+----------------+----------------+-----------------+-----------+------+--------+------------------------+
-- | name  |  phone_number  | account_number |    receiver    | passport_number | flight_id | hour | minute | destination_airport_id |
-- +-------+----------------+----------------+----------------+-----------------+-----------+------+--------+------------------------+
-- | Bruce | (367) 555-5533 | 49610011       | (375) 555-8161 | 5773159633      | 36        | 10   | 18     | 4                      |
-- +-------+----------------+----------------+----------------+-----------------+-----------+------+--------+------------------------+

-- The reciever of bruce's phone call

SELECT * FROM people WHERE phone_number= "(375) 555-8161";

-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
-- +--------+-------+----------------+-----------------+---------------+

-- Bruce's destination
SELECT city FROM airports WHERE id = 4;
-- +---------------+
-- |     city      |
-- +---------------+
-- | New York City |
-- +---------------+


