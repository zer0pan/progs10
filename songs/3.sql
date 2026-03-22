--names of the top 5 longest songs, in descending order of length
SELECT name FROM songs
ORDER BY LENGTH(name) DESC;