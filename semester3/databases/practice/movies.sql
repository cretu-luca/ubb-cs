DROP TABLE CinemaProductionsActors
DROP TABLE CinemaProductions
DROP TABLE Movies
DROP TABLE StageDirectors
DROP TABLE Companies
DROP TABLE Actors

-- Write an SQL script that creates the corresponding relational data model.
CREATE TABLE Actors (
    ActorID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50),
    Ranking INT
)

CREATE TABLE Companies (
    CompanyID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50)
)

CREATE TABLE StageDirectors (
    StageDirectorID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50),
    NumberOfAwards INT
)

CREATE TABLE Movies (
    MovieID INT PRIMARY KEY IDENTITY (1, 1),
    Name VARCHAR (50),
    ReleaseDate DATE,
    CompanyID INT FOREIGN KEY REFERENCES Companies (CompanyID),
    StageDirectorID INT FOREIGN KEY REFERENCES StageDirectors (StageDirectorID)
)

CREATE TABLE CinemaProductions (
    CinemaProductionID INT PRIMARY KEY IDENTITY (1, 1),
    Title VARCHAR (50),
    MovieID INT FOREIGN KEY REFERENCES Movies (MovieID)
)

CREATE TABLE CinemaProductionsActors (
    CinemaProductionID INT REFERENCES CinemaProductions (CinemaProductionID),
    ActorID INT REFERENCES Actors (ActorID),
    EntryMoment TIME,
    PRIMARY KEY (CinemaProductionID, ActorID)
)

INSERT INTO Companies (Name) VALUES
('Universal Pictures'),
('Warner Bros.'),
('Paramount Pictures');

INSERT INTO StageDirectors (Name, NumberOfAwards) VALUES
('Christopher Nolan', 5),
('Steven Spielberg', 7),
('Martin Scorsese', 6);

INSERT INTO Movies (Name, ReleaseDate, CompanyID, StageDirectorID) VALUES
('Inception', '2020-07-16', 2, 1),
('Jurassic Park', '2019-06-11', 1, 2),
('The Departed', '2021-10-06', 2, 3);

INSERT INTO Actors (Name, Ranking) VALUES
('Leonardo DiCaprio', 95),
('Tom Hanks', 98),
('Brad Pitt', 92),
('Morgan Freeman', 94);

INSERT INTO CinemaProductions (Title, MovieID) VALUES
('Inception Production', 1),
('Jurassic Production', 2),
('Departed Production', 3);

INSERT INTO CinemaProductions (Title, MovieID) VALUES
('Memento', 1)

INSERT INTO CinemaProductionsActors (CinemaProductionID, ActorID, EntryMoment) VALUES
(1, 1, '09:00:00'),
(2, 2, '10:30:00'),
(3, 1, '14:00:00'),
(3, 3, '15:30:00');

-- Create a stored procedure that receives an actor, an entry moment and a cinema production and adds the new actor to the cinema production.
CREATE OR ALTER PROCEDURE AddMovieToCinemaProductions (
   @GivenActorID INT,
   @GivenCinemaProductionID INT,
   @GivenEntryMoment TIME
) AS
BEGIN
   DECLARE @FoundActors INT
   SELECT @FoundActors = COUNT(*) FROM Actors WHERE ActorID = @GivenActorID

   IF (@FoundActors <> 1) BEGIN
       PRINT 'Invalid ActorID'
       RETURN
   END

   DECLARE @FoundCinemaProductions INT
   SELECT @FoundCinemaProductions = COUNT(*) FROM CinemaProductions WHERE CinemaProductionID = @GivenCinemaProductionID

   IF (@FoundCinemaProductions <> 1) BEGIN
       PRINT 'Invalid CinemaProductionID'
       RETURN
   END

   IF EXISTS (SELECT 1 FROM CinemaProductionsActors
             WHERE CinemaProductionID = @GivenCinemaProductionID
             AND ActorID = @GivenActorID) BEGIN
       UPDATE CinemaProductionsActors
       SET EntryMoment = @GivenEntryMoment
       WHERE CinemaProductionID = @GivenCinemaProductionID AND ActorID = @GivenActorID
   END
   ELSE BEGIN
       INSERT INTO CinemaProductionsActors VALUES (@GivenCinemaProductionID, @GivenActorID, @GivenEntryMoment)
   END
END

SELECT * FROM CinemaProductionsActors

SELECT P.Title, A.Name, PA.EntryMoment
FROM CinemaProductionsActors PA
JOIN Actors A on PA.ActorID = A.ActorID
JOIN CinemaProductions P on P.CinemaProductionID = PA.CinemaProductionID

EXEC AddMovieToCinemaProductions 2, 1, '12:00'
EXEC AddMovieToCinemaProductions 1, 1, '23:00'
EXEC AddMovieToCinemaProductions 1, 2, '23:00'

-- Create a view that shows the name of the actors that appear in all cinema productions.
CREATE OR ALTER VIEW ActorsAllCinemaProductions AS
SELECT A.Name
FROM Actors A
JOIN CinemaProductionsActors CPA on A.ActorID = CPA.ActorID
GROUP BY A.Name
HAVING COUNT(A.Name) = (
    SELECT COUNT(*)
    FROM CinemaProductions
)

SELECT A.Name, COUNT(CPA.CinemaProductionID) as ProductionCount
FROM Actors A
JOIN CinemaProductionsActors CPA on A.ActorID = CPA.ActorID
GROUP BY A.Name;

SELECT * FROM ActorsAllCinemaProductions

-- Create a function that returns all movies that have the release date after '2018-01-01' and have at least
-- P productions, where p is a function parameter.

CREATE OR ALTER FUNCTION AllPMovies (@P INT)
RETURNS @MoviesP TABLE (
    MovieID INT,
    Name VARCHAR (50),
    ReleaseDate DATE
) AS
BEGIN
    INSERT INTO @MoviesP
    SELECT m.MovieID, Name, ReleaseDate
    FROM Movies m
    JOIN CinemaProductions CP on m.MovieID = CP.MovieID
    GROUP BY m.MovieID, Name, ReleaseDate
    HAVING COUNT (*) >= @P AND ReleaseDate > '2018-01-01'

    RETURN
END

SELECT * FROM AllPMovies (2)
