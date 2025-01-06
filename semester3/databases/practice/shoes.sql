CREATE TABLE ShoeModels (
    ShoeModelID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50),
    Season VARCHAR (50)
)

CREATE TABLE Shoes (
    ShoeID      INT PRIMARY KEY,
    Price       INT,
    ShoeModelID INT FOREIGN KEY REFERENCES ShoeModels (ShoeModelID)
)

CREATE TABLE PresentationShops (
    ShopID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50),
    City VARCHAR (50)
)

CREATE TABLE Women (
    WomanID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50),
    Amount INT
)

CREATE TABLE ShoesPresentationShops (
    ShoeID INT FOREIGN KEY REFERENCES Shoes (ShoeID),
    ShopID INT FOREIGN KEY REFERENCES PresentationShops (ShopID),
    Availability INT,
    PRIMARY KEY (ShoeID, ShopID)
)

CREATE TABLE Purchases (
    WomanID INT FOREIGN KEY REFERENCES Women (WomanID),
    ShoeID INT FOREIGN KEY REFERENCES Shoes (ShoeID),
    ShoesBought INT,
    AmountSpent INT,
)

INSERT INTO ShoeModels (Name, Season) VALUES
    ('Nike Air', 'Summer'),
    ('Adidas Run', 'Winter');

INSERT INTO Shoes (ShoeID, Price, ShoeModelID) VALUES
    (1, 100, 1),
    (2, 150, 1),
    (3, 200, 2);

INSERT INTO PresentationShops (Name, City) VALUES
    ('FootShop', 'NYC'),
    ('ShoeStore', 'LA');

INSERT INTO Women (Name, Amount) VALUES
    ('Emma', 1000),
    ('Sarah', 1500);

INSERT INTO ShoesPresentationShops (ShoeID, ShopID, Availability) VALUES
    (1, 1, 5),
    (1, 2, 3),
    (2, 1, 2),
    (3, 1, 4);

INSERT INTO Purchases (WomanID, ShoeID, ShoesBought, AmountSpent) VALUES
    (1, 1, 1, 100),
    (1, 2, 1, 150),
    (1, 3, 1, 200),
    (2, 1, 2, 200);

INSERT INTO Purchases (WomanID, ShoeID, ShoesBought, AmountSpent) VALUES
    (1, 1, 10, 201),
    (1, 3, 24, 422);

CREATE OR ALTER PROCEDURE AddShoeToPresentation (
    @ShoeID INT,
    @PresentationShopID INT,
    @ShoesNumber INT
) AS
BEGIN
    DECLARE @Count INT;
    SET @Count = 0;

    SELECT @Count = COUNT(*) FROM ShoesPresentationShops WHERE ShopID = @PresentationShopID AND
                                                               ShoeID = @ShoeID;
    IF (@Count <> 0)
    BEGIN
        UPDATE ShoesPresentationShops
        SET Availability = @ShoesNumber
        WHERE ShoeID = @ShoeID AND
              ShopID = @PresentationShopID
    END
    ELSE
    BEGIN
        INSERT INTO ShoesPresentationShops VALUES (@ShoeID, @PresentationShopID, @ShoesNumber);
    END
END

EXEC AddShoeToPresentation 2, 2, 210

SELECT * FROM Shoes
SELECT * FROM PresentationShops
SELECT * FROM Women
SELECT * FROM Purchases
SELECT * FROM ShoeModels
SELECT * FROM ShoesPresentationShops

CREATE OR ALTER VIEW Women2Shoes AS
    SELECT Women.WomanID, Women.Name, S2.ShoeModelID
    FROM Women
    INNER JOIN Purchases P on Women.WomanID = P.WomanID
    INNER JOIN Shoes S2 on P.ShoeID = S2.ShoeID
    GROUP BY Women.WomanID, Women.Name, S2.ShoeModelID
    HAVING COUNT(*) >= 2

SELECT * FROM Women2Shoes;

CREATE OR ALTER FUNCTION AtLeastT (@T INT)
RETURNS @Result TABLE (
    ShoeID INT,
    Price INT,
    ShoeModelID INT,
    TimesFound INT
) AS
BEGIN
    INSERT INTO @Result
    SELECT s.ShoeID, s.Price, s.ShoeModelID, COUNT(*)
    FROM Shoes s
    INNER JOIN ShoesPresentationShops ps ON s.ShoeID = ps.ShoeID
    GROUP BY s.ShoeID, s.Price, s.ShoeModelID
    HAVING COUNT(*) >= @T

    RETURN
END

SELECT * FROM AtLeastT (2)
