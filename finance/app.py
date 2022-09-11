import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # get the user data and send it to the HTML page to display it
    users = db.execute(
        "SELECT users.cash, purchase.symbol,purchase.price,purchase.symbol_name,purchase.shares,purchase.total FROM users JOIN purchase ON users.username = purchase.username WHERE id =?", session["user_id"])

    return render_template("index.html", users=users)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # if the method is post then you get the data from the user to buy
    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Unvalid Shares")

        # call lookup to look up a stock’s current price
        dic_sym = lookup(symbol)
        # check for errors (Require that a user input a stock’s symbol and shares)
        if dic_sym is None:
            return apology("this symbol does not exist")
        elif not symbol:
            return apology("Unvalid Symbol")
        elif shares <= 0:
            return apology("Unvalid Shares")
        else:
            symbol_price = float(dic_sym["price"])
            user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            total = symbol_price * shares
            if (total) > user_cash[0]["cash"]:
                return apology("you need more money to buy!")
            else:

                user_cash_after = user_cash[0]["cash"] - total
                db.execute("UPDATE users SET cash=?  WHERE id = ?", user_cash_after, session["user_id"])

                username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])

                now = datetime.now()
                dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
                db.execute("INSERT INTO history (username, symbol, price, time, shares) VALUES(?,?,?,?,?)",
                           username[0]["username"], symbol, symbol_price, dt_string, shares)
                db.execute("INSERT INTO purchase (username, symbol, price, symbol_name, shares, total) VALUES(?,?,?,?,?,?)",
                           username[0]["username"], symbol, symbol_price, dic_sym["name"], shares, total)

                return redirect("/")
    # if the method is get you display the buy form to the user
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    history = db.execute("SELECT symbol,price,time,shares FROM history WHERE username=?", username[0]["username"])
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        dic_sym = lookup(symbol)

        if dic_sym is None:
            return apology("this symbol does not exist")
        else:
            return render_template("quote.html", dic_sym=dic_sym)
    else:
        return render_template("quoted.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        name = request.form.get("username")
        passwordCon = request.form.get("confirmation")
        password = request.form.get("password")

        names = db.execute("SELECT * FROM users WHERE username = ?", name)

        if not name:
            return apology("Username is not available")

        elif len(names) != 0:
            return apology("username already exists")

        elif not password or not passwordCon:
            return apology("Missing Password")

        elif password != passwordCon:
            return apology("Passwords Don't Match")

        else:
            hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", name, hash)

            rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
            session["user_id"] = rows[0]["id"]

            return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        shares = int(request.form.get("shares"))
        symbol = request.form.get("symbol")
        users = db.execute(
            "SELECT users.cash, users.username, purchase.symbol,purchase.price,purchase.symbol_name,purchase.shares,purchase.total FROM users JOIN purchase ON users.username = purchase.username WHERE users.id =? AND purchase.symbol = ?", session["user_id"], symbol)

        if shares > users[0]["shares"] or shares <= 0:
            return apology("invalid shares")
        elif not symbol:
            return apology("symbol required")
        else:
            users[0]["shares"] = users[0]["shares"] - shares
            users[0]["cash"] = users[0]["cash"] + (shares * users[0]["price"])
            users[0]["total"] = users[0]["total"] - (shares * users[0]["price"])

            if users[0]["shares"] == 0:
                db.execute("DELETE FROM purchase WHERE purchase.symbol = ?", symbol)

            now = datetime.now()
            dt_string = now.strftime("%d/%m/%Y %H:%M:%S")

            db.execute("INSERT INTO history (username, symbol, price, time, shares) VALUES(?,?,?,?,?)",
                       users[0]["username"], symbol, users[0]["price"], dt_string, -1*shares)
            db.execute("UPDATE users SET cash=? WHERE id = ?", users[0]["cash"], session["user_id"])
            db.execute("UPDATE purchase SET shares=?, total=? WHERE username = ? AND purchase.symbol = ?",
                       users[0]["shares"], users[0]["total"], users[0]["username"], symbol)

            return redirect("/")
    else:
        options = db.execute(
            "SELECT purchase.symbol FROM users JOIN purchase ON users.username = purchase.username WHERE id =?", session["user_id"])
        return render_template("sell.html", options=options)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        old = request.form.get("old_password")
        new = request.form.get("new_password")
        confirm = request.form.get("confirm_password")
        password = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])

        if not old or not new or not confirm:
            return apology("Missing Password")
        elif not check_password_hash(password[0]["hash"], old):
            return apology("Password is not correct")
        elif not (new == confirm):
            return apology("Passwords Don't Match")
        else:
            db.execute("UPDATE users SET hash =? WHERE id = ?", generate_password_hash(
                new, method='pbkdf2:sha256', salt_length=8), session["user_id"])

        return redirect("/")

    else:
        return render_template("change_password.html")