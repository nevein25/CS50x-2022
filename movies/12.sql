--  list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Johnny Depp.
-- You may assume that there is only one person in the database with the name Helena Bonham Carter.

-- SELECT m.title FROM movies m, stars s, people p
-- WHERE s.person_id = p.id AND m.id = s.movie_id AND  p.name = "Johnny Depp"
-- FULL OUTER JOIN
-- SELECT m.title FROM movies m, stars s, people p
-- WHERE s.person_id = p.id AND m.id = s.movie_id AND  p.name = "Helena Bonham";

-- SELECT p.id,p.name FROM movies m,stars s, people p
-- WHERE  s.person_id = p.id AND m.id = s.movie_id AND p.name = "Helena Bonham";

SELECT m.title FROM movies m, people p, stars s
WHERE m.id = s.movie_id AND s.person_id = p.id AND p.name = "Helena Bonham Carter" AND m.id IN (

SELECT m.id FROM movies m, stars s, people p
WHERE s.person_id = p.id AND m.id = s.movie_id AND  p.name = "Johnny Depp");


