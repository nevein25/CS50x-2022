import os
import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

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
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    purshases = db.execute("SELECT * FROM purchase WHERE user_id = ?", session["user_id"])

    # print(purshases[]['symbol'])
    # symbolInfo = lookup(symbol)
    # print(purshases)

    total = 0
    for purshase in purshases:
        total = total + purshase['shares'] * purshase['price']
    total = total + cash[0]['cash']
    #print(total + cash[0]['cash'])
    return render_template("index.html", purshases=purshases, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        price = lookup(symbol)

        if symbol == '' or shares == '':
            return apology("Fields can not be empty")

        if (not shares.isdigit()):
            return apology("Invalid number of shares")

        shares = int(shares)
        if shares <= 0:
            return apology("Invalid number of shares")

        if price == None:
            return apology("Symbol not found")

        else:
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cost = int(shares) * price['price']
            if int(cost) > cash[0]["cash"]:
                return apology("You do not have enough money")
            else:
                # alreadyEsistSymbol = db.execute("SELECT symbol FROM purchase WHERE user_id = ?",session["user_id"])
                db.execute("INSERT INTO purchase (symbol, shares, price, date, user_id )VALUES (?, ?, ?, ?, ?)",
                           symbol, shares, price['price'], datetime.datetime.now(), session["user_id"])

                db.execute("UPDATE users  SET cash = ?  WHERE id = ?", cash[0]["cash"] - int(cost), session["user_id"])
                return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM purchase WHERE user_id = ?", session["user_id"])

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
        stockQuote = lookup(symbol)

        if stockQuote == None:
            return apology("Stock Quote does not exsist")
        else:
            return render_template("quoted.html", stockQuote=stockQuote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if username == '' or password == '' or confirmation == '':
            return apology("must provide username and password")
        if password != confirmation:
            return apology("password does not match")
        if db.execute("SELECT username FROM users WHERE username = ?", username):
            return apology("username already taken")
        else:

            # Should have atleast 2 numbers & atleast 2 letters or symbols
            numbers = 0
            letters = 0
            for l in password:
                if l.isnumeric():
                    numbers += 1
                else:
                    letters += 1

            if numbers < 2 or letters < 2:
                return apology("Password should contain atleast 2 numbers & atleast 2 letters or symbols")
            hash = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

            # Redirect user to login form
            rows = db.execute("SELECT * FROM users WHERE username = ?", username)
            # print(rows)
            if (len(rows) == 1):
                session["user_id"] = rows[0]["id"]
            return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    symbols = db.execute("SELECT symbol FROM purchase WHERE user_id = ? GROUP BY symbol",
                         session["user_id"])

    if request.method == "POST":

        shares = request.form.get("shares")
        symbol = request.form.get("symbol")
        # print(symbol)
        if shares == '':
            return apology("Fields can not be empty")
        if not shares.isdigit():
            return apology("Invlaid shares")
        shares = int(shares)
        if shares <= 0:
            return apology("Invlaid number of shares")
        numOfShares = db.execute("SELECT shares FROM purchase WHERE user_id = ? AND symbol = ? GROUP BY symbol",
                                 session["user_id"], symbol)
        numOfShares = numOfShares[0]['shares']
        print(numOfShares)
        if (numOfShares < shares):
            return apology("You Do Not Have enough shares to sell")
        else:
            price = lookup(symbol)
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cost = shares * price['price']
            newCashAmount = cash[0]['cash'] + cost
            # print(newCash)
            db.execute("UPDATE users  SET cash = ?  WHERE id = ?", newCashAmount, session["user_id"])
            db.execute("UPDATE purchase  SET shares = ?  WHERE user_id = ? AND symbol = ?",
                       numOfShares - shares, session["user_id"], symbol)
            return redirect("/")
    else:

        return render_template("sell.html", symbols=symbols)
