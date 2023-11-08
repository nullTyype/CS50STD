SELECT DISTINCT people.name
FROM people
WHERE people.id IN
    (SELECT DISTINCT directors.person_id
    FROM directors
    WHERE directors.movie_id IN
        (SELECT DISTINCT movies.id
        FROM (movies
        JOIN ratings ON movies.id = ratings.movie_id)
        WHERE movie_id IN (SELECT movie_id FROM ratings WHERE rating >= 9)));