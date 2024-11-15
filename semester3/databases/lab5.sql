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
