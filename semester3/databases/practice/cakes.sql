DROP TABLE CakeTypes
DROP TABLE Cakes
DROP TABLE Chefs
DROP TABLE Orders
DROP TABLE CakesOrders
DROP TABLE ChefSpecialties

CREATE TABLE CakeTypes (
    CakeTypeID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50),
    Description VARCHAR (50)
)

CREATE TABLE Cakes (
    CakeID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50),
    Shape VARCHAR (50),
    Weight INT,
    Price INT,
    TypeID INT FOREIGN KEY REFERENCES CakeTypes (CakeTypeID)
)

CREATE TABLE Chefs (
    ChefID INT PRIMARY KEY IDENTITY (1, 1),
    ChefName VARCHAR (50),
    Gender VARCHAR (50),
    DateOfBirth DATE
)

CREATE TABLE Orders (
    OrderID INT PRIMARY KEY IDENTITY (1, 1),
    OrderDate DATE
)

CREATE TABLE CakesOrders (
    OrderID INT FOREIGN KEY REFERENCES Orders (OrderID),
    CakeID INT FOREIGN KEY REFERENCES Cakes (CakeID),
    Quantity INT,
    PRIMARY KEY (OrderID, CakeID)
)

CREATE TABLE ChefSpecialties (
    ChefID INT FOREIGN KEY REFERENCES Chefs (ChefID),
    CakeID INT FOREIGN KEY REFERENCES Cakes (CakeID),
    PRIMARY KEY (ChefID, CakeID)
)

INSERT INTO CakeTypes (Name, Description) VALUES
('Chocolate', 'Rich chocolate cake'),
('Fruit', 'Fresh fruit-based cake'),
('Cheesecake', 'Classic cheesecake');

INSERT INTO Cakes (Name, Shape, Weight, Price, TypeID) VALUES
('Black Forest', 'Round', 1000, 50, 1),
('Strawberry Cake', 'Square', 800, 45, 2),
('Classic Cheesecake', 'Round', 900, 55, 3);

INSERT INTO Chefs (ChefName, Gender, DateOfBirth) VALUES
('John Smith', 'Male', '1980-05-15'),
('Mary Jones', 'Female', '1990-03-20');

INSERT INTO Orders (OrderDate) VALUES
('2024-01-15'),
('2024-01-16');

INSERT INTO CakesOrders (OrderID, CakeID, Quantity) VALUES
(1, 1, 2),
(1, 2, 1),
(2, 3, 3);

INSERT INTO ChefSpecialties (ChefID, CakeID) VALUES
(1, 1),
(1, 2),
(2, 3);

INSERT INTO ChefSpecialties (ChefID, CakeID) VALUES
(1, 3);

-- Implement a stored procedure that receives an order ID, a cake name, and a positive number P
-- (the number of ordered pieces), and adds the cake to the order.
-- If the cake is already on there it number of ordered pieces is set to P.

CREATE OR ALTER PROCEDURE AddCakeToOrder (
    @GivenOrderID INT,
    @GivenCakeName VARCHAR (50),
    @GivenQuantity INT
) AS
BEGIN
    DECLARE @FoundOrder INT
    SELECT @FoundOrder = COUNT(*) FROM Orders WHERE OrderID = @GivenOrderID

    IF (@FoundOrder <> 1) BEGIN
        PRINT 'Invalid OrderID'
        RETURN
    END

    DECLARE @GivenCakeID INT
    SELECT @GivenCakeID = CakeID FROM Cakes WHERE Name = @GivenCakeName

    IF EXISTS(SELECT 1 FROM CakesOrders WHERE CakeID = @GivenCakeID AND OrderID = @GivenOrderID) BEGIN
        UPDATE CakesOrders
        SET Quantity = @GivenQuantity
        WHERE CakeID = @GivenCakeID AND OrderID = @GivenOrderID
    END
    ELSE BEGIN
        INSERT INTO CakesOrders VALUES (@GivenOrderID, @GivenCakeID, @GivenQuantity)
    END
END

SELECT * FROM CakesOrders

SELECT C.Name, O.OrderID, Quantity
FROM CakesOrders
JOIN Cakes C on CakesOrders.CakeID = C.CakeID
JOIN Orders O on CakesOrders.OrderID = O.OrderID

EXEC AddCakeToOrder 1, 'Black Forest', 5
EXEC AddCakeToOrder 2, 'Black Forest', 6

-- Implement a function that lists the names of the chefs who are specialized in the preparation of all cakes
CREATE OR ALTER FUNCTION ListChefs ()
RETURNS @Result TABLE (
    ChefName VARCHAR (50),
    Gender VARCHAR (50),
    DateOfBirth DATE
) AS
BEGIN
    INSERT INTO @Result
    SELECT ChefName, Gender, DateOfBirth
    FROM Chefs
    JOIN ChefSpecialties CS on Chefs.ChefID = CS.ChefID
    GROUP BY ChefName, Gender, DateOfBirth
    HAVING COUNT(*) = (SELECT COUNT(*) FROM Cakes)

    RETURN
END

SELECT * FROM ListChefs()
