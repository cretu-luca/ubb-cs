DROP TABLE UserActivities
DROP TABLE HealthMetric
DROP TABLE Meals
DROP TABLE Users
DROP TABLE Activities

CREATE TABLE Users (
    UserID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50) UNIQUE,
    Age INT,
    Gender VARCHAR (50)
)

CREATE TABLE Activities (
    ActivityID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50) UNIQUE,
    NumberOfCaloriesBurned INT
)

CREATE TABLE Meals (
    MealID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50) UNIQUE,
    NumberOfCaloriesPerServing INT
)

CREATE TABLE HealthMetric (
    HealthMetricID INT PRIMARY KEY IDENTITY (1, 1),
    UserID INT FOREIGN KEY REFERENCES Users (UserID),
    DateOfRecording DATE,
    Weight INT,
    BloodPressure INT,
    HeartRate INT,
)

CREATE TABLE UserActivities (
    UserActivityID INT PRIMARY KEY IDENTITY (1, 1),
    UserID INT FOREIGN KEY REFERENCES Users (UserID),
    ActivityID INT FOREIGN KEY REFERENCES Activities (ActivityID),
    PerformedAt DATETIME,
    Duration INT
)

INSERT INTO Users (Name, Age, Gender) VALUES
('John Smith', 28, 'Male'),
('Sarah Johnson', 35, 'Female'),
('Michael Brown', 42, 'Male');

INSERT INTO Activities (Name, NumberOfCaloriesBurned) VALUES
('Running', 600),
('Swimming', 500),
('Cycling', 450),
('Yoga', 200);

INSERT INTO Meals (Name, NumberOfCaloriesPerServing) VALUES
('Chicken Salad', 350),
('Spaghetti Bolognese', 550),
('Grilled Salmon', 400),
('Vegetable Stir Fry', 300);

INSERT INTO HealthMetric (UserID, DateOfRecording, Weight, BloodPressure, HeartRate) VALUES
(1, '2024-01-01', 75, 120, 72),
(2, '2024-01-01', 65, 118, 68),
(3, '2024-01-01', 82, 122, 70);

INSERT INTO HealthMetric (UserID, DateOfRecording, Weight, BloodPressure, HeartRate) VALUES
(2, '2024-5-01', 72, 192, 12),
(3, '2024-1-01', 69, 115, 35),
(1, '2024-6-01', 100, 126, 53);

DELETE FROM HealthMetric
DELETE FROM UserActivities

INSERT INTO UserActivities (UserID, ActivityID, PerformedAt, Duration) VALUES
(1, 1, '2024-01-09 08:30:00', 45),
(2, 3, '2024-01-09 17:00:00', 60),
(3, 2, '2024-01-09 12:00:00', 30),
(1, 4, '2024-01-09 19:00:00', 45),
(1, 4, '2024-01-09 19:00:00', 60);

-- Implement a stored procedure that receives the details of a health metric and adds the metric in the database. 
-- If the date of recording is in the future (e.g. today is 05-01-2024 and the date of recording for the health metric is 06-01-2024), 
-- the system will display an error message and it will not save the health metric in the database.
CREATE OR ALTER PROCEDURE AddHealthMetric (
    @GiveUserID INT,
    @GivenDateOfRecording DATE,
    @GivenWeight INT,
    @GivenBloodPressure INT,
    @GivenHeartRate INT
) AS
BEGIN
    IF @GivenDateOfRecording > SYSDATETIME() BEGIN
        THROW 51000, 'Invalid date.', 1;
    END

    INSERT INTO HealthMetric (UserID, DateOfRecording, Weight, BloodPressure, HeartRate)
    VALUES (@GiveUserID, @GivenDateOfRecording, @GivenWeight, @GivenBloodPressure, @GivenHeartRate)
END

SELECT * FROM HealthMetric
EXEC AddHealthMetric 2, '2026-01-02', 50, 120, 79

-- Create a view that displays the average weight and the maximum blood pressure for each user based on the data recorded during the last year (2023).
CREATE OR ALTER VIEW AvgWeightMaxBloodPressure AS
SELECT u.name, AVG (h.Weight) AS Weight, MAX (BloodPressure) AS BP
FROM HealthMetric h
JOIN Users u ON u.UserID = h.UserID
WHERE YEAR(DateOfRecording) = YEAR(DATEADD(YEAR, -1, SYSDATETIME()))
GROUP BY u.name

SELECT * FROM AvgWeightMaxBloodPressure

-- 4. Implement a function that returns the average duration of a specific activity A for a given user P
-- U, where A and U are function parameters.
CREATE OR ALTER FUNCTION GetAverage (@GivenActivityID INT, @GivenUserID INT)
RETURNS INT AS
BEGIN
    DECLARE @AvgDuration INT;
    SET @AvgDuration = 0;

    IF NOT EXISTS(SELECT 1 FROM UserActivities WHERE UserID = @GivenUserID AND ActivityID = @GivenActivityID) BEGIN
        RETURN @AvgDuration
    END
    ELSE BEGIN
        SELECT @AvgDuration = AVG(Duration)
        FROM UserActivities
        WHERE ActivityID = @GivenActivityID AND UserID = @GivenUserID
    END

    RETURN @AvgDuration
END

PRINT dbo.GetAverage (4, 6)
