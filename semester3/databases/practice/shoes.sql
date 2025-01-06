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
    CONSTRAINT PRIMARY KEY (ShoeID, ShopID)
)

CREATE TABLE Purchases (
    WomanID INT FOREIGN KEY REFERENCES Women (WomanID),
    ShoeID INT FOREIGN KEY REFERENCES Shoes (ShoeID),
    ShoesBought INT,
    AmountSpent INT,
)

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

CREATE VIEW Women2Shoes AS
    SELECT Women.WomanID, Women.Name, P.ShoeID
    FROM Women
    INNER JOIN Purchases P on Women.WomanID = P.WomanID
    GROUP BY Women.WomanID, Women.Name, ShoeID
    HAVING COUNT(ShoeID) > 2

CREATE FUNCTION AtLeastT (@T INT)
RETURNS @Result TABLE (
    ShoeID INT,
    Price INT,
    ShoeModelID INT,
    TimesFound INT
) AS
BEGIN
    INSERT INTO @Result
    SELECT s.ShoeID, Price, ShoeModelID, COUNT(s.ShoeID)
    FROM Shoes s
    INNER JOIN ShoesPresentationShops ps ON s.ShoeID =ps.ShoeID
    GROUP BY s.ShoeID, Price, ShoeModelID
    HAVING COUNT(s.ShoeID) > @T
END
