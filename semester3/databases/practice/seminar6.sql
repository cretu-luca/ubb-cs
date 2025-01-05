DROP TABLE Stops
DROP TABLE Routes
DROP TABLE Stations
DROP TABLE Trains
DROP TABLE TrainTypes

CREATE TABLE TrainTypes (
    Ty_ID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR(50) UNIQUE,
    Description VARCHAR(50)
)

CREATE TABLE Trains (
    Tr_ID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR(50) UNIQUE,
    Type VARCHAR(50) FOREIGN KEY REFERENCES TrainTypes (Name)
)

CREATE TABLE Stations (
    S_ID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR(50) UNIQUE
)

CREATE TABLE Routes (
    R_ID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR(50) UNIQUE,
    Train VARCHAR(50) REFERENCES Trains (Name)
)

CREATE TABLE Stops (
    R_ID INT FOREIGN KEY REFERENCES Routes (R_ID),
    S_ID INT FOREIGN KEY REFERENCES Stations (S_ID),
    ArrivalTime TIME,
    DepartureTime TIME,
    CONSTRAINT RS_ID PRIMARY KEY (R_ID, S_ID)
)

SELECT * FROM TrainTypes
SELECT * FROM Trains
SELECT * FROM Stations
SELECT * FROM Routes
SELECT * FROM Stops

INSERT INTO TrainTypes (Name, Description) VALUES ('name1', 'description1'), ('name2', 'description2')
INSERT INTO Trains (Name, Type) VALUES ('InterRegio', 'name1'), ('Intercity', 'name2'), ('Regio', 'name2')
INSERT INTO Stations (Name) VALUES ('Cluj-Napoca'), ('Brasov'), ('Bucuresti')
Insert into Routes (Name, Train) VALUES ('Sighisoara', 'InterRegio'), ('Medias', 'Intercity')
INSERT INTO Stops Values (3,1,'12:00:00', '18:00:00'), (4,2,'15:30:00', '22:42:00'), (3,2,'08:05:00', '21:48:00')

CREATE OR ALTER PROCEDURE AddStop (
    @New_R_ID INT,
    @New_S_ID INT,
    @ArrivalTime TIME,
    @DepartureTime TIME
)
AS
BEGIN
    DECLARE @NR INT;
    SET @NR = 0;

    SELECT @NR = COUNT(*) FROM Stops WHERE R_ID = @New_R_ID AND S_ID = @New_S_ID

    IF (@NR <> 0) BEGIN
        UPDATE Stops
        SET DepartureTime = @DepartureTime, ArrivalTime = @ArrivalTime
        WHERE R_ID = @New_R_ID AND S_ID = @New_S_ID
    END
    ELSE BEGIN
        INSERT INTO Stops VALUES (@New_R_ID, @New_S_ID, @ArrivalTime, @DepartureTime)
    END
END

EXEC AddStop 4, 1, '15:00', '20:15'
EXEC AddStop 3, 1, '12:10', '18:10'

CREATE OR ALTER PROCEDURE AddStopByName (
    @RouteName VARCHAR (50),
    @StationName VARCHAR (50),
    @ArrivalTime VARCHAR (50),
    @DepartureTime VARCHAR (50)
) AS
BEGIN
    DECLARE @R_ID INT;
    DECLARE @S_ID INT;

    SELECT @R_ID = R_ID FROM Routes WHERE Name = @RouteName
    SELECT @S_ID = S_ID FROM Stations WHERE Name = @StationName

    DECLARE @Exists INT;
    SELECT @Exists = COUNT(*) FROM Stops WHERE Stops.R_ID = @R_ID AND Stops.S_ID = @S_ID

    IF (@Exists <> 0)
    BEGIN
        UPDATE Stops
        SET ArrivalTime = @ArrivalTime, DepartureTime = @DepartureTime
        WHERE R_ID = @R_ID AND S_ID = @S_ID
    END
    ELSE BEGIN
        INSERT INTO Stops VALUES (@R_ID, @S_ID, @ArrivalTime, @DepartureTime);
    END
END

-- (4, 1), (3, 2)
EXEC AddStopByName 'Medias', 'Cluj-Napoca', '22:00', '22:15'
EXEC AddStopByName 'Sighisoara', 'Brasov', '17:00', '18:10'

SELECT r.R_ID, r.Name, s.S_ID, s2.Name
FROM Routes r
JOIN Stops s
ON r.R_ID = s.R_ID
JOIN Stations s2 on s.S_ID = s2.S_ID

SELECT * FROM Stops

CREATE OR ALTER VIEW RoutesThroughAllStations AS
    SELECT r.Name
    FROM Routes r
    INNER JOIN Stops st on r.R_ID = st.R_ID
    GROUP BY r.Name
    HAVING COUNT(*) = (SELECT COUNT(*) FROM Stations)

EXEC AddStop 4, 3, '16:00', '21:15'
EXEC AddStop 3, 3, '13:10', '19:10'

SELECT * FROM RoutesThroughAllStations

-- inline table-valued function
CREATE OR ALTER FUNCTION RStations (@R INT)
RETURNS TABLE AS
RETURN
    SELECT DISTINCT s.S_ID, s.Name, COUNT(Name) as Counter
    FROM Stations s
    INNER JOIN Stops st on s.S_ID = st.S_ID
    GROUP BY s.S_ID, s.Name
    HAVING COUNT(st.R_ID) >= @R

-- multi-statement table-valued function
CREATE OR ALTER FUNCTION RStations2 (@R INT)
RETURNS @Result Table (
    S_ID INT,
    NAME VARCHAR (50),
    Counter INT
) AS
BEGIN
    INSERT INTO @Result
    SELECT DISTINCT s.S_ID, s.Name, COUNT(Name) as Counter
    FROM Stations s
    INNER JOIN Stops st on s.S_ID = st.S_ID
    GROUP BY s.S_ID, s.Name
    HAVING COUNT(R_ID) >= @R

    RETURN
END

-- scalar function
CREATE OR ALTER FUNCTION RStations3 (@R INT)
RETURNS INT AS
BEGIN
    DECLARE @Nr INT;
    SET @Nr = 0;
    SELECT @Nr = COUNT(*) FROM Stations s INNER JOIN Stops st on s.S_ID = st.S_ID
                          GROUP BY s.Name, st.S_ID
                          HAVING COUNT(s.Name) >= @R

    RETURN @Nr
END

SELECT * FROM RStations(1)
SELECT * FROM RStations2(1)
PRINT dbo.RStations3(3)
