import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)
app.secret_key = 'super ultra secure secret key'

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    name = request.form.get("name")
    month = request.form.get("month")
    day = request.form.get("day")

    if request.method == "POST":
        # TODO: Add the user's entry into the database

        if not (1 <= int(month) <= 12) or not ( 1 <= int(day) <= 31) or name == "":
            flash("There was an error with the provided information. Your birthday wasn't saved.")
        else:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
            flash("Your birthday was successfully added.")

        return redirect("/")
    else:
        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", birthdays=birthdays)


# delete route;
@app.route("/delete", methods=["POST"])
def delete():
    user_id = request.form.get("user_id")

    if user_id:
        db.execute("DELETE FROM birthdays WHERE id = ?", user_id)
        flash("Birthday was succesfully deleted.")
    else:
        flash("Failed to delete birth.")

    return redirect("/")


# edit route;
@app.route("/edit", methods=["GET", "POST"])
def edit():
    name = request.form.get("name")
    month = request.form.get("month")
    day = request.form.get("day")

    if request.method == 'POST':
        birthdays = db.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?", name, month, day, request.form.get("user_id"))
        flash("Successfully updated birthday")
        return redirect(f"/edit?user_id={request.form.get('user_id')}")
    else:
        birthdays = db.execute("SELECT * FROM birthdays WHERE id = ?", request.args.get("user_id"))

    return render_template("edit.html", birthdays=birthdays)
