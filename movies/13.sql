-- list the names of all people who starred in a movie in which Kevin Bacon also starred.
-- Your query should output a table with a single column for the name of each person.
-- There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
-- Kevin Bacon himself should not be included in the resulting list.

-- SELECT m.title FROM movies m, people p, stars s
-- WHERE m.id = s.movie_id AND s.person_id = p.id AND p.name = "Helena Bonham Carter" AND m.id IN (

-- SELECT m.id FROM movies m, stars s, people p
-- WHERE s.person_id = p.id AND m.id = s.movie_id AND  p.name = "Johnny Depp");


-- SELECT p.name FROM people p
-- WHERE p.id
-- IN (
-- SELECT s.person_id FROM stars s, movies m, people p
-- WHERE m.id = s.movie_id AND p.id = s.person_id AND p.name = "Kevin Bacon"

-- );
SELECT p.name FROM people p,stars s WHERE p.id = s.person_id AND p.name != "Kevin Bacon" AND s.movie_id  IN (

SELECT m.id FROM stars s, movies m, people p
WHERE m.id = s.movie_id AND p.id = s.person_id AND p.name = "Kevin Bacon");

