SELECT name FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON movies.id = stars.movie_id WHERE name != "Kevin Bacon" AND movies.id IN (SELECT movies.id FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON people.id = stars.person_id WHERE name = "Kevin Bacon" AND birth = 1958);
