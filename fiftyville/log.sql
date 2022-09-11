-- Keep a log of any SQL queries you execute as you solve the mystery.
-- getting the description of the crime
SELECT description FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28
AND street = "Humphrey Street" AND id = 295;


-- getting the transcript of the witnesses on this day and looking for the word of thief in it
SELECT transcript, name FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28
AND transcript LIKE "%thief%";


--looking for the withdrawal atm transactions which happened in the Leggett Street on this day because of EUGENE testimony
SELECT account_number, amount FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28
AND atm_location = "Leggett Street"
AND transaction_type = "withdraw";


-- getting the names of the persons relating to the accounts numbers which we got and the amounts of money
SELECT name, atm_transactions.amount  FROM people JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2021 AND month = 7 AND day = 28
AND atm_location = "Leggett Street"
AND transaction_type = "withdraw";



--getting the names , abbreviations and cities of the airports in fifyville because of RAYMOND testimony
SELECT full_name, abbreviation,city FROM airports
WHERE city = "Fiftyville";


-- getting the flights in this day from Fiftyville
SELECT flights.id, flights.hour, flights.minute, full_name, city FROM flights
JOIN airports
ON flights.destination_airport_id = airports.id
WHERE flights.origin_airport_id =
(SELECT id FROM airports
WHERE city = "Fiftyville")
AND flights.year = 2021 AND flights.month = 7
AND flights.day = 29 ;



-- we found that the first flight the next day was to New York City at LaGuardia Airport at 8:20 and id(36)
-- so the next step is to find the passengers on this flight
SELECT passengers.passport_number, passengers.seat, name FROM people
JOIN passengers
ON passengers.passport_number = people.passport_number
JOIN flights
ON flights.id = passengers.flight_id
WHERE flights.id =36;



-- we also has information that the thief talked to someone less than one minute
-- so we get the calls happened is this day and get the names of the receivers
SELECT name, phone_calls.duration FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.receiver
WHERE phone_calls.year = 2021 AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60;



-- so we get the calls happened is this day and get the names of the callers
SELECT name, phone_calls.duration FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2021 AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60;




-- we had also an information form Ruth that within ten minutes of the theft , he saw the thief get into a car in the bakery parking lot and drive away.
-- so we will get the names of the owners of this cars
SELECT name FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.day = 28
AND bakery_security_logs.month = 7
AND bakery_security_logs.hour = 10
AND (bakery_security_logs.minute >= 15 AND bakery_security_logs.minute <= 25)
AND bakery_security_logs.activity = "exit";



-- so finally i think the thief is bruce because i found him in all the lists