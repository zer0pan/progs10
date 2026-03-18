for i in {1..8}; do
  sqlite3 songs.db < "${i}.sql"
done