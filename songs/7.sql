--average energy of songs that are by Drake
SELECT AVG(energy) FROM songs
WHERE songs.artist_id = (
    SELECT artists.id FROM artists 
    WHERE artists.name = 'Drake'
);