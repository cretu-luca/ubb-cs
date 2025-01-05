CREATE VIEW CityPopulation AS
SELECT CityID, CityName, Population 
FROM City 
WHERE Population > 80000;

CREATE VIEW CityDepartments AS
SELECT c.CityName, d.DepartmentName
FROM City c
JOIN Department d ON c.CityID = d.CityID;

CREATE VIEW CityDepartmentStats AS
SELECT c.CityName, COUNT(d.DepartmentID) as DepartmentCount, SUM(b.TotalValue) as TotalBudget
FROM City c
JOIN Department d ON c.CityID = d.CityID
JOIN Budget b ON c.BudgetID = b.BudgetID
GROUP BY c.CityName;

DROP VIEW CityPopulation
DROP VIEW CityDepartments
DROP VIEW CityDepartmentStats

SELECT * FROM CityPopulation
SELECT * FROM CityDepartments
SELECT * FROM CityDepartmentStats

CREATE PROCEDURE InsertTestBudget
    @count INT
AS
BEGIN
    DELETE FROM EmployeeProject
    DELETE FROM Employee
    DELETE FROM Department
    DELETE FROM City
    DELETE FROM Budget

    DECLARE @i INT = 1
    WHILE @i <= @count
    BEGIN
        INSERT INTO Budget (BudgetID, TotalValue, SpentSoFar)
        VALUES (@i, 1000, 500)
        SET @i = @i + 1
    END
END
GO

CREATE PROCEDURE InsertTestCity
    @count INT
AS
BEGIN
    DELETE FROM EmployeeProject
    DELETE FROM Employee
    DELETE FROM Department
    DELETE FROM City

    DECLARE @i INT = 1
    WHILE @i <= @count
    BEGIN
        INSERT INTO City (CityID, CityName, BudgetID, Population, Surface)
        VALUES (@i, 'TestCity' + CAST(@i AS VARCHAR), 1, 100000, 500000)
        SET @i = @i + 1
    END
END
GO

CREATE PROCEDURE InsertTestDepartment
    @count INT
AS
BEGIN
    DELETE FROM EmployeeProject
    DELETE FROM Employee
    DELETE FROM Department

    DECLARE @i INT = 1
    WHILE @i <= @count
    BEGIN
        INSERT INTO Department (DepartmentID, DepartmentName, EmployeesNumber, CityID)
        VALUES (@i, 'TestDept' + CAST(@i AS VARCHAR), 50, 1)
        SET @i = @i + 1
    END
END
GO

DROP PROCEDURE InsertTestBudget
DROP PROCEDURE InsertTestCity
DROP PROCEDURE InsertTestDepartment

EXEC InsertTestBudget 5
SELECT * FROM Budget

EXEC InsertTestCity 10
SELECT * FROM City

EXEC InsertTestDepartment 7
SELECT * FROM Department
