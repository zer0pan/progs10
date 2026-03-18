SELECT name FROM songs
WHERE songs.artist_id = (
    SELECT artists.id FROM artists 
    WHERE artists.name = 'Post Malone'
);