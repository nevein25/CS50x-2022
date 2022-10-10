-- list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.
-- Your query should output a table with two columns, one for the title of each movie and one for the rating of each movie.
-- Movies that do not have ratings should not be included in the result.

SELECT r.rating, m.title FROM ratings r, movies m  WHERE r.movie_id = m.id AND m.year = 2010 AND rating IS NOT NULL ORDER BY rating DESC,title;
