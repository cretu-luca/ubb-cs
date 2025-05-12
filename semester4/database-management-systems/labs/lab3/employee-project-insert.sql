USE CityPlanning

CREATE TABLE LogTable (
    LogID INT IDENTITY PRIMARY KEY,
    TypeOperation VARCHAR (50),
    TableOperation VARCHAR (50),
    ExecutionDate DATETIME DEFAULT GETDATE()
)

DROP TABLE LogTable

CREATE OR ALTER FUNCTION ValidateDate (
    @Date DATE
) RETURNS INT AS
BEGIN
    DECLARE @return INT = 0

    IF @Date > '01-01-2020'
        SET @return = 1

    RETURN @return
END
GO

CREATE OR ALTER FUNCTION ValidateName (
    @Name VARCHAR(50)
) RETURNS INT AS
BEGIN
    DECLARE @return INT = 0

    IF @Name IS NOT NULL AND LEN(@Name) > 2 AND @Name LIKE '[A-Z]%'
        SET @return = 1

    RETURN @return
END
GO

CREATE OR ALTER PROCEDURE EmployeeProjectInsertAtomic (
    @EmployeeName VARCHAR (50),
    @DepartmentID INT,
    @PositionID INT,

    @ProjectName VARCHAR (50),
    @StartDate DATE,
    @EndDate DATE,
    @SupplierID INT,
    @SponsorshipID INT
) AS
BEGIN
    BEGIN TRAN
        BEGIN TRY
            IF (dbo.ValidateName (@EmployeeName) <> 1)
            BEGIN
                RAISERROR ('Invalid name', 14, 1)
                RETURN
            END

            IF (dbo.ValidateDate (@StartDate) <> 1 OR dbo.ValidateDate (@EndDate) <> 1)
            BEGIN
                RAISERROR ('Invalid date', 14, 1)
                RETURN
            END

            INSERT INTO Employee (Name, DepartmentID, PositionID)
            VALUES (@EmployeeName, @DepartmentID, @PositionID)

            INSERT INTO LogTable (TypeOperation, TableOperation)
            VALUES ('INSERT', 'Employee')

            DECLARE @EmployeeID INT = SCOPE_IDENTITY()

            INSERT INTO Project (ProjectName, StartDate, EndDate, SupplierID, SponsorshipID)
            VALUES (@ProjectName, @StartDate, @EndDate, @SupplierID, @SponsorshipID)

            INSERT INTO LogTable (TypeOperation, TableOperation)
            VALUES ('INSERT', 'Project')

            DECLARE @ProjectID INT = SCOPE_IDENTITY()

            INSERT INTO dbo.EmployeeProject (EmployeeID, ProjectID)
            VALUES (@EmployeeID, @ProjectID)

            INSERT INTO LogTable (TypeOperation, TableOperation)
            VALUES ('INSERT', 'EmployeeProject')

            COMMIT TRAN
            SELECT 'Transaction committed'
        END TRY
        BEGIN CATCH
            ROLLBACK TRAN
            SELECT 'Transaction rolled back'
        END CATCH
    END
END
GO

SELECT * FROM dbo.Employee
SELECT * FROM dbo.Project
SELECT * FROM dbo.EmployeeProject
SELECT * FROM dbo.LogTable

DELETE FROM dbo.EmployeeProject
WHERE CityPlanning.dbo.EmployeeProject.EmployeeID = 6

DELETE FROM dbo.Project
WHERE CityPlanning.dbo.Project.ProjectID = 12

DELETE FROM dbo.Employee
WHERE CityPlanning.dbo.Employee.EmployeeID = 10

DELETE FROM dbo.Employee
WHERE CityPlanning.dbo.Employee.EmployeeID = 9

EXEC EmployeeProjectInsertAtomic 'Bogdan', 1, 1, 'Cultura', '01-05-2025', '01-06-2025', 1, 1
EXEC EmployeeProjectInsertAtomic 'Vasile', 1, 1, 'Ecologizare', '01-01-2019', '01-01-2020', 1, 1

CREATE OR ALTER PROCEDURE EmployeeProjectInsertNonAtomic (
    @EmployeeName VARCHAR (50),
    @DepartmentID INT,
    @PositionID INT,

    @ProjectName VARCHAR (50),
    @StartDate DATE,
    @EndDate DATE,
    @SupplierID INT,
    @SponsorshipID INT
) AS
BEGIN
    DECLARE @EmployeeID INT = -1
    DECLARE @ProjectID INT = -1

    BEGIN TRY
        BEGIN TRAN
            IF (dbo.ValidateName (@EmployeeName) <> 1)
            BEGIN
                RAISERROR ('Invalid name', 14, 1)
                RETURN
            END

            INSERT INTO Employee (Name, DepartmentID, PositionID)
            VALUES (@EmployeeName, @DepartmentID, @PositionID)

            INSERT INTO LogTable (TypeOperation, TableOperation)
            VALUES ('INSERT', 'Employee')

            SET @EmployeeID = SCOPE_IDENTITY()

        COMMIT TRAN
        SELECT 'Employee insert transaction commited'
    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0
            ROLLBACK TRAN

        SELECT 'Employee insert transaction rolled back: ' + ERROR_MESSAGE() AS Result
    END CATCH


    BEGIN TRY
        BEGIN TRAN
            IF (dbo.ValidateDate (@StartDate) <> 1 OR dbo.ValidateDate (@EndDate) <> 1)
            BEGIN
                RAISERROR ('Invalid date', 14, 1)
                RETURN
            END

            INSERT INTO Project (ProjectName, StartDate, EndDate, SupplierID, SponsorshipID)
            VALUES (@ProjectName, @StartDate, @EndDate, @SupplierID, @SponsorshipID)

            INSERT INTO LogTable (TypeOperation, TableOperation)
            VALUES ('INSERT', 'Project')

            SET @ProjectID = SCOPE_IDENTITY()

        COMMIT TRAN
        SELECT 'Project insert transaction commited'
    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0
            ROLLBACK TRAN

        SELECT 'Project insert transaction rolled back: ' + ERROR_MESSAGE() AS Result
    END CATCH

    BEGIN TRY
        BEGIN TRAN
            IF (@EmployeeID = -1 OR @ProjectID = -1)
            BEGIN
                RAISERROR ('EmployeeProject insert cannot be executed - previous insert failed', 14, 1)
                RETURN
            END

            INSERT INTO dbo.EmployeeProject (EmployeeID, ProjectID)
            VALUES (@EmployeeID, @ProjectID)

            INSERT INTO LogTable (TypeOperation, TableOperation)
            VALUES ('INSERT', 'EmployeeProject')

        COMMIT TRAN
        SELECT 'EmployeeProject insert transaction committed'
    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0
            ROLLBACK TRAN

        SELECT 'EmployeeProject insert transaction rolled back: ' + ERROR_MESSAGE() AS Result
    END CATCH
END
GO

SELECT * FROM dbo.Employee
SELECT * FROM dbo.Project
SELECT * FROM dbo.EmployeeProject

DELETE FROM dbo.EmployeeProject
WHERE CityPlanning.dbo.EmployeeProject.EmployeeID = 7

DELETE FROM dbo.Project
WHERE CityPlanning.dbo.Project.ProjectID = 7

DELETE FROM dbo.Employee
WHERE CityPlanning.dbo.Employee.EmployeeID = 7

DELETE FROM dbo.Employee
WHERE CityPlanning.dbo.Employee.EmployeeID = 8

EXEC EmployeeProjectInsertNonAtomic'Marcel', 1, 1, 'Cultura', '01-05-2025', '01-06-2025', 1, 1
EXEC EmployeeProjectInsertNonAtomic'Mirel', 1, 1, Ecologizare, '01-01-2019', '01-01-2020', 1, 1
