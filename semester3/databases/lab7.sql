CREATE TABLE Student (
    StudentID INTEGER PRIMARY KEY,
    StudentName VARCHAR(50),
    UniRankPosition INTEGER UNIQUE
)

SELECT * FROM Student
DROP TABLE Student

CREATE TABLE Supervisor (
    SupervisorID INTEGER PRIMARY KEY,
    YearsOfExperience INTEGER,
    SupervisorName VARCHAR(50)
)

SELECT * FROM Supervisor
DROP TABLE Supervisor

CREATE TABLE Thesis (
    ThesisID INTEGER PRIMARY KEY,
    StudentID INTEGER,
    SupervisorID INTEGER,
    ThesisName VARCHAR(50),
    FOREIGN KEY (StudentID) REFERENCES Student (StudentID) ON DELETE CASCADE,
    FOREIGN KEY (SupervisorID) REFERENCES Supervisor (SupervisorID) ON DELETE CASCADE
)

SELECT * FROM Thesis
DROP TABLE Thesis

INSERT INTO Student (StudentID, UniRankPosition, StudentName) VALUES (1, 9, 'Luca'),
                                                                     (2, 5, 'Cristi'),
                                                                     (3, 1, 'Serban'),
                                                                     (4, 2, 'David'),
                                                                     (5, 4, 'Denis'),
                                                                     (6, 3, 'Bogdan'),
                                                                     (7, 6, 'Vasile')

INSERT INTO Supervisor (SupervisorID, YearsOfExperience, SupervisorName) VALUES (1, 18, 'Onet-Marian Zsuzsanna'),
                                                                                (2, 15, 'Zsigmond Imre'),
                                                                                (3, 5, 'Nechita Mihai'),
                                                                                (4, 24, 'Pop Horia')

INSERT INTO Thesis (ThesisID, StudentID, SupervisorID, ThesisName) VALUES (2, 1, 3, 'PINNs for PDE Solutions'),
                                                                          (1, 2, 3, 'Diffusion Models for Image Generation'),
                                                                          (4, 3, 2, 'Procedural World Generation in Game Development'),
                                                                          (3, 4, 1, 'Object Recognition in Computer Vision'),
                                                                          (5, 5, 2, 'Containerized Virtual AI Environments')

CREATE PROCEDURE GetIndexes
    @TableName NVARCHAR(128)
AS
BEGIN
    DECLARE @ObjectID INT;
    SET @ObjectID = OBJECT_ID(@TableName);

    IF @ObjectID IS NULL
    BEGIN
        PRINT 'Table does not exist.';
        RETURN;
    END

    SELECT
        i.name AS IndexName,
        i.type_desc AS IndexType,
        c.name AS ColumnName
    FROM
        sys.indexes i
    JOIN
        sys.index_columns ic ON i.object_id = ic.object_id AND i.index_id = ic.index_id
    JOIN
        sys.columns c ON ic.object_id = c.object_id AND ic.column_id = c.column_id
    WHERE
        i.object_id = @ObjectID
    ORDER BY
        i.type_desc, i.name, ic.key_ordinal;
END;
GO

DROP PROCEDURE GetIndexes

EXEC GetIndexes Student
EXEC GetIndexes Supervisor
EXEC GetIndexes Thesis

-- a)

-- CLUSTERED INDEX SCAN
SELECT * FROM Student

-- CLUSTERED INDEX SEEK
SELECT * FROM Student WHERE Student.StudentID = 1

-- NON CLUSTERED INDEX SCAN
SELECT * FROM Student WHERE UniRankPosition > 2

-- NON CLUSTERED INDEX SEEK
SELECT * FROM Student WHERE UniRankPosition = 2

-- KEY LOOKUP
SELECT StudentName FROM Student WHERE UniRankPosition = 2

-- b)

-- without index
-- AvgRowSize = 44; EstimateCPU = 0.110157; EstimateIO = 0.470532; EstimateRebinds = 0; EstimateRewinds = 0; EstimateRows = 27939; EstimatedExecutionMode = Row; EstimatedRowsRead = 100000; EstimatedTotalSubtreeCost = 0.580689;

-- with index
-- AvgRowSize = 44; EstimateCPU = 0.0308899; EstimateIO = 0.0905324; EstimateRebinds = 0; EstimateRewinds = 0; EstimateRows = 27939; EstimatedExecutionMode = Row; EstimatedRowsRead = 27939; EstimatedTotalSubtreeCost = 0.121422;

SELECT * FROM Supervisor WHERE YearsOfExperience > 15 and YearsOfExperience < 30

CREATE PROCEDURE InsertSupervisorData
    @RowCount INT
AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @counter INT = 1;

    WHILE (@counter <= @RowCount)
    BEGIN
        INSERT INTO Supervisor (SupervisorID, YearsOfExperience, SupervisorName)
        VALUES (
            @counter,
            FLOOR(RAND() * 50),
            'Supervisor ' + CAST(@counter AS VARCHAR(10))
        );

        SET @counter = @counter + 1;
    END;
END;

SELECT COUNT(SupervisorID) FROM Supervisor

EXEC InsertSupervisorData 100000
SELECT * FROM Supervisor

CREATE NONCLUSTERED INDEX YearsOfExperienceIndex
ON Supervisor (YearsOfExperience)
INCLUDE (SupervisorName);

DROP INDEX Supervisor.YearsOfExperienceIndex

-- c)

CREATE VIEW JoinView
AS
SELECT
    st.StudentID,
    st.StudentName,
    su.SupervisorID,
    su.SupervisorName,
    su.YearsOfExperience,
    t.ThesisName,
    t.ThesisID
FROM Student st
INNER JOIN Thesis t ON st.StudentID = t.StudentID
INNER JOIN Supervisor su ON t.SupervisorID = su.SupervisorID;

DROP VIEW JoinView

CREATE NONCLUSTERED INDEX StudentSupervisorIDSIndex
ON Thesis (StudentID, SupervisorID)
INCLUDE (ThesisName)

DROP INDEX Thesis.StudentSupervisorIDSIndex

SELECT * FROM JoinView

SELECT * FROM JoinView WHERE YearsOfExperience > 15;
