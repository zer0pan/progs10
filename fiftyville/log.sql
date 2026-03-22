-- Keep a log of any SQL queries you execute as you solve the mystery.

--The theft took place on July 28, 2025 and that it took place on Humphrey Street
--Head start 
SELECT * FROM crime_scene_reports
WHERE month = 7 AND
day = 28 AND year = 2025
AND street = 'Humphrey Street';

--Lead 1
--Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. 
--Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery

SELECT * FROM interviews
WHERE month = 7 AND
day = 28 AND year = 2025
AND transcript LIKE '%bakery%'

"""
│ 161 │ Ruth    │ 2025 │ 7     │ 28  │ Sometime within ten minutes of the 
theft, I saw the thief get into a car in the bakery 
parking lot and drive away. If you have /security footage/ 
from the bakery parking lot, you might want to look for cars that left the 
parking lot in that time frame.                                                 

│ 162 │ Eugene  │ 2025 │ 7     │ 28  │ I don't know the thief's name, but 
it was someone I recognized. Earlier this morning, 
before I arrived at Emma's bakery, I was walking by the ATM on Leggett 
Street and saw the thief there withdrawing some money.   

│ 163 │ Raymond │ 2025 │ 7     │ 28  │ As the thief was leaving the bakery, 
they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the 
earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase 
the flight ticket. """

--From Ruth
SELECT * FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE month = 7 AND
day = 28 AND year = 2025
AND hour = 10 AND minute >= 15 AND minute <= 25;

--From Eugene
SELECT * FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE month = 7 AND
day = 28 AND year = 2025
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- Combination of Ruth and Eugene = Bruce Diane Iman Luca
CREATE TABLE suspect_list AS
SELECT * FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE month = 7 AND
day = 28 AND year = 2025
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw'
AND name IN (SELECT name FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE month = 7 AND
day = 28 AND year = 2025
AND hour = 10 AND (minute > 15 AND minute < 25));

--From Raymond
CREATE TABLE suspect_calls AS
SELECT * FROM phone_calls
WHERE caller IN 
-- Using the combination of Ruth and Eugene
(SELECT phone_number FROM suspect_list)
AND duration <=60;

-- Now I have the table suspect_calls 
SELECT * from suspect_calls 
JOIN people ON caller = people.phone_number;
-- Bruce Diana Bruce

SELECT * from suspect_calls 
JOIN people ON receiver = people.phone_number
WHERE month = 7 AND
day = 28 AND year = 2025;
-- Robin Philip

--From Raymond about the flights
SELECT * FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE month = 7 AND
day = 29 AND year = 2025
ORDER BY hour ASC LIMIT 1;
--LaGuardia Airport │ New York City

-- flight_id known
SELECT name FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE flight_id = (SELECT flights.id FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE month = 7 AND
day = 29 AND year = 2025
ORDER BY hour ASC LIMIT 1)
AND name IN (SELECT name from suspect_calls 
JOIN people ON caller = people.phone_number);
--Bruce

--Accomplice : Robin