from cs50 import SQL

db = SQL("sqlite:///favorites.db")

show = input("Show: ")

rows = db.execute("SELECT COUNT(*) AS n FROM shows WHERE title LIKE ?;", show)

row = rows[0]
print(row["n"])