SELECT DISTINCT people.name
FROM (people
JOIN stars ON people.id = stars.person_id)
WHERE stars.movie_id IN (SELECT DISTINCT stars.movie_id
    FROM ((movies
    JOIN stars ON movies.id = stars.movie_id)
    JOIN people ON stars.person_id = person_id)
    WHERE person_id IN (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958))
AND name != 'Kevin Bacon'
