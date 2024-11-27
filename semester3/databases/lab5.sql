---- MODIFY COLUMN TYPE STORED PROCEDURE ----
CREATE PROCEDURE ChangePopulationType
AS
BEGIN
    ALTER TABLE City
    ALTER COLUMN Population BIGINT;
END

EXEC ChangePopulationType
DROP PROCEDURE ChangePopulationType

CREATE PROCEDURE ChangePopulationTypeRevert
AS
BEGIN
    ALTER TABLE City
    ALTER COLUMN Population INT;
END

EXEC ChangePopulationTypeRevert
DROP PROCEDURE ChangePopulationTypeRevert

---- ADD/REMOVE COLUMN STORED PROCEDURE ----
CREATE PROCEDURE AddEmployeeTenure
AS
BEGIN
    ALTER TABLE Employee
    ADD Tenure VARCHAR(20);
END

EXEC AddEmployeeTenure
DROP PROCEDURE AddEmployeeTenure

CREATE PROCEDURE RemoveEmployeeTenure
AS
BEGIN
    ALTER TABLE Employee
    DROP COLUMN Tenure;
END

EXEC RemoveEmployeeTenure
DROP PROCEDURE RemoveEmployeeTenure

SELECT * FROM Employee
---- ADD/REMOVE DEFAULT CONSTRAINT ----
CREATE TABLE ProjectSupervisor (
    SupervisorID INT NOT NULL,
    ProjectID INT,
    ExperienceYears INT
)

CREATE PROCEDURE AddExperienceYearsDefaultConstraint
AS
BEGIN
    ALTER TABLE ProjectSupervisor
    ADD CONSTRAINT df_ExperienceYears
    DEFAULT 1234 FOR ExperienceYears;
END

INSERT INTO dbo.ProjectSupervisor(SupervisorID, ProjectID, ExperienceYears)
VALUES (1, 1, 1)

INSERT INTO ProjectSupervisor (SupervisorID, ProjectID)
VALUES (2, 2)

SELECT * FROM ProjectSupervisor

DROP TABLE ProjectSupervisor

EXEC AddExperienceYearsDefaultConstraint
DROP PROCEDURE AddExperienceYearsDefaultConstraint


CREATE PROCEDURE RemoveExperienceYearsDefaultConstraint
AS
BEGIN
    ALTER TABLE ProjectSupervisor
    DROP CONSTRAINT df_ExperienceYears
END

EXEC RemoveExperienceYearsDefaultConstraint
DROP PROCEDURE RemoveExperienceYearsDefaultConstraint

SELECT * FROM ProjectSupervisor


---- ADD/REMOVE PRIMARY KEY ----
CREATE PROCEDURE AddSupervisorProjectIDPrimaryKey
AS
BEGIN
    ALTER TABLE ProjectSupervisor
    ADD CONSTRAINT PK_SupervisorID PRIMARY KEY (SupervisorID);
END

EXEC AddSupervisorProjectIDPrimaryKey
DROP PROCEDURE AddSupervisorProjectIDPrimaryKey

CREATE PROCEDURE RemoveSupervisorProjectIDPrimaryKey
AS
BEGIN
    ALTER TABLE ProjectSupervisor
    DROP CONSTRAINT PK_SupervisorID
END

EXEC RemoveSupervisorProjectIDPrimaryKey
DROP PROCEDURE RemoveSupervisorProjectIDPrimaryKey

---- CREATE/DROP TABLE ----
CREATE PROCEDURE CreateTrainingTable
AS
BEGIN
    CREATE TABLE Training (
        TrainingID INT PRIMARY KEY,
        TrainingName VARCHAR(100),
        Duration INT,
        MaxParticipants INT,
        InstructorID INT
    );
END

EXEC CreateTrainingTable
DROP PROCEDURE CreateTrainingTable

CREATE PROCEDURE DropTrainingTable
AS
BEGIN
    DROP TABLE Training;
END

EXEC DropTrainingTable
DROP PROCEDURE DropTrainingTable

CREATE PROCEDURE CreateInstructorTable
AS
BEGIN
    CREATE TABLE Instructor (
        InstructorID INT PRIMARY KEY,
        InstructorName VARCHAR(100)
    );
END

EXEC CreateInstructorTable
DROP PROCEDURE CreateInstructorTable

CREATE PROCEDURE DropInstructorTable
AS
BEGIN
    DROP TABLE Instructor;
END

EXEC DropInstructorTable
DROP PROCEDURE DropInstructorTable

---- ADD/REMOVE CANDIDATE KEY ----
CREATE PROCEDURE AddTrainingCandidateKey
AS
BEGIN
    ALTER TABLE Training
    ADD CONSTRAINT CK_TrainingName_Duration UNIQUE (TrainingName, Duration);
END

EXEC AddTrainingCandidateKey
DROP PROCEDURE AddTrainingCandidateKey

CREATE PROCEDURE RemoveTrainingCandidateKey
AS
BEGIN
    ALTER TABLE Training
    DROP CONSTRAINT CK_TrainingName_Duration;
END

EXEC RemoveTrainingCandidateKey
DROP PROCEDURE RemoveTrainingCandidateKey

---- ADD/REMOVE FOREIGN KEY ----
CREATE PROCEDURE AddTrainingForeignKey
AS
BEGIN
    ALTER TABLE Training
    ADD CONSTRAINT FK_InstructorID
    FOREIGN KEY (InstructorID) REFERENCES Instructor(InstructorID);
END

EXEC AddTrainingForeignKey
DROP PROCEDURE AddTrainingForeignKey

CREATE PROCEDURE RemoveTrainingForeignKey
AS
BEGIN
    ALTER TABLE Training
    DROP CONSTRAINT FK_InstructorID;
END

EXEC RemoveTrainingForeignKey
DROP PROCEDURE RemoveTrainingForeignKey

---- VERSIONING ----
CREATE TABLE DatabaseVersion (
    Version INT PRIMARY KEY,
    Description VARCHAR(100)
)

INSERT INTO DatabaseVersion (Version, Description)
VALUES (0, 'Initial state')

CREATE TABLE DatabaseVersion (
    Version INT PRIMARY KEY,
    Description VARCHAR(100)
)

INSERT INTO DatabaseVersion (Version, Description)
VALUES (0, 'Initial state')

CREATE PROCEDURE UpdateVersion
    @TargetVersion INT
AS
BEGIN
    DECLARE @CurrentVersion INT
    SELECT @CurrentVersion = ISNULL(MAX(Version), 0) FROM DatabaseVersion

    WHILE @CurrentVersion < @TargetVersion
    BEGIN
        SET @CurrentVersion = @CurrentVersion + 1

        IF @CurrentVersion = 1
            EXEC CreateInstructorTable
        IF @CurrentVersion = 2
            EXEC CreateTrainingTable
        IF @CurrentVersion = 3
            EXEC AddTrainingForeignKey
        IF @CurrentVersion = 4
            EXEC AddTrainingCandidateKey
        IF @CurrentVersion = 5
            EXEC ChangePopulationType
        IF @CurrentVersion = 6
            EXEC AddEmployeeTenure
        IF @CurrentVersion = 7
            EXEC AddExperienceYearsDefaultConstraint

        INSERT INTO DatabaseVersion (Version, Description)
        VALUES (@CurrentVersion,
            CASE @CurrentVersion
                WHEN 1 THEN 'Created Instructor table'
                WHEN 2 THEN 'Created Training table'
                WHEN 3 THEN 'Added Training foreign key'
                WHEN 4 THEN 'Added Training candidate key'
                WHEN 5 THEN 'Changed Population type'
                WHEN 6 THEN 'Added Employee Tenure'
                WHEN 7 THEN 'Added Experience Years default'
            END)
    END

    WHILE @CurrentVersion > @TargetVersion
    BEGIN
        IF @CurrentVersion = 7
            EXEC RemoveExperienceYearsDefaultConstraint
        IF @CurrentVersion = 6
            EXEC RemoveEmployeeTenure
        IF @CurrentVersion = 5
            EXEC ChangePopulationTypeRevert
        IF @CurrentVersion = 4
            EXEC RemoveTrainingCandidateKey
        IF @CurrentVersion = 3
            EXEC RemoveTrainingForeignKey
        IF @CurrentVersion = 2
            EXEC DropTrainingTable
        IF @CurrentVersion = 1
            EXEC DropInstructorTable

        DELETE FROM DatabaseVersion WHERE Version = @CurrentVersion
        SET @CurrentVersion = @CurrentVersion - 1
    END
END

EXEC UpdateVersion 4
EXEC UpdateVersion 3
SELECT * FROM DatabaseVersion
