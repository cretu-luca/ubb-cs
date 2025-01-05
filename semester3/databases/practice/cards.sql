-- 1. write an SQL script that creates the corresponding relational data model
CREATE TABLE Customers (
    Cu_ID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50),
    DateOfBirth DATE
)

CREATE TABLE BankAccounts (
    B_ID INT PRIMARY KEY IDENTITY (1, 1),
    IBAN VARCHAR (50),
    Balance INT,
    HolderID INT FOREIGN KEY REFERENCES Customers (Cu_ID)
)

CREATE TABLE Cards (
    Cd_ID INT PRIMARY KEY IDENTITY (1, 1),
    Number VARCHAR (16),
    CVV VARCHAR (3),
    BankAccountID INT FOREIGN KEY REFERENCES BankAccounts (B_ID)
)

CREATE TABLE ATMs (
    A_ID INT PRIMARY KEY IDENTITY (1, 1),
    Address VARCHAR (50)
)

CREATE TABLE ATMTransactions (
    T_ID INT PRIMARY KEY IDENTITY (1, 1),
    Sum INT,
    CardID INT FOREIGN KEY REFERENCES Cards (Cd_ID),
    ATM_ID INT FOREIGN KEY REFERENCES ATMs (A_ID)
)

DROP TABLE ATMTransactions;
DROP TABLE ATMs;
DROP TABLE Cards;
DROP TABLE BankAccounts;
DROP TABLE Customers;

SELECT * FROM Customers;
SELECT * FROM BankAccounts;
SELECT * FROM Cards;
SELECT * FROM ATMs;
SELECT * FROM ATMTransactions;

INSERT INTO Customers (Name, DateOfBirth)
VALUES ('Luca', '2004-07-08'),
       ('Denis', '2005-01-05'),
       ('Serban', '2005-03-16'),
       ('David', '2004-10-06'),
       ('Bogdan', '2005-02-03');

SELECT * FROM Customers

INSERT INTO BankAccounts (IBAN, Balance, HolderID)
VALUES ('RO49AAAA1B31007593840000', 1000, 1),
       ('RO49AAAA1B31007593840001', 1500, 2),
       ('RO49AAAA1B31007593840002', 2000, 3),
       ('RO49AAAA1B31007593840003', 2500, 4),
       ('RO49AAAA1B31007593840004', 3000, 5);

SELECT * FROM BankAccounts

INSERT INTO Cards (CVV, Number, BankAccountID)
VALUES ('123', '1234567890123456', 6),
       ('456', '0987654321098765', 2),
       ('789', '1029384756102948', 3),
       ('234', '1209349845876125', 4),
       ('567', '1002993884775660', 5);

SELECT * FROM Cards

INSERT INTO ATMs (Address)
VALUES ('Main Street 1'),
       ('Central Park 2'),
       ('Station Road 3');

SELECT * FROM ATMs

DELETE FROM ATMTransactions
DELETE FROM Cards

INSERT INTO ATMTransactions (Sum, CardID, ATM_ID)
VALUES (200, 8, 1),
       (2000, 9, 1),
       (150, 10, 2),
       (1800, 11, 3),
       (250, 10, 2),
       (200, 12, 2);

SELECT * FROM ATMTransactions

-- 2.  implement a stored procedure that receives a card and deletes all the transactions related to the card
CREATE OR ALTER PROCEDURE DeleteTransactions (
    @CardID INT
) AS
BEGIN
    DELETE FROM ATMTransactions
    WHERE CardID = @CardID
END

EXEC DeleteTransactions 2

-- 3. create a view that shows the card number which were used in transactions at all the ATM's
CREATE OR ALTER VIEW CardsUsedAtAllATMs AS
    SELECT CardID
    FROM Cards
    INNER JOIN ATMTransactions A on Cards.Cd_ID = A.CardID
    GROUP BY CardID
    HAVING COUNT(DISTINCT A.ATM_ID) = (SELECT DISTINCT COUNT(A_ID)
                                FROM ATMs)

SELECT * FROM CardsUsedAtAllATMs

-- 4. implement a function that lists the cards (number and CVV code) that have the total
-- transactions sum greater than 2000 lei.
CREATE OR ALTER FUNCTION CardsFunction ()
RETURNS @Result TABLE (
    Number VARCHAR (16),
    CVV VARCHAR (3)
) AS
BEGIN
    INSERT INTO @Result
    SELECT Number, CVV
    FROM Cards
    INNER JOIN ATMTransactions T on Cards.Cd_ID = T.CardID
    GROUP BY Cd_ID, Number, CVV, BankAccountID
    HAVING SUM (T.Sum) >= 2000

    RETURN
END

SELECT * FROM dbo.CardsFunction()
